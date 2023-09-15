#version 330 core

in vec4 fColor; // the input variable from the vertex shader (same name and same type)  

out vec4 FragColor;

void main()
{
    FragColor = fColor;
} 