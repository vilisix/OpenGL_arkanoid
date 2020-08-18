/*
Arkanoid Game - Nikita Vilisov, 2020

___________________________________________________________________

vertex shader for objects on scene
____________________________________________________________________
*/

#pragma once


const char* vertexShaderText = 
"#version 330 core\n"
"layout (location = 0) in vec2 vPos;\n"
"uniform vec2 position;"
"void main()\n"
"{\n"
"   gl_Position = vec4(vPos.x + position.x, vPos.y + position.y, 0.0f, 1.0f);\n"
"}\0";

//gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0)