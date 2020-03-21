#include "HealthBar.h"
#include "ECS.h"
using namespace std;
HealthBar::HealthBar()
{
}
HealthBar::HealthBar(float health)
{
	m_health = health;
}

HealthBar::~HealthBar()
{
}

void HealthBar::DrawHUD()
{
	//healthbar
	{
		//Creates entity
		healthEntity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(healthEntity);
		ECS::AttachComponent<Transform>(healthEntity);

		string filename = "HealthBar.png";
		ECS::AttachComponent<AnimationController>(healthEntity);

		auto health = File::LoadJSON("HealthBar.json");

		auto& animation = ECS::GetComponent<AnimationController>(healthEntity);

		animation.InitUVs("HealthBar.png");

		animation.AddAnimation(health["Health_0"]);
		animation.AddAnimation(health["Health_1"]);
		animation.AddAnimation(health["Health_2"]);
		animation.AddAnimation(health["Health_3"]);
		animation.AddAnimation(health["Health_4"]);

		animation.SetActiveAnim(this->GetHealth());

		ECS::GetComponent<Sprite>(healthEntity).LoadSprite(filename, 19, 4, true, &animation);

		//HealthBar position
		
		auto helthPos = vec3(m_cam->GetPosition().x - 14, m_cam->GetPosition().y + 15, 99);

		ECS::GetComponent<Transform>(healthEntity).SetPosition(helthPos);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit()| EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(healthEntity, bitHolder, "Health Bar");
	}

	//the icon
	{
		//Creates entity
		iconEntity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(iconEntity);
		ECS::AttachComponent<Transform>(iconEntity);

		string filename = "Icon.png";
		ECS::AttachComponent<AnimationController>(iconEntity);

		auto icon = File::LoadJSON("Icon.json");

		auto& animation = ECS::GetComponent<AnimationController>(iconEntity);

		animation.InitUVs("Icon.png");

		animation.AddAnimation(icon["Icon"]);

		animation.SetActiveAnim(0);


		ECS::GetComponent<Sprite>(iconEntity).LoadSprite(filename, 7, 8, true, &animation);

		ECS::GetComponent<Sprite>(iconEntity).LoadSprite(filename, 7, 7, true, &animation);


		//Icon position

		auto iconPos = vec3(m_cam->GetPosition().x - 33, m_cam->GetPosition().y + 15, 99);

		ECS::GetComponent<Transform>(iconEntity).SetPosition(iconPos);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(iconEntity, bitHolder, "Icon");

	}
}

void HealthBar::GetCam()
{
	m_cam = &ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
}

float HealthBar::GetHealth() const
{
	return m_health;
}

void HealthBar::SetHealth(float health)
{
	m_health = health>m_max_h?m_max_h:health;
}

void HealthBar::SetMaxHealth(float health)
{
	m_max_h = health;
	m_health = health;
}

void HealthBar::Update()
{

	auto helthPos = vec3(m_cam->GetPosition().x - 20, m_cam->GetPosition().y + 14, 99);
	auto iconPos = vec3(m_cam->GetPosition().x - 34, m_cam->GetPosition().y + 15, 99);

	ECS::GetComponent<Transform>(healthEntity).SetPosition(helthPos);
	ECS::GetComponent<Transform>(iconEntity).SetPosition(iconPos);

	auto position = vec3(m_cam->GetPosition().x-20, m_cam->GetPosition().y+15, 99);

	ECS::GetComponent<Transform>(healthEntity).SetPosition(position);
	ECS::GetComponent<Transform>(iconEntity).SetPosition(vec3(position.x-14,position.y+1,position.z));

}
