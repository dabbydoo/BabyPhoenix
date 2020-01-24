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
		ECS::GetComponent<HorizontalScroll>(entity).SetOffset(1000.f);
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetOffset(1000.f);


		//Sets up the Identifier
		unsigned int bitHolder2 = EntityIdentifier::VerticalScrollCamBit() |EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder2, "Horizontal Scrolling Main Camera");
		ECS::SetIsMainCamera(entity, true);
		
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "background.png";
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

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (-tempSpr.GetHeight() / 11.f) * 6.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Ground");

		//Temporary left side wall
		auto& tempPhsBody2 = ECS::GetComponent<PhysicsBody>(entity);
		b2Body* wallBody;
		b2BodyDef wallBodyDef;
		wallBodyDef.type = b2_staticBody;
		wallBodyDef.position.Set(0.f, 0.f);
		wallBody = m_physicsWorld->CreateBody(&wallBodyDef);
		tempPhsBody2 = PhysicsBody(wallBody, 5.f, 200.f, vec2(-191.f, 0.f), false);
		

		//Temporary right side wall
		auto& tempPhsBody3 = ECS::GetComponent<PhysicsBody>(entity);
		b2Body* wallBody2;
		b2BodyDef wallBodyDef2;
		wallBodyDef2.type = b2_staticBody;
		wallBodyDef2.position.Set(0.f, 0.f);
		wallBody2 = m_physicsWorld->CreateBody(&wallBodyDef2);
		tempPhsBody3 = PhysicsBody(wallBody2, 5.f, 200.f, vec2(191.f, 0.f), false);
	}

	{

		//Creates entity
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainPlayer(entity);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "idle.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 40, 40);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);



		b2Body* tempBody;
		b2BodyDef tempDef;

		b2PolygonShape tempPoly;	
		tempPoly.SetAsBox(20, 20);

		b2Fixture* tempFixture;
		b2FixtureDef tempFixtureDef;

		tempFixtureDef.shape = &tempPoly;
		tempFixtureDef.density = 1.f;
		tempFixtureDef.friction = 0.f;
		
		

				
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-10.f), float32(-20.f));
		

		tempDef.fixedRotation = true;

	
		
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->CreateFixture(&tempFixtureDef);

		//Foot Sensor
		tempPoly.SetAsBox(0.3, 0.3, b2Vec2(0, -20), 0);
		tempFixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = tempBody->CreateFixture(&tempFixtureDef);
		footSensorFixture->SetUserData((void*)3);
		
		

		/*b2PolygonShape boxShape;
		boxShape.SetAsBox(10, 10);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		tempBody->CreateFixture(&boxFixtureDef);*/

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		tempPhsBody.SetFriction(0.05f);
		tempPhsBody.SetMaxVelo(.5f);
		tempPhsBody.SetGravity(true);

		
		
		
		

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box");
		ECS::SetIsMainPlayer(entity, true);

		m_player = entity;
		
	}
	{

		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "box.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 20, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(10.f), float32(100.f));

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

	{

		//Creates entity
		auto entity = ECS::CreateEntity();


		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "box.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 20, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(90.f, 10.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(5.f), float32(110.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box2");

		m_player = entity;
	}
	{

		//Creates entity
		auto entity = ECS::CreateEntity();


		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "box.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 20, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);



		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(0.f), float32(100.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), true);

		//tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box3");


		m_player = entity;
	}

	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

