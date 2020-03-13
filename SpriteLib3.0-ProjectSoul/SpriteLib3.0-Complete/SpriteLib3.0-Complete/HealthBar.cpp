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

		ECS::GetComponent<Sprite>(healthEntity).LoadSprite(filename, 26, 6, true, &animation);

		//HealthBar position
		
		auto position = vec3(m_cam->GetPosition().x - 14, m_cam->GetPosition().y + 13, 99);

		ECS::GetComponent<Transform>(healthEntity).SetPosition(position);

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

		ECS::GetComponent<Sprite>(iconEntity).LoadSprite(filename, 10, 10, true, &animation);

		//Icon position

		ECS::GetComponent<Transform>(iconEntity).SetPosition(ECS::GetComponent<Transform>(healthEntity).GetPosition());

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(iconEntity, bitHolder, "Icon");

	}
}

void HealthBar::SetCam()
{
	m_cam = &ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
}

void HealthBar::DisplayHealth()
{
	//std::cout << "Health: " << std::to_string((m_health*100.f)) << "%" << std::endl;

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
	auto position = vec3(m_cam->GetPosition().x-14, m_cam->GetPosition().y+13, 99);

	ECS::GetComponent<Transform>(healthEntity).SetPosition(position);
	//ECS::GetComponent<Transform>(iconEntity).SetPosition(vec3(position.x+5,position.y,position.z));
}
