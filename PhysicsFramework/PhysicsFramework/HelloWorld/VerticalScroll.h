#pragma once
#include "Camera.h"
using namespace std;

class VerticalScroll
{
public:
	VerticalScroll();
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

	float m_offset = 0.f;

	//Scroll correction
	float m_scrollCorrection = 1;
};

//Sends vertical scrolling camera FROM json file
inline void from_json(const nlohmann::json& j, VerticalScroll& horiScroll)
{
	horiScroll.SetOffset(j["Offset"]);
}
//Sends verticle scrolling camera TO json file
inline void to_json(nlohmann::json& j, const VerticalScroll& horiScroll)
{
	j["Offset"] = horiScroll.GetOffset();
}