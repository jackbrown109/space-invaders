#include "Background.h"
#include "SpaceInvaders.h"
#include "Application.h"
#include "iostream"
Background::Background(SpaceInvaders* a_Owner, float a_width, float a_height, int a_iScreenHeight, char* a_textureName) : Entity(a_textureName, a_width, a_height)
{
	m_iScreenHeight = a_iScreenHeight;

	SetPosition(320.f,400.f);


	UG::Application::MoveSprite(m_iSpriteID, m_xPos, m_yPos);

}
Background::Background(SpaceInvaders* a_pOwner, float a_width, float a_height, int a_iScreenHeight) : Entity("./images/background.png", a_width, a_height)
{
	

	m_iScreenHeight = a_iScreenHeight;


	m_pOwner = a_pOwner;

	SetPosition(0.f, 0.f);
	SetVelocity(0, 5); //Changes speed of the background


}

Background:: ~Background()
{

}

void Background::Update(float a_fDeltaTime)
{
	m_yPos++;
	
	Entity::Update(a_fDeltaTime);
	m_yPos -= m_velY;

	if (m_yPos <= -400)
	{
		m_yPos = 1200;
	}
	UG::Application::MoveSprite(m_iSpriteID, m_xPos, m_yPos);
}
void Background::Draw()
{
	
		UG::Application::DrawSprite(m_iSpriteID);
	
}


