#include "VerticalScroll.h"
#include "ECS.h"

VerticalScroll::VerticalScroll()
{
}

void VerticalScroll::Update()
{
	auto height = ECS::GetComponent<Sprite>(background).GetHeight();
	auto center = ECS::GetComponent<Transform>(background).GetPosition();

	if (m_focus->GetPosition().y > (m_cam->m_localPosition.y  + m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera right by
		float difference = m_focus->GetPosition().y - (m_cam->m_localPosition.y + m_offset);

		//Adjust the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x, clamp((m_cam->GetPosition().y + difference), (center.y - (height / 2)), (center.y + (height / 2))), m_cam->GetPosition().z));
	}
	//Below focus
	if (m_focus->GetPosition().y < (m_cam->m_localPosition.y - m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera left by
		float difference = m_focus->GetPosition().y - (m_cam->m_localPosition.y - m_offset);

		//Adjust the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x, clamp((m_cam->GetPosition().y + difference), (center.y - (height / 2)), (center.y + (height / 2))), m_cam->GetPosition().z));
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
