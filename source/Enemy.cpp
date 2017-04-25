#include "Enemy.h"
#include "SpaceInvaders.h"
#include "Entity.h"

Enemy::Enemy(SpaceInvaders* a_pOwner, const char* a_pTextureFileName, const float* a_v2Dimensions) : Entity(a_pTextureFileName, a_v2Dimensions[0], a_v2Dimensions[1])
{
	m_pOwner = a_pOwner;
	moveRight = true;
	SetPosition(0.f, 0.f);
	SetVelocity(5, 5);
	isAlive = true;
}

Enemy::Enemy(SpaceInvaders* a_pOwner, const char* a_pTextureFileName, const float* a_v2Dimensions, const float* a_fv4UVCoords) :
	Entity(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{
	m_pOwner = a_pOwner;
	moveRight = true;
	SetPosition(0.f, 0.f);
	SetVelocity(5, 5);
	isAlive = true;
}

Enemy::Enemy(SpaceInvaders*, const Enemy& a_enemy) : Entity(a_enemy)
{
	
}

Enemy::~Enemy()
{

}

void Enemy::Update(float a_fDeltaTime)
{
	if (isAlive)
	{

		m_xPos += m_velX * a_fDeltaTime;
		m_yPos += m_velY * a_fDeltaTime;

		if (m_xPos > 580)
		{
			m_pOwner->EnemyChangeDirection(-20.f, 0.f);
		}
		else if (m_xPos < 58)
		{
			m_pOwner->EnemyChangeDirection( 20.f, 0.f);
		}
		UG::Application::MoveSprite(m_iSpriteID, m_xPos, m_yPos);
	}

}

void Enemy::Draw()
{
	if (isAlive)
	{
		UG::Application::DrawSprite(m_iSpriteID);
	}
}

