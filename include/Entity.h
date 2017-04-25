#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity
{
public:
	Entity(const char* a_textureFileName, float a_width, float a_height);
	Entity(const char* a_textureFileName, const float* a_v2Size, const float* a_fv4UVCoords);
	//Copy Constructor        
	Entity(const Entity& a_Entity);
	//Virtual destructor - virtual so that child classes will call it upon their destruction
	virtual ~Entity();
	virtual void Update(float a_fdeltaTime);
	virtual void Draw();

	//sets position and movement for child classes to inherit
	void SetPosition(float a_x, float a_y);
	void GetPosition(float& a_x, float& a_y) const;
	void GetSize(float& a_Width, float& a_Height) const;
	void SetVelocity(int a_x, int a_y);
	void SetBoundary(const float& a_x, const float& a_y);

protected:
	
	unsigned int m_iSpriteID;
	float m_fWidth;
	float m_fHeight;

	float m_xPos;
	float m_yPos;

	float m_fXBoundary;
	float m_fYBoundary;

	int m_velX;
	int m_velY;

	float m_x;
	float m_y;

private:

};

#endif //__ENTITY_H__
