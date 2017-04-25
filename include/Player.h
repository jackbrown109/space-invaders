#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Application.h"

#define MAX_PLAYER_KEYS 3
class SpaceInvaders;
class Bullet;

class Player : public Entity
{
public:
	Player(SpaceInvaders* a_pOwner, const char* a_textureFileName);
	Player(SpaceInvaders* a_pOwner, const Player& a_Player);

	virtual ~Player();

	void CreateBullets();

	void FireBullet();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
	
protected:
private:
	unsigned int m_fLives;
	SpaceInvaders* m_pOwner;
	

	float cooldownCurrent;
	float cooldownMax;
};

#endif //__PLAYER_H__