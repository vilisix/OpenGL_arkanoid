/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

Game class header -> look in Game.cpp for methods description
____________________________________________________________________
*/

#pragma once
#include<iostream>
#include "GameObject.h"
#include "MeshRenderer.h"

enum GameState {
	MAIN_MENU,
	GAME,
	PAUSE_MENU,
	WIN_MENU,
	LOOSE_MENU
};

const float PLATFORM_VELOCITY = 1.0f;

class Game
{
public:
	bool  Keys[1024];
	bool  KeysProcessed[1024];
	GameState gameState;
	MeshRenderer* meshRenderer;
	unsigned int  screenWidth, screenHeight;

	GameObject* MainMenuBar;
	GameObject* Ball;
	GameObject* Platform;
	std::vector<GameObject*> Bricks;
	GameObject* PauseMenuBar;
	GameObject* EndMenuBar;
	GameObject* WinMenuBar;
	GameObject* DeathBar;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Start();
	void GenerateBricks();
	void Update(float dt);
	void Input(float dt);
	void Render();
	void CheckCollisions();
	glm::vec2 HitVelocityChange(GameObject* ball, GameObject* brick);
	bool CheckOverlapping(GameObject* A, GameObject* B);

	
};

