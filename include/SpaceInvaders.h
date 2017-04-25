#ifndef __SpaceInvaders_H_
#define __SpaceInvaders_H_

#include "Application.h"
#include <glm/glm.hpp>

class Player;
class Enemy;
class Bullet;
class Entity;
class Background;

//declares array size 
#define ENEMY_COUNT 30
#define MAX_BULLETS 8
#define SCREEN_SCROLL 2


enum GameState{
	SPLASH1,
	SPLASH2, //'You win!' screen
	MENU,
	HIGHSCORES,
	GAME
};
// Derived application class that wraps up all globals neatly
class SpaceInvaders : public UG::Application
{
public:

	SpaceInvaders();
	virtual ~SpaceInvaders();
	
	bool CanFireBullet();
	void FireBullet(Entity* a_pShooter);
	void BulletOutOfBounds(Bullet* a_bullet);
	bool TestCollision(Entity* a_pEnemy, Bullet* a_pBullet);
	void EnemyChangeDirection(float a_xDir, float a_yDir);
	
	
	virtual void resetgame();

	
	
protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();
	

private:
	int m_iScreenWidth;
	int m_iScreenHeight;

	virtual void DrawScores();
	virtual void LoadScores(int a_hiScoreValue); //Loads and saves scores. a_hiScoreValue is the score from the game, to compare against others and potentially save
	virtual void CompareScores();
	virtual void SaveScores();
	virtual void GetScores(int a_score);
	void Draw();
	
	int hiScoreValue;
	int m_tempStr[6];
	int m_iHighScores[5];
	const int m_iMAXHIGHSCORES = 5;




	GameState m_currentState;
	GameState m_nextState;



	Player* m_pPlayer;
	Enemy* m_pEnemy[ENEMY_COUNT];         
	Bullet* m_pBullets[MAX_BULLETS];
	Background* m_pBackground[SCREEN_SCROLL];
	Background* m_pSplashScreen;
	
};

#endif // __SpaceInvaders_H_