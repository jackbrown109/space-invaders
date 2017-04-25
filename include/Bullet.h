#ifndef __BULLET_H__
#define __BULLET_H__

#include "Entity.h"

class SpaceInvaders;
class Bullet : public Entity
{
public:
	Bullet(SpaceInvaders* m_Owner, float a_width, float a_height, int a_iScreenHeight);
	virtual ~Bullet();

	void Update(float a_fDeltaTime);
	void Draw();
	
	
	

	bool isAlive;

private:
	

	
	SpaceInvaders* m_pOwner;

	int m_iScreenHeight;
};

#endif // __BULLET_H__