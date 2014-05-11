#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include "DisplayObject.h"
#include <glfw3.h>
#include "Camera.h"

struct Particle{
	glm::vec3 pos, speed;
	unsigned char r,g,b,a;
	float size, angle, weight;
	float life;
};

class ParticleGenerator : DisplayObject
{
protected:
	static const int MaxParticles = 100000;
	static GLfloat* g_particule_position_size_data; 
	static GLubyte* g_particule_color_data;        
	GLuint b_vertex_buffer;
	int LastUsedParticle;
	Particle ParticlesContainer[MaxParticles];
	
public:
	ParticleGenerator(void);
	ParticleGenerator(const ParticleGenerator &other);
	ParticleGenerator &operator=( const ParticleGenerator &other );
	~ParticleGenerator(void);
	void init(void);
	//void render(void);
	int FindUnusedParticle(void);
	double lastTime;
	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
};

#endif