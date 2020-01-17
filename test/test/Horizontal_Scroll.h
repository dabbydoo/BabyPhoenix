#pragma once
#include"Camera.h"

using namespace std;

class Horizontal_Scroll {

public:
	Horizontal_Scroll();

	//to check if the camera is following the focus
	void update();

	//getters
	Camera* getcam() const;
	Transform* getfocus() const;
	float getoffset() const;

	//setter
	void setcam(Camera* cam);
	void setfocus(Transform* focus);
	void setoffset(float offset);



private:
	Camera* m_cam = nullptr;
	Transform* m_focus = nullptr;

	float m_offset = 5.f;

};


inline void from_json(const nlohmann::json& j, Horizontal_Scroll& horiscroll) {
	horiscroll.setoffset(j["Offset"]);
}

//sends vertical scrolling to json file
inline void to_json(nlohmann::json& j, const Horizontal_Scroll& horiscroll) {
	j["Offset"] = horiscroll.getoffset();
}