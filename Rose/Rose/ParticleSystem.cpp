#include "ParticleSystem.h"
#include "Res.h"
#include <iostream>

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

		//col[3 * ptr + 0] = particles[i].color.x;
		//col[3 * ptr + 1] = particles[i].color.y;
		//col[3 * ptr + 2] = particles[i].color.z;

		col[3 * ptr + 0] = .7f;
		col[3 * ptr + 1] = .5f;
		col[3 * ptr + 2] = .1f;

		ptr++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * particle_count, pos, GL_STREAM_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(2, 1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * particle_count, col, GL_STREAM_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(3, 1);

	delete[] pos;
	delete[] col;


}

void ParticleSystem::sortParticles()
{

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
		(((float)rand() / RAND_MAX) - .5f)).normalize() * particle_speed;

	//particles[index].color = color + Vector3f(colorDev.x * (float)rand() / RAND_MAX, colorDev.y * ((float)rand() / RAND_MAX), colorDev.z * ((float)rand() / RAND_MAX));
	particles[index].position = position;
}

void ParticleSystem::render() {


	Res::getShader("particleShader")->use();
	//Res::getTexture("ParticleTexture")->bindTexture();

	glBindVertexArray(this->VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, particle_count);

}

ParticleSystem::ParticleSystem(bool t)
{

	max_particles = 500;
	particle_count = 0;
	last_unused_particle = 0;
	particle_life = 0.5f;
	particle_speed = 32.0f;


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	float *pos = new float[0 * 3];
	float *col = new float[0 * 3];

	for (int i = 0; i < 0; i++) {
		pos[3 * i + 0] = particles[i].position.x;
		pos[3 * i + 1] = particles[i].position.y;

		/*
		col[3 * i + 0] = particles[i].color.x;
		col[3 * i + 1] = particles[i].color.y;
		col[3 * i + 2] = particles[i].color.z;
		*/
	}

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
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * max_particles, pos, GL_STREAM_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(2, 1);
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &VBO_colors);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * max_particles, col, GL_STREAM_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(3);

	delete[] pos;
	delete[] col;
}


ParticleSystem::~ParticleSystem()
{

}
