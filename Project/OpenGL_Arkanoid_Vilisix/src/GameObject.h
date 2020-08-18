/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

GameObject class header -> look in GameObject.cpp for methods description
____________________________________________________________________
*/


#pragma once
#include <glm/glm.hpp>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

enum Movement {
	FULLSCREEN,
	ARKANOID,
	LINEAR,
	NONE
};

enum Shape {
	RECTANGLE,
	CIRCLE
};

class GameObject
{
public:
	Shape ObjectShape;
	Movement MovementType;
	glm::vec2 Position, Size, Velocity;
	std::vector<glm::vec2> Mesh;
	unsigned int MeshSize;
	glm::vec3 Color;
	bool isSolid;
	
	unsigned int texture;
	unsigned char* data;

	GameObject(std::string path, Shape shape, Movement movement, glm::vec2 position, glm::vec2 size, glm::vec3 color, bool solid, glm::vec2 velocity);
	~GameObject();

	void Move(float dt);

};
