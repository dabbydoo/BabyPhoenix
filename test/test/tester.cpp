#include "tester.h"

tester::tester(std::string name)
	:Scene(name)
{
}

void tester::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;
	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;
	{
		auto entity = ECS::CreateEntity();

		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<Vertical_Scroll>(entity);

		ECS::AttachComponent<Horizontal_Scroll>(entity);


		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();

		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);


		ECS::GetComponent<Horizontal_Scroll>(entity).setcam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<Horizontal_Scroll>(entity).setoffset(15.f);

		ECS::GetComponent<Vertical_Scroll>(entity).setcam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<Vertical_Scroll>(entity).setoffset(15.f);



		unsigned int bitholder = EntityIdentifier::verticalscrollcameraBit() | EntityIdentifier::horizontalscrollcameraBit() | EntityIdentifier::CameraBit();

		//unsigned int bitholder =EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitholder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);

	}

	{
		//creates entity
		auto entity = ECS::CreateEntity();
		//creates an orthographic camera
		ECS::AttachComponent<healthbar>(entity);
		ECS::GetComponent<healthbar>(entity).SetHealth(1.f);

		//sets up an identifier
		unsigned int bitHolder = EntityIdentifier::healthbarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "HealthBar Entity");




	}

	{//sets up new entity
		auto entity = ECS::CreateEntity();

		//Adds components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up componets 
		string filename = "Background.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 390, 220);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 99.f));
		//sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "BackGround");
	}

	//soldier movement
	{
		auto movement = File::LoadJSON("Main_Character1.json");

		auto entity = ECS::CreateEntity();


		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components 
		string filename = "Main_Character.png";


		auto& animecontroller = ECS::GetComponent<AnimationController>(entity);
		animecontroller.InitUVs(filename);
		//adds first animations

		animecontroller.AddAnimation(movement["Regular_Stance"]);


		animecontroller.AddAnimation(movement["back_facing"]);

		animecontroller.AddAnimation(movement["walking_left"]);

		animecontroller.AddAnimation(movement["walking_right"]);

		animecontroller.AddAnimation(movement["walking_straight"]);


		//sets active animation

		animecontroller.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 25, 25, true, &animecontroller);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(5.f, 7.f, 100.f));

		//sets up identifier
		unsigned bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Soldier");
		ECS::SetIsMainPlayer(entity, true);

	}

	//venom suit up, off and walk
	{
		auto movement = File::LoadJSON("venom_sprite!.json");

		auto entity = ECS::CreateEntity();


		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components 
		string filename = "venom_sprite.png";


		auto& animecontroller = ECS::GetComponent<AnimationController>(entity);
		animecontroller.InitUVs(filename);
		//adds first animations

		animecontroller.AddAnimation(movement["movement"]);
		animecontroller.AddAnimation(movement["wear"]);
		animecontroller.AddAnimation(movement["unwear"]);

		//sets active animation

		animecontroller.SetActiveAnim(0);


		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 25, 25, true, &animecontroller);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, 25.f, 100.f));


		//sets up identifier
		unsigned bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Venom better");

	}


	//robot sprite
	{
		auto movement = File::LoadJSON("robot_sprite!.json");

		auto entity = ECS::CreateEntity();


		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components 
		string filename = "robot_sprite.png";


		auto& animecontroller = ECS::GetComponent<AnimationController>(entity);
		animecontroller.InitUVs(filename);
		//adds first animations

		animecontroller.AddAnimation(movement["run"]);
		animecontroller.AddAnimation(movement["fly"]);


		//sets active animation

		animecontroller.SetActiveAnim(0);


		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 25, 25, true, &animecontroller);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(55.f, 35.f, 100.f));


		//sets up identifier
		unsigned bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "RE: Robot");

	}
	//boss movement
	{

		auto movement = File::LoadJSON("bossSprite.json");

		auto entity = ECS::CreateEntity();


		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		string filename = "bossSprite.png";


		auto& animecontroller = ECS::GetComponent<AnimationController>(entity);
		animecontroller.InitUVs(filename);
		//adds first animations

		animecontroller.AddAnimation(movement["bossLeft"]);
		animecontroller.AddAnimation(movement["bossRight"]);


		//sets active animation

		animecontroller.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 50, 55, true, &animecontroller);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-117.f, 48.f, 100.f));

		//sets up identifier
		unsigned bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Boss");


	}
	{

		auto movement = File::LoadJSON("bossSprite.json");

		auto entity = ECS::CreateEntity();


		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		string filename = "bossSprite.png";


		auto& animecontroller = ECS::GetComponent<AnimationController>(entity);
		animecontroller.InitUVs(filename);
		//adds first animations

		animecontroller.AddAnimation(movement["bossLeft"]);
		animecontroller.AddAnimation(movement["bossRight"]);


		//sets active animation

		animecontroller.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(filename, 50, 55, true, &animecontroller);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-25.f, -80.f, 100.f));

		//sets up identifier
		unsigned bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Boss");


	}

}
