#include "Vertical_Scroll.h"

Vertical_Scroll::Vertical_Scroll()
{
}

void Vertical_Scroll::update()
{
	if (m_focus->GetPosition().y > m_cam->m_localPosition.y + m_offset) {

		//calculate the amount of focus that has been pushed the camera right by
		float difference = m_focus->GetPosition().y - (m_cam->m_localPosition.y + m_offset);

		//adjusting the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x, m_cam->GetPosition().y + difference, m_cam->GetPosition().z));
	}

	//below the focus
	if (m_focus->GetPosition().y < m_cam->m_localPosition.y - m_offset) {

		//calculate the amount of focus that has been pushed the camera left by
		float difference = m_focus->GetPosition().y - (m_cam->m_localPosition.y - m_offset);

		//adjusting the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x, m_cam->GetPosition().y + difference, m_cam->GetPosition().z));

	}
}

Camera* Vertical_Scroll::getcam() const
{
	return m_cam;
}

Transform* Vertical_Scroll::getfocus() const
{
	return m_focus;
}

float Vertical_Scroll::getoffset() const
{
	return m_offset;
}

void Vertical_Scroll::setcam(Camera* cam)
{
	m_cam = cam;
}

void Vertical_Scroll::setfocus(Transform* focus)
{
	m_focus = focus;
}

void Vertical_Scroll::setoffset(float offset)
{
	m_offset = offset;
}
