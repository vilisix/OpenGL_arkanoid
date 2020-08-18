/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

MeshRenderer - constructor, here we load shaders(two vertex and two fragment)
                for color and image rendered object. Create two programs

~MeshRenderer - destructor

Render - rendering colored GameObject from mesh my glDrawArrays

SpriteRender - rendering GameObject with image by glDrawElements
____________________________________________________________________
*/


#include "MeshRenderer.h"

#include "VertexShader.h"
#include "VertexSpriteShader.h"
#include "FragmentShader.h"
#include "FragmentSpriteShader.h"


MeshRenderer::MeshRenderer()
{
    
    // vertex shader #1
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
    glCompileShader(vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader #1
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // vertex shader #2
    int vertexSpriteShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexSpriteShader, 1, &vertexSpriteShaderText, NULL);
    glCompileShader(vertexSpriteShader);

    glGetShaderiv(vertexSpriteShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexSpriteShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::SPRITE VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader #2
    int fragmentSpriteShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentSpriteShader, 1, &fragmentSpriteShaderText, NULL);
    glCompileShader(fragmentSpriteShader);

    glGetShaderiv(fragmentSpriteShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentSpriteShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::SPRITE FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    this->shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // link sprite shaders
    this->spriteShaderProgram = glCreateProgram();

    glAttachShader(spriteShaderProgram, vertexSpriteShader);
    glAttachShader(spriteShaderProgram, fragmentSpriteShader);
    glLinkProgram(spriteShaderProgram);

    glGetProgramiv(spriteShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(spriteShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // clear memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentSpriteShader);

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Render(GameObject* renderingObject)
{
	//creating VAO and VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) *  renderingObject->MeshSize, renderingObject->Mesh.data(), GL_STATIC_DRAW);

    if(renderingObject->ObjectShape == RECTANGLE)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    else if(renderingObject->ObjectShape == CIRCLE)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glUseProgram(shaderProgram);

    glUniform2f(glGetUniformLocation(shaderProgram, "position"), renderingObject->Position.x, renderingObject->Position.y);
    glUniform3f(glGetUniformLocation(shaderProgram, "ObjectColor"),
        renderingObject->Color.x,
        renderingObject->Color.y,
        renderingObject->Color.z);


	//drawing into buffer
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO);

	if (renderingObject->isSolid)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, renderingObject->MeshSize);
	}
	else
	{
		glDrawArrays(GL_LINE_LOOP, 0, renderingObject->MeshSize);
	}
 
	glDisableVertexAttribArray(0);

	//clearing VAO and VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}


void MeshRenderer::SpriteRender(GameObject* renderingObject)
{
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    //creating VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * renderingObject->MeshSize, renderingObject->Mesh.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //drawing into buffer
    

   glBindTexture(GL_TEXTURE_2D, renderingObject->texture);

   glUseProgram(spriteShaderProgram);

    glUniform2f(glGetUniformLocation(spriteShaderProgram, "position"), renderingObject->Position.x, renderingObject->Position.y);
    
    glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //clearing VAO, VBO, EBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}