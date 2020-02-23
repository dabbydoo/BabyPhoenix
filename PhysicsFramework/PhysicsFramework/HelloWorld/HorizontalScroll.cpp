#include "HorizontalScroll.h"
#include "ECS.h"
#include <iostream>


HorizontalScroll::HorizontalScroll()
{
}

void HorizontalScroll::Update()
{
	auto width = ECS::GetComponent<Sprite>(background).GetWidth();
	float rightScrollLimit = (m_cam->GetOrthoSize().x - m_cam->GetOrthoSize().w) / 2 * m_cam->GetAspect() + (width / 2 - m_scrollCorrection);
	float leftScrollLimit = (m_cam->GetOrthoSize().x - m_cam->GetOrthoSize().w) / -2 * m_cam->GetAspect() - (width / 2 - m_scrollCorrection);
	
	//Reset camera position within scroll limit
	//Right
	if (m_focus->GetPosition().x > rightScrollLimit)
		m_focus->SetPositionX(rightScrollLimit);
	//Left
	if (m_focus->GetPosition().x < leftScrollLimit)
		m_focus->SetPositionX(leftScrollLimit);

	//Above focus
	if (m_focus->GetPosition().x > (m_cam->m_localPosition.x + m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera right by
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x + m_offset);

		//Adjust the camera
		if (m_cam->GetPosition().x < rightScrollLimit)
		{
			float newX = m_cam->GetPositionX() + difference;
			vec3 newPos = vec3(newX, m_cam->GetPosition().y, m_cam->GetPosition().z);
			m_cam->SetPosition(newPos);
		}
	}
	//Below focus
	if (m_focus->GetPosition().x < (m_cam->m_localPosition.x - m_offset))
	{
		//Calculate the amount the focus has "pushed" the camera left by
		float difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x - m_offset);

		//Adjust the camera
		if (m_cam->GetPosition().x > leftScrollLimit)
		{
			float newX = m_cam->GetPositionX() + difference;
			vec3 newPos = vec3(newX, m_cam->GetPosition().y, m_cam->GetPosition().z);
			m_cam->SetPosition(newPos);
		}
	}

	/*cout << "\nGetpositionX: " << m_cam->GetPosition().x <<endl;
	cout << "\nGetFOCUSX: " << m_focus->GetPosition().x << endl;
	cout << "GetORTHOpositionX: " << m_cam->GetOrthoPos().x << endl;
	cout << "windowSize: " << m_cam->GetWindowSize().x << endl;
	cout << "getScale: " << m_cam->GetScale().x << endl;*/

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
