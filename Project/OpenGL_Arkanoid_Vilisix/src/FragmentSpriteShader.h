/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

fragment sprite shader for objects on scene,
	to calculate images
____________________________________________________________________
*/


#pragma once

const char* fragmentSpriteShaderText = "#version 330 core\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"uniform sampler2D sprite;\n"
"void main()\n"
"{\n"
"   FragColor = texture(sprite,TexCoord);\n"
"}\n\0";