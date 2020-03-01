using namespace std;
#include "AssignmentScene.h"

AssignmentScene::AssignmentScene(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-10.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void AssignmentScene::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;
	//Attach the register
	ECS::AttachRegister(m_sceneReg);
	//Sets up the aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Sets up the Main Camera Entity
	{
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
		unsigned int bitHolder2 = EntityIdentifier::VerticalScrollCamBit() | EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder2, "Horizontal Scrolling Main Camera");
		ECS::SetIsMainCamera(entity, true);

	}

	//BackgroundImage
	{
		auto entity = ECS::CreateEntity();
		m_background = entity;

		ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetBackground(m_background);
		ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetBackground(m_background);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "practiceMap.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 480, 270);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -10.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "bgImage");
	}

	//Ground
	{
		auto entity = ECS::CreateEntity();

		auto bgEntity = ECS::GetComponent<Sprite>(m_background);
		float thickness = 5;

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* groundBody;
		b2BodyDef groundBodyDef;
		groundBodyDef.type = b2_staticBody;
		groundBodyDef.position.Set(0.f, 0.f);

		groundBodyDef.userData = ((void*)GROUND);
		groundBody = m_physicsWorld->CreateBody(&groundBodyDef);

		phsBody = PhysicsBody(groundBody, float(bgEntity.GetWidth()), thickness,
			vec2(0.f, -bgEntity.GetHeight() / 2 -	 (thickness / 2)), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Ground");

	}

	//Ceiling
	{
		auto entity = ECS::CreateEntity();

		auto bgEntity = ECS::GetComponent<Sprite>(m_background);
		float thickness = 5;

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* groundBody;
		b2BodyDef groundBodyDef;
		groundBodyDef.type = b2_staticBody;
		groundBodyDef.position.Set(0.f, 0.f);

		groundBodyDef.userData = ((void*)PLATFORM);
		groundBody = m_physicsWorld->CreateBody(&groundBodyDef);

		phsBody = PhysicsBody(groundBody, float(bgEntity.GetWidth()), thickness,
			vec2(0.f, bgEntity.GetHeight() / 2 + (thickness / 2)), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Ceiling");

	}

	//Left Wall
	{
		auto entity = ECS::CreateEntity();

		auto bgEntity = ECS::GetComponent<Sprite>(m_background);
		float thickness = 5;

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* wallBody;
		b2BodyDef wallBodyDef;
		wallBodyDef.type = b2_staticBody;
		wallBodyDef.position.Set(0.f, 0.f);

		wallBodyDef.userData = ((void*)WALL);
		wallBody = m_physicsWorld->CreateBody(&wallBodyDef);

		phsBody = PhysicsBody(wallBody, thickness, bgEntity.GetHeight(), vec2(-bgEntity.GetWidth() / 2 - (thickness / 2), 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "LeftWall");

	}

	//Right Wall 
	{
		auto entity = ECS::CreateEntity();

		auto bgEntity = ECS::GetComponent<Sprite>(m_background);
		float thickness = 5;

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* wallBody;
		b2BodyDef wallBodyDef;
		wallBodyDef.type = b2_staticBody;
		wallBodyDef.position.Set(0.f, 0.f);

		wallBodyDef.userData = ((void*)WALL);
		wallBody = m_physicsWorld->CreateBody(&wallBodyDef);

		phsBody = PhysicsBody(wallBody, thickness, bgEntity.GetHeight(), vec2(bgEntity.GetWidth() / 2 + (thickness / 2), 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "RightWall");
	}

	//Main Player
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainPlayer(entity);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<HealthBar>(entity);

		string filename = "entire_sheet.png";
		ECS::AttachComponent<AnimationController>(entity);

		ECS::GetComponent<HealthBar>(entity).SetMaxHealth(3.f);

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
	//	animation.AddAnimation(movement["Jump_End_Left"]);
		animation.AddAnimation(movement["Falling_Right"]);
		animation.AddAnimation(movement["Falling_Left"]);

		animation.SetActiveAnim(8);


		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 20, 40, true, &animation);
		ECS::GetComponent<Sprite>(entity).SetUVs(vec2(1.f, 3.f), vec2(3.f, 1.f));
		
		//ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 20, 40);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));
	
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//Create box2d body
		b2Body* tempBody;
		b2BodyDef tempDef;

		//Set body type
		tempDef.type = b2_dynamicBody;

		//Set position of body
		tempDef.position.Set(float32(-220.f), float32(-70.f));

		//Set body rotation to false
		tempDef.fixedRotation = true;

		//Set user data and create body in scene
		tempDef.userData = ((void*)PLAYER);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		//Set gravity scale
		tempBody->SetGravityScale(7);

		//Construct box collider 
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false, 1.5f);

		b2PolygonShape tempShape;
		b2FixtureDef tempFixture;

		//Create foot sensor
		tempShape.SetAsBox(float(tempSpr.GetWidth()) * (2.3f / 5.f), float(tempSpr.GetHeight()) * (1.f / 10.f), b2Vec2(0, -float(tempSpr.GetHeight()) / 2.5f), 0);
		tempFixture.shape = &tempShape;
		tempFixture.isSensor = true;
		b2Fixture* footSensorFixture = tempBody->CreateFixture(&tempFixture);
		footSensorFixture->SetUserData((void*)FOOTSENSOR);

		//Create head sensor
		tempShape.SetAsBox(float(tempSpr.GetWidth()) * (2.3f / 5.f), float(tempSpr.GetHeight()) * (1.f / 10.f), b2Vec2(0, float(tempSpr.GetHeight()) / 2.5f), 0);
		tempFixture.shape = &tempShape;
		tempFixture.isSensor = true;
		b2Fixture* headSensorFixture = tempBody->CreateFixture(&tempFixture);
		headSensorFixture->SetUserData((void*)HEADSENSOR);

		//Create Right side sensor
		tempShape.SetAsBox(float(tempSpr.GetWidth()) * (1.f / 10.f), float(tempSpr.GetHeight()) * (2.3f / 5.f), b2Vec2(float(tempSpr.GetWidth()) / 2.5f, 0), 0);
		tempFixture.shape = &tempShape;
		tempFixture.isSensor = true;
		b2Fixture* rightSensorFixture = tempBody->CreateFixture(&tempFixture);
		rightSensorFixture->SetUserData((void*)SIDESENSOR);

		//Create Left side sensor
		tempShape.SetAsBox(float(tempSpr.GetWidth()) * (1.f / 10.f), float(tempSpr.GetHeight()) * (2.3f / 5.f), b2Vec2(-float(tempSpr.GetWidth()) / 2.5f, 0), 0);
		tempFixture.shape = &tempShape;
		tempFixture.isSensor = true;
		b2Fixture* leftSensorFixture = tempBody->CreateFixture(&tempFixture);
		leftSensorFixture->SetUserData((void*)SIDESENSOR);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Player");
		ECS::SetIsMainPlayer(entity, true);
	}

	//BOX1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "platform.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 40, 7);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(40.f), float32(11.f));

		tempDef.userData = ((void*)PLATFORM);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box1");
	}

	//BOX2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "platform.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 40, 7);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(100.f, -30.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(140.f), float32(-58.5f));

		tempDef.userData = ((void*)PLATFORM);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box2");
	}

	//BOX3
	{
		//Creates entity
		auto entity = ECS::CreateEntity();


		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "platform.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 40, 7);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);



		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-80.f), float32(60.f));

		tempDef.userData = ((void*)PLATFORM);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), true);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box3");
	}

	//BOX4
	{
		//Creates entity
		auto entity = ECS::CreateEntity();


		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "box.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 5, 5);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);



		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(0.f));

		tempDef.userData = ((void*)PLATFORM);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), true);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box4");
	}

	//Magnet
	{
		//Creates entity
		auto entity = ECS::CreateEntity();


		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "magnet.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 5, 5);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);



		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(120.f), float32(0.f));

		tempDef.userData = ((void*)PLATFORM);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), true);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box4");
	}
	
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

