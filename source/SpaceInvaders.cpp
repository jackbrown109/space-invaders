#include "Application.h"
#include "SpaceInvaders.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Background.h"

//This is an example of a complex #define that obfuscates the entry point of the application
//APPLICATION_ENTRY can be found in Application.h it is a define that hides the main() entry point
//of the application. This is done so that each application can be called and run in the same manner
//it is not something that needs to be fully understood until much later in the CGP course.

APPLICATION_ENTRY(SpaceInvaders);

//A default constructor for SpaceInvaders() and it's accompanying destructor ~FrameworkTest()
//Any initialisation could be placed in here, these are empty for now. They are here to ensure that
//the correct application creation sequence is called.
SpaceInvaders::SpaceInvaders(){}
SpaceInvaders::~SpaceInvaders(){}

//onCreate is a function that is called once on the creation of the application. This is where items 
//that will last for the duration of the application should be created. EG Player sprites
bool SpaceInvaders::onCreate(int a_argc, char* a_argv[])
{
	LoadScores(0);
	m_currentState = m_nextState = SPLASH1;
	Application::GetScreenSize(m_iScreenWidth, m_iScreenHeight);
	
	Application::SetBackgroundColor(UG::SColour(0x00, 0x00, 0x00, 0xFF));
	Application::AddFont("./fonts/invaders.fnt");
	

	m_pBackground[0] = new Background(this, 650, 800, m_iScreenHeight);
	m_pBackground[1] = new Background(this, 650, 800, m_iScreenHeight);
	m_pSplashScreen = new Background(this, 650, 800, m_iScreenHeight, "./images/space_invaders_logo.png");
	//\Now lets create the sprite for our players cannon. That's right in space invaders we control a cannon
	//\So lets create that with an appropriate variable name and move it to a suitable location (say the middle of our screen)
	m_pPlayer = new Player(this, "./images/cannon.png");
	float dimensions[2] = { 32.f, 32.f };       //size of enemy
	float uvCoords[4] = { 0.f, 0.85f, 0.25f, 1.f };        //slices enemy sprite sheet
	float x = m_iScreenWidth * 0.1f;
	float y = m_iScreenHeight * 0.75f;
	for (int i = 0; i < ENEMY_COUNT; ++i)
	{
		m_pEnemy[i] = new Enemy(this, "./images/invaders.png", dimensions, uvCoords);
		m_pEnemy[i]->SetPosition(x ,y);
		m_pEnemy[i]->SetVelocity(40.f, 0.f); //change enemy movement speed
		x += 32.f;
		if ((i + 1) % 10 == 0 && i != 0)
		{
			x = m_iScreenWidth * 0.1f; //set boundary where enemies go to
			y -= 32.f;
		}
	}
	//Create bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		m_pBullets[i] = new Bullet(this, 2, 8, m_iScreenHeight); //numbers change x and y size of bullet
		m_pBullets[i]->isAlive = false;
	}
	
	
	//For SetPosition to function you will need to have written a function in the Entity class called SetPosition
	//that allows for two floats to be passed in then calls Move Sprite with this information

	m_pPlayer->SetPosition(m_iScreenWidth * 0.5f, m_iScreenHeight * 0.07f);

	        

	m_pBackground[0]->SetPosition(m_iScreenWidth * 0.5f, m_iScreenHeight * 0.5f);

	m_pBackground[1]->SetPosition(m_iScreenWidth * 0.5f, m_iScreenHeight * 1.5f);

	return true;
}

//onUpdate - this function is called each frame of the application, the a_deltaTime variable is a floating point value
//that gives the length of time that has passed since the previous frame was rendered.
void SpaceInvaders::onUpdate(float a_deltaTime)
{
	if (m_currentState != m_nextState)			
	{
		m_currentState = m_nextState;
	}

	switch (m_currentState)
	{
		case SPLASH1: //happens within splash screen
		{
			static float fTime = 5.f;
			fTime -= a_deltaTime;
			if (fTime < 0.f)
			{
				m_nextState = MENU;
			}
			   break;
		}
		
		
		case MENU:  //happens within menu screen
		{
					 if (Application::IsKeyDown(UG::KEY_1))
					 {
						 resetgame();
						 m_nextState = GAME;
					 }
					 if (Application::IsKeyDown(UG::KEY_Q))
					 {
						 destroy();
					 }
					 if (Application::IsKeyDown(UG::KEY_H))
					 {
						// LoadScores(30);

						 m_nextState = HIGHSCORES;
					 }
			   break;
		}

		case HIGHSCORES:
		{

						   //LoadScores(hiScoreValue);
						   
						   if (Application::IsKeyDown(UG::KEY_SPACE))
						   {
							   m_nextState = MENU;
							   break;
						   }
		}
		case SPLASH2: //the 'You Win!' screen
		{
						static float fTime = 3.f; //how long screen is displayed
						fTime -= a_deltaTime;
						if (fTime < 0.f)
						{
							m_nextState = MENU;
							fTime = 3.f; //reset time frame so win screen is displayed after game is reset
						}
						break;
		}
		case GAME: //happens within the game
		{
			m_pPlayer->Update(a_deltaTime);
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				m_pBullets[i]->Update(a_deltaTime);
			}

			m_pBackground[0]->Update(a_deltaTime);

			m_pBackground[1]->Update(a_deltaTime);

			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				m_pEnemy[i]->Update(a_deltaTime);
			}

			for (Bullet* b : m_pBullets)
			{
				if (b->isAlive)
				{
					for (Enemy* enemy : m_pEnemy)
					{
						if (enemy->isAlive)
						{
							if (TestCollision(enemy, b))
							{
								enemy->isAlive = false;
								b->isAlive = false;
								hiScoreValue= hiScoreValue +10;
								std::cout << hiScoreValue << std::endl;
								break;
							}
						}
					}
				}
			}

			if (hiScoreValue == 300)
			{
				m_nextState = SPLASH2;
				LoadScores(hiScoreValue);
				break;
			}

			if (Application::IsKeyDown(UG::KEY_ESCAPE))
				//LoadScores(hiScoreValue);
				m_nextState = MENU;
			  ;
		}
		default:
			break;
	}
	


}

bool SpaceInvaders::TestCollision(Entity* a_pEnemy, Bullet* a_pBullet)
{
	//Get the dimensions of the bullet
	float bulletX = 0.f, bulletY = 0.f;
	float bulletWidth = 0.f, bulletHeight = 0.f;
	a_pBullet->GetPosition(bulletX, bulletY);
	a_pBullet->GetSize(bulletWidth, bulletHeight);
	
	//Get the dimension and position of enemy
	float enemyX = 0.f, enemyY = 0.f;
	float enemyWidth = 0.f, enemyHeight = 0.f;
	a_pEnemy->GetPosition(enemyX, enemyY);
	a_pEnemy->GetSize(enemyWidth, enemyHeight);
	//Drawn from the centre so get half the sizes
	enemyWidth *= 0.5f;
	enemyHeight *= 0.5f;

	/*Sprite draws from the centre, test Y first as less chance the of the bullet
	being within this area*/
	if (bulletY + bulletHeight > enemyY - enemyHeight && bulletY - bulletHeight < enemyY + enemyHeight)
	{
		//Then test X direction
		if (bulletX + bulletWidth > enemyX - enemyWidth && bulletX - bulletWidth < enemyX + enemyWidth)
		{
			return true;
		}
	}
	return false;
}


//onDraw is called each frame after onUpdate has been called
//this is where any rendering should be carried out
void SpaceInvaders::onDraw()
{
	Application::ClearScreen();

	switch (m_currentState)
	{
	case SPLASH1: //draws on splash screen
	{
				   m_pSplashScreen->Draw();
				   Application::SetFont("./fonts/invaders.fnt");
				   Application::DrawString("Remade by Jack Brown", (int)(m_iScreenWidth * 0.25f), m_iScreenHeight * 0.25f, 1.f);

				   break;
	}
	case MENU: //draws on menu screen
	{
				 Application::SetFont("./fonts/invaders.fnt");
				 Application::DrawString("PRESS 1 To Play GAME", (int)(m_iScreenWidth * 0.30f), m_iScreenHeight * 0.7f, 1.f);
				 Application::DrawString("PRESS Q To QUIT Game", (int)(m_iScreenWidth * 0.30f), m_iScreenHeight * 0.6, 1.f);
				 Application::DrawString("PRESS H to Display High Scores", (int)(m_iScreenWidth * 0.20f), m_iScreenHeight * 0.5, 1.f);

				 Application::DrawString("Left / Right Arrow Keys = Move", (int)(m_iScreenWidth * 0.15f), m_iScreenHeight * 0.2, 1.f);
				 Application::DrawString("Up Arrow Key = Fire", (int)(m_iScreenWidth * 0.15f), m_iScreenHeight * 0.15, 1.f);
				 Application::DrawString("Esc Key = Quit to Menu", (int)(m_iScreenWidth * 0.15f), m_iScreenHeight * 0.1, 1.f);
				 break;
	}
	case HIGHSCORES:
	{
					   Application::SetFont("./fonts/invaders.fnt");
					   Application::DrawString("High Scores", (int)(m_iScreenWidth * 0.35f), m_iScreenHeight * 0.9f, 1.f);
					   float m_fLineSpacing = 0.8f;
					   for (int i = 0; i < 5; i++)
					   {
						   std::string highscore = std::to_string(m_iHighScores[i]);
						   char m_chighscores[4];
						   strcpy(m_chighscores, highscore.c_str());
						   m_fLineSpacing -= 0.1f;
						   Application::DrawString(m_chighscores, (int)(m_iScreenWidth * 0.45f), m_iScreenHeight * m_fLineSpacing, 1.f);
					   }
					   
					   break;
	}
	case SPLASH2:
	{
					if (hiScoreValue == 300)
					{
						Application::SetFont("./fonts/invaders.fnt");
						Application::DrawString("You Win!", (int)(m_iScreenWidth * 0.40f), m_iScreenHeight * 0.7f, 1.f);
						break;
					}
					
					
	}
	case GAME: //draws within the game
	{
		m_pBackground[0]->Draw();
		m_pBackground[1]->Draw();


		m_pPlayer->Draw();

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			m_pBullets[i]->Draw();
		}

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			m_pEnemy[i]->Draw();
		}

		


		Application::SetFont("./fonts/invaders.fnt");
		Application::DrawString("SCORE ", (int)(m_iScreenWidth * 0.4f), m_iScreenHeight - 2, 1.f);
		
		Application::DrawString("CREDIT = 1", (int)(m_iScreenWidth * 0.65f), 38);
		std::string score = std::to_string(hiScoreValue);
		char highscore[4];
		strcpy(highscore, score.c_str());
		Application::DrawString(highscore, (int)(m_iScreenWidth * 0.55f), m_iScreenHeight - 2, 1.f);

		Application::DrawLine(0, 40, m_iScreenWidth, 40, UG::SColour(0x00, 0xFC, 0x00, 0xFF));
		Application::SetFont(nullptr);
		break;
	}
	default:
		break;
	}

	
	

}


void SpaceInvaders::resetgame()  //called in order to make sure game reloads after quitting to menu
{
	Application::GetScreenSize(m_iScreenWidth, m_iScreenHeight);

	Application::SetBackgroundColor(UG::SColour(0x00, 0x00, 0x00, 0xFF));
	Application::AddFont("./fonts/invaders.fnt");

	m_pBackground[0] = new Background(this, 650, 800, m_iScreenHeight);
	m_pBackground[1] = new Background(this, 650, 800, m_iScreenHeight);
	//\Now lets create the sprite for our players cannon. That's right in space invaders we control a cannon
	//\So lets create that with an appropriate variable name and move it to a suitable location (say the middle of our screen)
	m_pPlayer = new Player(this, "./images/cannon.png");
	float dimensions[2] = { 32.f, 32.f };       //size of enemy
	float uvCoords[4] = { 0.f, 0.85f, 0.25f, 1.f };        //slices enemy sprite sheet
	float x = m_iScreenWidth * 0.1f;
	float y = m_iScreenHeight * 0.75f;
	for (int i = 0; i < ENEMY_COUNT; ++i)
	{
		m_pEnemy[i]->isAlive = true;
		m_pEnemy[i] = new Enemy(this, "./images/invaders.png", dimensions, uvCoords);
		m_pEnemy[i]->SetPosition(x, y);
		m_pEnemy[i]->SetVelocity(40.f, 0.f); //change enemy movement speed
		
		x += 32.f;
		if ((i + 1) % 10 == 0 && i != 0)
		{
			x = m_iScreenWidth * 0.1f; //set boundary where enemies go to
			y -= 32.f;
		}
	}
	//Create bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		m_pBullets[i] = new Bullet(this, 2, 8, m_iScreenHeight); //numbers change x and y size of bullet
		m_pBullets[i]->isAlive = false;
	}


	//For SetPosition to function you will need to have written a function in the Entity class called SetPosition
	//that allows for two floats to be passed in then calls Move Sprite with this information

	m_pPlayer->SetPosition(m_iScreenWidth * 0.5f, m_iScreenHeight * 0.07f);



	m_pBackground[0]->SetPosition(m_iScreenWidth * 0.5f, m_iScreenHeight * 0.5f);

	m_pBackground[1]->SetPosition(m_iScreenWidth * 0.5f, m_iScreenHeight * 1.5f);

	hiScoreValue = 0;

	return;

}

//onDestroy - this will be called at the termination of the application. Any items which need to be
//deallocated should be done so in here. E.G things that were created in the onCreate function.
void SpaceInvaders::onDestroy()
{
	delete m_pPlayer;
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete m_pBullets[i];
	}
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		delete m_pEnemy[i];
	}

	delete m_pBackground[0];
	delete m_pBackground[1];
}


void SpaceInvaders::FireBullet(Entity* a_pShooter)
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!m_pBullets[i]->isAlive)
		{
			m_pBullets[i]->isAlive = true;
			float xPos = 0.f, yPos = 0.f;
			a_pShooter->GetPosition(xPos, yPos);
			//a_pShooter->GetDirection() == +1 , -1
			m_pBullets[i]->SetPosition(xPos, yPos);
			break;
		}
	}
	
}


//involved in making enemies keep formation when bouncing off boundary
void SpaceInvaders::EnemyChangeDirection(float a_xDir, float a_yDir)
{
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		m_pEnemy[i]->SetVelocity( a_xDir, a_yDir );
	}
}



void SpaceInvaders::DrawScores()
{
	float m_fLineSpacing = 0.45f;
	for (int i = 0; i < 5; i++)
	{
		std::string highscore = std::to_string(m_tempStr[i]);
		char m_cHighScores[4];
		strcpy(m_cHighScores, highscore.c_str());
		m_fLineSpacing -= 0.05f;

	}
}





void SpaceInvaders::LoadScores(int a_hiScoreValue)
{
	
	GetScores(a_hiScoreValue);
	CompareScores();
	SaveScores();



	
}





void SpaceInvaders::GetScores(int a_score)
{
	m_tempStr[0] = a_score;

	std::fstream scoresFile;
	scoresFile.open("scores.txt", std::ios_base::in);

	if (scoresFile.is_open())
	{
		std::string scoresLine = "9";
		for (int i = 1; i < 6; i++)
		{
			std::getline(scoresFile, scoresLine);
			std::cout << scoresLine << std::endl;
			m_tempStr[i] = std::stoi(scoresLine);
		}
	}
	scoresFile.close();
}

void SpaceInvaders::SaveScores()
{
	std::fstream scoresFile;
	scoresFile.open("scores.txt", std::ios_base::out);

	if (scoresFile.is_open())
	{
		for (int i = 0; i < 5; i++)
		{
			
			scoresFile << std::to_string(m_tempStr[i]) << std::endl;
			m_iHighScores[i] = m_tempStr[i];
		}
	}

	scoresFile.close();
}

void SpaceInvaders::CompareScores()
{
	//check each number in .txt file against current score
	for (int i = 0; i <= 5; i++)

	{
		int m_iValue = m_tempStr[i];
		int m_jValue = m_tempStr[i + 1];

		//if the value is higher then in txt file
		if (m_iValue <= m_jValue)
		{
			m_tempStr[i] = (m_jValue);
			m_tempStr[i + 1] = (m_iValue);
		}
	}
}



