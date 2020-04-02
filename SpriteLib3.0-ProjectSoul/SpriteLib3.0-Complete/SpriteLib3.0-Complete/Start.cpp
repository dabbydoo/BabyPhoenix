//#include "Start.h"
//
//Start::Start(string name)
//	:Scene(name)
//{
//}
//
//void Start::InitScene(float windowWidth, float windowHeight)
//{
//
//	//main camera
//	{
//	float aspectRatio = windowWidth / windowHeight;
//
//	//Creates Camera Entity
//	auto entity = ECS::CreateEntity();
//
//	//Creates new orthographic camera
//	ECS::AttachComponent<Camera>(entity);
//	
//	vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
//	ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
//	ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
//
//	
//
//	//Sets up the Identifier
//	unsigned int bitHolder2 = EntityIdentifier::VertScrollCameraBit() ;
//	ECS::SetUpIdentifier(entity, bitHolder2, "Main Camera");
//	ECS::SetIsMainCamera(entity, true);
//	}
//
//
//	//start button
//	{
//		Start_entity = ECS::CreateEntity();
//
//		all_components.push_back(Start_entity);
//
//		ECS::AttachComponent<Sprite>(Start_entity);
//		ECS::AttachComponent<Transform>(Start_entity);
//
//		string filename = "Start_Menu.png";
//		ECS::AttachComponent<AnimationController>(Start_entity);
//
//		auto& animation = ECS::GetComponent<AnimationController>(Start_entity);
//
//
//		animation.InitUVs(filename);
//
//		animation.AddAnimation(Animation());
//		animation.AddAnimation(Animation());
//
//		auto& anim = animation.GetAnimation(0);
//
//		anim.AddFrame(vec2(1,74),vec2(266,1));
//
//		anim.SetRepeating(false);
//
//		 anim = animation.GetAnimation(1);
//
//		 anim.AddFrame(vec2(268, 74), vec2(649, 1));
//
//		 anim.SetRepeating(false);
//
//
//		animation.SetActiveAnim(1);
//
//
//
//		ECS::GetComponent<Sprite>(Start_entity).LoadSprite(filename, 10, 20, true, &animation);
//
//		ECS::GetComponent<Transform>(Start_entity).SetPosition(vec3(10,20,30));
//		
//		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
//		ECS::SetUpIdentifier(Start_entity, bitHolder, "Start Button");
//		
//	}
//
//
//
//
//}
//
//void Start::Update()
//{
//}
//
//void Start::GamepadStroke(XInputController* con)
//{
//	//selected
//	if (con->IsButtonPressed(Buttons::A))
//	{
//
//	}
//
//	//going back or unselected
//	if (con->IsButtonPressed(Buttons::B))
//	{
//
//	}
//
// //going up 
//	if (con->IsButtonPressed(Buttons::DPAD_UP))
//	{
//
//	}
//
//	//going down
//	if (con->IsButtonPressed(Buttons::DPAD_DOWN))
//	{
//
//	}
//
//
//	
//}
//
//void Start::GamepadUp(XInputController* con)
//{
//	return;
//}
//
//void Start::GamepadDown(XInputController* con)
//{
//	return;
//}
//
//void Start::GamepadStick(XInputController* con)
//{
//	Stick stick[2];
//
//	con->GetSticks(stick);
//
//	//going up
//	if (stick[0].y > 0.3f) {
//
//	}
//	//going down
//	if (stick[0].y < -0.3f) {
//
//	}
//
//}
//
//void Start::GamepadTrigger(XInputController* con)
//{
//	return;
//}
//
//void Start::KeyboardHold()
//{
//}
//
//void Start::KeyboardDown()
//{
//}
//
//void Start::KeyboardUp()
//{
//}
//
//vec2 Start::ConvertToGl(vec2 clickCoord)
//{
//	Camera tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
//
//	//Need to convert cliccked point to screen space first!
//	vec2 clickedPoint = clickCoord;
//	vec2 position = vec2(tempCam.GetPositionX(), tempCam.GetPositionY());
//
//	//Window in windowX x windowY space
//	//Need to get into (right-left) x (top-bottome) space
//
//	//First task, make it so bottom is 0 and top is windowHeight
//	clickedPoint = vec2(clickedPoint.x, float(BackEnd::GetWindowHeight()) - clickedPoint.y);
//
//	float glX = (tempCam.GetAspect() * (tempCam.GetOrthoSize().y) - tempCam.GetAspect() * (tempCam.GetOrthoSize().x));
//	float glY = (tempCam.GetOrthoSize().w - tempCam.GetOrthoSize().z);
//
//	//Spaces
//	vec2 glSpace = vec2(glX, glY);
//	vec2 windowSpace = vec2(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
//
//	vec2 percentPoint = vec2(clickedPoint.x / windowSpace.x, clickedPoint.y / windowSpace.y);
//
//	//In glspace
//	clickedPoint = vec2(glSpace.x * percentPoint.x, glSpace.y * percentPoint.y);
//
//	clickedPoint = clickedPoint + vec2(tempCam.GetAspect() * tempCam.GetOrthoSize().x, tempCam.GetOrthoSize().z);
//
//	clickedPoint = clickedPoint + vec2(tempCam.GetPositionX(), tempCam.GetPositionY());
//
//	return clickedPoint;
//}
//
//void Start::MouseMotion(SDL_MouseMotionEvent evnt)
//{
//}
//
//void Start::MouseClick(SDL_MouseButtonEvent evnt)
//{
//}
//
//void Start::MouseWheel(SDL_MouseWheelEvent evnt)
//{
//}
