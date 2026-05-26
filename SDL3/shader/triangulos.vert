#version 430 core

layout (location = 0) in vec4 vPosision;

void main()
{
    gl_Position = vPosision;
}