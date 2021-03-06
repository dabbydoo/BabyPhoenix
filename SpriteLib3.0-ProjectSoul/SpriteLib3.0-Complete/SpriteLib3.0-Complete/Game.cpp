#include "Game.h"
#include "MyListener.h"
#include <random>

//Contact listener 
MyContactListener listener;
RayCastClosestCallback rayCastCallBack;


Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	BackEnd::InitBackEnd(719.f, 436.f);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Creates a new scene.
	//Replace this with your own scene.


	m_scenes.push_back(new Start("Menu"));
	m_scenes.push_back(new EndlessMode("Endless Mode"));
	m_scenes.push_back(new Room("Start"));
	m_scenes.push_back(new Room("Hallway1"));
	m_scenes.push_back(new Room("Hallway2"));
	m_scenes.push_back(new Room("Storage"));
	m_scenes.push_back(new Room("Vent"));
	m_scenes.push_back(new Room("BossRoom"));
	m_scenes.push_back(new Room("Armory"));
	m_scenes.push_back(new Room("Infest"));
	m_scenes.push_back(new Room("HPUpgrade"));
	m_scenes.push_back(new Room("MagnetUpgrade"));
	m_scenes.push_back(new Room("MagnetPractice"));

	
	
	//Sets active scene reference to our scene
	m_activeScene = m_scenes[0];

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();

	m_activeScene->SetInMenu(&in_Menu);
	m_activeScene->SetEndlessSelected(&Endless_selected);

	BackEnd::SetWindowName(m_activeScene->GetName());

	PhysicsSystem::Init();

	//Set contact listener
	listener.SetGame(this);
	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);

	//Get player body
	rayCastCallBack.SetGame(this);
}

bool Game::Run()
{
	//Frames per second
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	//While window is still open
	while (m_window->isOpen())
	{
		//Initial frame time
		frameStart = SDL_GetTicks();

		//Clear window with activescene clearColor
		m_window->Clear(m_activeScene->GetClearColor());
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();

		//Flips the windows
		m_window->Flip();

		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}

		//Frame cap
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	return true;
}

void Game::Update()
{

	//Update timer
	Timer::Update();

	//Update Physics System
	PhysicsSystem::Update(m_register, m_activeScene->GetPhysicsWorld());
	//Update the backend
	BackEnd::Update(m_register);

	ChangeRoomUpdate();
	
	//Updates the active scene
	m_activeScene->Update();

	
}

void Game::DrawPause()
{
	{
		auto entity = ECS::CreateEntity();
		m_pauseID = entity;

		//Set camera scroll focus to  main player
		ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<AnimationController>(entity);

		string filename = "pause.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).GetOrthoSize().y * 2.5, ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).GetOrthoSize().w * 2);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).GetPositionX(), ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).GetPositionY(), 100));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Pause Menu");
	}
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	XInputManager::Update();

	//Just calls all the other input functions 
	GamepadInput();

}

void Game::GamepadInput()
{
	XInputController* tempCon;

	bool is_contected = false;
	
	//Gamepad button stroked (pressed)
	for (int i = 0; i<3; i++)
	{
		if (XInputManager::ControllerConnected(i))
		{
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);

			//If the controller is connected, we run the different input types
			GamepadStick(tempCon);
			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadTrigger(tempCon);

			is_contected = true;

		}

	}

	if (!is_contected) {

		KeyboardHold();
		KeyboardDown();
		KeyboardUp();

		//Resets the key flags
		//Must be done once per frame for input to work
		Input::ResetKeys();
	}
}

void Game::GamepadStroke(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.

	m_activeScene->GamepadStroke(con);
}

void Game::GamepadUp(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadUp(con);



}

void Game::GamepadDown(XInputController* con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadDown(con);

}
	
void Game::GamepadStick(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadStick(con);

}

void Game::GamepadTrigger(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadTrigger(con);


}

void Game::KeyboardHold()
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.

	if (m_isPaused) 
			return;

	m_activeScene->KeyboardHold();

}

void Game::KeyboardDown()
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	if (m_activeScene->GetName()!="Menu") {

	if (Input::GetKeyDown(Key::Escape)&&!m_pause_drawn) {
		DrawPause();
		m_pause_drawn = true;
	}

	if (Input::GetKeyDown(Key::Escape)&& m_pause_drawn)
	{
			m_isPaused = !m_isPaused;

		if (m_isPaused)
		{
			ECS::GetComponent<Transform>(m_pauseID).SetPositionZ(100.f);
			
		}

		if (!m_isPaused)
		{
			ECS::GetComponent<Transform>(m_pauseID).SetPositionZ(1.f);
		}
	}

	if (m_isPaused) {
		if (Input::GetKeyDown(Key::S) || Input::GetKeyDown(Key::DownArrow)) {
			//Goes down 
			
		}
		if (Input::GetKeyDown(Key::W) || Input::GetKeyDown(Key::UpArrow)) {
			//Goes Up

		}
		if (Input::GetKeyDown(Key::Enter)) {
			//Changes the 
		}
		return;
	}
	
	}

	m_activeScene->KeyboardDown();

	}

void Game::KeyboardUp()
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.

	if (m_isPaused)
		return;

	m_activeScene->KeyboardUp();

	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}

	if (Input::GetKeyUp(Key::P))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}


	
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseMotion(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseClick(evnt);

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		vec2 clickedPoint = ConvertToGl(vec2(float(evnt.x), float(evnt.y)));
		cout << "x: " << clickedPoint.x << endl;
		cout << "Y: " << clickedPoint.y << endl;
	}

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseWheel(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}



void Game::MagnetScan()
{

	auto* m_playerBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();

	{
		b2Vec2 point1(m_playerBody->GetPosition());
		float distance = 40.f;
		float angleRAD = 0;
		b2Fixture* fixture = NULL;
		b2Vec2 fixturePoint, fixtureNormal;
		float fraction = 0;

		//2 means no magnet in range
		m_activeScene->SetClosestMagnetDistance(2);

		//Reset closest magnet
		/*auto* temp = */m_activeScene->SetClosestMagnet(NULL);

		/*temp = nullptr;*/
		//Magnet scanning 360 degrees
		for (int angleDEG = 0; angleDEG <= 360; ++angleDEG)
		{
			angleRAD = angleDEG * b2_pi / 180.0f;

			b2Vec2 d(distance * cosf(angleRAD), distance * sinf(angleRAD));

			b2Vec2 point2 = point1 + d;

			m_activeScene->GetPhysicsWorld().RayCast(&rayCastCallBack, point1, point2);
		}
	}
}

void Game::BeginCollision(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	//Recording both fixture data
	int f1 = (int)fixtureA->GetUserData();
	int f2 = (int)fixtureB->GetUserData();
	
	

	//Check if Player footsensor begin collision with ground or platform 
	if ((f1 == FOOTSENSOR && (f2 == GROUND || f2 == PLATFORM))
		|| ((f2 == FOOTSENSOR) && (f1 == GROUND || f1 == PLATFORM)))
	{
		auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

		//0 is m_playeronground , 1 is m_playerjumping , 2 is m_playerheadcolide, 3 is m_isPlayerOnWall, 4 is m_isPlayerOnCollision, 5 is m_isBroken, 6 is m_magnetCollision,
		//7 is m_isBulletHit, 8 is m_isPlayerSideCollide

		auto* status = m_activeScene->Player_Status(0);

		*status = true;

		if (!Endless_selected) {
			animation.SetActiveAnim(m_activeScene->PlayerDirection() + JUMP_END);
			animation.GetAnimation(m_activeScene->PlayerDirection() + JUMP_BEGIN).Reset();
		}

		if (status = m_activeScene->Player_Status(1))
			*status = false;
	}

	//Check if Player sidesensor begin collision with wall 
	if ((f1 == SIDESENSOR && f2 == WALL)
		|| ((f2 == SIDESENSOR) && f1 == WALL)) {
		auto* status = m_activeScene->Player_Status(3);
		*status = true;
	}

	//Check if Player headsensor begin collision with platform 
	if ((f1 == HEADSENSOR && f2 == PLATFORM)
		|| (f2 == HEADSENSOR && f1 == PLATFORM))
	{
		auto* status = m_activeScene->Player_Status(2);
		*status = true;
	}

	//Check if Player sideSensor begin collision with platform 
	if ((f1 == SIDESENSOR && f2 == PLATFORM)
		|| (f2 == SIDESENSOR && f1 == PLATFORM))
	{
		auto* status = m_activeScene->Player_Status(8);
		*status = true;
	}

	//Check if Player end collision with any entity that isn't a ground, platform, wall, magnet, enemy, enemybullet
	if ((f1 == PLAYER && f2 != GROUND && f2 != PLATFORM && f2 != WALL && f2 != MAGNET && f2 != ENEMY && f2 != ENEMYBULLET)
		|| (f2 == PLAYER && f1 != GROUND && f1 != PLATFORM && f1 != WALL && f1 != MAGNET && f1 != ENEMY && f1 != ENEMYBULLET))
	{
		auto* status = m_activeScene->Player_Status(4);
		*status = true;
	}

	//Check if player collides with magnet
	if ((f1 == PLAYER && f2 == MAGNET)
		|| ((f2 == PLAYER) && f1 == MAGNET))
	{
		auto* status = m_activeScene->Player_Status(6);
		*status = true;
	}

	////Breakable collision
	//if (f1 == BULLET && f2 == BREAKABLE)
	//{
	//	auto* status = m_activeScene->Player_Status(5);
	//	*status = true;
	//	m_activeScene->SetBreakableUserData((unsigned int)fixtureB->GetBody()->GetUserData());
	//}
	//if (f2 == BULLET && f1 == BREAKABLE)
	//{
	//	auto* status = m_activeScene->Player_Status(5);
	//	*status = true;
	//	m_activeScene->SetBreakableUserData((unsigned int)fixtureA->GetBody()->GetUserData());
	//}

	//Player Bullet vs environment collision
	if (f1 == BULLET && f2 != PLAYER && f2 != SIDESENSOR && f2 != ENEMYBULLET)
	{
		auto* status = m_activeScene->Player_Status(7);
		*status = true;
		m_activeScene->SetBulletHitUserData((unsigned int)fixtureA->GetBody()->GetUserData());
	}
	if (f2 == BULLET && f1 != PLAYER && f1 != SIDESENSOR && f2 != ENEMYBULLET)
	{
		auto* status = m_activeScene->Player_Status(7);
		*status = true;
		m_activeScene->SetBulletHitUserData((unsigned int)fixtureB->GetBody()->GetUserData());
	}

	//Player bullet vs Enemy collision
	if (f1 == BULLET && f2 == ENEMY)
	{
		m_activeScene->SetEnemyBeingHit(fixtureB->GetBody());
	}
	if (f1 == ENEMY && f2 == BULLET)
	{
		m_activeScene->SetEnemyBeingHit(fixtureA->GetBody());
	}

	//Enemy Bullet vs environment collision
	if (f1 == ENEMYBULLET && f2 != ENEMY && f2 != BULLET)
	{
		m_activeScene->SetEnemyBulletHit(true);
		m_activeScene->SetEnemyBulletHitUserData((unsigned int)fixtureA->GetBody()->GetUserData());

	}
	if (f2 == ENEMYBULLET && f1 != ENEMY && f1 != BULLET)
	{
		m_activeScene->SetEnemyBulletHit(true);
		m_activeScene->SetEnemyBulletHitUserData((unsigned int)fixtureB->GetBody()->GetUserData());
	}

	//Enemy Bullet vs Player Collision
	if (f1 == ENEMYBULLET && f2 == PLAYER)
	{
		m_activeScene->SetPlayerBeingHit(true);
	}
	if (f2 == ENEMYBULLET && f1 == PLAYER)
	{
		m_activeScene->SetPlayerBeingHit(true);
	}
//------------------------------------------------------------------------------------------------------------------------------------------------------------
	//Check if player collides with doorway
	if ((f1 == SIDESENSOR && f2 == DOORWAY)
		|| ((f2 == SIDESENSOR) && f1 == DOORWAY))
		m_changeScene = true;

}

void Game::EndCollision(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	int f1 = (int)fixtureA->GetUserData();
	int f2 = (int)fixtureB->GetUserData();

	

	//0 is m_playeronground , 1 is m_playerjumping , 2 is m_playerheadcolide, 3 is m_isPlayerOnWall, 4 is m_isPlayerOnCollision, 5 is m_isBroken, 6 is m_magnetCollision, 7 is m_isBulletHit, 8 is m_isPlayerSideCollide

	//Check if Player footSensor end contact with ground or platform
	if ((f1 == FOOTSENSOR && (f2 == GROUND || f2 == PLATFORM))
		|| ((f2 == FOOTSENSOR) && (f1 == GROUND || f1 == PLATFORM)))
	{
		if (!m_activeScene->Player_Status(0))
		{
			auto* status = m_activeScene->Player_Status(0);
			*status = false;
		}
	}

	//Check if Player sidesensor end collision with wall
	if ((f1 == SIDESENSOR && f2 == WALL)
		|| ((f2 == SIDESENSOR) && f1 == WALL))
	{
		auto* status = m_activeScene->Player_Status(3);
		*status = false;
	}


	//Check if Player headSensor end collision with platform 
	if ((f1 == HEADSENSOR && f2 == PLATFORM)
		|| (f2 == HEADSENSOR && f1 == PLATFORM))
	{
		auto* status = m_activeScene->Player_Status(2);
		*status = false;
	}


	//Check if Player sideSensor end collision with platform 
	if ((f1 == SIDESENSOR && f2 == PLATFORM)
		|| (f2 == SIDESENSOR && f1 == PLATFORM))
	{
		auto* status = m_activeScene->Player_Status(8);
		*status = false;
	}


	//Check if Player end collision with any entity that isn't a ground, platform, wall, magnet, enemy, enemybullet
	if ((f1 == PLAYER && f2 != GROUND && f2 != PLATFORM && f2 != WALL && f2 != MAGNET && f2 != ENEMY && f2 != ENEMYBULLET)
		|| (f2 == PLAYER && f1 != GROUND && f1 != PLATFORM && f1 != WALL && f1 != MAGNET && f1 != ENEMY && f1 != ENEMYBULLET))
	{
		auto* status = m_activeScene->Player_Status(4);
		*status = false;
	}


	//Check if player end collision with magnet
	if ((f1 == PLAYER && f2 == MAGNET)
		|| ((f2 == PLAYER) && f1 == MAGNET))
	{
		auto* status = m_activeScene->Player_Status(6);
		*status = false;
	}

}

void Game::ChangeRoom(RoomName room, vec3 pos)
{
	if(m_activeScene->GetName()!="Menu")
	m_scenes[room]->SetRoom(m_activeScene);
	
	Menu_unloaded = true;

	m_activeScene->Unload();

	m_activeScene = m_scenes[room];

	m_activeScene->SetInitPlayerPos(pos);

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();

	BackEnd::SetWindowName(m_activeScene->GetName());

	PhysicsSystem::Init();

	//Set contact listener
	listener.SetGame(this);
	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);

	if(!Endless_selected)
	m_activeScene->SetBody(m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody());
	
	//Get player body
	rayCastCallBack.SetGame(this);
}

void Game::ChangeRoomUpdate()
{
	if (!in_Menu) {

		if (!Menu_unloaded && m_activeScene->GetName() == "Menu" && !Endless_selected) {
			ChangeRoom(STARTING, vec3(-43, -17, 50));
		}

		if (!Menu_unloaded && m_activeScene->GetName() == "Menu" && Endless_selected)
			ChangeRoom(ENDLESS, vec3(0, -47.5, 100));

		if (m_changeScene&&Menu_unloaded&&!Endless_selected) {
			m_playerPreviousPos = m_activeScene->GetBody()->GetPosition();

		if (m_activeScene->GetName() == "Start")
		{
			
			ChangeRoom(HALLWAY1, vec3(-44.1086, -17.1648, 100));
			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "Hallway1")
		{

			if (m_playerPreviousPos.x < 0)
				ChangeRoom(STARTING, vec3(43, -17, 50));
			if (m_playerPreviousPos.x > 0)
				ChangeRoom(HALLWAY2, vec3(-44, -15, 50));

			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "Hallway2")
		{

			if (m_playerPreviousPos.x < 0)
				ChangeRoom(HALLWAY1, vec3(43, -17, 50));
			if (m_playerPreviousPos.x > 0)
				ChangeRoom(STORAGE, vec3(-48, -22, 50));

			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "Storage")
		{
			if (m_playerPreviousPos.x < 0)
				ChangeRoom(HALLWAY2, vec3(44, -15, 50));
			if (m_playerPreviousPos.x > 0 && m_playerPreviousPos.y > 0)
				ChangeRoom(VENT, vec3(-67.5406, 114.672, 100));

			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "Vent")
		{
			if (m_playerPreviousPos.x < -65 && m_playerPreviousPos.y > 90)
				ChangeRoom(STORAGE, vec3(39, 20, 50));
			if (m_playerPreviousPos.x > 30 && m_playerPreviousPos.y < -80)
				ChangeRoom(BOSS, vec3(-44.1086, 10.1648, 100));

			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "BossRoom")
		{
			ChangeRoom(ARMORY, vec3(-40.1086, -15.1648, 100));

			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "Armory")
		{
			if(m_playerPreviousPos.x < 0)
				ChangeRoom(BOSS, vec3(45.1086, -15, 100));
			if(m_playerPreviousPos.x > 0)
				ChangeRoom(INFESTED, vec3(-120, -40, 100));


				m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "Infest")
		{
			if (m_playerPreviousPos.x < 0 && m_playerPreviousPos.y < 0)
				ChangeRoom(ARMORY, vec3(40.1086, -10, 100));
			if (m_playerPreviousPos.x < 0 && m_playerPreviousPos.y > 0)
				ChangeRoom(HPUPGRADE, vec3(-60, 30, 100));
			if (m_playerPreviousPos.x > 0)
				ChangeRoom(MAGNETUPGRADE, vec3(-47, 22, 100));

			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "HPUpgrade")
		{
			/*if (m_playerPreviousPos.x < 0 && m_playerPreviousPos.y < 0)
				ChangeRoom(ARMORY, vec3(40.1086, -10, 100));
			if (m_playerPreviousPos.x > 0 && m_playerPreviousPos.y > 0)
				ChangeRoom(HPUPGRADE, vec3(-60, 30, 100));
			if (m_playerPreviousPos.x > 0)
				ChangeRoom(MAGNETUPGRADE, vec3(-47, 22, 100));*/

			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "MagnetUpgrade")
		{
			if (m_playerPreviousPos.x < 0)
				ChangeRoom(INFESTED, vec3(123, -110, 100));
			if (m_playerPreviousPos.x > 0)
				ChangeRoom(MAGNETPRACTICE, vec3(-60, 30, 100));

			m_changeScene = false;
		}
		else if (m_activeScene->GetName() == "MagnetPractice")
		{
			if (m_playerPreviousPos.x < 0)
				ChangeRoom(MAGNETUPGRADE, vec3(43, -10, 100));
			if (m_playerPreviousPos.x > 0)
				ChangeRoom(INFESTED, vec3(123, -110, 100));

			m_changeScene = false;
		}



		}




		//0 is m_playeronground , 1 is m_playerjumping , 2 is m_playerheadcolide, 3 is m_isPlayerOnWall, 4 is m_isPlayerOnCollision, 5 is m_isBroken, 
	/*6 is m_magnetCollision, 7 is m_isBulletHit, 8 is m_isPlayerSideCollide, 9 is m_moveToMagnet, 10 is m_isMagnetInRange*/


		bool* m_moveToMagnet = m_activeScene->Player_Status(9);
		bool* m_magnetCollision = m_activeScene->Player_Status(6);


		if (!Endless_selected && !*m_moveToMagnet && !*m_magnetCollision)
		{
			MagnetScan();
		}
	}
	else if (in_Menu) {
		m_activeScene->SetInMenu(&in_Menu);
		m_activeScene->SetEndlessSelected(&Endless_selected);
	}
}

float Game::RayCastCollision(b2Fixture* fixture, b2Vec2 point, float fraction)
{

		int f = (int)fixture->GetUserData();
		b2Vec2 fixturePoint = point;
		b2Vec2 playerPoint = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->GetPosition();

		float angleDeg = atan((fixturePoint.y - playerPoint.y) / (fixturePoint.x - playerPoint.x)) * 180.0f / b2_pi;

		//Get closest magnet fixture and the distance
		if (f == MAGNET)
		{
			if (fraction < m_activeScene->GetClosestMagnetDistance())
			{
				m_activeScene->SetClosestMagnetDistance(fraction);
				m_activeScene->SetClosestMagnet(fixture);
			}
		}

		auto* status = m_activeScene->Player_Status(10);

		//Flagging magnet in range
		if (m_activeScene->GetClosestMagnetDistance() <= 1)
			*status = true;
		else
			*status = false;

		return 0.0f;
	}

vec2 Game::ConvertToGl(vec2 clickCoord)
{
	Camera tempCam = m_register->get<Camera>(EntityIdentifier::MainCamera());

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



