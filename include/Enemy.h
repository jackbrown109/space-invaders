#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"

class SpaceInvaders;

class Enemy : public Entity
{
public:
	Enemy(SpaceInvaders* a_pOwner, const char* a_pTextureFileName, const float* a_v2Dimensions);
	Enemy(SpaceInvaders* a_pOwner, const char* a_pTextureFileName, const float* a_v2Dimensions, const float* a_fv4UVCoords);
	Enemy(SpaceInvaders* a_pOwner, const Enemy& a_copy);

	virtual ~Enemy();
	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
	
	bool isAlive;
	

protected:
private:
	unsigned int m_fHealth;
	SpaceInvaders* m_pOwner;
	int iScreenHeight;
	

	bool moveRight;
	
};

#endif //__ENEMY_H__