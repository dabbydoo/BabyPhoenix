#pragma once
#include"Camera.h"

using namespace std;

class Vertical_Scroll{

public:
	Vertical_Scroll();

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


inline void from_json(const nlohmann::json& j, Vertical_Scroll& veriscroll) {
	veriscroll.setoffset(j["Offset"]);
}

//sends vertical scrolling to json file
inline void to_json(nlohmann::json& j, const Vertical_Scroll& veriscroll) {
	j["Offset"] = veriscroll.getoffset();
}