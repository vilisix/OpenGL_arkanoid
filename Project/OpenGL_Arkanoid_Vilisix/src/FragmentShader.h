/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

fragment shader for objects on scene,
	to calculate object's color
____________________________________________________________________
*/


#pragma once

const char* fragmentShaderText = "#version 330 core\n"
"uniform vec3 ObjectColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ObjectColor, 1.0f);\n"
"}\n\0";