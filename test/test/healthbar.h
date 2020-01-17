#pragma once
#include "JSON.h"

class healthbar {

public: 
	
	//creates the health bar
	healthbar();
	
	//creates the health bar with the amount of health
	healthbar(float health);

	//destroys the health bar
	~healthbar();

	void displayhealth();

	//getter
	float GetHealth() const;

	//setter
	void SetHealth(float health);
private:

	//100% health

	float m_health = 1.f;

};

inline void to_json(nlohmann::json& j, const healthbar& bar) {

	j["Health"] = bar.GetHealth();

}

inline void from_json(const nlohmann::json& j, healthbar& bar) {
	bar.SetHealth(j["Health"]);
}