/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

Game - constructor. Here we create all common gameObjects
(menu windows and death trigger)

~Game - destructor. Here we delete all scene objects

Start - Here we create ball, platform and bricks

Update - Here we update all positions of moving object

Input - Here we check for pressed keys 
		Platform movement logic also handles here (not good :c)

Render - Here we render all objects 
		depends on current scene state

CheckCollisions - Here we check collisions between ball and
				other scene objects

CheckOverlapping - Here we check bounding box overlapping
					(not really good for ball)

GenerateBricks - Here we generate random bricks
				(random color and filling)

HitVelocityChange - Here we check ball's velocity change after
					brick hit. Sometimes it works weird on 
					transparent bricks
____________________________________________________________________
*/

using namespace std;

#include "Game.h"


Game::Game(unsigned int width, unsigned int height)
	: gameState(MAIN_MENU), screenWidth(width), screenHeight(height)
{
	this->meshRenderer = new MeshRenderer();
	
	this->PauseMenuBar = new GameObject("src/Textures/pause.jpg", RECTANGLE, FULLSCREEN,
		glm::vec2(-0.25f, 0.0f), glm::vec2(0.5f, 0.25f), glm::vec3(0.7f, 0.4f, 0.5f),
		true, glm::vec2(-0.3f, 0.5f));

	this->MainMenuBar =	new GameObject("src/Textures/start.png",RECTANGLE, FULLSCREEN, 
		glm::vec2(0.5f, 0.5f), glm::vec2(0.5f, 0.25f), glm::vec3(0.1f, 0.4f, 0.5f), 
		true, glm::vec2(0.3f,0.3f));

	this->EndMenuBar = new GameObject("src/Textures/loose.png",RECTANGLE, FULLSCREEN,
		glm::vec2(-0.25f, 0.0f), glm::vec2(0.5f, 0.25f), glm::vec3(1.0f, 0.1f, 0.15f),
		true, glm::vec2(0.3f, 0.2f));

	this->WinMenuBar = new GameObject("src/Textures/win.png",RECTANGLE, FULLSCREEN,
		glm::vec2(-0.25f, 0.0f), glm::vec2(0.5f, 0.25f), glm::vec3(0.7f, 0.3f, 0.8f),
		true, glm::vec2(0.14f, 0.4f));

	this->DeathBar = new GameObject("",RECTANGLE, FULLSCREEN, glm::vec2(-1.0f, -1.2f),
		glm::vec2(2.0f, 0.3f), glm::vec3(0.6f, 0.1f, 0.5f), true, glm::vec2(0.0f, 0.0f));

}

Game::~Game()
{
	delete Ball;
	delete Platform;
	delete MainMenuBar;
	delete PauseMenuBar;
	delete EndMenuBar;
	delete WinMenuBar;
}

void Game::Start()
{
	delete Ball;
	delete Platform;
	
	if (Bricks.empty() == false)
	{
		for (int i = 0; i < Bricks.size(); i++)
			delete Bricks[i];
		Bricks.clear();
	}

	this->Platform = new GameObject("", RECTANGLE, ARKANOID, glm::vec2(-0.2f, -0.9f),
		glm::vec2(0.4f, 0.03f), glm::vec3(0.1f, 0.9f, 0.5f), true, glm::vec2(0.0f, 0.0f));

	
	this->Ball = new GameObject("", CIRCLE, ARKANOID, glm::vec2(-0.2f, -0.8f),
		glm::vec2(0.06f, 0.06f), glm::vec3(0.6f, 0.1f, 0.5f), false, glm::vec2(0.3f, 0.6f));

	GenerateBricks();
}

void Game::Update(float dt)
{
	if (gameState == MAIN_MENU)
	{
		MainMenuBar->Move(dt);
	}
	if (gameState == PAUSE_MENU)
	{
		PauseMenuBar->Move(dt);
	}
	if (gameState == WIN_MENU)
	{
		WinMenuBar->Move(dt);
	}

	if (gameState == LOOSE_MENU)
	{
		EndMenuBar->Move(dt);
	}

	if (gameState == GAME)
	{
		Ball->Move(dt);
	}
	
}

void Game::Input(float dt)
{
	if (gameState == MAIN_MENU)
	{
		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
		{
			this->gameState = GAME;
			this->Start();
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
		}
	}

	if (gameState == PAUSE_MENU)
	{
		if (this->Keys[GLFW_KEY_ESCAPE] && !this->KeysProcessed[GLFW_KEY_ESCAPE])
		{
			this->gameState = GAME;
			this->KeysProcessed[GLFW_KEY_ESCAPE] = true;
		}

		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
		{
			this->gameState = MAIN_MENU;
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
		}
	}

	if (gameState == WIN_MENU)
	{
		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
		{
			this->gameState = MAIN_MENU;
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
		}

		if (this->Keys[GLFW_KEY_R] && !this->KeysProcessed[GLFW_KEY_R])
		{
			Start();
			this->gameState = GAME;
			this->KeysProcessed[GLFW_KEY_R] = true;
		}
	}

	if (gameState == LOOSE_MENU)
	{
		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
		{
			this->gameState = MAIN_MENU;
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
		}

		if (this->Keys[GLFW_KEY_R] && !this->KeysProcessed[GLFW_KEY_R])
		{
			Start();
			this->gameState = GAME;
			this->KeysProcessed[GLFW_KEY_R] = true;
		}
	}

	if (gameState == GAME)
	{
		if (this->Keys[GLFW_KEY_A])
		{
			if (Platform->Position.x >= -1.0f)
			{
				Platform->Position.x -= PLATFORM_VELOCITY * dt;
			}
		}

		if (this->Keys[GLFW_KEY_D])
		{
			if (Platform->Position.x <= 1.0f - Platform->Size.x)
			{
				Platform->Position.x += PLATFORM_VELOCITY * dt;
			}
		}

		if (this->Keys[GLFW_KEY_ESCAPE] && !this->KeysProcessed[GLFW_KEY_ESCAPE])
		{
			this->gameState = PAUSE_MENU;
			this->KeysProcessed[GLFW_KEY_ESCAPE] = true;
		}
	}
}

void Game::Render()
{
	if (gameState == MAIN_MENU)
	{
		this->meshRenderer->SpriteRender(MainMenuBar);
	}

	if (gameState == GAME)
	{
		this->meshRenderer->Render(Platform);
		this->meshRenderer->Render(Ball);
		for(int i=0; i< Bricks.size(); i++)
		this->meshRenderer->Render(Bricks[i]);
	}

	if (gameState == PAUSE_MENU)
	{
		this->meshRenderer->Render(Platform);
		this->meshRenderer->Render(Ball);
		for (int i = 0; i < Bricks.size(); i++)
			this->meshRenderer->Render(Bricks[i]);
		this->meshRenderer->SpriteRender(PauseMenuBar);

	}

	if (gameState == LOOSE_MENU)
	{
		this->meshRenderer->Render(Platform);
		this->meshRenderer->Render(Ball);
		for (int i = 0; i < Bricks.size(); i++)
			this->meshRenderer->Render(Bricks[i]);
		this->meshRenderer->SpriteRender(EndMenuBar);
	}

	if (gameState == WIN_MENU)
	{
		this->meshRenderer->Render(Platform);
		this->meshRenderer->Render(Ball);
		this->meshRenderer->SpriteRender(WinMenuBar);
	}
}

void Game::CheckCollisions()
{
	if (gameState == GAME)
	{
		if (CheckOverlapping(Ball, DeathBar))
			gameState = LOOSE_MENU;

		if (CheckOverlapping(Platform, Ball))
		{
			Ball->Velocity.x = ((Ball->Position.x + Ball->Size.x / 2 - Platform->Position.x) - (Platform->Size.x / 2)) / (Platform->Size.x / 2);

			Ball->Position.y = Platform->Position.y + Ball->Size.y;
			Ball->Velocity.y = -Ball->Velocity.y;
		}

		bool bricksDestroyed = false;
		for (int i = 0; i < Bricks.size(); i++)
		{
			if (Bricks[i]->isSolid) bricksDestroyed = true;
			if (CheckOverlapping(Bricks[i], Ball))
			{
				glm::vec2 velocityChange =  HitVelocityChange(Ball, Bricks[i]);

					Ball->Velocity *= velocityChange;
				if (Bricks[i]->isSolid == true)
				{
					delete Bricks[i];
					Bricks.erase(Bricks.begin() + i);
				}
				if (Bricks.size() == 0) gameState = WIN_MENU;
			}
		}
		if(bricksDestroyed == false) gameState = WIN_MENU;
	}
}

bool Game::CheckOverlapping(GameObject* A, GameObject* B) // AABB - AABB collision
{
	// collision x-axis?
	bool collisionX = 	A->Position.x + A->Size.x >= B->Position.x &&
		B->Position.x + B->Size.x >= A->Position.x;
	// collision y-axis?
	bool collisionY = A->Position.y - A->Size.y <= B->Position.y &&
		B->Position.y - B->Size.y <= A->Position.y;
	// collision only if on both axes
	return collisionX && collisionY;
}

void Game::GenerateBricks()
{
	float xBrickPosition = -0.8f;
	float yBrickPosition = 0.8f;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			bool solid = true;
			if (rand() % 4 == 0) solid = false;

			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			Bricks.push_back(new GameObject("", RECTANGLE, FULLSCREEN, glm::vec2(xBrickPosition, yBrickPosition),
				glm::vec2(0.3f, 0.06f), glm::vec3(r, g, b), solid , glm::vec2(0.0f, 0.0f)));

			xBrickPosition += 0.315f;
		}

		yBrickPosition += -0.075f;
		xBrickPosition = -0.8f;
	}

}

glm::vec2 Game::HitVelocityChange(GameObject* ball, GameObject* brick)
{
	// remap coordinates
	float rBallX = ball->Position.x + 1;
	float rBallY = ball->Position.y + 1;

	float rBrickX = brick->Position.x + 1;
	float rBrickY = brick->Position.y + 1;

	float xOverlapValue = 0.0f;
	if (rBallX < rBrickX)
	{
		xOverlapValue = rBallX + ball->Size.x - rBrickX;
	}
	else if (rBallX >= rBrickX && rBallX + ball->Size.x <= rBrickX + brick->Size.x)
	{
		xOverlapValue = ball->Size.x;
	}
	else if (rBallX + ball->Size.x > rBrickX + brick->Size.x)
	{
		xOverlapValue = rBrickX + brick->Size.x - rBallX;
	}

	float yOverlapValue = 0.0f;
	if (rBallY > rBrickY)
	{
		yOverlapValue = rBrickY - (rBallY - ball->Size.y);
	}
	else if (rBallY <= rBrickY && rBallY - ball->Size.y >= rBrickY - brick->Size.y)
	{
		yOverlapValue = ball->Size.y;
	}
	else if (rBallY - ball->Size.y < rBrickY - brick->Size.y)
	{
		yOverlapValue = rBallY - (rBrickY - brick->Size.y);
	}

	if (xOverlapValue >= yOverlapValue) return glm::vec2(1.0f, -1.0f);
	else return glm::vec2(-1.0f, 1.0f);
}