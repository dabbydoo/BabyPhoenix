#include "Game.h"
#include <random>
#include"AssignmentScene.h"
#include "MyContactListener.h"

//Contact listener GLOBAL SCOPE
MyListener listener;

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
	//Scene names and clear colors
	m_name = "Assignment Scene";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();
	m_scenes.push_back(new AssignmentScene("Assignment Scene Project"));
	//m_activeScene = m_scenes[2];
	m_activeScene = m_scenes[0];
    m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	//*m_activeScene = File::LoadJSON("Hello World.json");
	
	//Get active scene
	m_register = m_activeScene->GetScene();

	//Initialize physics
	PhysicsSystem::Init();

	//Set contact listener
	listener.SetGame(this);
	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);

	//Get player body
	m_playerBody = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
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
	}
	
	

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);

	PhysicsSystem::Update(m_register, m_activeScene->GetPhysicsWorld());

	//Update if player can dash. (Check if player on ground)
	if (m_playerBody->GetLinearVelocity().y < .1f)
	{
		//Resets dash to 1 when player grounded
		if (m_isPlayerOnGround && !m_isDashing) {
			m_dashCounter = 1;
		}
	}

	//End of Dash 
	if (m_isDashing)
	{
		//**ADJUST DASH LENGTH HERE**
		float dashTime = .3;

		//End dash when foot sensor collides with (ground or platform) OR time of dash reached
		if (m_isPlayerOnGround)
			if ((float)(clock() - m_initDashTime) / CLOCKS_PER_SEC > dashTime || !m_initDashOnGround)
			{
				m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
				m_playerBody->SetGravityScale(m_playerGravity);
				m_isDashing = false;
			}

		//End dash when head sensor collides with platform 
		if (m_isPlayerHeadCollide || m_isPlayerSideCollide)
		{
			m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
			m_playerBody->SetGravityScale(m_playerGravity);
			m_isDashing = false;
		}

		//End dash when player collides with anything but (ground or platform) OR time of dash reached
		if (isPlayerOnCollision() || ((float)(clock() - m_initDashTime) / CLOCKS_PER_SEC > dashTime))
		{
			cout << m_dashCounter << endl;
			m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
			m_playerBody->SetGravityScale(m_playerGravity);
			m_isDashing = false;
		}
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
	//Just calls all the other input functions 
	XInputManager::Update();
	GamepadInput();
	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::GamepadInput()
{
	XInputController* tempCon;
	for (int i = 0; i < 3; i++)
	{
		if (XInputManager::ControllerConnected(i)) {
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);
			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);
		}
	}
}

void Game::GamepadStroke(XInputController * con)
{
	if (con->IsButtonStroked(Buttons::A)) {
		printf("A Stroked\n");
	}
}

void Game::GamepadUp(XInputController * con)
{
	if (con->IsButtonReleased(Buttons::RB)) {
		printf("RB Release\n");
	}
}

void Game::GamepadDown(XInputController * con)
{
	if (con->IsButtonPressed(Buttons::THUMB_LEFT)) {
		printf("Left Thumbstick Clicked in\n");
	}
}

void Game::GamepadStick(XInputController * con)
{
	Stick sticks[2];
	con->GetSticks(sticks);
	if (sticks[0].x < -0.1f) {
		printf("Left Pointing\n");
	}
	if (sticks[0].x > 0.1f) {
		printf("Right Pointing\n");
	}
	if (sticks[0].y < -0.1f) {
		printf("Down Pointing\n");
	}
	if (sticks[0].y > 0.1f) {
		printf("Up Pointing\n");
	}
	system("cls");
}

void Game::GamepadTrigger(XInputController * con)
{
	Triggers triggers;
	con->GetTriggers(triggers);
	if (triggers.RT > 0.5f && triggers.RT < 0.8f) {
		printf("Half Press\n");
	}
	if (triggers.RT > 0.5f && triggers.RT < 0.8f) {
		printf("Full Press\n");
	}
}


//KEYBOARD HOLD
void Game::KeyboardHold()
{
	//Player Movement 
	{
		//Movement direction 
		b2Vec2 direction = b2Vec2(0.f, 0.f);

		float force = 40000;
		float velocity = 30; //Change for player velocity on ground

		//Left 
		if (Input::GetKey(Key::A)) 
			direction = b2Vec2(-1, 0);	

		//Right
		if (Input::GetKey(Key::D)) 
			direction = b2Vec2(1, 0);	
		
		//Apply force for movement
		if (direction.Length() > 0) {
			if (isPlayerOnGround() && !m_isDashing)
				m_playerBody->SetLinearVelocity(b2Vec2(direction.x * velocity, direction.y * velocity));
			else
				m_playerBody->ApplyForce(b2Vec2(direction.x * force, direction.y * force), b2Vec2(m_playerBody->GetPosition().x, m_playerBody->GetPosition().y), true);
		}
	}
}

void Game::KeyboardDown()
{	
	//Jump
	if (Input::GetKeyDown(Key::Space))
	{
		if (isPlayerOnGround())
		{
			float impulse = m_playerBody->GetMass() * 80; //Adjust to change height of jump
			m_playerBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_playerBody->GetWorldCenter(), true);
			m_isPlayerOnGround = false;
		}	
	}

	//Dash direction
	if (Input::GetKeyDown(Key::LeftShift) && m_dashCounter == 1) {
		b2Vec2 direction = b2Vec2(0.f, 0.f);
		float magnitude = 250000.f;

		//Dash Up
		if (Input::GetKey(Key::W)) {
			direction = b2Vec2(direction.x, direction.y + magnitude);
		}

		//Dash Left
		if (Input::GetKey(Key::A)) {
			direction = b2Vec2(direction.x - magnitude, direction.y);
		}

		//Dash Down
		if (Input::GetKey(Key::S)) {
			direction = b2Vec2(direction.x, direction.y - magnitude);
		}

		//Dash Right
		if (Input::GetKey(Key::D)) {
			direction = b2Vec2(direction.x + magnitude, direction.y);
		}

		//Start Dashing
		if (direction.Length() > 0) {

			//Flag whether initial dash position on ground
			if (isPlayerOnGround())
				m_initDashOnGround = true;
			else
				m_initDashOnGround = false;

			//Apply impulse
			m_playerBody->SetGravityScale(0);
			m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
			m_playerBody->ApplyLinearImpulse(direction, m_playerBody->GetWorldCenter(), true);
			m_isDashing = true;
			m_initDashTime = clock();
			m_dashCounter = 0;
		}
	}
}

void Game::KeyboardUp()
{
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
	if (Input::GetKeyUp(Key::P)) {
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}

	//Set linear velocity of x to zero when A or D key is up and is not dashing
	if ((Input::GetKeyUp(Key::A) || Input::GetKeyUp(Key::D)) && !m_isDashing) 
		m_playerBody->SetLinearVelocity(b2Vec2(0, m_playerBody->GetLinearVelocity().y));
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	//printf("Mouse Moved(%f,%f)\n", float(evnt.x), float(evnt.y));
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
	if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(SDL_BUTTON_LEFT)) {
		printf("Left Mouse Clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
	}
	if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		printf("Right Mouse Clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
	}
	if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
		printf("Middle Mouse Clicked at (%f,%f)\n", float(evnt.x), float(evnt.y));
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
	printf("Mouse Scroll %f\n", float(evnt.y));
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}

//Check if player is grounded
bool Game::isPlayerOnGround() {
	return m_isPlayerOnGround;  		 
}

//Flag if player on collision
bool Game::isPlayerOnCollision()
{
	return m_isPlayerOnCollision;
}

void Game::BeginCollision(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	//Recording both fixture data
	int f1 = (int)fixtureA->GetUserData();
	int f2 = (int)fixtureB->GetUserData();

	//cout << "Started Fixture: " << (int)fixtureA->GetUserData() << " - " << (int)fixtureB->GetUserData() << endl;

	//Check if Player footsensor begin collision with ground or platform 
	if ((f1 == FOOTSENSOR && (f2 == GROUND || f2 == PLATFORM))
		|| ((f2 == FOOTSENSOR) && (f1 == GROUND || f1 == PLATFORM)))
		m_isPlayerOnGround = true;

	//Check if Player headsensor begin collision with platform 
	if ((f1 == HEADSENSOR && f2  == PLATFORM)
		|| (f2 == HEADSENSOR && f1 == PLATFORM))
		m_isPlayerHeadCollide = true;

	//Check if Player sideSensor end collision with platform 
	if ((f1 == SIDESENSOR && f2 == PLATFORM)
		|| (f2 == SIDESENSOR && f1 == PLATFORM))
		m_isPlayerSideCollide = true;

	//Check if Player begin collision with any entity but ground or platform
	if ((f1 == PLAYER && f2 != GROUND && f2 != PLATFORM)
		|| (f2 == PLAYER && f1 != GROUND && f1 != PLATFORM))
		m_isPlayerOnCollision = true;
}

void Game::EndCollision(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	//cout << "Ended Fixture: " << (int)fixtureA->GetUserData() << " - " << (int)fixtureB->GetUserData() << endl;

	//Record both fixture data
	int f1 = (int)fixtureA->GetUserData();
	int f2 = (int)fixtureB->GetUserData();

	//Check if Player footSensor end contact with ground or platform
	if ((f1 == FOOTSENSOR && (f2 == GROUND || f2 == PLATFORM))
		|| ((f2 == FOOTSENSOR) && (f1 == GROUND || f1 == PLATFORM)))
		m_isPlayerOnGround = false;

	//Check if Player headSensor end collision with platform 
	if ((f1 == HEADSENSOR && f2 == PLATFORM)
		|| (f2 == HEADSENSOR && f1 == PLATFORM))
		m_isPlayerHeadCollide = false;

	//Check if Player sideSensor end collision with platform 
	if ((f1 == SIDESENSOR && f2 == PLATFORM)
		|| (f2 == SIDESENSOR && f1 == PLATFORM))
		m_isPlayerSideCollide = false;

	//Check if Player end collision with any entity but ground or platform
	if ((f1 == PLAYER && f2 != GROUND && f2 != PLATFORM)
		|| (f2 == PLAYER && f1 != GROUND && f1 != PLATFORM))
		m_isPlayerOnCollision = false;
}

