#include "HorizontalScroll.h"
#include "ECS.h"
#include <iostream>

HorizontalScroll::HorizontalScroll()
{
}

void HorizontalScroll::Update()
{
	auto width = ECS::GetComponent<Sprite>(background).GetWidth();
	auto center = ECS::GetComponent<Transform>(background).GetPosition();

	float fixCam = clamp(m_cam->m_localPosition.x, center.x - (width / 2), center.x + (width / 2));

	//Above focus
	if (m_focus->GetPosition().x > (m_cam->m_localPosition.x + m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera right by
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x + m_offset);

		//Adjust the camera
		m_cam->SetPosition(vec3(clamp((m_cam->GetPosition().x + difference), center.x - (width / 2), center.x + (width / 2)), m_cam->GetPosition().y, m_cam->GetPosition().z));
	}
	//Below focus
	else if (m_focus->GetPosition().x < (m_cam->m_localPosition.x - m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera left by
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x - m_offset);

		//Adjust the camera
		m_cam->SetPosition(vec3(clamp((m_cam->GetPosition().x + difference), center.x - (width / 2), center.x + (width / 2)), m_cam->GetPosition().y, m_cam->GetPosition().z));
	}
}

Camera* HorizontalScroll::GetCam() const
{
	return m_cam;
}

Transform* HorizontalScroll::GetFocus() const
{
	return m_focus;
}

float HorizontalScroll::GetOffset() const
{
	return m_offset;
}

void HorizontalScroll::SetCam(Camera* cam)
{
	m_cam = cam;
}

void HorizontalScroll::SetFocus(Transform* focus)
{
	m_focus = focus;
}

void HorizontalScroll::SetOffset(float offset)
{
	m_offset = offset;
}

void HorizontalScroll::SetBackground(unsigned int entity)
{
	background = entity;
}
