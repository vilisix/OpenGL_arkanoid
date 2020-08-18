/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

MeshRenderer class header -> look in MeshRenderer.cpp for methods description
____________________________________________________________________
*/


#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"



class MeshRenderer
{
private:
	unsigned int VAO, VBO, EBO;
	
public:
	
	MeshRenderer();
	~MeshRenderer();
	unsigned int shaderProgram;
	unsigned int spriteShaderProgram;

	void Render(GameObject* gameObject);
	void SpriteRender(GameObject* gameObject);
};