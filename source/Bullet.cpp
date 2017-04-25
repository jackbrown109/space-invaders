#include "Bullet.h"
#include "SpaceInvaders.h"
#include "Application.h"
#include "iostream"


Bullet::Bullet(SpaceInvaders* a_pOwner, float a_width, float a_height, int a_iScreenHeight) : Entity( "./images/bullet.png",a_width, a_height )
{

	m_iScreenHeight = a_iScreenHeight;

	isAlive = false;

	
	m_pOwner = a_pOwner;

	SetPosition(0.f, 0.f);
	SetVelocity(300, 300); //Changes speed of the bullet
}
Bullet:: ~Bullet()
{
	
}

void Bullet::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	if (isAlive)
	{
		m_yPos += m_velX * a_fDeltaTime;
		UG::Application::MoveSprite(m_iSpriteID, m_xPos, m_yPos);
		float fHalfSize = m_fWidth * 0.5f;
		if (m_yPos > m_iScreenHeight || m_yPos < 0.f)
		{
			isAlive = false;
		}
	}
}
void Bullet::Draw()
{
	if (isAlive)
	{
		UG::Application::DrawSprite(m_iSpriteID);
	}
}




