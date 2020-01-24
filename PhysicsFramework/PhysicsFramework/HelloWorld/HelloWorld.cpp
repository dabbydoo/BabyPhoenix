#include "HelloWorld.h"

HelloWorld::HelloWorld(std::string name)
 :Scene(name)
{

}

void HelloWorld::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;
	ECS::AttachRegister(m_sceneReg);
	float aspectRatio = windowWidth / windowHeight;

	/*{
		auto entity = ECS::CreateEntity();

		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		unsigned int bitHolder2 = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder2, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<AnimationController>(entity);
		std::string filename = "HelloWorld.png";
		//std::string filename2 = "spritesheets/link.png";
		//std::string filename2 = "HelloWorld.png";
		
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 100, 50);
		//ECS::GetComponent<Sprite>(entity).LoadSprite(filename2, 101, 100);
		//ECS::GetComponent<Sprite>(entity).SetUVs(vec2(0.f, 150.f), vec2(319.f, 0.f));
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 99.f));
		//unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		unsigned int bitHolder = 0x0;
		ECS::SetUpIdentifier(entity, bitHolder, "Hello World Sign");
	}

	{
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<HealthBar>(entity);
		ECS::GetComponent<HealthBar>(entity).SetHealth(.7f);
		unsigned int bitHolder = EntityIdentifier::healthBarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "HealthBar Entity");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<AnimationController>(entity);
		std::string filename = "bulbasaur.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 100, 100);
		//ECS::GetComponent<Sprite>(entity).LoadSprite(filename2, 101, 100);
		//ECS::GetComponent<Sprite>(entity).SetUVs(vec2(0.f, 150.f), vec2(319.f, 0.f));
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-25.f, -25.f, 98.f));
		//unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		unsigned int bitHolder = 0x0;
		ECS::SetUpIdentifier(entity, bitHolder, "Balbasaur");
	}
	{		
		auto entity = ECS::CreateEntity();

		auto soldierMovement = File::LoadJSON("soldier_sprite.json");

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		//ECS::AttachComponent<AnimationController>(entity);
		std::string filename = "soldier_sprite.png";

		auto &animation_controller = ECS::GetComponent<AnimationController>(entity);
		
		animation_controller.InitUVs(filename);

		animation_controller.AddAnimation(soldierMovement["move"]);

		animation_controller.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 101, 100,true,&animation_controller);
		//ECS::GetComponent<Sprite>(entity).SetUVs(vec2(0.f, 150.f), vec2(319.f, 0.f));
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()| EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "i AM THERE");
	}*/
}
