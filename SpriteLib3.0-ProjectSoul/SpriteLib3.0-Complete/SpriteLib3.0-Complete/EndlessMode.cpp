#include "EndlessMode.h"

void EndlessMode::ShootBullet()
{
	string fileName = "Bullet.png";

	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 5);

	auto* m_playerBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();


	
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(m_playerBody->GetPosition().x + 5, m_playerBody->GetPosition().y, 100.f));
	

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

	//Create physics body
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

		bodyDef.position.Set(m_playerBody->GetPosition().x + 5, m_playerBody->GetPosition().y);
	

	//Body user data is same as entityID
	bodyDef.userData = ((void*)entity);


	body = GetPhysicsWorld().CreateBody(&bodyDef);
	body->SetGravityScale(0);

	body->IsBullet();

	phsBody = PhysicsBody(body, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f), true, BULLET, true);

	body->GetFixtureList()->SetRestitution(100);
	body->SetLinearVelocity(b2Vec2(80, 0));

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Bullet");
}

vec2 ConvertToGl(vec2 clickCoord)
{
	Camera tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());

	//Need to convert cliccked point to screen space first!
	vec2 clickedPoint = clickCoord;
	vec2 position = vec2(tempCam.GetPositionX(), tempCam.GetPositionY());

	//Window in windowX x windowY space
	//Need to get into (right-left) x (top-bottome) space

	//First task, make it so bottom is 0 and top is windowHeight
	clickedPoint = vec2(clickedPoint.x, float(BackEnd::GetWindowHeight()) - clickedPoint.y);

	float glX = (tempCam.GetAspect() * (tempCam.GetOrthoSize().y) - tempCam.GetAspect() * (tempCam.GetOrthoSize().x));
	float glY = (tempCam.GetOrthoSize().w - tempCam.GetOrthoSize().z);

	//Spaces
	vec2 glSpace = vec2(glX, glY);
	vec2 windowSpace = vec2(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	vec2 percentPoint = vec2(clickedPoint.x / windowSpace.x, clickedPoint.y / windowSpace.y);

	//In glspace
	clickedPoint = vec2(glSpace.x * percentPoint.x, glSpace.y * percentPoint.y);

	clickedPoint = clickedPoint + vec2(tempCam.GetAspect() * tempCam.GetOrthoSize().x, tempCam.GetOrthoSize().z);

	clickedPoint = clickedPoint + vec2(tempCam.GetPositionX(), tempCam.GetPositionY());

	return clickedPoint;
}


void EndlessMode::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	m_physicsWorld->SetGravity(b2Vec2(0,-10));

	//Attach the register
	ECS::AttachRegister(m_sceneReg);
	
	auto Entity = ECS::CreateEntity();

	ECS::AttachComponent<PhysicsBody>(Entity);


	{
		float aspectRatio = windowWidth / windowHeight;

		//Creates Camera Entity
		auto entity = ECS::CreateEntity();

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);

		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);



		//Sets up the Identifier
		unsigned int bitHolder2 = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder2, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	}


	{
		auto entity = ECS::CreateEntity();

		Floor.push_back(new InfoHolder(entity,Object::FLOOR));
		
		infoHolder.push_back(Floor[Floor.size()-1]);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		string filename = "Floor Tiles.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 356.0, 35.0);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -82.5f, 1.f));

		vec2 pos = vec2(0, -82.5);

		auto& sprite = ECS::GetComponent<Sprite>(entity);

		b2Body* body;
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(pos.x, pos.y);
		b2FixtureDef myFixtureDef;

		bodyDef.userData = ((void*)GROUND);
		body = m_physicsWorld->CreateBody(&bodyDef);

		auto& phsBody = ECS::GetComponent<PhysicsBody>(Entity);

		phsBody = PhysicsBody(body, float(sprite.GetWidth()),float(sprite.GetHeight()),
			vec2(0.f, 0.f), false);

		//Left Wall
		{
			bodyDef.userData = ((void*)WALL);
			body = m_physicsWorld->CreateBody(&bodyDef);

			phsBody = PhysicsBody(body, 1, 165.0,
				vec2(-195 , 0.f), false);
		}

		//Right Wall 
		{
			bodyDef.userData = ((void*)WALL);
			body = m_physicsWorld->CreateBody(&bodyDef);

			phsBody = PhysicsBody(body, 1,165.0,
				vec2(195, 0.f), false);
		}


		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Floor");
	}

	{
		auto entity = ECS::CreateEntity();

		Floor.push_back(new InfoHolder(entity, Object::FLOOR));

		infoHolder.push_back(Floor[Floor.size() - 1]);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		string filename = "Floor Tiles.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 356.0, 35.0);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(356.f, -82.5f, 1.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Floor");
	}

	{
		auto entity = ECS::CreateEntity();

		Background.push_back(new InfoHolder(entity, Object::BACKGROUND));

		infoHolder.push_back(Background[Background.size() - 1]);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		string filename = "Background Tiles.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 178.0, 165.0);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-88.8f, 17.4f, 1.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Background");
	}

	{
		auto entity = ECS::CreateEntity();

		Background.push_back(new InfoHolder(entity, Object::BACKGROUND));

		infoHolder.push_back(Background[Background.size() - 1]);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		string filename = "Background Tiles.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 178.0, 165.0);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(88.8f, 17.4f, 1.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Background");
	}

	{
		auto entity = ECS::CreateEntity();

		Background.push_back(new InfoHolder(entity, Object::BACKGROUND));

		infoHolder.push_back(Background[Background.size() - 1]);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		string filename = "Background Tiles.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 178.0, 165.0);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(266.8f, 17.4f, 1.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Background");
	}



	//Main Player
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "entire_sheet.png";
		ECS::AttachComponent<AnimationController>(entity);

		auto movement = File::LoadJSON("entire_sheet.json");

		auto& animation = ECS::GetComponent<AnimationController>(entity);

		animation.InitUVs(filename);
		
		animation.AddAnimation(movement["Walk_Right"]); //0
	
		animation.AddAnimation(movement["Run_Right"]);//1
		
		animation.AddAnimation(movement["Jump_Begin_Right"]);//2 
		
		animation.AddAnimation(movement["Jump_Middle_Right"]); //3
		
		animation.AddAnimation(movement["Jump_End_Right"]);//4
		
		animation.AddAnimation(movement["Falling_Right"]);//5
		
		animation.AddAnimation(movement["Flinch_Right"]);//6
		
		animation.AddAnimation(movement["Death_Right"]);//7
		
		animation.AddAnimation(movement["Gun_Shoot_Right"]);//8
		

		animation.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 30, 50, true, &animation);

		//Player position
		vec3 position(0,-47.5,100);

		ECS::GetComponent<Transform>(entity).SetPosition(position);

		auto& sprite = ECS::GetComponent<Sprite>(entity);
		auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

		//Create box2d body
		b2Body* body;
		b2BodyDef bodyDef;

		//Set body type
		bodyDef.type = b2_dynamicBody;

		//Set position of body
		bodyDef.position.Set(float32(position.x), float32(position.y));

		//Set body rotation to false
		bodyDef.fixedRotation = true;

		//Set user data and create body in scene
		bodyDef.userData = ((void*)PLAYER);
		body = m_physicsWorld->CreateBody(&bodyDef);

		//Set gravity scale
		body->SetGravityScale(7);

		//Construct box collider 
		phsBody = PhysicsBody(body, float(sprite.GetWidth()), float(sprite.GetHeight() * 0.9),
			vec2(0.f, 0.f), false, 2.5f);

		b2PolygonShape shape;
		b2FixtureDef fixtureDef;

		//Create foot sensor
		shape.SetAsBox(float(sprite.GetWidth()) * (2.3f / 5.f), float(sprite.GetHeight()) * (1.f / 10.f), b2Vec2(0, -float(sprite.GetHeight()) / 2.5f), 0);
		fixtureDef.shape = &shape;
		fixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = body->CreateFixture(&fixtureDef);
		footSensorFixture->SetUserData((void*)FOOTSENSOR);

		//Create head sensor
		shape.SetAsBox(float(sprite.GetWidth()) * (2.3f / 5.f), float(sprite.GetHeight()) * (1.f / 10.f), b2Vec2(0, float(sprite.GetHeight()) / 2.5f), 0);
		fixtureDef.shape = &shape;
		fixtureDef.isSensor = true;
		b2Fixture* headSensorFixture = body->CreateFixture(&fixtureDef);
		headSensorFixture->SetUserData((void*)HEADSENSOR);

		//Create Right side sensor
		shape.SetAsBox(float(sprite.GetWidth()) * (1.f / 10.f), float(sprite.GetHeight()) * (2.1f / 5.f), b2Vec2(float(sprite.GetWidth()) / 2.5f, 0), 0);
		fixtureDef.shape = &shape;
		fixtureDef.isSensor = true;
		b2Fixture* rightSensorFixture = body->CreateFixture(&fixtureDef);
		rightSensorFixture->SetUserData((void*)SIDESENSOR);

		//Create Left side sensor
		shape.SetAsBox(float(sprite.GetWidth()) * (1.f / 10.f), float(sprite.GetHeight()) * (2.1f / 5.f), b2Vec2(-float(sprite.GetWidth()) / 2.5f, 0), 0);
		fixtureDef.shape = &shape;
		fixtureDef.isSensor = true;
		b2Fixture* leftSensorFixture = body->CreateFixture(&fixtureDef);
		leftSensorFixture->SetUserData((void*)SIDESENSOR);


		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit() | EntityIdentifier::healthBarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Player");
		ECS::SetIsMainPlayer(entity, true);
	}

	DrawHUD();

	{
		mouse = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(mouse);
		ECS::AttachComponent<Transform>(mouse);

		string filename = "Mouse.png";
		ECS::GetComponent<Sprite>(mouse).LoadSprite(filename, 3.0, 5.0);
		ECS::GetComponent<Transform>(mouse).SetPosition(vec3(0.f, 82.5f, 1.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(mouse, bitHolder, "Mouse");
	}

}

void EndlessMode::GamepadStroke(XInputController* con)
{
	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
	
	auto* m_playerBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();

	
		static bool has_jumped = false;

		if (con->IsButtonPressed(Buttons::A))
			//to do the animation first
			if (m_isPlayerOnGround)
				has_jumped = true;



		if (has_jumped) {
			animation.SetActiveAnim(2);
			animation.GetAnimation(4).Reset();
		}
		if (animation.GetAnimation(2).GetAnimationDone() && has_jumped) {
			has_jumped = false;
			float impulse = m_playerBody->GetMass() * 75; //Adjust to change height of jump
			m_playerBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_playerBody->GetWorldCenter(), true);
			m_isPlayerOnGround = false;
			animation.SetActiveAnim(3);
			animation.GetAnimation(2).Reset();
		}


		if (animation.GetAnimation(3).GetAnimationDone() && m_isPlayerOnGround) {
			animation.SetActiveAnim(4);
			animation.GetAnimation(3).Reset();
		}
	
}

void EndlessMode::GamepadUp(XInputController* con)
{
}

void EndlessMode::GamepadDown(XInputController* con)
{
	if (con->IsButtonPressed(Buttons::X)) {
		ShootBullet();
	}
}

void EndlessMode::GamepadStick(XInputController* con)
{
	Stick sticks[2];

	con->GetSticks(sticks);

	static bool has_ran = false;

	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

	if (con->IsButtonPressed(Buttons::START))
		exit(0);

	if (m_isPlayerOnGround && (animation.GetAnimation(4).GetAnimationDone()||has_ran))
		animation.SetActiveAnim(0);

	auto* m_playerBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();

	b2Vec2 velocity = m_playerBody->GetLinearVelocity();

	//left
	if (sticks[0].x <= -0.7f && sticks[0].x > -1.f) {
		velocity.x = -50;
		m_playerBody->SetLinearVelocity(velocity);
	}

	//right
	if (sticks[0].x >= 0.7f && sticks[0].x <= 1.f)
	{
		if (m_isPlayerOnGround)
			animation.SetActiveAnim(1);

		has_ran = true;

		velocity.x = 50;
		m_playerBody->SetLinearVelocity(velocity);
	}

	if (sticks[0].x < 0.7f && sticks[0].x > -.7f){
		m_playerBody->SetLinearVelocity(b2Vec2(0, velocity.y));
		has_ran = false;
}

}

void EndlessMode::GamepadTrigger(XInputController* con)
{
}

void EndlessMode::KeyboardHold()
{
}

void EndlessMode::KeyboardDown()
{
}

void EndlessMode::KeyboardUp()
{
}

void EndlessMode::DrawHUD()
{
		//healthbar
		{
			//Creates entity
			auto healthEntity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(healthEntity);
			ECS::AttachComponent<Transform>(healthEntity);

			string filename = "HealthBar.png";
			ECS::AttachComponent<AnimationController>(healthEntity);

			auto health = File::LoadJSON("HealthBar.json");

			auto& animation = ECS::GetComponent<AnimationController>(healthEntity);

			animation.InitUVs("HealthBar.png");

			animation.AddAnimation(health["Health_0"]);
			animation.AddAnimation(health["Health_1"]);
			animation.AddAnimation(health["Health_2"]);
			animation.AddAnimation(health["Health_3"]);
			animation.AddAnimation(health["Health_4"]);

			animation.SetActiveAnim(m_player_health);

			ECS::GetComponent<Sprite>(healthEntity).LoadSprite(filename, 90, 25, true, &animation);

			//HealthBar position

			auto helthPos = vec3(-92,78.2,99);

			ECS::GetComponent<Transform>(healthEntity).SetPosition(helthPos);

			//Sets up the Identifier
			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
			ECS::SetUpIdentifier(healthEntity, bitHolder, "Health Bar");
		}

		//the icon
		{
			//Creates entity
			iconEntity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(iconEntity);
			ECS::AttachComponent<Transform>(iconEntity);

			string filename = "Icon.png";
			ECS::AttachComponent<AnimationController>(iconEntity);

			auto icon = File::LoadJSON("Icon.json");

			auto& animation = ECS::GetComponent<AnimationController>(iconEntity);

			animation.InitUVs("Icon.png");

			animation.AddAnimation(icon["Icon"]);

			animation.SetActiveAnim(0);


			ECS::GetComponent<Sprite>(iconEntity).LoadSprite(filename, 35, 40, true, &animation);

			//Icon position

			auto iconPos = vec3(-156.8,78.1,99);

			ECS::GetComponent<Transform>(iconEntity).SetPosition(iconPos);

			//Sets up the Identifier
			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
			ECS::SetUpIdentifier(iconEntity, bitHolder, "Icon");

		}
	
}

void EndlessMode::Update()
{
	backgroudUpdate();
	floorUpdate();
	bulletUpdate();
	enemyUpdate();

}

void EndlessMode::floorUpdate()
{
	for (unsigned i = 0; i < Floor.size(); i++) {
		vec3 tempPos = Floor[i]->GetPos();

		tempPos.x = tempPos.x - 1;

		if (tempPos.x <= -356) {
			tempPos.x = 356;
		}

		Floor[i]->SetPos(tempPos);

		
	}
}

void EndlessMode::backgroudUpdate()
{
	for (unsigned i = 0; i < Background.size(); i++) {
		vec3 tempPos = Background[i]->GetPos();

		tempPos.x = tempPos.x - 1;

		if (tempPos.x <= -266.8f) {
			tempPos.x = 266.8f;
		}

		Background[i]->SetPos(tempPos);
	}
}

void EndlessMode::enemyUpdate()
{
}

void EndlessMode::objectUpdate()
{
}

void EndlessMode::bulletUpdate()
{
	if (m_isBulletHit)
	{
		ECS::GetComponent<PhysicsBody>(m_bulletHitUserData).DeleteBody();
		ECS::DestroyEntity(m_bulletHitUserData);
		m_isBulletHit = false;
	}
}

void EndlessMode::MouseMotion(SDL_MouseMotionEvent evnt)
{
	auto temp = ConvertToGl(vec2(evnt.x,evnt.y));

	ECS::GetComponent<Transform>(mouse).SetPosition(vec3(temp.x,temp.y,100));
}

void EndlessMode::MouseClick(SDL_MouseButtonEvent evnt)
{
}

void EndlessMode::MouseWheel(SDL_MouseWheelEvent evnt)
{
}
