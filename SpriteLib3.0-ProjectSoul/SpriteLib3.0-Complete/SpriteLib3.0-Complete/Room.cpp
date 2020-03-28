#include "Room.h"
#include"Xinput.h"


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
	
	/*
	if (m_name == "Start")
	{

		CreateBackground("Start.png", vec2(480 / 4.5, 270 / 4.5));
		auto bgEntity = ECS::GetComponent<Sprite>(m_background);

		//Boundary
		CreateRoomBoundary();
		
		//Ground
		CreateEdge(b2Vec2(-bgEntity.GetWidth() / 2, -28), b2Vec2(bgEntity.GetWidth() / 2, -28), GROUND);

		//Doorway
		CreateDoorWay(b2Vec2(53, -20));

		//Magnet
		CreateMagnet(vec2(4, 4), vec2(20, 5));
		CreateMagnet(vec2(4, 4), vec2(-10, 5));

		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
		CreateMainPlayer(10, 20, vec3(-43, -18, 50));
		
	}
	*/
	if (m_name == "Hallway")
	{
		CreateBackground("Hallway Finished.png", vec2(480 / 4.5, 270 / 4.5));
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
		b2FixtureDef myFixtureDef;

		//Platform 1
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-51.9074, -21.1759);
			vertices[1].Set(-38.2963, -21.1759);
			vertices[2].Set(-38.2963, -28.9074);
			vertices[3].Set(-51.9074, -28.9074);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)GROUND);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 2
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-28.1788, -20.25);
			vertices[1].Set(-14.4288, -20.25);
			vertices[2].Set(-14.4288, -28.6759);
			vertices[3].Set(-28.1788, -28.6759);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)GROUND);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 3
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-6.45719, -19.0926);
			vertices[1].Set(11.9687, -19.0926);
			vertices[2].Set(12.1539, -28.537);
			vertices[3].Set(-6.45719, -28.537);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)GROUND);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 4
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(19.5561, -15.7593);
			vertices[1].Set(33.8617, -15.7593);
			vertices[2].Set(32.5191, -28.7222);
			vertices[3].Set(20.2043, -28.7222);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)GROUND);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 5
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(40.5648, -23.7999);
			vertices[1].Set(51.9537, -23.7999);
			vertices[2].Set(51.9537, -25.5128);
			vertices[3].Set(40.5648, -25.5128);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)GROUND);
			body->CreateFixture(&myFixtureDef);
		}

		//Plant 1
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[8];
			vertices[0].Set(-37.5093, -22.9815);
			vertices[1].Set(-37.6481, -14.6944);
			vertices[2].Set(-35.9815, -14.5556);
			vertices[3].Set(-34.6852, -10.8519);
			vertices[4].Set(-33.1111, -9.69444);
			vertices[5].Set(-32.2778, -14.787);
			vertices[6].Set(-30.2407, -16.2222);
			vertices[7].Set(-30.6574, -22.287);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 8); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)WALL);
			body->CreateFixture(&myFixtureDef);
		}

		//Plant 2
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[8];
			vertices[0].Set(-13.1667, -22.6574);
			vertices[1].Set(-11.0833, -17.5648);
			vertices[2].Set(-12.3333, -13.8611);
			vertices[3].Set(-10.7593, -9.41667);
			vertices[4].Set(-9.50926, -10.8056);
			vertices[5].Set(-9.0463, -14.9259);
			vertices[6].Set(-9.27778, -18.3056);
			vertices[7].Set(-6.82407, -20.25);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 8); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)WALL);
			body->CreateFixture(&myFixtureDef);
		}

		//Plant 3
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[5];
			vertices[0].Set(14.5618, -18.6296);
			vertices[1].Set(12.4322, -10.7593);
			vertices[2].Set(12.71, -7.61111);
			vertices[3].Set(15.3025, -12.6111);
			vertices[4].Set(19.5155, -15.5741);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 5); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)WALL);
			body->CreateFixture(&myFixtureDef);
		}

		//Plant 4
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[8];
			vertices[0].Set(35.0093, -16.5776);
			vertices[1].Set(32.8333, 1.7557);
			vertices[2].Set(37.2778, 5.64459);
			vertices[3].Set(37.463, 7.72792);
			vertices[4].Set(39.8704, 0.644589);
			vertices[5].Set(39.3148, -4.17022);
			vertices[6].Set(41.1667, -2.41097);
			vertices[7].Set(39.5463, -20.8369);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 8); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)WALL);
			body->CreateFixture(&myFixtureDef);
		}

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
			bodyDef.userData = ((void*)WALL);
			body = m_physicsWorld->CreateBody(&bodyDef);

			phsBody = PhysicsBody(body, thickness, bgEntity.GetHeight(),
				vec2(bgEntity.GetWidth() / 2 + (thickness / 2), 0.f), false);
		}

		//Doorway
		CreateDoorWay(b2Vec2(53, -20));

		CreateMainPlayer(10 / 1.3, 20 / 1.3, vec3(-44, -13, 50));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}


	if (m_name == "Storage")
	{
		CreateBackground("Latest Version 2.png", vec2(480 / 4.5, 270 / 4.5));
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
		b2FixtureDef myFixtureDef;

		//Platform 1
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-18.97, -14.3704);
			vertices[1].Set(-3.46074, -14.3241);
			vertices[2].Set(-4.15519, -15.3889);
			vertices[3].Set(-18.3219, -15.3889);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 2
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-35.8649, -15.3439);
			vertices[1].Set(-20.4019, -15.3439);
			vertices[2].Set(-21.05, -16.3161);
			vertices[3].Set(-35.263, -16.4087);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 3
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-35.8693, 1.38534);
			vertices[1].Set(-20.36, 1.38534);
			vertices[2].Set(-21.0082, 0.227937);
			vertices[3].Set(-35.2674, 0.227937);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 4
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-19.5, 17.9815);
			vertices[1].Set(-3.49902, 17.9815);
			vertices[2].Set(-4.63889, 16.8241);
			vertices[3].Set(-18.8056, 16.8241);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 5
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(12.6319, 17.9329);
			vertices[1].Set(28.1991, 17.9329);
			vertices[2].Set(27.5625, 16.7755);
			vertices[3].Set(13.3843, 16.7755);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Platform 6
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(29.4884, 14.1713);
			vertices[1].Set(45.4606, 14.1713);
			vertices[2].Set(44.4769, 13.6226);
			vertices[3].Set(30.1829, 13.6226);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Box
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-24.9913, 6.56752);
			vertices[1].Set(-20.1765, 6.56752);
			vertices[2].Set(-20.1765, 1.70641);
			vertices[3].Set(-24.9913, 1.70641);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Left Side Vent
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(37.9259, 28.5833);
			vertices[1].Set(38.3889, 28.5833);
			vertices[2].Set(38.3889, 23.8611);
			vertices[3].Set(37.9259, 23.8611);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Right Side Vent
		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(44.8704, 28.5833);
			vertices[1].Set(45.5648, 28.5833);
			vertices[2].Set(45.5648, 23.8611);
			vertices[3].Set(44.8704, 23.8611);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		//Ground
		{
			bodyDef.userData = ((void*)GROUND);
			body = m_physicsWorld->CreateBody(&bodyDef);

			phsBody = PhysicsBody(body, float(bgEntity.GetWidth()), thickness,
				vec2(0.f, -bgEntity.GetHeight() / 2/* - (thickness / 2)*/), false);
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
			bodyDef.userData = ((void*)WALL);
			body = m_physicsWorld->CreateBody(&bodyDef);

			phsBody = PhysicsBody(body, thickness, bgEntity.GetHeight(),
				vec2(bgEntity.GetWidth() / 2 + (thickness / 2), 0.f), false);
		}
		CreateMagnet(vec2(2, 2), vec2(3.17, 0.72));
		//CreateMagnet("magnetTemp.PNG", vec2(2, 2), vec2(31.90 , 0.72));
		//CreateDestructable("enemy.PNG", vec2(4, 4), vec2(39, -22));
		CreateMainPlayer(10 / 1.9, 20 / 1.9, vec3(-48, -23, 50));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}

	if (m_name == "Vent")
	{
		CreateBackground("Vent.png", vec2(480 / 4.5, 625 / 4.5));

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
		b2FixtureDef myFixtureDef;

		//Bottom Exit

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[6];
			vertices[0].Set(22.2155, -35.3276);
			vertices[1].Set(2.30814, -35.3276);
			vertices[2].Set(2.30814, -28.198);
			vertices[3].Set(-5.60853, -22.5961);
			vertices[4].Set(-26.6546, -22.5961);
			vertices[5].Set(-26.6546, -38.1004);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 6); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
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
			bodyDef.userData = ((void*)WALL);
			body = m_physicsWorld->CreateBody(&bodyDef);

			phsBody = PhysicsBody(body, thickness, bgEntity.GetHeight(),
				vec2(bgEntity.GetWidth() / 2 + (thickness / 2), 0.f), false);
		}
		CreateMainPlayer(10, 20, vec3(0, 0, 50));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}
	//INFESTED
	
	if (m_name == "Start")
	{
		CreateBackground("moninfest.png", vec2(1200 / 4.5, 1200 / 4.5));

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
		b2FixtureDef myFixtureDef;

		//Bottom Exit

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(23.734, -91.6255);
			vertices[1].Set(61.1872, -91.6255);
			vertices[2].Set(61.1872, -96.6442);
			vertices[3].Set(23.734, -96.6442);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-17.3927, -74.7715);
			vertices[1].Set(15.5661, -74.7715);
			vertices[2].Set(15.5661, -79.7154);
			vertices[3].Set(-17.3927, -79.7154);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(66.633, -122.337);
			vertices[1].Set(132.85, -122.337);
			vertices[2].Set(132.85, -131.625);
			vertices[3].Set(66.633, -131.625);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(31.9107, -51.9363);
			vertices[1].Set(132.85, -51.9363);
			vertices[2].Set(132.85, -62.3483);
			vertices[3].Set(31.9107, -62.3483);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-133, -122.787);
			vertices[1].Set(-85.7341, -122.787);
			vertices[2].Set(-85.7341, -131.85);
			vertices[3].Set(-133, -131.85);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-85.1348, -96.3446);
			vertices[1].Set(-67.3071, -96.3446);
			vertices[2].Set(-67.3071, -101.438);
			vertices[3].Set(-85.1348, -101.438);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(23.698, -19.8365);
			vertices[1].Set(132.95, -19.8365);
			vertices[2].Set(132.95, -30.2621);
			vertices[3].Set(23.698, -30.2621);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-11.3065, -28.764);
			vertices[1].Set(6.62107, -28.764);
			vertices[2].Set(6.62107, -33.9076);
			vertices[3].Set(-11.3065, -33.9076);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-133, -41.6506);
			vertices[1].Set(-27.3889, -41.6506);
			vertices[2].Set(-27.3889, -52.2983);
			vertices[3].Set(-133, -52.2983);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(115.022, 9.41421);
			vertices[1].Set(132.95, 9.41421);
			vertices[2].Set(132.95, 4.23468);
			vertices[3].Set(115.022, 4.23468);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-133, 12.8328);
			vertices[1].Set(-10.7316, 12.8328);
			vertices[2].Set(-10.7316, 2.37408);
			vertices[3].Set(-133, 2.37408);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(85.9089, 32.2369);
			vertices[1].Set(103.737, 32.2369);
			vertices[2].Set(103.737, 27.0434);
			vertices[3].Set(85.9089, 27.0434);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-27.3473, 56.5078);
			vertices[1].Set(74.7119, 56.5078);
			vertices[2].Set(74.7119, 45.971);
			vertices[3].Set(-27.3473, 45.971);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}


		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-53.3109, 101.154);
			vertices[1].Set(-35.633, 101.154);
			vertices[2].Set(-35.633, 95.9105);
			vertices[3].Set(-53.3109, 95.9105);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-133, 109.844);
			vertices[1].Set(-60.0091, 109.844);
			vertices[2].Set(-60.0091, 67.5952);
			vertices[3].Set(-133, 67.5952);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(72.0041, 94.7546);
			vertices[1].Set(132.95, 94.7546);
			vertices[2].Set(132.95, 84.2178);
			vertices[3].Set(72.0041, 84.2178);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
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
			bodyDef.userData = ((void*)WALL);
			body = m_physicsWorld->CreateBody(&bodyDef);

			phsBody = PhysicsBody(body, thickness, bgEntity.GetHeight(),
				vec2(bgEntity.GetWidth() / 2 + (thickness / 2), 0.f), false);
		}

		CreateMagnet(vec2(10, 5), vec2(23.6257, 5.03368));
		CreateMagnet(vec2(10, 5), vec2(77.7484, -99.0911));
		CreateMagnet(vec2(10, 5), vec2(-51.0106, -78.4656));
		CreateMagnet(vec2(10, 5), vec2(-97.794, -105.034));
		CreateMagnet(vec2(10, 5), vec2(101.102, 2.93997));
		CreateMagnet(vec2(10, 5), vec2(-22.0795, -29.2955));
		CreateMagnet(vec2(10, 5), vec2(47.0852, 88.9823));
		CreateMagnet(vec2(10, 5), vec2(-14.7432, 89.1034));
		CreateMainPlayer(10, 20, vec3(0, 0, 100));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}
	
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
		bodyDef.userData = ((void*)WALL);
		body = m_physicsWorld->CreateBody(&bodyDef);

		phsBody = PhysicsBody(body, thickness, bgEntity.GetHeight(),
			vec2(bgEntity.GetWidth() / 2 + (thickness / 2), 0.f), false);
	}

	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "RoomBoundary");
}


void Room::CreateMainPlayer(int width, int height, vec3 position)
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
		
		ECS::GetComponent<HealthBar>(entity).GetCam();
		ECS::GetComponent<HealthBar>(entity).DrawHUD();

		auto movement = File::LoadJSON("entire_sheet.json");

		auto& animation = ECS::GetComponent<AnimationController>(entity);

		animation.InitUVs("entire_sheet.png");

		animation.AddAnimation(movement["Idle_Right"]); //0
		animation.AddAnimation(movement["Idle_Left"]);
		animation.AddAnimation(movement["Walk_Right"]); //2
		animation.AddAnimation(movement["Walk_Left"]);
		animation.AddAnimation(movement["Run_Right"]);//4
		animation.AddAnimation(movement["Run_Left"]);
		animation.AddAnimation(movement["Dash_Right"]);//6
		animation.AddAnimation(movement["Dash_Left"]);
		animation.AddAnimation(movement["Jump_Begin_Right"]); //8
		animation.AddAnimation(movement["Jump_Begin_Left"]);
		animation.AddAnimation(movement["Jump_Middle_Right"]); //10
		animation.AddAnimation(movement["Jump_Middle_Left"]);
		animation.AddAnimation(movement["Jump_End_Right"]);// 12
		animation.AddAnimation(movement["Jump_End_Left"]);
		animation.AddAnimation(movement["Falling_Right"]);// 14
		animation.AddAnimation(movement["Falling_Left"]);
	    animation.AddAnimation(movement["Flinch_Right"]);//16
		animation.AddAnimation(movement["Flinch_Left"]);
		animation.AddAnimation(movement["Death_Right"]);//18
		animation.AddAnimation(movement["Death_Left"]);
		animation.AddAnimation(movement["Gun_Shoot_Right"]);//20
		animation.AddAnimation(movement["Gun_Shoot_Left"]);

		animation.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, width, height, true, &animation);

		//Player position
		vec3 position(position.x, position.y, position.z);

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

void Room::CreateMagnet(vec2 size, vec2 position)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	string fileName = "Magnet.png";

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
		vec2(0.f, 0.f), true, MAGNET, true);

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

void Room::CreateDestructable(string fileName, vec2 size, vec2 position)
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

	bodyDef.userData = ((void*)entity);
	//bodyDef.userData = ((void*)BREAKABLE);
	body = m_physicsWorld->CreateBody(&bodyDef);

	phsBody = PhysicsBody(body, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f), true, BREAKABLE, false);

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Breakable");
}

void Room::CreateDoorWay(b2Vec2 position)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0, 0, 49));

	auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

	//Create physics body
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	//Set position of doorway
	bodyDef.position.Set(position.x, position.y);

	//Body user data is same as entityID
	bodyDef.userData = ((void*)entity);

	body = m_physicsWorld->CreateBody(&bodyDef);
	body->SetGravityScale(0);

	//Create collider
	phsBody = PhysicsBody(body, 0.5f, 20.f,
		vec2(0.f, 0.f), true, DOORWAY, true);

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Doorway");
}

void Room::ShootBullet(float velocity)
{
	string fileName = "box.png";

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

	if (velocity > 0)
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(m_playerBody->GetPosition().x + 5, m_playerBody->GetPosition().y, 50.f));
	else
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(m_playerBody->GetPosition().x - 5, m_playerBody->GetPosition().y, 50.f));

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& phsBody = ECS::GetComponent<PhysicsBody>(entity);

	//Create physics body
	b2Body* body;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	if (velocity > 0)
		bodyDef.position.Set(m_playerBody->GetPosition().x + 5, m_playerBody->GetPosition().y);
	else
		bodyDef.position.Set(m_playerBody->GetPosition().x - 5, m_playerBody->GetPosition().y);

	//Body user data is same as entityID
	bodyDef.userData = ((void*)entity);


	body = GetPhysicsWorld().CreateBody(&bodyDef);
	body->SetGravityScale(0);

	body->IsBullet();

	phsBody = PhysicsBody(body, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
		vec2(0.f, 0.f), true, BULLET, true);

	body->GetFixtureList()->SetRestitution(100);
	body->SetLinearVelocity(b2Vec2(velocity, 0));

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Bullet");
}

vec2 Room::ConvertToGl(vec2 clickCoord)
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



void Room::GamepadStroke(XInputController* con)
{
}

void Room::GamepadUp(XInputController* con)
{
}

void Room::GamepadDown(XInputController* con)
{

	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

	{	static bool has_jumped = false;

	if (con->IsButtonPressed(Buttons::A))
		//to do the animation first
		if (m_isPlayerOnGround)
			has_jumped = true;



	if (has_jumped) {
		animation.SetActiveAnim(m_character_direction + JUMP_BEGIN);
		animation.GetAnimation(m_character_direction + JUMP_END).Reset();
	}
	if (animation.GetAnimation(m_character_direction + JUMP_BEGIN).GetAnimationDone()) {
		has_jumped = false;
		float impulse = m_playerBody->GetMass() * 50; //Adjust to change height of jump
		m_playerBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_playerBody->GetWorldCenter(), true);
		m_isPlayerOnGround = false;
		animation.SetActiveAnim(m_character_direction + JUMP_MIDDLE);
		animation.GetAnimation(m_character_direction + JUMP_BEGIN).Reset();
	}


	if (animation.GetAnimation(m_character_direction + JUMP_MIDDLE).GetAnimationDone() && m_isPlayerOnGround) {
		animation.SetActiveAnim(m_character_direction + JUMP_END);
		animation.GetAnimation(m_character_direction + JUMP_MIDDLE).Reset();
	}
	}

	//shooting
	{

	}

	//DASH
	{
		if (con->IsButtonStroked(Buttons::B)) {

			b2Vec2 direction = b2Vec2(0.f, 0.f);
			float magnitude = 50.f;


			Stick sticks[2];

			con->GetSticks(sticks);

			//right
			if (sticks[0].x >= 0.7f && sticks[0].x <= 1.f) {
				direction = b2Vec2((direction.x + magnitude), direction.y);
				m_character_direction = false;
			}
			//left
			else if (sticks[0].x <= -0.7f && sticks[0].x >= -1.f) {
				direction = b2Vec2((direction.x - magnitude), direction.y);
				m_character_direction = true;
			}
			//up
			if (sticks[0].y >= 0.7f && sticks[0].y <= 1.f) {
				direction = b2Vec2(direction.x, (direction.y + magnitude));
				m_character_direction = false;
			}
			//down
			else if (sticks[0].y <= -0.7f && sticks[0].y >= -1.f) {
				direction = b2Vec2(direction.x, (direction.y - magnitude));
				m_character_direction = true;
			}
			animation.SetActiveAnim(m_character_direction + DASH);

			//Start Dashing
			if (direction.Length() > 0)
			{
				//Flag whether initial dash position on ground
				if (m_isPlayerOnGround)
					m_initDashOnGround = true;
				else
					m_initDashOnGround = false;

				//Flag whether initial dash position on wall
				if (m_isPlayerOnWall)
					m_initDashOnWall = true;
				else
					m_initDashOnWall = false;

				//Set velocity
				m_playerBody->SetGravityScale(0);
				m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
				m_playerBody->SetLinearVelocity(direction);
				m_isDashing = true;
				m_initDashTime = clock();
				m_dashCounter = 0;
				m_initVelocity = m_playerBody->GetLinearVelocity();
			}
		}
	}
}

void Room::GamepadStick(XInputController* con)
{
	Stick sticks[2];

	con->GetSticks(sticks);

	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

	if (con->IsButtonPressed(Buttons::START))
		exit(0);

	//Movement direction 
	b2Vec2 direction = b2Vec2(0.f, 0.f);

	float force = 40000;
	float velocity = 30; //Change for player velocity on ground

	

	//Apply force for movement
	if (m_isPlayerOnGround && !m_isDashing) {

		if (sticks[0].x <= 0.2f && sticks[0].x > -0.2f&&animation.GetActiveAnim()!=(JUMP_END+m_character_direction))
			animation.SetActiveAnim(m_character_direction + IDLE);

		//right run
		if (sticks[0].x >= 0.7f && sticks[0].x <= 1.f)
		{
			direction += b2Vec2(1, 0);
			m_character_direction = false;
			animation.SetActiveAnim(m_character_direction + RUN);


		}

		//left run
		else if (sticks[0].x <= -0.7f && sticks[0].x >= -1.f)
		{
			direction = b2Vec2(-1, 0);
			m_character_direction = true;
			animation.SetActiveAnim(m_character_direction + RUN);

		}

		//right walk 
		else if (sticks[0].x >= 0.2f && sticks[0].x < 0.7f) {
			direction += b2Vec2(0.5, 0);
			m_character_direction = false;
			animation.SetActiveAnim(m_character_direction + WALK);
		}

		//left walk
		else if (sticks[0].x <= -0.2f && sticks[0].x >= -.7f)
		{
			direction = b2Vec2(-0.5f, 0);
			m_character_direction = true;
			animation.SetActiveAnim(m_character_direction + WALK);
		}

		if (direction.Length() > 0)
			m_playerBody->SetLinearVelocity(b2Vec2(direction.x * velocity, direction.y * velocity));

		if (!m_isDashing)
		{
			if (sticks[0].x < 0.2f && sticks[0].x > -0.2f)
				m_playerBody->SetLinearVelocity(b2Vec2(0, m_playerBody->GetLinearVelocity().y));
		}
	}


	else if (!m_isPlayerOnGround)
	{
		if (sticks[0].x >= 0.2f && sticks[0].x < 0.7f) {
			direction += b2Vec2(0.5, 0);
			m_character_direction = false;
		}

		//left walk
		else if (sticks[0].x <= -0.2f && sticks[0].x >= -.7f)
		{
			direction = b2Vec2(-0.5f, 0);
			m_character_direction = true;

		}
		m_playerBody->ApplyForce(b2Vec2(direction.x * force, direction.y * force), b2Vec2(m_playerBody->GetPosition().x, m_playerBody->GetPosition().y), true);
	}
}

void Room::GamepadTrigger(XInputController* con)
{
	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

	// ADD THE SHOOT TO THE ROOM

	if (con->IsButtonPressed(Buttons::RB)) {

		animation.SetActiveAnim(m_character_direction + SHOOT);

		if (m_character_direction)
			ShootBullet(-50);
		else
			ShootBullet(50);
	}
}

void Room::KeyboardHold()
{
	if (Input::GetKey(Key::Enter))
	{
		if (m_isMagnetInRange)
		{
			m_moveToMagnet = true;
			bool distanceReached = (float)abs(m_playerBody->GetPosition().x - m_closestMagnet->GetBody()->GetPosition().x) < 0.5
				&& (float)abs(m_playerBody->GetPosition().y - m_closestMagnet->GetBody()->GetPosition().y) < 0.5;

			if (!distanceReached)
			{
				float speed = 50;
				b2Vec2 velocity = (m_closestMagnet->GetBody()->GetPosition() - m_playerBody->GetPosition());
				velocity.Normalize();
				m_playerBody->SetGravityScale(0);
				m_playerBody->SetLinearVelocity(b2Vec2(velocity.x * speed, velocity.y * speed));
			}
			else
				m_playerBody->SetLinearVelocity(b2Vec2(0, 0)); //Stop player
		}
	}

	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

	b2Vec2 velocity2 = m_playerBody->GetLinearVelocity();

	//Player Movement 
	{
		if (!m_isDashing)
		{
			if (m_isPlayerOnGround)
				animation.SetActiveAnim(m_character_direction + IDLE);


			//Left 
			if (Input::GetKey(Key::A) && !Input::GetKey(Key::D))
			{
				m_character_direction = true;

				if (m_isPlayerOnGround)
					animation.SetActiveAnim(RUN + m_character_direction);

				velocity2.x = -20;
				m_playerBody->SetLinearVelocity(velocity2);
			}

			//Right
			if (Input::GetKey(Key::D) && !Input::GetKey(Key::A))
			{
				m_character_direction = false;

				if (m_isPlayerOnGround)
					animation.SetActiveAnim(RUN + m_character_direction);

				velocity2.x = 20;
				m_playerBody->SetLinearVelocity(velocity2);
			}

			if (Input::GetKey(Key::A) && Input::GetKey(Key::D))
			{
				m_playerBody->SetLinearVelocity(b2Vec2(0, m_playerBody->GetLinearVelocity().y));
			}
		}
	}
}

void Room::KeyboardDown()
{
	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

	b2Vec2 velocity2 = m_playerBody->GetLinearVelocity();

	if (Input::GetKeyDown(Key::Escape))
		exit(0);

	//Jump
	if (Input::GetKeyDown(Key::Space))
	{
		if (m_isPlayerOnGround)
		{
			animation.SetActiveAnim(m_character_direction + JUMP_BEGIN);
			velocity2.y = 40;
			m_playerBody->SetLinearVelocity(velocity2);
			m_isPlayerJumping = true;
			m_isPlayerOnGround = false;
			animation.GetAnimation(m_character_direction + JUMP_END).Reset();
		}
	}

	//Shoot bullet
	if (Input::GetKeyDown(Key::Space)&&!m_character_direction)
	{
		ShootBullet(50);
	}
	if (Input::GetKeyDown(Key::Space)&&m_character_direction)
	{
		ShootBullet(-50);
	}

	//Dash direction
	if (Input::GetKeyDown(Key::LeftShift) && m_dashCounter == 1)
	{
		b2Vec2 direction = b2Vec2(0.f, 0.f);
		float magnitude = 50.f;

		//Dash Up
		if (Input::GetKey(Key::W)) {
			direction = b2Vec2(direction.x, (direction.y + magnitude));
		}

		//Dash Left
		if (Input::GetKey(Key::A)) {
			direction = b2Vec2((direction.x - magnitude), direction.y);
			m_character_direction = true;
		}

		//Dash Down
		if (Input::GetKey(Key::S)) {
			direction = b2Vec2(direction.x, (direction.y - magnitude));
		}

		//Dash Right
		if (Input::GetKey(Key::D)) {
			direction = b2Vec2((direction.x + magnitude), direction.y);
			m_character_direction = false;
		}

		animation.SetActiveAnim(m_character_direction + DASH);

		//Start Dashing
		if (direction.Length() > 0)
		{
			//Flag whether initial dash position on ground
			if (m_isPlayerOnGround)
				m_initDashOnGround = true;
			else
				m_initDashOnGround = false;

			//Flag whether initial dash position on wall
			if (m_isPlayerOnWall)
				m_initDashOnWall = true;
			else
				m_initDashOnWall = false;

			//Set velocity
			m_playerBody->SetGravityScale(0);
			m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
			m_playerBody->SetLinearVelocity(direction);
			m_isDashing = true;
			m_initDashTime = clock();
			m_dashCounter = 0;
			m_initVelocity = m_playerBody->GetLinearVelocity();
		}
	}
}

void Room::KeyboardUp()
{
	if (Input::GetKeyUp(Key::Enter))
	{
		m_moveToMagnet = false;
		m_playerBody->SetGravityScale(m_playerGravity);
		m_playerBody->ApplyForce(b2Vec2(0, -0.01), m_playerBody->GetWorldCenter(), true);
	}
	//Set linear velocity of x to zero when A or D key is up and is not dashing
	if ((Input::GetKeyUp(Key::A) || Input::GetKeyUp(Key::D)) && !m_isDashing)
		m_playerBody->SetLinearVelocity(b2Vec2(0, m_playerBody->GetLinearVelocity().y));
}

void Room::MouseMotion(SDL_MouseMotionEvent evnt)
{
}

void Room::MouseClick(SDL_MouseButtonEvent evnt)
{
}


void Room::MouseWheel(SDL_MouseWheelEvent evnt)
{
}


void Room::SetAction(bool dash, bool magnet, bool shoot)
{
	can_dash = dash;
	can_magent = magnet;
	can_shoot = shoot;
}

void Room::SetRoom(Scene* room)
{
	SetAction(room->CanDash(),room->CanMagent(),room->CanShoot());
}

void Room::DashUpdate()
{
	if (m_isPlayerOnGround && !m_isDashing)
	{
		m_dashCounter = 1;
	}

	//End of Dash 
	if (m_isDashing)
	{
		//**ADJUST DASH LENGTH HERE**
		float dashTime = .3;

		//End dash when head sensor collides with platform 
		if (m_isPlayerHeadCollide)
		{
			m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
			m_playerBody->SetGravityScale(m_playerGravity);
			m_isDashing = false;
		}

		//End dash when side sensor collides with wall OR time of dash reached
		if (m_isPlayerOnWall)
			if ((float)(clock() - m_initDashTime) / CLOCKS_PER_SEC > dashTime || !m_initDashOnWall)
			{
				m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
				m_playerBody->SetGravityScale(m_playerGravity);
				m_isDashing = false;
			}

		//End dash when side sensor collides with platform OR time of dash reached
		if (m_isPlayerSideCollide)
		{
			if (abs(m_initVelocity.x) > 0.001 || ((float)(clock() - m_initDashTime) / CLOCKS_PER_SEC > dashTime))
			{
				m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
				m_playerBody->SetGravityScale(m_playerGravity);
				m_isDashing = false;
			}
		}

		//End dash when player collides with anything but (ground or platform) OR time of dash reached
		if (m_isPlayerOnCollision || ((float)(clock() - m_initDashTime) / CLOCKS_PER_SEC > dashTime))
		{
			m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
			m_playerBody->SetGravityScale(m_playerGravity);
			m_isDashing = false;
			m_isPlayerOnCollision = false;
		}

		//End dash when foot sensor collides with (ground or platform) OR time of dash reached
		if (m_isPlayerOnGround)
		{
			if ((float)(clock() - m_initDashTime) / CLOCKS_PER_SEC > dashTime || !m_initDashOnGround)
			{
				m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
				m_playerBody->SetGravityScale(m_playerGravity);
				m_isDashing = false;
			}
		}

	}
}
//
//void Room::MagnetScan()
//{
//	{
//		b2Vec2 point1(m_playerBody->GetPosition());
//		RayCastClosestCallback callback;
//		float distance = 40.f;
//		float angleRAD = 0;
//		b2Fixture* fixture = NULL;
//		b2Vec2 fixturePoint, fixtureNormal;
//		float fraction = 0;
//
//		//2 means no magnet in range
//		m_closestMagnetDistance = 2;
//
//		//Reset closest magnet
//		m_closestMagnet = NULL;
//
//		//Magnet scanning 360 degrees
//		for (int angleDEG = 0; angleDEG <= 360; ++angleDEG)
//		{
//			angleRAD = angleDEG * b2_pi / 180.0f;
//
//			b2Vec2 d(distance * cosf(angleRAD), distance * sinf(angleRAD));
//
//			b2Vec2 point2 = point1 + d;
//
//			GetPhysicsWorld().RayCast(&callback, point1, point2);
//		}
//	}
//}



void Room::ProjectileUpdate()
{
	if (m_isBulletHit)
	{
		ECS::GetComponent<PhysicsBody>(m_bulletHitUserData).DeleteBody();
		ECS::DestroyEntity(m_bulletHitUserData);
		m_isBulletHit = false;
	}
}

void Room::BreakableUpdate()
{
	if (m_isBroken)
	{
		ECS::GetComponent<PhysicsBody>(m_breakableUserData).DeleteBody();
		ECS::DestroyEntity(m_breakableUserData);
		m_isBroken = false;
		//Set camera scroll focus to  main player
		ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	}
}

//the room's update function
void Room::Update()
{
	ProjectileUpdate();
	DashUpdate();

	/*if (!m_moveToMagnet && !m_magnetCollision)
		MagnetScan();*/
}