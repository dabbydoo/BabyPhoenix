#include "Scene.h"
#include"BackEnd.h"

Scene::Scene(std::string name)
{
	m_physicsWorld = new b2World(m_gravity);
	m_name = name;
}

void Scene::Unload()
{
	if (m_sceneReg != nullptr)
	{
		delete m_sceneReg;
		delete m_physicsWorld;
		m_physicsWorld = nullptr;
		m_sceneReg = nullptr;

		m_physicsWorld = new b2World(m_gravity);
	}
}

void Scene::SaveScene()
{
	//Our scene
	nlohmann::json scene;

	//Casts to scene so all inherited classes can be saved the same way
	//The only data that matters for saving is the actual registry
	//which exists in the base class, meaning data won't be lost
	scene["Scene"] = *this;

	//Create the file and output the scene's contents to it
	File::CreateJSON(m_name + ".json", scene);
}

void Scene::InitScene(float windowWidth, float windowHeight)
{
	//Default scene class init just includes a camera so stuff doesn't immediately crash
	printf("You shouldn't be running this, while initializing this Scene Type.\n");

	//Dynamically allocates the register
	m_sceneReg = new entt::registry;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Setup Main Camera entity
	{
		//Creates Camera entity
		auto entity = ECS::CreateEntity();

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		//ECS::AttachComponent<HorizontalScroll>(entity);
		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Horizontal Scrolling Cam");
		ECS::SetIsMainCamera(entity, true);
	}
}

vec2 Scene::ConvertToGl(vec2 clickCoord)
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

entt::registry* Scene::GetScene() const
{
	return m_sceneReg;
}

void Scene::SetScene(entt::registry& scene)
{
	m_sceneReg = &scene;
}

vec4 Scene::GetClearColor() const
{
	return m_clearColor;
}

void Scene::SetClearColor(vec4 clearColor)
{
	m_clearColor = clearColor;
}

std::string Scene::GetName() const
{
	return m_name;
}

void Scene::SetName(std::string name)
{
	m_name = name;
}

b2Vec2 Scene::GetGravity() const
{
	return m_gravity;
}

void Scene::SetGravity(b2Vec2 grav)
{
	m_gravity = grav;
}

b2World & Scene::GetPhysicsWorld()
{
	return *m_physicsWorld;
}

void Scene::SetWindowSize(float windowWidth, float windowHeight)
{
	auto& tempCam = m_sceneReg->get<Camera>(EntityIdentifier::MainCamera());
	
	tempCam.SetWindowSize(vec2(windowWidth, windowHeight));
	tempCam.Orthographic(float(windowWidth / windowHeight), tempCam.GetOrthoSize().x, tempCam.GetOrthoSize().y,
															tempCam.GetOrthoSize().z, tempCam.GetOrthoSize().w,
															tempCam.GetNear(), tempCam.GetFar());
}