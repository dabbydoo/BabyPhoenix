#include "Horizontal_Scroll.h"

Horizontal_Scroll::Horizontal_Scroll()
{
}

void Horizontal_Scroll::update()
{
	//above the focus
	if (m_focus->GetPosition().x > m_cam->m_localPosition.x + m_offset) {
		
		//calculate the amount of focus that has been pushed the camera right by
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x + m_offset);

		//adjusting the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x+difference,m_cam->GetPosition().y, m_cam->GetPosition().z));
		}

	//below the focus
	if (m_focus->GetPosition().x < m_cam->m_localPosition.x - m_offset) {
		
		//calculate the amount of focus that has been pushed the camera left by
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x - m_offset);
	
		//adjusting the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x + difference, m_cam->GetPosition().y, m_cam->GetPosition().z));

	}

}

Camera* Horizontal_Scroll::getcam() const
{
	return m_cam;
}

Transform* Horizontal_Scroll::getfocus() const
{
	return m_focus;
}

float Horizontal_Scroll::getoffset() const
{
	return m_offset;
}

void Horizontal_Scroll::setcam(Camera* cam)
{
	m_cam = cam;
}

void Horizontal_Scroll::setfocus(Transform* focus)
{
	m_focus = focus;
}

void Horizontal_Scroll::setoffset(float offset)
{
	m_offset = offset;
}
