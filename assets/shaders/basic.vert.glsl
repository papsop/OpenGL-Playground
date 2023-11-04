#version 330 core
layout (location = 0) in vec3 vPos;

uniform mat4 vProjectionMatrix;
uniform mat4 vModelMatrix;
uniform vec4 vColor;

out vec4 fColor;

void main()
{
    fColor = vColor;
    gl_Position = vProjectionMatrix * vModelMatrix * vec4(vPos, 1.0);
}