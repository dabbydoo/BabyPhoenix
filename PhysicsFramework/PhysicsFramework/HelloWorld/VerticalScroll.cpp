#include "VerticalScroll.h"
#include "ECS.h"

VerticalScroll::VerticalScroll()
{
}

void VerticalScroll::Update()
{
	auto height = ECS::GetComponent<Sprite>(background).GetHeight();
	//auto center = ECS::GetComponent<Transform>(background).GetPosition();

	//Above focus
	if (m_focus->GetPosition().y > (m_cam->m_localPosition.y + m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera right by
		float difference = m_focus->GetPosition().y - (m_cam->m_localPosition.y + m_offset);

		//Adjust the camera
		float newY = m_cam->GetPositionY() + difference;
		vec3 newPos = vec3(m_cam->GetPosition().x, newY, m_cam->GetPosition().z);
		m_cam->SetPosition(newPos);
	}
	//Below focus
	if (m_focus->GetPosition().y < (m_cam->m_localPosition.y - m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera left by
		float difference = m_focus->GetPosition().y - (m_cam->m_localPosition.y - m_offset);

		//Adjust the camera
		float newY = m_cam->GetPositionY() + difference;
		vec3 newPos = vec3(m_cam->GetPosition().x, newY, m_cam->GetPosition().z);
		m_cam->SetPosition(newPos);
	}

}
Camera* VerticalScroll::GetCam() const
{
	return m_cam;
}

Transform* VerticalScroll::GetFocus() const
{
	return m_focus;
}

float VerticalScroll::GetOffset() const
{
	return m_offset;
}

void VerticalScroll::SetCam(Camera* cam)
{
	m_cam = cam;
}

void VerticalScroll::SetFocus(Transform* focus)
{
	m_focus = focus;
}

void VerticalScroll::SetOffset(float offset)
{
	m_offset = offset;
}

void VerticalScroll::SetBackground(unsigned int entity)
{
	background = entity;
}
