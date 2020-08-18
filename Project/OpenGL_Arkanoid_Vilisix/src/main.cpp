/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

main() - game entry point
here we create main application window and game class instance,
then launch main game cycle

key_callback - handling keyboard input

____________________________________________________________________
*/

#include "Window.h"
#include "GameObject.h"
#include "Game.h"
#include <iostream>


// window dimensions
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 800;

Game* pGame;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    Window appWindow("ArkanoidGame_Vilisix", SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetKeyCallback(appWindow.getWindowPointer(), key_callback);

    pGame = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);

    appWindow.LaunchGameLoop(*pGame);



    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// exit from application if ESC pressed from main menu
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && pGame->gameState == MAIN_MENU)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			pGame->Keys[key] = true;
		else if (action == GLFW_RELEASE)
		{
			pGame->Keys[key] = false;
			pGame->KeysProcessed[key] = false;
		}
	}
}
