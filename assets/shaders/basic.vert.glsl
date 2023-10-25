#version 330 core
layout (location = 0) in vec3 vPos;

uniform mat4 vProjectionMatrix;
uniform mat4 vModelMatrix;

void main()
{
    gl_Position = vProjectionMatrix * vModelMatrix * vec4(vPos, 1.0);
}