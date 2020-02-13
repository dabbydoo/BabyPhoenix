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
		unsigned int bitHolder2 = EntityIdentifier::VerticalScrollCamBit() |EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder2, "Horizontal Scrolling Main Camera");
		ECS::SetIsMainCamera(entity, true);
		
	}

	//Ground
	{
		auto entity = ECS::CreateEntity();
		m_background = entity;

		ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetBackground(m_background);
		ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetBackground(m_background);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "practiceMap.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 405, 260);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -10.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = (tempSpr.GetHeight() / 2.f);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(-10.f));

		tempDef.userData = ((void*)GROUND);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (-tempSpr.GetHeight() / 11.f) * 6.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Ground");
	}

	//Left Wall
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* wallBody;
		b2BodyDef wallBodyDef;
		wallBodyDef.type = b2_staticBody;
		wallBodyDef.position.Set(0.f, 0.f);

		wallBodyDef.userData = ((void*)WALL);
		wallBody = m_physicsWorld->CreateBody(&wallBodyDef);

		phsBody = PhysicsBody(wallBody, 5.f, 200.f, vec2(-191.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "LeftWall");

	}

	//Right Wall 
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* wallBody;
		b2BodyDef wallBodyDef;
		wallBodyDef.type = b2_staticBody;
		wallBodyDef.position.Set(0.f, 0.f);

		wallBodyDef.userData = ((void*)WALL);
		wallBody = m_physicsWorld->CreateBody(&wallBodyDef);

		phsBody = PhysicsBody(wallBody, 5.f, 200.f, vec2(191.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
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

		string filename = "box.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 20, 40);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		
		//Create box2d body
		b2Body* tempBody;
		b2BodyDef tempDef;
		
		//Set body type
		tempDef.type = b2_dynamicBody;

		//Set position of body
		tempDef.position.Set(float32(-50.f), float32(-50.f));

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
		tempShape.SetAsBox(float(tempSpr.GetWidth())* (1.f / 10.f), float(tempSpr.GetHeight())* (2.3f / 5.f), b2Vec2(-float(tempSpr.GetWidth()) / 2.5f, 0), 0);
		tempFixture.shape = &tempShape;
		tempFixture.isSensor = true;
		b2Fixture* leftSensorFixture = tempBody->CreateFixture(&tempFixture);
		leftSensorFixture->SetUserData((void*)SIDESENSOR);
		
		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
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
		tempDef.position.Set(float32(40.f), float32(-10.f));

		tempDef.userData = ((void*)PLATFORM);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
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
		tempDef.position.Set(float32(140.f), float32(-20.f));

		tempDef.userData = ((void*)PLATFORM);
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
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
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box3");
	}

	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

