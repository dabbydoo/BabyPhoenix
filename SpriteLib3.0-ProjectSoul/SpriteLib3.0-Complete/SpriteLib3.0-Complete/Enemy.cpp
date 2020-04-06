#include "Enemy.h"

void Enemy::CreateBody(vec2 size, b2Vec2 position, b2World* physicsWorld, float speed)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	m_enemyID = entity;

	//Add components
	ECS::AttachComponent<Sprite>(m_enemyID);
	ECS::AttachComponent<Transform>(m_enemyID);
	ECS::AttachComponent<PhysicsBody>(m_enemyID);

	string fileName = "Ranged.png";
	ECS::AttachComponent<AnimationController>(m_enemyID);

	auto movement = File::LoadJSON("Ranged.json");

	auto& animation = ECS::GetComponent<AnimationController>(m_enemyID);

	animation.InitUVs(fileName);

	animation.AddAnimation(movement["Left"]);
	animation.AddAnimation(movement["Right"]);

	animation.SetActiveAnim(LEFT);

	ECS::GetComponent<Sprite>(m_enemyID).LoadSprite(fileName, size.x, size.y, true, &animation);

	ECS::GetComponent<Transform>(m_enemyID).SetPosition(vec3(position.x, position.y, 50.f));


	auto& tempSpr = ECS::GetComponent<Sprite>(m_enemyID);
	auto& phsBody = ECS::GetComponent<PhysicsBody>(m_enemyID);

	//Create physics body
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	//Set b2body pos
	bodyDef.position.Set(position.x, position.y);

	//Set body rotation to false
	bodyDef.fixedRotation = true;

	//Body user data is same as entityID
	bodyDef.userData = ((void*)entity);

	m_physicsWorld = physicsWorld;
	body = m_physicsWorld->CreateBody(&bodyDef);
	body->SetGravityScale(0);


	phsBody = PhysicsBody(body, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f), true, ENEMY, true);
	
	m_initPos = position;
	m_body = body;
	m_speed = speed;

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Ranged_Enemy");
}

void Enemy::Update()
{
	if (checkPlayerInSight())
		EngagePlayer();
	else
		PatrolUpdate();
}

void Enemy::Move(Direction dir)
{
	auto& animation = ECS::GetComponent<AnimationController>(m_enemyID);

	m_faceDir = dir;
	animation.SetActiveAnim(m_faceDir);

	if(m_faceDir == LEFT)
		m_body->SetLinearVelocity(b2Vec2(-m_speed, 0));
	if (m_faceDir == RIGHT)
		m_body->SetLinearVelocity(b2Vec2(m_speed, 0));
}

void Enemy::EngagePlayer()
{
	auto playerPos = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->GetPosition();

	//Player on left side
	if (m_playerInSight == -1)
	{
		SetViewDirection(LEFT);

		if (m_bulletCounter == m_bulletFireRate)
		{
			ShootBullet(LEFT);
			m_bulletCounter = 0;
		}

		if (m_patrolDistance != 0)
		{
			//Move towards player until target distance reached
			if (abs(playerPos.x - GetPosition().x) > m_targetDistance && abs(GetPosition().x - m_initPos.x) < abs(m_patrolDistance))
				Move(LEFT);
			else
				StopMoving();
		}
	}

	//Player on right side
	if (m_playerInSight == 1)
	{
		SetViewDirection(RIGHT);

		if (m_bulletCounter == m_bulletFireRate)
		{
			ShootBullet(RIGHT);
			m_bulletCounter = 0;
		}

		if (m_patrolDistance != 0)
		{
			//Move towards player until target distance reached
			if (abs(playerPos.x - GetPosition().x) > m_targetDistance && abs(GetPosition().x - m_initPos.x) < abs(m_patrolDistance))
				Move(RIGHT);
			else
				StopMoving();
		}
	}

	m_bulletCounter++;
}

void Enemy::ShootBullet(Direction dir)
{
	string fileName = "Enemy Bullet.png";

	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Set camera scroll focus to  main player
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));

	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 1, 1);

	if (dir == RIGHT)
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(GetPosition().x + 5, GetPosition().y + 2, 50.f));
	else
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(GetPosition().x - 5, GetPosition().y + 2, 50.f));

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

	//Create physics body
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	if (dir == RIGHT)
		bodyDef.position.Set(GetPosition().x + 5, GetPosition().y + 2);
	else
		bodyDef.position.Set(GetPosition().x - 5, GetPosition().y + 2);

	//Body user data is same as entityID
	bodyDef.userData = ((void*)entity);


	body = m_physicsWorld->CreateBody(&bodyDef);
	body->SetGravityScale(0);

	body->IsBullet();

	phsBody = PhysicsBody(body, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f), true, ENEMYBULLET, true);

	if (dir == RIGHT)
		body->SetLinearVelocity(b2Vec2(m_bulletSpeed, 0));
	else
		body->SetLinearVelocity(b2Vec2(-m_bulletSpeed, 0));
	
	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Enemy Bullet");
}

void Enemy::Delete()
{
	ECS::GetComponent<PhysicsBody>(m_enemyID).DeleteBody();
	ECS::DestroyEntity(m_enemyID);	
}

bool Enemy::checkPlayerInSight()
{
	b2Vec2 enemyPos(m_body->GetPosition());
	RayCastEnemyFOV callback;

	float distance = m_fireDistance;
	float angleRAD = 0;

	static int i = 0;

	//Enemy scan degrees
	for (int angleDEG = 0; angleDEG <= 180; angleDEG = angleDEG + 180)
	{
		angleRAD = angleDEG * b2_pi / 180.0f;

		b2Vec2 d(distance * cosf(angleRAD), distance * sinf(angleRAD));

		b2Vec2 point2 = enemyPos + d;

		callback.m_hit = false;
		m_physicsWorld->RayCast(&callback, enemyPos, point2);

		
		if (callback.m_hit)
		{
			if (callback.m_userData == PLAYER)
			{
				//Evaluate if player on left or right side
				if (callback.m_point.x < enemyPos.x)
					m_playerInSight = -1;
				else
					m_playerInSight = 1;
				return true;
			}
		}
	}
	m_playerInSight = 0;
	return false;
}

void Enemy::SetViewDirection(Direction dir)
{
	m_faceDir = dir;
	ECS::GetComponent<AnimationController>(m_enemyID).SetActiveAnim(m_faceDir);
}

void Enemy::Patrol(float distance)
{
	m_patrolDistance = distance;

	if (m_patrolDistance < 0)
		Move(LEFT);
	if (m_patrolDistance > 0)
		Move(RIGHT);
}

void Enemy::PatrolUpdate()
{
	if (m_patrolDistance != 0)
	{
		Move(m_faceDir);

		if (abs(GetPosition().x - m_initPos.x) > abs(m_patrolDistance))
			m_body->SetLinearVelocity(-m_body->GetLinearVelocity());

		if (abs(GetPosition().x - m_initPos.x) < 0.1)
			m_body->SetLinearVelocity(-m_body->GetLinearVelocity());

		auto& animation = ECS::GetComponent<AnimationController>(m_enemyID);
		if (m_body->GetLinearVelocity().x < 0)
		{
			animation.SetActiveAnim(LEFT);
			m_faceDir = LEFT;
		}
		else
		{
			animation.SetActiveAnim(RIGHT);
			m_faceDir = RIGHT;
		}
	}
}
