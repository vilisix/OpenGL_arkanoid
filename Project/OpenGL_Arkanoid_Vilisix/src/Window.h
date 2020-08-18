/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

Window class header -> look in Window.cpp for methods description
____________________________________________________________________
*/


#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <string>
#include <stdexcept>

class Window
{
private:
	GLFWwindow* pWindow;
	Game* game;
	//bool isPaused;
public:
	Window(const std::string& tltle, int width, int height);
	~Window();

	GLFWwindow* getWindowPointer();
	
	void LaunchGameLoop(Game& game);

	//void PauseGameLoop();
};

