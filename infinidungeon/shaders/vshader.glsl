#version 150

in vec4 vPosition;

uniform mat4 ortho;
uniform mat4 world;

void main()
{
    gl_Position = ortho * world * vPosition;
}
