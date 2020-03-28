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
	
	/* Menu scenes
	m_scenes.push_back(new Room("Menu"));
	m_scenes.push_back(new Room("Pause_Menu"));
	*/

	//m_scenes.push_back(new Start("Menu"));
	m_scenes.push_back(new Room("Start"));
	m_scenes.push_back(new Room("Hallway"));
	m_scenes.push_back(new Room("Storage"));
	m_scenes.push_back(new Room("Vent"));
	m_scenes.push_back(new Room("Infested"));

	
	//Sets active scene reference to our scene
	m_activeScene = m_scenes[0];

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();

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

	if (m_changeScene) {
		if (m_activeScene->GetName() == "Start")
		{
			ChangeRoom(HALLWAY);
			m_changeScene = false;
		}

		else if (m_activeScene->GetName() == "Hallway")
		{
			ChangeRoom(STORAGE);
			m_changeScene = false;
		}

	}

	//0 is m_playeronground , 1 is m_playerjumping , 2 is m_playerheadcolide, 3 is m_isPlayerOnWall, 4 is m_isPlayerOnCollision, 5 is m_isBroken,
	/*6 is m_magnetCollision, 7 is m_isBulletHit, 8 is m_isPlayerSideCollide, 9 is m_moveToMagnet, 10 is m_isMagnetInRange*/

	bool* m_moveToMagnet = m_activeScene->Player_Status(9);
	bool* m_magnetCollision = m_activeScene->Player_Status(6);

	//cout << *m_moveToMagnet << " " << *m_magnetCollision << endl;

	if (!*m_moveToMagnet && !*m_magnetCollision)
	MagnetScan();

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
	//0 is m_playeronground , 1 is m_playerjumping , 2 is m_playerheadcolide, 3 is m_isPlayerOnWall, 4 is m_isPlayerOnCollision, 5 is m_isBroken, 
	/*6 is m_magnetCollision, 7 is m_isBulletHit, 8 is m_isPlayerSideCollide, 9 is m_moveToMagnet, 10 is m_isMagnetInRange*/

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
		auto* temp = m_activeScene->GetClosestMagnet();

		temp = nullptr;
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

		//0 is m_playeronground , 1 is m_playerjumping , 2 is m_playerheadcolide, 3 is m_isPlayerOnWall, 4 is m_isPlayerOnCollision, 5 is m_isBroken, 6 is m_magnetCollision, 7 is m_isBulletHit, 8 is m_isPlayerSideCollide

		auto* status = m_activeScene->Player_Status(0);

		*status = true;

		animation.SetActiveAnim(m_activeScene->PlayerDirection() + JUMP_END);
		animation.GetAnimation(m_activeScene->PlayerDirection() + JUMP_BEGIN).Reset();

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
	//Check if Player begin collision with any entity that isn't a ground, platform, or wall
	if ((f1 == PLAYER && f2 != GROUND && f2 != PLATFORM && f2 != WALL && f2 != MAGNET)
		|| (f2 == PLAYER && f1 != GROUND && f1 != PLATFORM && f1 != WALL && f1 != MAGNET))
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

	//Breakable collision
	if (f1 == BULLET && f2 == BREAKABLE)
	{
		auto* status = m_activeScene->Player_Status(5);
		*status = true;
		m_activeScene->SetBreakableUserData((unsigned int)fixtureB->GetBody()->GetUserData());
	}
	if (f2 == BULLET && f1 == BREAKABLE)
	{
		auto* status = m_activeScene->Player_Status(5);
		*status = true;
		m_activeScene->SetBreakableUserData((unsigned int)fixtureA->GetBody()->GetUserData());
	}

	//Bullet collision
	if (f1 == BULLET && f2 != PLAYER && f2 != SIDESENSOR)
	{
		auto* status = m_activeScene->Player_Status(7);
		*status = true;
		m_activeScene->SetBulletHitUserData((unsigned int)fixtureA->GetBody()->GetUserData());
	
	}
	if (f2 == BULLET && f1 != PLAYER && f1 != SIDESENSOR)
	{
		auto* status = m_activeScene->Player_Status(7);
		*status = true;
		m_activeScene->SetBulletHitUserData((unsigned int)fixtureB->GetBody()->GetUserData());
	}

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
		auto* status = m_activeScene->Player_Status(0);
		*status = false;
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
		auto* status = m_activeScene->Player_Status(3);
		*status = false;
	}


	//Check if Player sideSensor end collision with platform 
	if ((f1 == SIDESENSOR && f2 == PLATFORM)
		|| (f2 == SIDESENSOR && f1 == PLATFORM))
	{
		auto* status = m_activeScene->Player_Status(8);
		*status = false;
	}

	//Check if Player end collision with any entity that isn't a ground, platform, or wall
	if ((f1 == PLAYER && f2 != GROUND && f2 != PLATFORM && f2 != WALL && f2 != MAGNET)
		|| (f2 == PLAYER && f1 != GROUND && f1 != PLATFORM && f1 != WALL && f1 != MAGNET))
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

void Game::ChangeRoom(RoomName room)
{
	m_scenes[room]->SetRoom(m_activeScene);

	m_activeScene->Unload();

	m_activeScene = m_scenes[room];

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();

	BackEnd::SetWindowName(m_activeScene->GetName());

	PhysicsSystem::Init();

	//Set contact listener
	listener.SetGame(this);
	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	m_activeScene->SetBody(m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody());
	//Get player body
	rayCastCallBack.SetGame(this);
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



