#include "Entity.h"
#include "Application.h"


Entity::Entity(const char* a_textureFileName, float a_width, float a_height)
{
	m_iSpriteID = UG::Application::CreateSprite(a_textureFileName, a_width, a_height, true);
	m_fWidth = a_width;
	m_fHeight = a_height;
}

Entity::Entity(const char* a_textureFileName, const float* a_v2Size, const float* a_fv4UVCoords)
{
	float origin[2] = { 0.5f, 0.5f };
	m_iSpriteID = UG::Application::CreateSprite(a_textureFileName, a_v2Size, origin, a_fv4UVCoords);
	m_fWidth = a_v2Size[0];
	m_fHeight = a_v2Size[1];
}

Entity::Entity(const Entity& a_Entity)
{
	m_iSpriteID = UG::Application::DuplicateSprite(a_Entity.m_iSpriteID);
	m_fWidth = a_Entity.m_fWidth;
	m_fHeight = a_Entity.m_fHeight;

}

Entity::~Entity()
{
	UG::Application::DestroySprite(m_iSpriteID);
}

void Entity::Update(float a_fDeltaTime)
{
}

void Entity::Draw()
{
	UG::Application::DrawSprite(m_iSpriteID);
}

void Entity::SetPosition(float a_x, float a_y)
{
	m_xPos = a_x;
	m_yPos = a_y;
	UG::Application::MoveSprite(m_iSpriteID, m_xPos, m_yPos);
}

void Entity::GetPosition(float& a_x, float& a_y) const
{
	a_x = m_xPos;
	a_y = m_yPos;
}

void Entity::GetSize(float& a_width, float& a_height) const
{
	a_width = m_fWidth;
	a_height = m_fHeight;
}

void Entity::SetBoundary(const float& a_x, const float& a_y)
{
	m_fXBoundary = a_x;
	m_fYBoundary = a_y;
}

void Entity::SetVelocity(int a_x, int a_y)
{
	m_velX = a_x;
	m_velY = a_y;

}

