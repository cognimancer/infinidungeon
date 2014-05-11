/*
#version 150

out vec4 fColor;

uniform vec4 dColor;

void main() {
	fColor = dColor;
}
*/
#version 330

in vec4 fVert;
in vec2 UV;
in vec3 fColor;
in vec3 fNormal;
out vec3 gl_Color;

uniform sampler2D TextureID;
uniform mat4 model;
uniform int nTexture = 0;

uniform struct Light {
	vec3 position;
	vec3 intensities; //a.k.a the color of the light
} light;

uniform vec3 lPosition;

void main()
{
	//calculate normal in world coordinates
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 normal = normalize(normalMatrix * fNormal);

	//calculate the location of this fragment (pixel) in world coordinates
	vec3 fragPosition = vec3(model * fVert);
	
	//calculate the vector from this pixels surface to the light source
	vec3 surfaceToLight = lPosition - fragPosition;

    //calculate the cosine of the angle of incidence (brightness)
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);

	if(nTexture == 0)
	{
		//gl_Color = fColor;
	}
	else
	{
		//gl_Color = texture2D( TextureID, UV ).rgb;
		//gl_Color = gl_Color * fColor;
		gl_Color = brightness * texture(TextureID, UV).rgb;
		//gl_Color = vec3(brightness,brightness,brightness);
		gl_Color = clamp(gl_Color, 0.0, 1.0);
	}
}