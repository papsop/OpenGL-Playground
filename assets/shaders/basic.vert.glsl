#version 330 core
layout (location = 0) in vec3 vPos;

uniform mat4 vProjectionMatrix;

void main()
{
    gl_Position = vProjectionMatrix * vec4(vPos, 1.0);
}