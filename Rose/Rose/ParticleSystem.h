#pragma once
#include "GL\glew.h"
#include "Vector2f.h"
#include "Color.h"
#include <vector>


class ParticleSystem
{
public:

	bool systemInitiated = false;

	struct Particle {
		Vector2f position;
		Vector2f velocity;
		float life;
	};

	bool renderAsPoints = false;
	float particleScale = 1.0f;

	bool emit;
	int max_particles;
	int particle_count;
	int last_unused_particle;
	float particle_life;
	float particle_speed;

	Vector2f position;
	Color color;
	Particle * particles;

	GLuint VAO, VBO_positions, VBO_colors;

	void init();
	void update(float dt);
	int getLastUnused();
	void setNewParticle(int index);
	void draw();


	ParticleSystem();
	ParticleSystem(Vector2f pos, Color col=Color(0,0,0), float speed=32.0f, float life=1.0f, int max=500);
	~ParticleSystem();


};

