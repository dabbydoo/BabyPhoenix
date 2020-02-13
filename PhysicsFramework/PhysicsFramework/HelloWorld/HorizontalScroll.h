#pragma once
//#include <iostream>
#include "Camera.h"

using namespace std;

class HorizontalScroll
{
public:
	HorizontalScroll();
	//~HorizontalScroll();

	//Makes sure that the camera is following the focus
	void Update();

	//Getters
	Camera* GetCam() const;
	Transform* GetFocus() const;
	float GetOffset() const;
	
	//Setters
	void SetCam(Camera* cam);
	void SetFocus(Transform* focus);
	void SetOffset(float offset);
	void SetBackground(unsigned int entity);

private:
	Camera* m_cam = nullptr;
	Transform* m_focus = nullptr;

	unsigned int background;

	float m_offset = 5.f;
};

//Sends vertical scrolling camera FROM json file
inline void from_json(const nlohmann::json& j, HorizontalScroll& horiScroll)
{
	horiScroll.SetOffset(j["Offset"]);
}
//Sends verticle scrolling camera TO json file
inline void to_json(nlohmann::json& j, const HorizontalScroll& horiScroll)
{
	j["Offset"] = horiScroll.GetOffset();
}