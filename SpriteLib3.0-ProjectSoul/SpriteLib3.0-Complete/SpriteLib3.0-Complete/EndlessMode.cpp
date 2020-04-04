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

void EndlessMode::Update()
{
	backgroudUpdate();
	floorUpdate();
	bulletUpdate();
	enemyUpdate();

}

void EndlessMode::floorUpdate()
{
}

void EndlessMode::backgroudUpdate()
{
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
