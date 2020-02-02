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

	//Update if player can player dash. (Check if player on ground)
	if (m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->GetLinearVelocity().y < .1f)
	{
		if (isPlayerGrounded())
			m_dashCounter = 1;
		cout << m_dashCounter << endl;
	}

	//Update current player position
	m_playerPos = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->GetPosition();

	if (((m_playerPos - m_initDashPos).Length() > 100.f) && m_isDashing)
	{
		m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		m_isDashing = false;
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



void Game::KeyboardHold()
{
	//Get player position
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition(); 

	//Apply horizontal and vertical force
	/*vec3 hPush = vec3(30000.f, 0.f, 0.f);
	vec3 vPush = vec3(0.f, 30000.f, 0.f);*/

	//Directional force
	vec3 dirForce = vec3(0.f, 0.f, 0.f);
	float magForce = 30000;

	//Get physics body
	b2Body* body;
	body = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();

	b2Vec2 velocity;
	float speed;

	//bool isDash = false;

	b2Vec2 box = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition();
	//auto boxbody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition();

	//Up
	if (Input::GetKey(Key::W))
	{
		dirForce = vec3(dirForce.x, dirForce.y + magForce, dirForce.z);
		
	}

	//Down
	if (Input::GetKey(Key::S))
	{
		//dirForce = vec3(dirForce.x, dirForce.y - impulse, dirForce.z);
	}

	//Left 
	if (Input::GetKey(Key::A)) {
		dirForce = vec3(dirForce.x - magForce, dirForce.y, dirForce.z);
	
	}
	
	//Right
	if (Input::GetKey(Key::D)) {
		dirForce = vec3(dirForce.x + magForce, dirForce.y, dirForce.z);
		
	}

	//Test direction
	//cout << "X " << dirForce.x << " Y " << dirForce.y << endl;

	//Apply force for movement
	if (dirForce.GetMagnitude() > 0) {
		//Player movement

		//body->ApplyLinearImpulse(b2Vec2(-1000, 0), body->GetWorldCenter(), true);
		m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).ApplyForce(dirForce);
		velocity = body->GetLinearVelocity();
		speed = velocity.Normalize();
		//body->ApplyForce(.5 * speed * speed * -velocity, body->GetWorldCenter(), true); CHECK
		//cout << "X " << velocity.x << "Y " << velocity.y << endl;
	
	}

}

void Game::KeyboardDown()
{	
	b2Body* body;
	body = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();

	//Jump
	if (Input::GetKeyDown(Key::Space))
	{
		if (isPlayerGrounded())
		{
			float impulse = body->GetMass() * 80; //Adjust to change height of jump
			body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);			
		}
		
	}

	//Dash
	if (Input::GetKeyDown(Key::LeftShift) && m_dashCounter == 1) {
		b2Vec2 impulse = b2Vec2(0.f, 0.f);
		float magImpulse = 250000.f;

		//Dash Up
		if (Input::GetKey(Key::W)) {
			impulse = b2Vec2(impulse.x, impulse.y + magImpulse);
		}

		//Dash Left
		if (Input::GetKey(Key::A)) {
			impulse = b2Vec2(impulse.x - magImpulse, impulse.y);
		}

		//Dash Down
		if (Input::GetKey(Key::S)) {
			impulse = b2Vec2(impulse.x, impulse.y - magImpulse);
		}

		//Dash Right
		if (Input::GetKey(Key::D)) {
			impulse = b2Vec2(impulse.x + magImpulse, impulse.y);
		}

		//Apply impulse
		if (impulse.Length() > 0) {
			body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
			m_isDashing = true;
			m_initDashPos = body->GetPosition();
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

//Check if player is grounded
bool Game::isPlayerGrounded() {
	int numFootContacts = 0;

	for (b2ContactEdge* ce = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* contact = ce->contact;

		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
		//cout << "User Data: " << (int)fixtureUserData << endl;

		//Sensor fixture identified with UserData = 3
		if ((int)fixtureAUserData == 3 || (int)fixtureBUserData == 3)
		{
			numFootContacts++;
		}
	}
	if (numFootContacts > 0) {

		return true;
	}
	else
		return false;			   		 
}
