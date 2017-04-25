#include "Player.h"
#include "iostream"
#include "Bullet.h"
#include "SpaceInvaders.h"

Player::Player(SpaceInvaders* a_pOwner, const char* a_TextureFileName) : Entity(a_TextureFileName, 64, 32)
{
	cooldownMax = 1.0f; //Change this to alter the rate of fire
	cooldownCurrent = cooldownMax;
	m_pOwner = a_pOwner;
}

Player::Player(SpaceInvaders* a_pOwner, const Player& a_player) : Entity(a_player)
{
	m_pOwner = a_pOwner;
	cooldownMax = 0.1f; 
	cooldownCurrent = cooldownMax;
}

Player::~Player()
{
}

void Player::Update(float a_fTimeStep)
{
	Entity::Update(a_fTimeStep);

	cooldownCurrent -= a_fTimeStep;
	

	float posx = m_xPos;
	//Used to test for player movement
	if (UG::Application::IsKeyDown(UG::KEY_RIGHT) && posx <= 614)
	{
	
		posx += 2.f;      //change to alter speed to the right
	}
	if (UG::Application::IsKeyDown(UG::KEY_LEFT) && posx >= 24)
	{
		posx -= 2.f;     //change to alter speed to the left
		
	}
	m_xPos = posx;
	
	if (UG::Application::IsKeyDown(UG::KEY_UP) && cooldownCurrent < 0.f)
	{
		m_pOwner->FireBullet(this);
		cooldownCurrent = cooldownMax;
	}

	SetPosition(m_xPos, m_yPos);

	
}

void Player::Draw()
{
	UG::Application::DrawSprite(m_iSpriteID);
}

