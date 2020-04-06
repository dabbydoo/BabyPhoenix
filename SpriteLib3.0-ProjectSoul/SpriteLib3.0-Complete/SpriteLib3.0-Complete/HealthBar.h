#pragma once
#include "JSON.h"
#include "Camera.h"
class HealthBar
{

public:
	HealthBar();
	HealthBar(float health);
	~HealthBar();

	void DrawHUD();

	void GetCam();

	float GetHealth() const;
	void SetHealth(float health);
	float GetMaxHealth() const;
	void SetMaxHealth(float health);

	void DestroyHealthBar();

	void Update();


	//0 is healthEntity, 1 is soulFillerEntity, 2 is iconEntity, 3 is gunEntity
	unsigned int GetBarStatus(int index) {

		if (index == 0) {
			return healthEntity;
		}

		if (index == 1) {
			return soulFillerEntity;
		}
		if (index == 2) {
			return iconEntity;
		}
		if (index == 3) {
			return gunEntity;
		}
	}

	bool dontUpdate = false;
	bool can_shoot = false;

private:

	

	int m_health = 0.f;
	int m_max_h = 0.f;
	unsigned healthEntity = 0, soulFillerEntity = 0, iconEntity = 0, gunEntity = 0;
	Camera *m_cam;
};
inline void to_json(nlohmann::json& j, const HealthBar& bar) {
	j["Health"] = bar.GetHealth();
}
inline void from_json(nlohmann::json& j, HealthBar& bar) {
	bar.SetHealth(j["Health"]);;
}