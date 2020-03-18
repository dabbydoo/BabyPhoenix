#include "Game.h"
#include "MyListener.h"
#include "Room.h"
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

	m_scenes.push_back(new Room("Start"));
	m_scenes.push_back(new Room("Hallway"));
	m_scenes.push_back(new Room("Storage"));
	
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
	m_playerBody = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
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

	if (m_changeScene)
		if (m_activeScene->GetName() == "Start")
		{
			ChangeRoom(HALLWAY);
			m_changeScene = false;
		}
	if (m_changeScene)
		if (m_activeScene->GetName() == "Hallway")
		{
			ChangeRoom(STORAGE);
			m_changeScene = false;
		}
		
	
	ProjectileUpdate();
	BreakableUpdate();
	DashUpdate();

	if(!m_moveToMagnet && !m_magnetCollision)
		MagnetScan();
	
	//Updates the active scene
	m_activeScene->Update();

	
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

		else {
			is_contected = false;
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

void Game::GamepadDown(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadDown(con);
	
	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

	if (con->IsButtonPressed(Buttons::A)) {
		//to do the animation first
		if (m_isPlayerOnGround)
		{
			animation.SetActiveAnim(m_character_direction+JUMP_BEGIN);
			animation.GetAnimation(m_character_direction + JUMP_END).Reset();
		}
	}

	if (animation.GetAnimation(m_character_direction + JUMP_BEGIN).GetAnimationDone()) {
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

void Game::GamepadStick(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadStick(con);
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
	if (m_isPlayerOnGround) {
	
		if (sticks[0].x <= 0.2f && sticks[0].x > -0.2f)
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

void Game::GamepadTrigger(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadTrigger(con);

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
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->KeyboardHold();

	auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());

	b2Vec2 velocity2 = m_playerBody->GetLinearVelocity();

	//Player Movement 
	{
		if (!m_isDashing)
		{
			if (m_isPlayerOnGround)
			//	animation.SetActiveAnim(m_character_direction + IDLE);


			//Left 
			if (Input::GetKey(Key::A) && !Input::GetKey(Key::D))
			{
				m_character_direction = true;

				if(m_isPlayerOnGround)
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

void Game::KeyboardDown()
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->KeyboardDown();

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
			velocity2.y =40;
			m_playerBody->SetLinearVelocity(velocity2);
			m_isPlayerJumping = true;
			m_isPlayerOnGround = false;
			animation.GetAnimation(m_character_direction + JUMP_END).Reset();
		}
	}

	//Shoot bullet
	if (Input::GetKeyDown(Key::RightArrow))
	{
		ShootBullet(50);
	}
	if (Input::GetKeyDown(Key::LeftArrow))
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
		}

		//Dash Down
		if (Input::GetKey(Key::S)) {
			direction = b2Vec2(direction.x, (direction.y - magnitude));
		}

		//Dash Right
		if (Input::GetKey(Key::D)) {
			direction = b2Vec2((direction.x + magnitude), direction.y);
		}

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
}

void Game::KeyboardUp()
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
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

	//Stop moving towards magnet
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

void Game::BeginCollision(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	//Recording both fixture data
	int f1 = (int)fixtureA->GetUserData();
	int f2 = (int)fixtureB->GetUserData();

	//cout << "Started Fixture: " << (int)fixtureA->GetUserData() << " - " << (int)fixtureB->GetUserData() << endl;

	//Check if Player footsensor begin collision with ground or platform 
	if ((f1 == FOOTSENSOR && (f2 == GROUND || f2 == PLATFORM))
		|| ((f2 == FOOTSENSOR) && (f1 == GROUND || f1 == PLATFORM)))
	{
		auto& animation = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
		m_isPlayerOnGround = true;

		animation.SetActiveAnim(m_character_direction+JUMP_END);
		animation.GetAnimation(m_character_direction + JUMP_BEGIN).Reset();

		if (m_isPlayerJumping)
			m_isPlayerJumping = false;
	}

	//Check if Player sidesensor begin collision with wall 
	if ((f1 == SIDESENSOR && f2 == WALL)
		|| ((f2 == SIDESENSOR) && f1 == WALL))
		m_isPlayerOnWall = true;

	//Check if Player headsensor begin collision with platform 
	if ((f1 == HEADSENSOR && f2 == PLATFORM)
		|| (f2 == HEADSENSOR && f1 == PLATFORM))
		m_isPlayerHeadCollide = true;

	//Check if Player sideSensor begin collision with platform 
	if ((f1 == SIDESENSOR && f2 == PLATFORM)
		|| (f2 == SIDESENSOR && f1 == PLATFORM))
		m_isPlayerSideCollide = true;

	//Check if Player begin collision with any entity that isn't a ground, platform, or wall
	if ((f1 == PLAYER && f2 != GROUND && f2 != PLATFORM && f2 != WALL && f2 != MAGNET)
		|| (f2 == PLAYER && f1 != GROUND && f1 != PLATFORM && f1 != WALL && f1 != MAGNET))
		m_isPlayerOnCollision = true;

	//Check if player collides with magnet
	if ((f1 == PLAYER && f2 == MAGNET)
		|| ((f2 == PLAYER) && f1 == MAGNET))
		m_magnetCollision = true;

	//Check if player collides with doorway
	if ((f1 == SIDESENSOR && f2 == DOORWAY)
		|| ((f2 == SIDESENSOR) && f1 == DOORWAY))
		m_changeScene = true;

	//Breakable collision
	if (f1 == BULLET && f2 == BREAKABLE)
	{
		m_isBroken = true;
		m_breakableUserData = (unsigned int)fixtureB->GetBody()->GetUserData();
	}
	if (f2 == BULLET && f1 == BREAKABLE)
	{
		m_isBroken = true;
		m_breakableUserData = (unsigned int)fixtureA->GetBody()->GetUserData();
	}

	//Bullet collision
	if (f1 == BULLET && f2 != PLAYER && f2 != SIDESENSOR)
	{
		m_isBulletHit = true;
		m_bulletHitUserData = (unsigned int)fixtureA->GetBody()->GetUserData();
	}
	if (f2 == BULLET && f1 != PLAYER && f1 != SIDESENSOR)
	{
		m_isBulletHit = true;
		m_bulletHitUserData = (unsigned int)fixtureB->GetBody()->GetUserData();
	}
	
	
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

	//Check if Player sidesensor end collision with wall
	if ((f1 == SIDESENSOR && f2 == WALL)
		|| ((f2 == SIDESENSOR) && f1 == WALL))
		m_isPlayerOnWall = false;

	//Check if Player headSensor end collision with platform 
	if ((f1 == HEADSENSOR && f2 == PLATFORM)
		|| (f2 == HEADSENSOR && f1 == PLATFORM))
		m_isPlayerHeadCollide = false;

	//Check if Player sideSensor end collision with platform 
	if ((f1 == SIDESENSOR && f2 == PLATFORM)
		|| (f2 == SIDESENSOR && f1 == PLATFORM))
		m_isPlayerSideCollide = false;

	//Check if Player end collision with any entity that isn't a ground, platform, or wall
	if ((f1 == PLAYER && f2 != GROUND && f2 != PLATFORM && f2 != WALL && f2 != MAGNET)
		|| (f2 == PLAYER && f1 != GROUND && f1 != PLATFORM && f1 != WALL && f1 != MAGNET))
		m_isPlayerOnCollision = false;

	//Check if player end collision with magnet
	if ((f1 == PLAYER && f2 == MAGNET)
		|| ((f2 == PLAYER) && f1 == MAGNET))
		m_magnetCollision = false;

	
}

float Game::RayCastCollision(b2Fixture* fixture, b2Vec2 point, float fraction)
{
	//cout << "Fixture: " << (int)fixture->GetUserData() << "  Fraction: " << fraction << endl;
	//Record fixture data
	int f = (int)fixture->GetUserData();
	b2Vec2 fixturePoint = point;
	b2Vec2 playerPoint = m_playerBody->GetPosition();
 
	float angleDeg = atan((fixturePoint.y - playerPoint.y) / (fixturePoint.x - playerPoint.x)) * 180.0f / b2_pi;

	//Get closest magnet fixture and the distance
	if (f == MAGNET)
	{
		if (fraction < m_closestMagnetDistance)
		{
			m_closestMagnetDistance = fraction;
			m_closestMagnet = fixture;
		}
		//cout << "Angle: " << angleDeg << "  Fraction: " << fraction << endl;
	}

	//Flagging magnet in range
	if (m_closestMagnetDistance <= 1)
		m_isMagnetInRange = true;
	else
		m_isMagnetInRange = false;
	
	return 0.0f;
}

void Game::DashUpdate()
{
	//Update if player can dash. (Check if player on ground)
	 //Resets dash to 1 when player grounded
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

void Game::MagnetScan()
{
	b2Vec2 point1(m_playerBody->GetPosition());
	RayCastClosestCallback callback;
	float distance = 40.f;
	float angleRAD = 0;
	b2Fixture* fixture = NULL;
	b2Vec2 fixturePoint, fixtureNormal;
	float fraction = 0;

	//2 means no magnet in range
	m_closestMagnetDistance = 2;

	//Reset closest magnet
	m_closestMagnet = NULL;

	//Magnet scanning 360 degrees
	for (int angleDEG = 0; angleDEG <= 360; ++angleDEG)
	{
		angleRAD = angleDEG * b2_pi / 180.0f;

		b2Vec2 d(distance * cosf(angleRAD), distance * sinf(angleRAD));

		b2Vec2 point2 = point1 + d;

		m_activeScene->GetPhysicsWorld().RayCast(&callback, point1, point2);	
	}
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

void Game::ChangeRoom(RoomName room)
{
	m_activeScene->Unload();
	//Sets active scene reference to our scene
	m_activeScene = m_scenes[room];

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();

	BackEnd::SetWindowName(m_activeScene->GetName());

	PhysicsSystem::Init();

	//Set contact listener
	listener.SetGame(this);
	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);

	//Get player body
	m_playerBody = m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	rayCastCallBack.SetGame(this);
}

void Game::ShootBullet(float velocity)
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

	if(velocity > 0)
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

	
	body = m_activeScene->GetPhysicsWorld().CreateBody(&bodyDef);
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

void Game::ProjectileUpdate()
{
	if (m_isBulletHit)
	{
		ECS::GetComponent<PhysicsBody>(m_bulletHitUserData).DeleteBody();
		ECS::DestroyEntity(m_bulletHitUserData);
		m_isBulletHit = false;
	}
}

void Game::BreakableUpdate()
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
