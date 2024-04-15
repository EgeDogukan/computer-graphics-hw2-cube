#version 410

in vec4 vPosition;
in vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
//uniform vec4 disp;

void main()
{
    gl_Position = Projection * ModelView * vPosition;
    //gl_Position = Projection * (vPosition + disp);
    color = vColor;
}
