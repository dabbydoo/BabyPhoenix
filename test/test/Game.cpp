#include "Game.h"

#include <random>
#include"MainHeader.h"

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
	m_name = "Test";
	m_clearColor = vec4(0.15f, 0.33f, 0.52f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Creates a new Helloworld Scene
	m_scenes.push_back(new test("Going again"));
	m_scenes.push_back(new Scene("What"));


	//sets active page refence to our Hello world scene
	m_activeScene = m_scenes[0];
	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	//Initializes the scene
	//*m_activeScene=File::LoadJSON("Ok.json");

	//sets m_register to point to the register in the active scene
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

	PhysicsSystem::Update(m_register,m_activeScene->GetPhysicsWorld());

	
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
	//Gamepad button pressed Stroked (pressed)

	for (int i = 0; i < 3; i++) {

		if (XInputManager::ControllerConnected(i)) {
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(-0.1f);

			//If the controller is connected, we run the different input types
			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);
		}
	}
}

void Game::GamepadStroke(XInputController* con)
{

	//Game pad button stroke (press)
	if (con->IsButtonStroked(Buttons::A)) {
		cout << "A Stroked\n";
	}
	if (con->IsButtonStroked(Buttons::B)) {
		cout << "B Key held" << endl;
	}

	if (con->IsButtonStroked(Buttons::X)) {
		cout << "X Key held\n";
	}

	if (con->IsButtonStroked(Buttons::Y)) {
		cout << "Y Key held\n";
	}
}

void Game::GamepadUp(XInputController* con)
{
	//Gamepad button up
	if (con->IsButtonPressed(Buttons::RB)) {
		cout << "RB released\n";
	}
}

void Game::GamepadDown(XInputController* con)
{
	//Gamepad button down
	if (con->IsButtonPressed(Buttons::THUMB_LEFT)) {
		cout << "left thumbstick clicked in\n";
	}
}

void Game::GamepadStick(XInputController* con)
{
	//Gamepad stick stuff 
	Stick sticks[2];
	con->GetSticks(sticks);

	if (sticks[0].x > 0.1f) {
		cout << "Right Pointing\n";
	}

	if (sticks[0].y > 0.1f) {
		cout << "Up Pointing\n";
	}

	if (sticks[0].x < -0.1f) {
		cout << "Left pointing\n";
	}
	if (sticks[0].y < -0.1f) {
		cout << "Down Pointing\n";
	}
	if (sticks[1].x > 0.1f) {
		cout << "Right Pointing\n";
	}

	if (sticks[1].y > 0.1f) {
		cout << "Up Pointing\n";
	}

	if (sticks[1].x < -0.1f) {
		cout << "Left pointing\n";
	}
	if (sticks[1].y < -0.1f) {
		cout << "Down Pointing\n";
	}

	//system("cls");
}

void Game::GamepadTrigger(XInputController* con)
{
	//gamepad trigger stuff
	Triggers triggers;
	con->GetTriggers(triggers);

	if (triggers.RT > 0.5f && triggers.RT < 0.8f)
	{
		cout << "Half Press\n";
	}
	if (triggers.RT > 0.8f)
	{
		cout << "Full Press\n";
	}
	if (triggers.LT > 0.8f)
	{
		cout << "left Full Press\n";
	}
}
void Game::KeyboardDown()
{
	//spamming the button movement 

}
void Game::KeyboardHold()
{
	
}



void Game::KeyboardUp()
{
	if (Input::GetKeyUp(Key::F1))
	{
		cout << "\nF1 key realsed";
		if (!UI::m_isInit)
		{
			//cout << "\nF1 key realsed";
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
	if (Input::GetKeyUp(Key::P)) {
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}

	vec3 push = vec3(50000.f,0.f,0.f);

	b2Vec2 box = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition();
	//auto boxbody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition();


	if (Input::GetKey(Key::A)) {
		m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).ApplyForce(-push);
	}
	if (Input::GetKey(Key::D)) {
		m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).ApplyForce(push);
	}
	
	
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	cout << "Mouse Moved (" << evnt.x << "," << evnt.y << ")" << endl;

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

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		cout << "Left mouse button clicked at (" << evnt.x << "," << evnt.y << ")" << endl;
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		cout << "Right mouse button clicked at (" << evnt.x << "," << evnt.y << ")" << endl;
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
		cout << "Middle mouse button clicked at (" << evnt.x << "," << evnt.y << ")" << endl;
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
	cout << "Mouse scroll " << evnt.y << endl;

	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
