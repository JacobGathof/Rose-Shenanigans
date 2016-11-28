#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "Vector2f.h"
#include "Color.h"
#include "Object.h"
#include "Camera.h"
#include <vector>

#define SPIN 0x01
#define EMIT 0x02
#define ACTIVE 0x04
#define RANDOM_VELOCITY 0x08
#define RANDOM_COLOR 0x10
#define COLOR_HSV 0x20

class ParticleSystem
{
public:

	int options = 0x00;

	bool systemInitiated = false;
	//bool active;
	//bool spin = false;
	//bool emit = false;			/*True == particles are blown away from center. False == Particles are sucked into center*/
	float particleScale = 1.0f;
	float system_size;

	float temp = 0;

	struct Particle {
		Vector2f position;
		Vector2f velocity;
		ColorRGB color;
		float life;
	};

	Vector2f position;
	Vector2f positionDev;
	Color colorDev;
	Color color;

	void init();
	void update(float dt);
	void draw();
	bool isActive();
	bool isEmitting();
	bool isSpinning();
	bool isRandomVel();
	bool isRandomColor();
	bool isColorHSV();

	ParticleSystem();
	ParticleSystem(Vector2f pos, Color col = Color(0, 0, 0), float speed = 32.0f, float size = 32.0f, int max = 500, int op = 0x00);
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

