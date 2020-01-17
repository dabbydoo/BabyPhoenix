#ifndef __SCENE_H__
#define __SCENE_H__

#include "JSON.h"
#include "ECS.h"
#include "Physics_Body.h"

using namespace std;

class Scene
{
public:
	Scene() { m_sceneReg = new entt::registry(); m_physicsWorld = new b2World(m_gravity); }
	Scene(std::string name);
	~Scene() { }

	void Unload();

	//Each scene will need to have a different
	//init, as each scene's contents will be different
	virtual void InitScene(float windowWidth, float windowHeight) { printf("windowwidth: %f, windowHeight: %f", windowWidth, windowHeight); };

	//Saves the scene
	void SaveScene();

	//Get the scene registry
	entt::registry* GetScene() const;
	//Set the scene registry
	void SetScene(entt::registry& scene);
	std::string GetName() const;
	void SetName(std::string name);
	b2Vec2 GetGravity() const;
	void SetGravity(b2Vec2 grav);
	//Physics world
	b2World& GetPhysicsWorld();
	
	//Set window size (makes sure the camera aspect is proper)
	void SetWindowSize(float windowWidth, float windowHeight);
protected:

	b2World* m_physicsWorld = nullptr;
	b2Vec2 m_gravity = b2Vec2(float32(0.f), float32(0.f));

	entt::registry* m_sceneReg = nullptr;	
	std::string m_name = "Default Name";
};

#ifndef __SCENEJSON_H__
#define __SCENEJSON_H__

//Sends animation TO json file
inline void to_json(nlohmann::json& j, const Scene& scene)
{
	j["SceneName"] = scene.GetName();

	auto view = scene.GetScene()->view<EntityIdentifier>();
	
	//keeps count of how many entities were stored
	unsigned int counter = 0;

	for (auto entity : view)
	{
		//Stores the entity identifier
		j[std::to_string(counter)]["Identifier"] = view.get(entity);

		//Identifier used to check what components are within this entity
		unsigned int identity = view.get(entity).GetIdentifier();
		
		//If Identity includes the Camera bit
			//This means the entity contains a camera
	
	
		if (identity & EntityIdentifier::CameraBit())
		{
			//Stores the camera
			j[std::to_string(counter)]["Camera"] = scene.GetScene()->get<Camera>(entity);
		}

		//If Identity includes the Sprite bit
			//This means the entity contains a Sprite
		if (identity & EntityIdentifier::SpriteBit())
		{
			//Stores the sprite
			j[std::to_string(counter)]["Sprite"] = scene.GetScene()->get<Sprite>(entity);
		}

		//If Identity includes the Animation Controller bit
			//This means that the entity contains an Animation Controller
		if (identity & EntityIdentifier::AnimationBit())
		{
			//Stores the Animation controllers
			j[std::to_string(counter)]["AnimationController"] = scene.GetScene()->get<AnimationController>(entity);
		}

		//If Identity includes the Transform bit
			//This means that the entity contains a Transform
		if (identity & EntityIdentifier::TransformBit())
		{
			//Stores the transform
			j[std::to_string(counter)]["Transform"] = scene.GetScene()->get<Transform>(entity);
		}

		//If you create new classes that you add as a component,
		//you need to #1 add a static (unique) bit for that class
		//And then add more if statements after this point

		//if identity includes health bar bit
		//which means the entity contains a health bar

		if (identity & EntityIdentifier::healthbarBit()) {

			//stores the health bar
			j[to_string(counter)]["HealthBar"] = scene.GetScene()->get<healthbar>(entity);

		}
		if (identity & EntityIdentifier::horizontalscrollcameraBit()) {

			//stores the horizontal camera
			j[to_string(counter)]["HoriScrollCam"] = scene.GetScene()->get<Horizontal_Scroll>(entity);
		}
		if (identity & EntityIdentifier::verticalscrollcameraBit()) {

			//stores the horizontal camera
			j[to_string(counter)]["VeriScrollCam"] = scene.GetScene()->get<Vertical_Scroll>(entity);
		}

		if (identity & EntityIdentifier::PhysicsBit())
		{

			//Stores the transform
			j[std::to_string(counter)]["PhysicsBody"] = scene.GetScene()->get<PhysicsBody>(entity);                                       //
		}

		//For each loop increase the counter
		counter++;
	}

	//Stores the number of entities (for your loops)
	j["NumEntities"] = counter;
}

//Reads animation in FROM json file
inline void from_json(const nlohmann::json& j, Scene& scene)
{
	//Stores number of entities
	unsigned int numEntities = j["Scene"]["NumEntities"];

	//Sets the scene name (so you can save over the same file)
	scene.SetName(j["Scene"]["SceneName"]);

	//Reference to the registry
	auto &reg = *scene.GetScene();

	//checking for horizontal scroll	
	bool horiscroll = false;
	bool veriscroll = false;
	
	//Allows you to create each entity
	for (unsigned i = 0; i < numEntities; i++)
	{
		//Has animation
		bool hasAnim = false;

		//Creates new entity
		auto entity = reg.create();
		reg.assign<EntityIdentifier>(entity);
		//Sets the entity identifier correctly
		reg.get<EntityIdentifier>(entity) = j["Scene"][std::to_string(i)]["Identifier"];
		reg.get<EntityIdentifier>(entity).SetEntity(entity);
		
		//Just check if this entity is the main camera
		if (reg.get<EntityIdentifier>(entity).GetIsMainCamera())
		{
			//Sets main camera
			EntityIdentifier::MainCamera(entity);
		}
		if (reg.get<EntityIdentifier>(entity).GetIsMainPlayer())
		{
			//Sets main player
			EntityIdentifier::MainPlayer(entity);
		}

		unsigned int identity = reg.get<EntityIdentifier>(entity).GetIdentifier();

		//If Identity includes the Camera bit
			//This means the entity contains a camera
		if (identity & EntityIdentifier::CameraBit())
		{
			//Adds camera to the entity
			reg.assign<Camera>(entity);
			//Sets the camera to the saved version
			reg.get<Camera>(entity) = j["Scene"][std::to_string(i)]["Camera"];
		}

		//If Identity includes the Animation Controller bit
			//This means that the entity contains an Animation Controller
		if (identity & EntityIdentifier::AnimationBit())
		{
			//Adds Animation Controller to the entity
			reg.assign<AnimationController>(entity);
			//Sets the Animation Controller to the saved version
			reg.get<AnimationController>(entity) = j["Scene"][std::to_string(i)]["AnimationController"];

			hasAnim = true;

			//Animation controllers requires that we init the UVs with the filename
			reg.get<AnimationController>(entity).InitUVs(reg.get<AnimationController>(entity).GetFileName());
		}

		//If Identity includes the Sprite bit
			//This means the entity contains a Sprite
		if (identity & EntityIdentifier::SpriteBit())
		{
			AnimationController* anim = nullptr;
			if (hasAnim)
				anim = &reg.get<AnimationController>(entity);
			
			//Adds sprite to the entity
			reg.assign<Sprite>(entity);
			//Sets the sprite to the saved version
			reg.get<Sprite>(entity) = j["Scene"][std::to_string(i)]["Sprite"];

			//Sprite requires that we load in the sprite
			std::string fileName = reg.get<Sprite>(entity).GetFileName();
			reg.get<Sprite>(entity).LoadSprite(fileName, reg.get<Sprite>(entity).GetWidth(), reg.get<Sprite>(entity).GetHeight(), hasAnim, anim);
			if (reg.get<Sprite>(entity).GetIsSpriteSheet())
			{
				reg.get<Sprite>(entity).SetUVs(reg.get<Sprite>(entity).GetBottomLeft(), reg.get<Sprite>(entity).GetTopRight());
			}
		}

		//If Identity includes the Transform bit
			//This means that the entity contains a Transform
		if (identity & EntityIdentifier::TransformBit())
		{
			//Adds transform to the entity
			reg.assign<Transform>(entity);
			//Sets the transform to the saved version
			reg.get<Transform>(entity) = j["Scene"][std::to_string(i)]["Transform"];

			//Transforms require no further initialization
		}

		//same thing from above but, for health bar
		if (identity & EntityIdentifier::healthbarBit()) {
			//adds health bar to the entity 
			reg.assign<healthbar>(entity);
			//sets the health bar to our saved version 
			reg.get<healthbar>(entity) = j["Scene"][to_string(i)]["HealthBar"];
		}

		if (identity & EntityIdentifier::PhysicsBit())
		{
			//Adds transform to the entity
			reg.assign<PhysicsBody>(entity);
			//Sets the transform to the saved version
			reg.get<PhysicsBody>(entity) = j["Scene"][std::to_string(i)]["PhysicsBody"];                                               //

		}



		if (identity & EntityIdentifier::horizontalscrollcameraBit()) {

			reg.assign<Horizontal_Scroll>(entity);
			reg.get<Horizontal_Scroll>(entity) = j["Scene"][to_string(i)]["HoriScrollCam"];
			horiscroll = true;
		}
		if (identity & EntityIdentifier::verticalscrollcameraBit()) {

			reg.assign<Vertical_Scroll>(entity);
			reg.get<Vertical_Scroll>(entity) = j["Scene"][to_string(i)]["VeriScrollCam"];
	veriscroll = true;
		}
	}

	if (horiscroll) {
		reg.get<Horizontal_Scroll>(EntityIdentifier::MainCamera()).setcam(&reg.get<Camera>(EntityIdentifier::MainCamera()));

		reg.get<Horizontal_Scroll>(EntityIdentifier::MainCamera()).setfocus(&reg.get<Transform>(EntityIdentifier::MainPlayer()));
	}
	if (veriscroll) {
		reg.get<Vertical_Scroll>(EntityIdentifier::MainCamera()).setcam(&reg.get<Camera>(EntityIdentifier::MainCamera()));

		reg.get<Vertical_Scroll>(EntityIdentifier::MainCamera()).setfocus(&reg.get<Transform>(EntityIdentifier::MainPlayer()));
	}
}

#endif // !__TRANSFORMJSON_H__

#endif // !__SCENE_H__
