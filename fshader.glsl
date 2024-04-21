#version 410

in vec4 color;
out vec4 fragColor;

uniform float intensity; // The blinking intensity


void main()
{
     fragColor = color;
}

