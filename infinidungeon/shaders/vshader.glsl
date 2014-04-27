#version 150

in vec4 vPosition;  // relative position
uniform mat4 mvp; // model, view, projection

void main() {
    gl_Position = mvp * vPosition;
}
