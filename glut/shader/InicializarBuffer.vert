#version 430 core

layout (location = 0) in vec4 vPosision;
layout (location = 1) in vec4 color;

out vec4 vColor;

void main()
{
    vColor = color;
    gl_Position = vPosision;
}