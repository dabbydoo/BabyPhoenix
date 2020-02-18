#include "HorizontalScroll.h"
#include "ECS.h"

HorizontalScroll::HorizontalScroll()
{
}

void HorizontalScroll::Update()
{
	auto width = ECS::GetComponent<Sprite>(background).GetWidth();
	//auto center = ECS::GetComponent<Transform>(background).GetPosition();

	//Above focus
	if (m_focus->GetPosition().x > (m_cam->m_localPosition.x + m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera right by
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x + m_offset);

		//Adjust the camera
		float newX = m_cam->GetPositionX() + difference;
		vec3 newPos = vec3(newX, m_cam->GetPosition().y, m_cam->GetPosition().z);
		m_cam->SetPosition(newPos);
	}
	//Below focus
	if (m_focus->GetPosition().x < (m_cam->m_localPosition.x - m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera left by
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x - m_offset);

		//Adjust the camera
		float newX = m_cam->GetPositionX() + difference;
		vec3 newPos = vec3(newX, m_cam->GetPosition().y, m_cam->GetPosition().z);
		m_cam->SetPosition(newPos);
	}

	// Check every frame if the camera is out of bounds, if it is, move it back in bounds
	float size = abs(m_cam->GetOrthoSize().y - m_cam->GetOrthoSize().x);

	float newX = m_cam->GetPositionX();
	if (newX - size < -width / 2) // Left side check
	{
		vec3 newPos = m_cam->GetPosition();
		newPos.x = -width / 2 + size;
		m_cam->SetPosition(newPos);
	}
	else if (newX - size < width / 2) // Right side check
	{
		vec3 newPos = m_cam->GetPosition();
		newPos.x = width / 2 - size;
		m_cam->SetPosition(newPos);
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
