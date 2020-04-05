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
		CreateDestructable("enemy.PNG", vec2(4, 4), vec2(39, -22));
		CreateMainPlayer(10 / 1.9, 20 / 1.9, vec3(-48, -23, 50));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}



	//HP ROOM
	
	if (m_name == "HPUpgrade")
	{
		CreateBackground("hproom.png", vec2(480 / 4.5, 270 / 4.5));

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

		//Floor

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-53, -23.9563);
			vertices[1].Set(52.9001, -23.9563);
			vertices[2].Set(52.9001, -28.7503);
			vertices[3].Set(-53, -28.7503);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-50.6529, -3.33208);
			vertices[1].Set(-39.7166, -3.33208);
			vertices[2].Set(-39.7166, -4.33084);
			vertices[3].Set(-50.6529, -4.33084);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-21.1898, 12.3473);
			vertices[1].Set(-9.95381, 12.3473);
			vertices[2].Set(-9.95381, 11.3486);
			vertices[3].Set(-21.1898, 11.3486);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(10.4707, 21.0864);
			vertices[1].Set(43.9114, 21.0864);
			vertices[2].Set(43.9114, 20.0563);
			vertices[3].Set(10.4707, 20.0563);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-53, 50);
			vertices[1].Set(-29.7291, 50);
			vertices[2].Set(-29.7291, 29);
			vertices[3].Set(-53, 17.3146);

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
		CreateMainPlayer(8, 16, vec3(43.412, -17.4644, 100));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}
	
	//MAGNET ROOM

    
	if (m_name == "MagnetUpgrade")
	{
		CreateBackground("magroom.png", vec2(480 / 4.5, 270 / 4.5));

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

		//Floor

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-53, 15.2437);
			vertices[1].Set(-34.2734, 15.2437);
			vertices[2].Set(-34.2734, -6.72882);
			vertices[3].Set(-53, -6.72882);
			

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-34.2734, -6.72882);
			vertices[1].Set(-17.7441, -6.72882);
			vertices[2].Set(-17.7441, -17.2647);
			vertices[3].Set(-34.2734, -17.2647);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-17.7441, -17.2647);
			vertices[1].Set(52.9501, -17.3146);
			vertices[2].Set(52.9501, -28.4507);
			vertices[3].Set(-17.7441, -28.4507);


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
		CreateMainPlayer(8, 16, vec3(43.412, -17.4644, 100));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}
	
	//MAGNET PRACTICE
	
	if (m_name == "MagnetPractice")
	{
		CreateBackground("magpractice.png", vec2(960 / 4.5, 270 / 4.5));

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

		//Floor

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(80.2322, -20.0612);
			vertices[1].Set(105.9, -20.0612);
			vertices[2].Set(105.9, -28.7004);
			vertices[3].Set(80.2322, -28.7004);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-22.8049, -20.1111);
			vertices[1].Set(21.6395, -20.1111);
			vertices[2].Set(21.6395, -28.7503);
			vertices[3].Set(-22.8049, -28.7503);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-106, -20.0612);
			vertices[1].Set(-82.4794, -20.0612);
			vertices[2].Set(-82.4794, -28.8002);
			vertices[3].Set(-106, -28.8002);


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
		CreateMagnet(vec2(10, 5), vec2(-48.9214, 2.91011));
		CreateMagnet(vec2(10, 5), vec2(51.32, 3.00999));
		CreateMainPlayer(8, 16, vec3(-99.7578, -14.3683, 100));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}
	
	
	//HALLP1
	if (m_name == "Hallp1")
	{
		CreateBackground("hallp1.png", vec2(460 / 4.5, 270 / 4.5));

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

		//Floor

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-51, -23.8624);
			vertices[1].Set(51, -23.8624);
			vertices[2].Set(51, -28.7004);
			vertices[3].Set(-51, -28.7004);


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
		CreateMainPlayer(8, 16, vec3(-44.1086, -17.1648, 100));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}

	//BOSS ROOM

	if (m_name == "BossRoom")
	{
		CreateBackground("boss.png", vec2(460 / 4.5, 270 / 4.5));

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

		//Floor

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-45.9541, -25.422);
			vertices[1].Set(-25.7706, -25.422);
			vertices[2].Set(-25.7706, -28.7004);
			vertices[3].Set(-45.9541, -28.7004);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-16.9633, -25.422);
			vertices[1].Set(18.5379, -25.422);
			vertices[2].Set(18.5379, -28.7004);
			vertices[3].Set(-16.9633, -28.7004);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(27.789, -25.422);
			vertices[1].Set(50.7248, -25.422);
			vertices[2].Set(50.7248, -28.7004);
			vertices[3].Set(27.789, -28.7004);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-46.9551, 3.70911);
			vertices[1].Set(-33.0724, 3.70911);
			vertices[2].Set(-33.0724, 2.86018);
			vertices[3].Set(-46.9551, 2.86018);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-7.53559, -2.6829);
			vertices[1].Set(7.28089, -2.6829);
			vertices[2].Set(7.28089, -3.53183);
			vertices[3].Set(-7.53559, -3.53183);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(34.221, 3.85893);
			vertices[1].Set(48.2534, 3.85893);
			vertices[2].Set(48.2534, 2.91011);
			vertices[3].Set(34.221, 2.91011);


			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			myFixtureDef.userData = ((void*)PLATFORM);
			body->CreateFixture(&myFixtureDef);
		}

		{
			body = m_physicsWorld->CreateBody(&bodyDef);

			b2Vec2 vertices[4];
			vertices[0].Set(-51, -2.13358);
			vertices[1].Set(-46.0062, -2.13358);
			vertices[2].Set(-46.0062, -25.3546);
			vertices[3].Set(-51, -25.3546);


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

		//Ceiling
		{
			bodyDef.userData = ((void*)PLATFORM);
			body = m_physicsWorld->CreateBody(&bodyDef);

			phsBody = PhysicsBody(body, float(bgEntity.GetWidth()), thickness,
				vec2(0.f, bgEntity.GetHeight() / 2 + (thickness / 2)), false);
		}
		CreateMagnet(vec2(10, 5), vec2(-17.9413, 24.3558));
		CreateMagnet(vec2(10, 5), vec2(21.0599, 24.3059));
		CreateMainPlayer(8, 16, vec3(-44.1086, -17.1648, 100));
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).Zoom(80);
	}

	//INFESTED
	
	if (m_name == "Infest") 
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
		CreateForeground("fence.png", vec2(105, 9.5), vec2(-79.9726, -38.4034));
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

void Room::CreateForeground(string fileName, vec2 size, vec2 position)
{
	auto entity = ECS::CreateEntity();

	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);


	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, size.x, size.y);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(position.x, position.y, 100.f));

	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
	ECS::SetUpIdentifier(entity, bitHolder, "fgImage");
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
		vec3 position(position.x, position.y, 90);

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