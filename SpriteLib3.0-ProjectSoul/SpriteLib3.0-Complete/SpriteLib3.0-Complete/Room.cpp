#include "Room.h"

Room::Room(string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-10.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void Room::InitScene(float windowWidth, float windowHeight)
{
	//Get registry
	m_sceneReg = new entt::registry;
	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	CreateCamera(windowWidth, windowHeight);
	

	if (m_name == "Start")
	{
		string platformPNG = "platform.png";
		CreateBackground("Start.png", vec2(480 / 4.5, 270 / 4.5));
		auto bgEntity = ECS::GetComponent<Sprite>(m_background);

		CreateRoomBoundary();
		
		//Ground
		CreateEdge(b2Vec2(-bgEntity.GetWidth() / 2, -28), b2Vec2(bgEntity.GetWidth() / 2, -28), GROUND);

		//Doorway
		//CreateDoorWay()
		//CreateEdge(b2Vec2(40, -12.63), b2Vec2(40, -28.96), DOORWAY);
		//CreatePlatform(platformPNG, vec2(40, 7), vec2(0, 0));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
		
	}

	if (m_name == "Tutorial")
	{

		string platformPNG = "platform.png";

		CreateBackground("tutorial.png", vec2(480 / 3, 270 / 3));
		auto bgEntity = ECS::GetComponent<Sprite>(m_background);

		CreateRoomBoundary();

		CreateEdge(b2Vec2(-bgEntity.GetWidth() / 2, -32), b2Vec2(bgEntity.GetWidth() / 2, -32), GROUND);

		//Doorway
		//CreateEdge(b2Vec2(-74, 32.07), b2Vec2(-74, -16), DOORWAY);

		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(60);

		//CreatePlatform(platformPNG, vec2(40, 7), vec2(-50, -30));
		//CreatePlatform(platformPNG, vec2(40, 7), vec2(0, 0));
	}

	CreateMainPlayer();

	//Set camera scroll focus to  main player
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}


void Room::CreateCamera(float windowWidth, float windowHeight)
{
	//Sets up the aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Creates Camera Entity
	auto entity = ECS::CreateEntity();

	//EntityIdentifier::MainCamera(entity);

	//Creates new orthographic camera
	ECS::AttachComponent<Camera>(entity);
	ECS::AttachComponent<HorizontalScroll>(entity);
	ECS::AttachComponent<VerticalScroll>(entity);

	vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
	ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
	ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

	//attaches the camera to the Horizontal scroll
	ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));

	ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));


	//Sets up the Identifier
	unsigned int bitHolder2 = EntityIdentifier::VertScrollCameraBit() | EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
	ECS::SetUpIdentifier(entity, bitHolder2, "Horizontal and vertical Scrolling Main Camera");
	ECS::SetIsMainCamera(entity, true);
}

void Room::CreateBackground(string fileName, vec2 size)
{
	auto entity = ECS::CreateEntity();
	m_background = entity;

	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetBackground(m_background);
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetBackground(m_background);

	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);

	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, size.x, size.y);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 1.f));

	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "bgImage");
}

void Room::CreateRoomBoundary()
{
	auto entity = ECS::CreateEntity();
	auto bgEntity = ECS::GetComponent<Sprite>(m_background);
	float thickness = 5;

	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.f, 0.f);

	//Ground
	{	
		bodyDef.userData = ((void*)GROUND);
		body = m_physicsWorld->CreateBody(&bodyDef);

		phsBody = PhysicsBody(body, float(bgEntity.GetWidth()), thickness,
			vec2(0.f, -bgEntity.GetHeight() / 2 - (thickness / 2)), false);
	}

	//Ceiling
	{
		bodyDef.userData = ((void*)PLATFORM);
		body = m_physicsWorld->CreateBody(&bodyDef);

		phsBody = PhysicsBody(body, float(bgEntity.GetWidth()), thickness,
			vec2(0.f, bgEntity.GetHeight() / 2 + (thickness / 2)), false);
	}

	//Left Wall
	{
		bodyDef.userData = ((void*)WALL);
		body = m_physicsWorld->CreateBody(&bodyDef);

		phsBody = PhysicsBody(body, thickness, bgEntity.GetHeight(), 
			vec2(-bgEntity.GetWidth() / 2 - (thickness / 2), 0.f), false);
	}

	//Right Wall 
	{
		bodyDef.userData = ((void*)DOORWAY);
		body = m_physicsWorld->CreateBody(&bodyDef);

		phsBody = PhysicsBody(body, thickness, bgEntity.GetHeight(),
			vec2(bgEntity.GetWidth() / 2 + (thickness / 2), 0.f), false);
	}

	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "RoomBoundary");
}

void Room::CreateMainPlayer()
{
	//Main Player
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<HealthBar>(entity);

		ECS::GetComponent<HealthBar>(entity).SetMaxHealth(3.f);

		string filename = "entire_sheet.png";
		ECS::AttachComponent<AnimationController>(entity);

		auto movement = File::LoadJSON("entire_sheet.json");

		auto& animation = ECS::GetComponent<AnimationController>(entity);

		animation.InitUVs("entire_sheet.png");

		animation.AddAnimation(movement["Idle_Right"]);
		animation.AddAnimation(movement["Idle_Left"]);
		animation.AddAnimation(movement["Walk_Right"]);
		animation.AddAnimation(movement["Walk_Left"]);
		animation.AddAnimation(movement["Run_Right"]);
		animation.AddAnimation(movement["Run_Left"]);
		animation.AddAnimation(movement["Dash_Right"]);
		animation.AddAnimation(movement["Dash_Left"]);
		animation.AddAnimation(movement["Jump_Begin_Right"]);
		animation.AddAnimation(movement["Jump_Begin_Left"]);
		animation.AddAnimation(movement["Jump_End_Right"]);
		animation.AddAnimation(movement["Jump_End_Left"]);
		animation.AddAnimation(movement["Falling_Right"]);
		animation.AddAnimation(movement["Falling_Left"]);
	    animation.AddAnimation(movement["Flinch_Right"]);
		animation.AddAnimation(movement["Flinch_Left"]);
		animation.AddAnimation(movement["Death_Right"]);
		animation.AddAnimation(movement["Death_Left"]);


		animation.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 10, 20, true, &animation);

		//Player position
		vec3 position(1.f, 1.f, 50.f);

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
		phsBody = PhysicsBody(body, float(sprite.GetWidth()), float(sprite.GetHeight()*0.9),
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
		shape.SetAsBox(float(sprite.GetWidth()) * (1.f / 10.f), float(sprite.GetHeight()) * (2.3f / 5.f), b2Vec2(float(sprite.GetWidth()) / 2.5f, 0), 0);
		fixtureDef.shape = &shape;
		fixtureDef.isSensor = true;
		b2Fixture* rightSensorFixture = body->CreateFixture(&fixtureDef);
		rightSensorFixture->SetUserData((void*)SIDESENSOR);

		//Create Left side sensor
		shape.SetAsBox(float(sprite.GetWidth()) * (1.f / 10.f), float(sprite.GetHeight()) * (2.3f / 5.f), b2Vec2(-float(sprite.GetWidth()) / 2.5f, 0), 0);
		fixtureDef.shape = &shape;
		fixtureDef.isSensor = true;
		b2Fixture* leftSensorFixture = body->CreateFixture(&fixtureDef);
		leftSensorFixture->SetUserData((void*)SIDESENSOR);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit()|EntityIdentifier::healthBarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Player");
		ECS::SetIsMainPlayer(entity, true);

		
	}

}

void Room::CreatePlatform(string fileName, vec2 size, vec2 position)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, size.x, size.y);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 50.f));

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

	//Create physics body
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(float32(position.x), float32(position.y));

	bodyDef.userData = ((void*)PLATFORM);
	body = m_physicsWorld->CreateBody(&bodyDef);

	phsBody = PhysicsBody(body, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f), true);

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Platform");
}

void Room::CreateMagnet(string fileName, vec2 size, vec2 position)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, size.x, size.y);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 50.f));

	auto& sprite = ECS::GetComponent<Sprite>(entity);
	auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(float32(position.x), float32(position.y));

	bodyDef.userData = ((void*)MAGNET);
	body = m_physicsWorld->CreateBody(&bodyDef);

	phsBody = PhysicsBody(body, float(sprite.GetWidth()), float(sprite.GetHeight()),
		vec2(0.f, 0.f), true);

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Magnet");
}

void Room::CreateEdge(b2Vec2 point1, b2Vec2 point2, fixtureName fixtureName, bool sensor)
{
	b2BodyDef bodyDef;
	b2Body* body = m_physicsWorld->CreateBody(&bodyDef);

	b2EdgeShape shape;
	shape.Set(b2Vec2(point1), b2Vec2(point2));
	
	b2Fixture* fixture;
	fixture = body->CreateFixture(&shape, 0.0f);
	fixture->SetSensor(sensor);
	fixture->SetUserData((void*)fixtureName);
}

void Room::CreateDoorWay(b2Vec2 position)
{
	auto entity = ECS::CreateEntity();
	float thickness = 5;

	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.f, 0.f);
	bodyDef.userData = ((void*)WALL);
	body = m_physicsWorld->CreateBody(&bodyDef);

	phsBody = PhysicsBody(body, 5,10,
		vec2(0.f , 0.f), false);
}


