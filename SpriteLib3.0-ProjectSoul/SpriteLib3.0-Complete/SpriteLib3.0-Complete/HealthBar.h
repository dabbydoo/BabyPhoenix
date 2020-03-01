#pragma once
#include "JSON.h"
class HealthBar
{

public:
	HealthBar();
	HealthBar(float health);
	~HealthBar();

	void DisplayHealth();
	float GetHealth() const;
	void SetHealth(float health);
	void SetMaxHealth(float health);
private:
	float m_health = 0.f;
	float m_max_h = 0.f;
};
inline void to_json(nlohmann::json& j, const HealthBar& bar) {
	j["Health"] = bar.GetHealth();
}
inline void from_json(nlohmann::json& j, HealthBar& bar) {
	bar.SetHealth(j["Health"]);;
}