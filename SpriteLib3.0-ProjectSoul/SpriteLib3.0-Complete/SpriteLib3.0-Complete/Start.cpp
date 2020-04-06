#include "Start.h"

static unsigned entity;

static bool is_Controls_Drawn = false;

static bool is_Controls_in_use = false;

Start::Start(string name)
	:Scene(name)
{
}

void Start::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);
	//main camera
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

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		string filename = "Menu.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 384.0, 224.0);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 1.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "bgImage");
	}
	//start button
	{
		Start_entity = ECS::CreateEntity();

		all_components.push_back(Start_entity);

		ECS::AttachComponent<Sprite>(Start_entity);
		ECS::AttachComponent<Transform>(Start_entity);

		string filename = "Start_Menu.png";
		ECS::AttachComponent<AnimationController>(Start_entity);

		auto& animation = ECS::GetComponent<AnimationController>(Start_entity);


		animation.InitUVs(filename);

		animation.AddAnimation(Animation());
		animation.AddAnimation(Animation());

		auto& anim = animation.GetAnimation(0);

		anim.AddFrame(vec2(1, 74), vec2(266, 1));

		anim.SetRepeating(false);

		auto& anim2 = animation.GetAnimation(1);

		anim2.AddFrame(vec2(268, 74), vec2(532, 1));

		anim2.SetRepeating(false);


		animation.SetActiveAnim(1);



		ECS::GetComponent<Sprite>(Start_entity).LoadSprite(filename, 60, 15, true, &animation);

		ECS::GetComponent<Transform>(Start_entity).SetPosition(vec3(6.0, 35.2, 100));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(Start_entity, bitHolder, "Start Button");

	}


	//endless maode button
	{
		endlessMode_entity = ECS::CreateEntity();

		all_components.push_back(endlessMode_entity);

		ECS::AttachComponent<Sprite>(endlessMode_entity);
		ECS::AttachComponent<Transform>(endlessMode_entity);

		string filename = "Endless_Mode.png";
		ECS::AttachComponent<AnimationController>(endlessMode_entity);

		auto& animation = ECS::GetComponent<AnimationController>(endlessMode_entity);


		animation.InitUVs(filename);

		animation.AddAnimation(Animation());
		animation.AddAnimation(Animation());

		auto& anim = animation.GetAnimation(0);

		anim.AddFrame(vec2(1, 81), vec2(759, 1));

		anim.SetRepeating(false);

		auto& anim2 = animation.GetAnimation(1);

		anim2.AddFrame(vec2(761, 81), vec2(1519, 1));

		anim2.SetRepeating(false);


		animation.SetActiveAnim(0);


		ECS::GetComponent<Sprite>(endlessMode_entity).LoadSprite(filename, 140, 15, true, &animation);

		ECS::GetComponent<Transform>(endlessMode_entity).SetPosition(vec3(6.0, -0.60, 100));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(endlessMode_entity, bitHolder, "EndlessMode Button");

	}

	//Controls
	{
		controls_entity = ECS::CreateEntity();

		all_components.push_back(controls_entity);

		ECS::AttachComponent<Sprite>(controls_entity);
		ECS::AttachComponent<Transform>(controls_entity);

		string filename = "Controls.png";
		ECS::AttachComponent<AnimationController>(controls_entity);

		auto& animation = ECS::GetComponent<AnimationController>(controls_entity);


		animation.InitUVs(filename);

		animation.AddAnimation(Animation());
		animation.AddAnimation(Animation());

		auto& anim = animation.GetAnimation(0);

		anim.AddFrame(vec2(1, 81), vec2(459, 1));

		anim.SetRepeating(false);

		auto& anim2 = animation.GetAnimation(1);

		anim2.AddFrame(vec2(460, 81), vec2(917, 1));

		anim2.SetRepeating(false);


		animation.SetActiveAnim(0);


		ECS::GetComponent<Sprite>(controls_entity).LoadSprite(filename, 85, 15, true, &animation);

		ECS::GetComponent<Transform>(controls_entity).SetPosition(vec3(6.0, -34.5, 100));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(controls_entity, bitHolder, "Controls Button");

	}

	

	{
		exit_entity = ECS::CreateEntity();

		all_components.push_back(exit_entity);

		ECS::AttachComponent<Sprite>(exit_entity);
		ECS::AttachComponent<Transform>(exit_entity);

		string filename = "Exit.png";
		ECS::AttachComponent<AnimationController>(exit_entity);

		auto& animation = ECS::GetComponent<AnimationController>(exit_entity);


		animation.InitUVs(filename);

		animation.AddAnimation(Animation());
		animation.AddAnimation(Animation());

		auto& anim = animation.GetAnimation(0);

		anim.AddFrame(vec2(1, 81), vec2(212, 1));

		anim.SetRepeating(false);

		auto& anim2 = animation.GetAnimation(1);

		anim2.AddFrame(vec2(214, 81), vec2(425, 1));

		anim2.SetRepeating(false);


		animation.SetActiveAnim(0);


		ECS::GetComponent<Sprite>(exit_entity).LoadSprite(filename, 50, 15, true, &animation);

		ECS::GetComponent<Transform>(exit_entity).SetPosition(vec3(6.0, -67.6, 100));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(exit_entity, bitHolder, "Exit Button");

	}

	//arrow
	{
		arrow_entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(arrow_entity);
		ECS::AttachComponent<Transform>(arrow_entity);

		string filename = "Arrow.png";


		ECS::GetComponent<Sprite>(arrow_entity).LoadSprite(filename, 20, 15);

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(arrow_entity, bitHolder, "Arrow Button");
	}


}

void Start::Update()
{

}

void Start::GamepadStroke(XInputController* con)
{
	

	//selected
	if (con->IsButtonPressed(Buttons::A))
	{
		//Starts the game
		if (all_components[index] == Start_entity)
		{
			*menu = false;
		}

		//Starts endless game
		if (all_components[index] == endlessMode_entity)
		{
			*menu = false;
			*endless = true;
		}
		//shows the controls
		if (all_components[index] == controls_entity)
		{
			MakeTransparent();
			if(!is_Controls_Drawn)
			{
				 entity = ECS::CreateEntity();


				 ECS::AttachComponent<Sprite>(entity);
				 ECS::AttachComponent<Transform>(entity);

				 string filename = "Instruction.png";


				 ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 260, 152);

				 ECS::GetComponent<Transform>(entity).SetPosition(vec3(-10.16, -17.9, 100));

				 unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
				 ECS::SetUpIdentifier(entity, bitHolder, "Controls Image");

				 is_Controls_Drawn = true;
			}
			else 
				ECS::GetComponent<Sprite>(entity).SetTransparency(1);
		
		}

		//exits the game
		if (all_components[index] == exit_entity)
			exit(0);

	}

	//going back or unselected
	if (con->IsButtonPressed(Buttons::B))
	{
		UndoTransparent();
		ECS::GetComponent<Sprite>(entity).SetTransparency(0);
	}

 //going up 
	if (con->IsButtonStroked(Buttons::DPAD_UP))
	{
		auto tempIndex = index;

		index = (index == 0 )? all_components.size()-1 : index - 1;

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

	 ECS::GetComponent<AnimationController>(all_components[tempIndex]).SetActiveAnim(0);


	 ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(1);
	}

	//going down
	if (con->IsButtonStroked(Buttons::DPAD_DOWN))
	{
		auto tempIndex = index;

		index = (index== all_components.size() - 1) ? 0 : index + 1;

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

		ECS::GetComponent<AnimationController>(all_components[tempIndex]).SetActiveAnim(0);


		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(1);
	}


	
}

void Start::GamepadUp(XInputController* con)
{
	return;
}

void Start::GamepadDown(XInputController* con)
{
	return;
}

void Start::GamepadStick(XInputController* con)
{
	Stick stick[2];

	con->GetSticks(stick);

	static bool stop = false;

	//going up
	if (stick[0].y > 0.5f && !stop) {
		auto tempIndex = index;

		index = (index == 0) ? all_components.size() - 1 : index - 1;

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

		ECS::GetComponent<AnimationController>(all_components[tempIndex]).SetActiveAnim(0);


		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(1);
	
		stop = true;
	}
	//going down
	if (stick[0].y < -0.5f && !stop) {

		auto tempIndex = index;

		index = (index == all_components.size() - 1) ? 0 : index + 1;

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

		ECS::GetComponent<AnimationController>(all_components[tempIndex]).SetActiveAnim(0);


		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(1);
		stop = true;
	}

	if (stick[0].y < 0.5f && stick[0].y > -0.5f && stop)
		stop = false;

}

void Start::GamepadTrigger(XInputController* con)
{
	return;
}

void Start::KeyboardHold()
{
}

void Start::KeyboardDown()
{
	//going up
	if (Input::GetKeyDown(Key::UpArrow)) {
		auto tempIndex = index;

		index = (index == 0) ? all_components.size() - 1 : index - 1;

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

		ECS::GetComponent<AnimationController>(all_components[tempIndex]).SetActiveAnim(0);


		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(1);

	}

	//going down
	if (Input::GetKeyDown(Key::DownArrow)) {
		auto tempIndex = index;

		index = (index == all_components.size() - 1) ? 0 : index + 1;

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

		ECS::GetComponent<AnimationController>(all_components[tempIndex]).SetActiveAnim(0);


		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(1);
	}

	//going up
	if (Input::GetKeyDown(Key::W)) {
		auto tempIndex = index;

		index = (index == 0) ? all_components.size() - 1 : index - 1;

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

		ECS::GetComponent<AnimationController>(all_components[tempIndex]).SetActiveAnim(0);


		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(1);

	}

	//going down
	if (Input::GetKeyDown(Key::S)) {
		auto tempIndex = index;

		index = (index == all_components.size() - 1) ? 0 : index + 1;

		auto tempPos = ECS::GetComponent<Transform>(all_components[index]).GetPosition().y;

		ECS::GetComponent<Transform>(arrow_entity).SetPosition(vec3(101.6, tempPos, 100));

		ECS::GetComponent<AnimationController>(all_components[tempIndex]).SetActiveAnim(0);


		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(1);
	}
	

	//selected
	if (Input::GetKeyDown(Key::Enter)) {

		//Starts the game
		if (all_components[index] == Start_entity)
		{
			*menu = false;
		}

		//Starts endless game
		if (all_components[index] == endlessMode_entity)
		{
			*menu = false;
			*endless = true;
		}
		//shows the controls
		if (all_components[index] == controls_entity)
		{
			MakeTransparent();
			if (!is_Controls_Drawn)
			{
				entity = ECS::CreateEntity();


				ECS::AttachComponent<Sprite>(entity);
				ECS::AttachComponent<Transform>(entity);

				string filename = "Instruction.png";


				ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 260, 152);

				ECS::GetComponent<Transform>(entity).SetPosition(vec3(-10.16, -17.9, 100));

				unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
				ECS::SetUpIdentifier(entity, bitHolder, "Controls Image");

				is_Controls_Drawn = true;
				is_Controls_in_use = true;
			}
			else {
				ECS::GetComponent<Sprite>(entity).SetTransparency(1);
				is_Controls_in_use = true;
			}
		}


		if (all_components[index] == exit_entity)
			exit(0);

	}

	//going back
	if (Input::GetKeyDown(Key::Escape)) {
		if (!is_Controls_in_use || !is_Controls_Drawn)
			exit(0);

		UndoTransparent();
		ECS::GetComponent<Sprite>(entity).SetTransparency(0);
		is_Controls_in_use = false;

		
	}

}

void Start::KeyboardUp()
{
}

void Start::MakeTransparent()
{
	for (unsigned i = 0; i < all_components.size(); i++) {
		ECS::GetComponent<Sprite>(all_components[i]).SetTransparency(0);
	}

	ECS::GetComponent<Sprite>(arrow_entity).SetTransparency(0);
}

void Start::UndoTransparent()
{
	for (unsigned i = 0; i < all_components.size(); i++) {
		ECS::GetComponent<Sprite>(all_components[i]).SetTransparency(1);
	}
	ECS::GetComponent<Sprite>(arrow_entity).SetTransparency(1);
}

vec2 Start::ConvertToGl(vec2 clickCoord)
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

void Start::MouseMotion(SDL_MouseMotionEvent evnt)
{
	static bool on_it = false;

	auto mousePos = ConvertToGl(vec2(evnt.x,evnt.y));

	auto startPos = ECS::GetComponent<Transform>(Start_entity).GetPosition();

	auto startHeight = ECS::GetComponent<Sprite>(Start_entity).GetHeight();
	auto startWidth = ECS::GetComponent<Sprite>(Start_entity).GetWidth();

	//min is on the x side and max is on the y
	vec2 StartX = vec2(startPos.x-(startWidth*0.5), startPos.x + (startWidth * 0.5));

	//min is on the x side and max is on the y
	vec2 StartY = vec2(startPos.y - (startHeight * 0.5), startPos.y + (startHeight * 0.5));
	
	//in the parameters of start
	if (mousePos.x>=StartX.x&& mousePos.x <= StartX.y&& mousePos.y >= StartY.x&& mousePos.y <= StartY.y) {
		if (!on_it)
		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(0);

		ECS::GetComponent<AnimationController>(Start_entity).SetActiveAnim(1);
		ECS::GetComponent<Transform>(arrow_entity).SetPositionY(startPos.y);
		
		on_it = true;
		index = 0;
	}

	auto EndlessPos = ECS::GetComponent<Transform>(endlessMode_entity).GetPosition();

	auto EndlessHeight = ECS::GetComponent<Sprite>(endlessMode_entity).GetHeight();
	auto EndlessWidth = ECS::GetComponent<Sprite>(endlessMode_entity).GetWidth();

	//min is on the x side and max is on the y
	vec2 EndlessX = vec2(EndlessPos.x - (EndlessWidth * 0.5), EndlessPos.x + (EndlessWidth * 0.5));

	//min is on the x side and max is on the y
	vec2 EndlessY = vec2(EndlessPos.y - (EndlessHeight * 0.5), EndlessPos.y + (EndlessHeight * 0.5));

	//in the parameters of endless mode
	if (mousePos.x >= EndlessX.x && mousePos.x <= EndlessX.y && mousePos.y >= EndlessY.x && mousePos.y <= EndlessY.y) {
		if(!on_it)
		ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(0);
		
		ECS::GetComponent<AnimationController>(endlessMode_entity).SetActiveAnim(1);
		ECS::GetComponent<Transform>(arrow_entity).SetPositionY(EndlessPos.y);

		on_it = true;
		index = 1;
	}

	auto controlsPos = ECS::GetComponent<Transform>(controls_entity).GetPosition();

	auto controlsHeight = ECS::GetComponent<Sprite>(controls_entity).GetHeight();
	auto controlsWidth = ECS::GetComponent<Sprite>(controls_entity).GetWidth();

	//min is on the x side and max is on the y
	vec2 controlsX = vec2(controlsPos.x - (controlsWidth * 0.5), controlsPos.x + (controlsWidth * 0.5));

	//min is on the x side and max is on the y
	vec2 controlsY = vec2(controlsPos.y - (controlsHeight * 0.5), controlsPos.y + (controlsHeight * 0.5));

	//in the parameters of endless mode
	if (mousePos.x >= controlsX.x && mousePos.x <= controlsX.y && mousePos.y >= controlsY.x && mousePos.y <= controlsY.y) {
		if (!on_it)
			ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(0);

		ECS::GetComponent<AnimationController>(controls_entity).SetActiveAnim(1);
		ECS::GetComponent<Transform>(arrow_entity).SetPositionY(controlsPos.y);

		on_it = true;
		index = 2;
	}

	auto exitPos = ECS::GetComponent<Transform>(exit_entity).GetPosition();

	auto exitHeight = ECS::GetComponent<Sprite>(exit_entity).GetHeight();
	auto exitWidth = ECS::GetComponent<Sprite>(exit_entity).GetWidth();

	//min is on the x side and max is on the y
	vec2 exitX = vec2(exitPos.x - (exitWidth * 0.5), exitPos.x + (exitWidth * 0.5));

	//min is on the x side and max is on the y
	vec2 exitY = vec2(exitPos.y - (exitHeight * 0.5), exitPos.y + (exitHeight * 0.5));

	//in the parameters of endless mode
	if (mousePos.x >= exitX.x && mousePos.x <= exitX.y && mousePos.y >= exitY.x && mousePos.y <= exitY.y) {
		if (!on_it)
			ECS::GetComponent<AnimationController>(all_components[index]).SetActiveAnim(0);

		ECS::GetComponent<AnimationController>(exit_entity).SetActiveAnim(1);
		ECS::GetComponent<Transform>(arrow_entity).SetPositionY(exitPos.y);

		on_it = true;
		index = 3;
	}



	else {
		on_it = false;
	}

}

void Start::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{

		auto mousePos = ConvertToGl(vec2(evnt.x, evnt.y));

		auto startPos = ECS::GetComponent<Transform>(Start_entity).GetPosition();

		auto startHeight = ECS::GetComponent<Sprite>(Start_entity).GetHeight();
		auto startWidth = ECS::GetComponent<Sprite>(Start_entity).GetWidth();

		//min is on the x side and max is on the y
		vec2 StartX = vec2(startPos.x - (startWidth * 0.5), startPos.x + (startWidth * 0.5));

		//min is on the x side and max is on the y
		vec2 StartY = vec2(startPos.y - (startHeight * 0.5), startPos.y + (startHeight * 0.5));

		//in the parameters of start
		if (mousePos.x >= StartX.x && mousePos.x <= StartX.y && mousePos.y >= StartY.x && mousePos.y <= StartY.y) {
			*menu = false;
		}

		auto EndlessPos = ECS::GetComponent<Transform>(endlessMode_entity).GetPosition();

		auto EndlessHeight = ECS::GetComponent<Sprite>(endlessMode_entity).GetHeight();
		auto EndlessWidth = ECS::GetComponent<Sprite>(endlessMode_entity).GetWidth();

		//min is on the x side and max is on the y
		vec2 EndlessX = vec2(EndlessPos.x - (EndlessWidth * 0.5), EndlessPos.x + (EndlessWidth * 0.5));

		//min is on the x side and max is on the y
		vec2 EndlessY = vec2(EndlessPos.y - (EndlessHeight * 0.5), EndlessPos.y + (EndlessHeight * 0.5));

		//in the parameters of endless mode
		if (mousePos.x >= EndlessX.x && mousePos.x <= EndlessX.y && mousePos.y >= EndlessY.x && mousePos.y <= EndlessY.y) {
			*menu = false;
			*endless = true;
		}

		auto controlsPos = ECS::GetComponent<Transform>(controls_entity).GetPosition();

		auto controlsHeight = ECS::GetComponent<Sprite>(controls_entity).GetHeight();
		auto controlsWidth = ECS::GetComponent<Sprite>(controls_entity).GetWidth();

		//min is on the x side and max is on the y
		vec2 controlsX = vec2(controlsPos.x - (controlsWidth * 0.5), controlsPos.x + (controlsWidth * 0.5));

		//min is on the x side and max is on the y
		vec2 controlsY = vec2(controlsPos.y - (controlsHeight * 0.5), controlsPos.y + (controlsHeight * 0.5));

		//in the parameters of endless mode
		if (mousePos.x >= controlsX.x && mousePos.x <= controlsX.y && mousePos.y >= controlsY.x && mousePos.y <= controlsY.y) {

			MakeTransparent();
			if (!is_Controls_Drawn)
			{
				entity = ECS::CreateEntity();


				ECS::AttachComponent<Sprite>(entity);
				ECS::AttachComponent<Transform>(entity);

				string filename = "Instruction.png";


				ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 260, 152);

				ECS::GetComponent<Transform>(entity).SetPosition(vec3(-10.16, -17.9, 100));

				unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
				ECS::SetUpIdentifier(entity, bitHolder, "Controls Image");

				is_Controls_Drawn = true;
				is_Controls_in_use = true;
			}
			else {
				ECS::GetComponent<Sprite>(entity).SetTransparency(1);
				is_Controls_in_use = true;
			}


		}

		auto exitPos = ECS::GetComponent<Transform>(exit_entity).GetPosition();

		auto exitHeight = ECS::GetComponent<Sprite>(exit_entity).GetHeight();
		auto exitWidth = ECS::GetComponent<Sprite>(exit_entity).GetWidth();

		//min is on the x side and max is on the y
		vec2 exitX = vec2(exitPos.x - (exitWidth * 0.5), exitPos.x + (exitWidth * 0.5));

		//min is on the x side and max is on the y
		vec2 exitY = vec2(exitPos.y - (exitHeight * 0.5), exitPos.y + (exitHeight * 0.5));

		//in the parameters of endless mode
		if (mousePos.x >= exitX.x && mousePos.x <= exitX.y && mousePos.y >= exitY.x && mousePos.y <= exitY.y) {
			exit(0);
		}



	}

}

void Start::MouseWheel(SDL_MouseWheelEvent evnt)
{
}
