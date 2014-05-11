#include "ParticleGenerator.h"


ParticleGenerator::ParticleGenerator(void) : DisplayObject() {}

ParticleGenerator::ParticleGenerator(const ParticleGenerator &other)
{

}

ParticleGenerator &ParticleGenerator::operator=(const ParticleGenerator&other)
{
	return *this;
}

ParticleGenerator::~ParticleGenerator(void)
{
	glDeleteBuffers( 1, &_buffer );
	glDeleteProgram( _shader );
	glDeleteVertexArrays( 1, &_vao );
}

void ParticleGenerator::init(void)
{
	LastUsedParticle = 0;
	//g_particule_position_size_data = new GLfloat[MaxParticles * 4];
	//g_particule_color_data  = new GLubyte[MaxParticles * 4];
	for(int i=0; i<MaxParticles; i++){
		ParticlesContainer[i].life = -1.0f;
	}

	//lastTime = glfwGetTime();


	//VBO for particles
	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};
	glGenBuffers(1, &b_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, b_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//vbo containing positon and size of particles
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	//initialize with empty null buffer
	glBufferData(GL_ARRAY_BUFFER, MaxParticles *4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

	//vbo containing colors of the particles

	glGenBuffers(1, &particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	//initialize with empty null buffer
	glBufferData(GL_ARRAY_BUFFER, MaxParticles *4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
}
/*
void ParticleGenerator::render(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Might be redundant.
	double currentTime = glfwGetTime();
	double delta = currentTime - lastTime;
	lastTime = currentTime;

	// Generate 10 new particule each millisecond,
	// but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
	 newparticles will be huge and the next frame even longer.
	int newparticles = (int)(delta*10000.0);
	if (newparticles > (int)(0.016f*10000.0))
		newparticles = (int)(0.016f*10000.0);
		
	for(int i=0; i<newparticles; i++){
		int particleIndex = FindUnusedParticle();
		ParticlesContainer[particleIndex].life = 5.0f; // This particle will live 5 seconds.
		ParticlesContainer[particleIndex].pos = glm::vec3(0,0,-20.0f);

		float spread = 1.5f;
		glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);

			// generate random direction
			glm::vec3 randomdir = glm::vec3(
				(rand()%2000 - 1000.0f)/1000.0f,
				(rand()%2000 - 1000.0f)/1000.0f,
				(rand()%2000 - 1000.0f)/1000.0f
			);
			
			ParticlesContainer[particleIndex].speed = maindir + randomdir*spread;


			// generate a random color
			ParticlesContainer[particleIndex].r = rand() % 256;
			ParticlesContainer[particleIndex].g = rand() % 256;
			ParticlesContainer[particleIndex].b = rand() % 256;
			ParticlesContainer[particleIndex].a = (rand() % 256) / 3;

			ParticlesContainer[particleIndex].size = (rand()%1000)/2000.0f + 0.1f;
	}

	// simulate all particles
	int ParticlesCount = 0;
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);

	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);
	

}
*/
int ParticleGenerator::FindUnusedParticle(void)
{
	for(int i = LastUsedParticle; i<MaxParticles; i++)
	{
		if (ParticlesContainer[i].life < 0){
			LastUsedParticle = i;
			return i;
		}
	}

	for(int i=0; i<LastUsedParticle; i++)
	{
		if (ParticlesContainer[i].life < 0){
			LastUsedParticle = i;
			return i;
		}
	}
	
	return 0;
}
