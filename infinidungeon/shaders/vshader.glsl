/*
#version 150

in vec4 vPosition;  // relative position
uniform mat4 mvp; // model, view, projection

void main() {
    gl_Position = mvp * vPosition;
}
*/
#version 330

in vec4 vPosition; //Vertex Position
in vec3 vColor; //Vertex Color
in vec2 vUV; //Vertex UV
in vec3 vNormal; // Vertex Normal

out vec3 fColor; //Fragment Color (sent to the fragment shader)
out vec2 UV; //UVCoordinate
out vec3 fNormal;
out vec4 fVert;

uniform mat4 MVP; //Final Composed Matrix

void main()
{
	gl_Position = MVP * vPosition;
	fColor = vColor;
	fNormal = vNormal;
	UV = vUV;
	fVert = vPosition;
}
