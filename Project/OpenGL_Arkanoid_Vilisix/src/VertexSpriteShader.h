/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

vertex sprite shader for objects on scene, 
	included position and texCoord VBO's (0 and 1)
____________________________________________________________________
*/

#pragma once

const char* vertexSpriteShaderText = "#version 330 core\n"
"layout (location = 0) in vec2 vPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"uniform vec2 position;"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   TexCoord = aTexCoord; \n"
"   gl_Position = vec4(vPos.x + position.x, vPos.y + position.y, 0.0f, 1.0f);\n"
"}\n\0";