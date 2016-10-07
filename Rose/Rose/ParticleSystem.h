#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "Vector2f.h"
#include "Color.h"
#include "Object.h"
#include <vector>


class ParticleSystem : public Object
{
public:

	bool systemInitiated = false;
	bool active;
	bool spin = false;
	bool emit = false;			/*True == particles are blown away from center. False == Particles are sucked into center*/
	bool renderAsPoints = false;
	float particleScale = 1.0f;

	struct Particle {
		Vector2f position;
		Vector2f velocity;
		Color color;
		float life;
	};

	Vector2f position;
	Vector2f positionDev;
	Color colorDev;
	Color color;

	void init();
	void update(float dt);
	void draw();


	ParticleSystem();
	ParticleSystem(Vector2f pos, Color col = Color(0, 0, 0), bool renderAsP = true, float speed = 32.0f, float size = 32.0f, int max = 500, bool spin = false, bool emit = false);
	~ParticleSystem();

private:

	void generateVAO();
	void updateBuffers();
	int getLastUnused();
	void setNewParticle(int index);

	GLuint VAO, VBO_positions, VBO_colors;
	float newParticlePart = 0.0f;

	int max_particles;
	int particle_count;
	int last_unused_particle;
	float particle_life;
	float particle_speed;

	Particle * particles;

};

