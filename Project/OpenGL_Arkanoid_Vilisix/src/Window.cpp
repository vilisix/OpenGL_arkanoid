/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

Window - constructor, here we enable GLFW and GLEW

~Window - destructor, here we destroy window and glfw

getWindowPointer - for key callback from main.cpp

LaunchGameLoop - launch while cycle with all game states
				Input->Update->Collisions->Render

____________________________________________________________________
*/


#include "Window.h"


Window::Window(const std::string& title, int width, int height)
{
	//initialize glfw
	if (glfwInit() == false)
	{
		throw std::runtime_error("Oops! Can't init GLFW!");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	pWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!pWindow)
	{
		throw std::runtime_error("Oops! Can't init game window!");
	}

	glfwMakeContextCurrent(pWindow);

	glewExperimental = GL_TRUE;

	//initialize glew
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Oops! Can't init GLEW!");
	}


}

Window::~Window()
{
	glfwDestroyWindow(pWindow);
	glfwTerminate();
}

GLFWwindow* Window::getWindowPointer()
{
	return this->pWindow;
}

void Window::LaunchGameLoop(Game& refGame) 
{

	game = &refGame;


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//game loop
	while (glfwWindowShouldClose(pWindow) == false)
	{
		
		// dt calculations
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		glClearColor(0.855f, 0.882f, 0.910f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwPollEvents();

		game->Input(deltaTime);
		game->Update(deltaTime);

		game->CheckCollisions();

		game->Render();

		glfwSwapBuffers(pWindow);
	}
}



