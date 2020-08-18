/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

GameObject - constructor. Here we set all parameters(like in Unity)
			and generate object mesh.
			Alse we load images for menu bars here.

~GameObject - destructor

Move - Handles movement logic over the screen
		FULLSCREEN - object bounce from all screen borders
		ARKANOID - object not bounce from bottom border

____________________________________________________________________
*/


#include "GameObject.h"
#include <math.h>
#include "stb_image.h"


GameObject::GameObject(std::string path,Shape shape, Movement movement, glm::vec2 position, glm::vec2 size, glm::vec3 color, bool solid, glm::vec2 velocity)
{
	this->ObjectShape = shape;
	this->MovementType = movement;
	this->Position = position;
	this->Size = size;
	this->Color = color;
	this->isSolid = solid;
	this->Velocity = velocity;
	
	if (shape == RECTANGLE)
	{
		this->MeshSize = 8;
		this->Mesh.push_back(glm::vec2(0.0f, 0.0f)); // vertex
		this->Mesh.push_back(glm::vec2(0.0f, 0.0f)); // texture


		this->Mesh.push_back(glm::vec2(size.x, 0.0f));  //vertex
		this->Mesh.push_back(glm::vec2(1.0f, 0.0f)); // texture
		

		this->Mesh.push_back(glm::vec2(size.x, -size.y)); //vertex
		this->Mesh.push_back(glm::vec2(1.0f, 1.0f)); //texture

		this->Mesh.push_back(glm::vec2(0.0f, -size.y)); // vertex
		this->Mesh.push_back(glm::vec2(0.0f, 1.0f)); // texture		

	}
	
	if (shape == CIRCLE)
	{
		this->MeshSize = 20;
		float x = size.x / 2;
		float y = - size.y / 2;
		for (int j = 0; j < 20; j++)
		{
			this->Mesh.push_back(
				glm::vec2(
					(x + (size.x / 2 * cos(j * 6.28f / 20))),
					(y + (size.y / 2 * sin(j* 6.28f / 20)))
				)
			);
		}

	}

	if (path.size() > 0)
	{
		// load and create a texture 
   // -------------------------
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
	
	
}


GameObject::~GameObject()
{

}


void GameObject::Move(float dt)
{
	if (this->MovementType != NONE)
	{
		if (this->Velocity.x != 0.0f && this->Velocity.y != 0.0f)
		{
			this->Position += this->Velocity * dt;

			if (this->MovementType == ARKANOID || this->MovementType == FULLSCREEN)
			{
				if (this->Position.x <= -1.0f)
				{
					this->Velocity.x = -this->Velocity.x;
					this->Position.x = -1.0f;
				}
				else if (this->Position.x + this->Size.x >= 1.0f)
				{
					this->Velocity.x = -this->Velocity.x;
					this->Position.x = 1.0f - this->Size.x;
				}

				if (this->Position.y >= 1.0f)
				{
					this->Velocity.y = -this->Velocity.y;
					this->Position.y = 1.0f;
				}
				else if (this->Position.y - this->Size.y <= -1.0f && this->MovementType == FULLSCREEN)
				{
					this->Velocity.y = -this->Velocity.y;
					this->Position.y = -1.0 + this->Size.y;
				}
			}


		}
	}
	
	
}