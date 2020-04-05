#include "EndlessMode.h"

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
		
		animation.AddAnimation(movement["Walk_Right"]); 
	
		animation.AddAnimation(movement["Run_Right"]);
		
		animation.AddAnimation(movement["Jump_Begin_Right"]); 
		
		animation.AddAnimation(movement["Jump_Middle_Right"]); 
		
		animation.AddAnimation(movement["Jump_End_Right"]);
		
		animation.AddAnimation(movement["Falling_Right"]);
		
		animation.AddAnimation(movement["Flinch_Right"]);
		
		animation.AddAnimation(movement["Death_Right"]);
		
		animation.AddAnimation(movement["Gun_Shoot_Right"]);
		

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
}

void EndlessMode::GamepadUp(XInputController* con)
{
}

void EndlessMode::GamepadDown(XInputController* con)
{
}

void EndlessMode::GamepadStick(XInputController* con)
{
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
