#include "ParticleSystem.h"
#include "Res.h"
#include <iostream>

void ParticleSystem::init(){

	systemInitiated = true;
	particles = new Particle[max_particles];

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint vertices;
	GLuint tex;

	float vertices_[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0 };
	float tex_[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };

	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, 4 * 12, vertices_, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(0);


	glGenBuffers(1, &tex);
	glBindBuffer(GL_ARRAY_BUFFER, tex);
	glBufferData(GL_ARRAY_BUFFER, 4 * 12, tex_, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &VBO_positions);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * max_particles, 0, GL_STREAM_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(2, 1);
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &VBO_colors);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * max_particles, 0, GL_STREAM_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(3);

}

void ParticleSystem::update(float dt)
{

	int new_particles = (int)(max_particles*dt / (particle_life));
	if (new_particles <= 0)
		new_particles = 1;
	if (new_particles > 1)
		new_particles = 1;

	if (emit) {
		for (int i = 0; i < new_particles; i++) {
			int index = getLastUnused();
			if (index == -1) continue;

			setNewParticle(index);
		}
	}

	particle_count = 0;

	for (int i = 0; i < max_particles; i++) {

		if (particles[i].life <= 0.0f) {
			continue;
		}

		particle_count++;

		particles[i].position = particles[i].position + dt* particles[i].velocity;
		particles[i].life -= dt;

	}


	glBindVertexArray(VAO);

	float *pos = new float[particle_count * 2];
	float *col = new float[particle_count * 3];
	int ptr = 0;

	for (int i = 0; i < max_particles; i++) {
		if (particles[i].life <= 0) continue;

		pos[2 * ptr + 0] = particles[i].position.x;
		pos[2 * ptr + 1] = particles[i].position.y;

		col[3 * ptr + 0] = color.r;
		col[3 * ptr + 1] = color.g;
		col[3 * ptr + 2] = color.b;

		ptr++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 2 * particle_count, pos);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 3 * particle_count, col);

	delete[] pos;
	delete[] col;


}

int ParticleSystem::getLastUnused()
{
	for (int i = last_unused_particle; i < max_particles; i++) {
		if (particles[i].life <= 0) {
			last_unused_particle = i;
			return i;
		}
	}

	for (int i = 0; i < last_unused_particle; i++) {
		if (particles[i].life <= 0) {
			last_unused_particle = i;
			return i;
		}
	}

	return -1;
}

void ParticleSystem::setNewParticle(int index)
{
	particles[index].life = particle_life;
	particles[index].velocity = Vector2f((
		((float)rand() / RAND_MAX) - .5f),
		(((float)rand() / RAND_MAX) - .5f)).normalize() * particle_speed * ((float)rand()/RAND_MAX/2 + .5);

	//particles[index].color = color + Vector3f(colorDev.x * (float)rand() / RAND_MAX, colorDev.y * ((float)rand() / RAND_MAX), colorDev.z * ((float)rand() / RAND_MAX));
	particles[index].position = position;
}

void ParticleSystem::draw() {


	Res::getShader("particleShader")->use();
	//Res::getTexture("ParticleTexture")->bindTexture();

	glBindVertexArray(this->VAO);

	glDrawArraysInstanced(GL_POINTS, 0, 1, particle_count);

}

ParticleSystem::ParticleSystem()
{

	particle_count = 0;
	last_unused_particle = 0;
	emit = true;

	max_particles = 500;
	particle_life = 0.5f;
	particle_speed = 32.0f;
	color = Color(1,0,0);
	position = Vector2f(0, 0);
}

ParticleSystem::ParticleSystem(Vector2f pos, Color col, float speed, float life, int max)
{
	particle_count = 0;
	last_unused_particle = 0;
	emit = true;

	position = Vector2f(pos.x, pos.y);
	color = Color(col.r, col.g, col.b);
	particle_speed = speed;
	particle_life = life;
	max_particles = max;
}


ParticleSystem::~ParticleSystem()
{
	if (systemInitiated) {
		delete[] particles;
		std::cout << "Particles Deleted\n";
	}
}
