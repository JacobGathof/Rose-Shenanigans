#pragma once
#include "GL\glew.h"
#include "Vector2f.h"
#include <vector>


class ParticleSystem
{
public:

	struct Particle {
		Vector2f position;
		Vector2f velocity;
		float life;
	};


	bool emit = true;
	int max_particles = 500;
	int particle_count = 0;
	int last_unused_particle = 0;
	float particle_life = 1.0f;
	float particle_speed = 10.0f;


	Vector2f position;
	Vector2f color;
	Particle particles[500];

	GLuint VAO, VBO_positions, VBO_colors;

	void update(float dt);
	void sortParticles();
	int getLastUnused();
	void setNewParticle(int index);
	void render();
	ParticleSystem() {};
	ParticleSystem(bool t);
	~ParticleSystem();


};

