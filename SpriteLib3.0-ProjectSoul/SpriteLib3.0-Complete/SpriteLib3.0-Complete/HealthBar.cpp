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

		ECS::GetComponent<Sprite>(healthEntity).LoadSprite(filename, 19*(-m_cam->GetOrthoSize().x/20), 4 * (m_cam->GetOrthoSize().y / 20), true, &animation);

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


		ECS::GetComponent<Sprite>(iconEntity).LoadSprite(filename, 7 * (-m_cam->GetOrthoSize().x / 20), 8 * (m_cam->GetOrthoSize().y / 20), true, &animation);


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

float HealthBar::GetMaxHealth() const
{
	return m_max_h;
}

void HealthBar::SetMaxHealth(float health)
{
	m_max_h = health;
	m_health = health;
}

void HealthBar::DestroyHealthBar()
{
	ECS::DestroyEntity(healthEntity);
	ECS::DestroyEntity(iconEntity);
}

void HealthBar::Update()
{

	auto& Healthspr = ECS::GetComponent<Sprite>(healthEntity);

	Healthspr.SetWidth(19 * (-m_cam->GetOrthoSize().x / 20));
	Healthspr.SetHeight(4 * (m_cam->GetOrthoSize().y / 20));

	auto& iconspr = ECS::GetComponent<Sprite>(iconEntity);

	iconspr.SetWidth(7 * (-m_cam->GetOrthoSize().x / 20));
	iconspr.SetHeight(8 * (m_cam->GetOrthoSize().y / 20));
	
	if (!dontUpdate) {
		auto helthPos = vec3(m_cam->GetPosition().x - 18, m_cam->GetPosition().y + 15, 99);
		auto iconPos = vec3(m_cam->GetPosition().x - 32, m_cam->GetPosition().y + 16, 99);

		auto& animation = ECS::GetComponent<AnimationController>(healthEntity);

		animation.SetActiveAnim(this->GetHealth());

		ECS::GetComponent<Transform>(healthEntity).SetPosition(helthPos);
		ECS::GetComponent<Transform>(iconEntity).SetPosition(iconPos);
	}
}
