#include "Game.h"

#include <random>

#include"AssignmentScene.h"

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
	
	m_register = m_activeScene->GetScene();

	PhysicsSystem::Init();
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



void Game::KeyboardHold()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	float speed = 30.f;

	vec3 hPush = vec3(50000.f, 0.f, 0.f);
	vec3 vPush = vec3(0.f, 50000.f, 0.f);

	b2Vec2 box = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition();
	//auto boxbody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition();


	if (Input::GetKey(Key::A)) {
		m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).ApplyForce(-hPush);
		
	}
	if (Input::GetKey(Key::D)) {
		m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).ApplyForce(hPush);
		
	}


	//Keyboard button held
	
	if (Input::GetKey(Key::W)) 
	{
		
	}
	
	if (Input::GetKey(Key::S)) 
	{
	
	}
	
	
}

void Game::KeyboardDown()
{
	vec3 vPush = vec3(0.f, 4500000.f, 0.f);

	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	

	if (Input::GetKeyDown(Key::Space))
	{
		if ((position.y <= -66)) {
			m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).ApplyForce(vPush);
		}
	}

	for (b2ContactEdge* ce = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;

		if (c->IsTouching())
		{
			cout << "Touching" << endl;
		}
		else
			cout << "NOT Touching" << endl;

	}

	if (Input::GetKeyDown(Key::K))
	{
		



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
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	printf("Mouse Moved(%f,%f)\n", float(evnt.x), float(evnt.y));
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
