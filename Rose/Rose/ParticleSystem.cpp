#include "ParticleSystem.h"
#include "Res.h"
#include <iostream>

void ParticleSystem::init(){

	systemInitiated = true;
	particles = new Particle[max_particles];

	generateVAO();

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

void ParticleSystem::generateVAO(){

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

}


void ParticleSystem::update(float dt)
{
	float newParticlesUnrounded = (max_particles*dt / (particle_life));
	int new_particles = (int)newParticlesUnrounded;

	if (new_particles <= 0) {
		newParticlePart += newParticlesUnrounded;
		if (newParticlePart >= 1.0f) {
			new_particles = 1;
			newParticlePart -= 1.0f;
		}
	}

	if (new_particles > 50)
		new_particles = 50;

	if (active) {
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
		
		if (spin && !emit) {
			Vector2f vel = (position - particles[i].position);
			particles[i].velocity = vel.normalize()*particle_speed;
			//TODO: work on calculation optimization
			particles[i].velocity += (Vector2f(vel.y, -vel.x) * (particle_speed * sqrt(particle_life) / (vel.magnitude())) );
		}
		else if(spin && emit) {
			particles[i].velocity += 1*dt*Vector2f(particles[i].velocity.y, -particles[i].velocity.x);
		}
		else {
			
		}
		particles[i].position += dt* particles[i].velocity;
		particles[i].life -= dt;

	}

	updateBuffers();

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
	if (emit) {
		particles[index].life = particle_life;
		particles[index].velocity = Vector2f((
			((float)rand() / RAND_MAX) - .5f),
			(((float)rand() / RAND_MAX) - .5f)).normalize() * particle_speed * ((float)rand() / RAND_MAX / 2 + .5);

		particles[index].color = color % colorDev;
		particles[index].position = position % positionDev;
	}

	else {
		particles[index].life = particle_life;
		Vector2f vel = Vector2f((
			((float)rand() / RAND_MAX) - .5f),
			(((float)rand() / RAND_MAX) - .5f)).normalize() * particle_speed * ((float)rand() / RAND_MAX / 2 + .5);

		particles[index].velocity = -1 * vel;

		particles[index].color = color % colorDev;
		particles[index].position = position + particle_life*vel % positionDev;
	}

}

void ParticleSystem::draw() {


	Res::getShader(particleShader);
	//Res::getTexture("Fire")->bind();

	glBindVertexArray(this->VAO);

	glDrawArraysInstanced(	renderAsPoints ? GL_POINTS : GL_TRIANGLES, 0, 
							renderAsPoints ? 1 : 6, particle_count);

}

void ParticleSystem::updateBuffers() {

	glBindVertexArray(VAO);

	float *pos = new float[particle_count * 2];
	float *col = new float[particle_count * 3];
	int ptr = 0;

	for (int i = 0; i < max_particles; i++) {
		if (particles[i].life <= 0) continue;

		pos[2 * ptr + 0] = particles[i].position.x;
		pos[2 * ptr + 1] = particles[i].position.y;

		col[3 * ptr + 0] = particles[i].color.r;
		col[3 * ptr + 1] = particles[i].color.g;
		col[3 * ptr + 2] = particles[i].color.b;

		ptr++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 2 * particle_count, pos);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 3 * particle_count, col);

	delete[] pos;
	delete[] col;

}

ParticleSystem::ParticleSystem()
{

	particle_count = 0;
	last_unused_particle = 0;
	active = true;
	spin = false;
	emit = emit;

	max_particles = 500;
	particle_life = 0.5f;
	particle_speed = 32.0f;
	color = Color(1,0,0);
	position = Vector2f(0, 0);
}

ParticleSystem::ParticleSystem(Vector2f pos, Color col, bool renderAsP, float speed, float life, int max, bool spin, bool emit)
{
	renderAsPoints = renderAsP;
	particle_count = 0;
	last_unused_particle = 0;
	active = true;
	this->spin = spin;
	this->emit = emit;

	position = Vector2f(pos.x, pos.y);
	positionDev = Vector2f(0,0);
	color = Color(col.r, col.g, col.b);
	colorDev = Color(0,0,0);
	particle_speed = speed;
	particle_life = life;
	max_particles = max;

	init();
}


ParticleSystem::~ParticleSystem()
{
	if (systemInitiated) {
		delete[] particles;
	}
}
