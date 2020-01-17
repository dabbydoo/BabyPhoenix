#include "MainHeader.h"

using namespace std;
test::test(std::string name)
	:Scene(name)
{
	m_gravity = b2Vec2(float32(0.f),float32(-9.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void test::InitScene(float windowWidth, float windowHeight)
{


	m_sceneReg = new entt::registry;
	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;
	{
		auto entity = ECS::CreateEntity();

		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		
		//ECS::AttachComponent<Vertical_Scroll>(entity);
		ECS::AttachComponent<Horizontal_Scroll>(entity);


vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();

ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

ECS::GetComponent<Horizontal_Scroll>(entity).setcam(&ECS::GetComponent<Camera>(entity));
ECS::GetComponent<Horizontal_Scroll>(entity).setoffset(15.f);
/*

ECS::GetComponent<Vertical_Scroll>(entity).setcam(&ECS::GetComponent<Camera>(entity));
ECS::GetComponent<Vertical_Scroll>(entity).setoffset(15.f);
	
	*/

unsigned int bitholder = EntityIdentifier::horizontalscrollcameraBit() | EntityIdentifier::CameraBit();

//unsigned int bitholder =EntityIdentifier::CameraBit();
ECS::SetUpIdentifier(entity, bitholder, "Main Camera");
ECS::SetIsMainCamera(entity, true);

	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BG.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 615, 228);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -10.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = (tempSpr.GetHeight() / 2.f);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(0.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (-tempSpr.GetHeight() / 16.f) * 6.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Ground");
	}

	{
		
		//Creates entity
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainPlayer(entity);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		string filename = "box.png";
	
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 40, 40);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-10.f), float32(100.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		tempPhsBody.SetFriction(0.05f);
		tempPhsBody.SetMaxVelo(1.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() |EntityIdentifier::PhysicsBit();
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 40, 40);
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

		tempPhsBody.SetFriction(0.15f);
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 40, 40);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(90.f, 0.f, 100.f));
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 2.f;
		float shrinkY = tempSpr.GetWidth() / 2.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(5.f), float32(100.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		tempPhsBody.SetFriction(0.15f);
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 40, 40);
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

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.50f);
		tempPhsBody.SetGravity(true);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Box3");
		

		m_player = entity;
	}

 ECS::GetComponent<Horizontal_Scroll>(EntityIdentifier::MainCamera()).setfocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
 //ECS::GetComponent<Vertical_Scroll>(EntityIdentifier::MainCamera()).setfocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
 
}