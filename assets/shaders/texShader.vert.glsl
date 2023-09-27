#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vTexCoords;

uniform mat4 vProjectionMatrix;

out vec2 TexCoords;

void main()
{
    gl_Position = vProjectionMatrix * vec4(vPos, 1.0, 1.0);
    TexCoords = vTexCoords;
}  