#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Entity.h"

class SpaceInvaders;
class Background : public Entity
{
public:
	Background(SpaceInvaders* a_Owner, float a_width, float a_height, int a_iScreenHeight);
	Background(SpaceInvaders* a_Owner, float a_width, float a_height, int a_iScreenHeight, char* a_textureName);
	
	virtual ~Background();

	void Update(float a_fDeltaTime);
	void Draw();

	


	

private:

	


	SpaceInvaders* m_pOwner;

	int m_iScreenHeight;
};

#endif // __BACKGROUND_H__