#include "ParticleSystem.h"
#include "Res.h"
#include <iostream>
#include "Input.h"

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

	if ((Camera::position.x - SCALEFACTOR - system_size < position.x) && (Camera::position.x + SCALEFACTOR + system_size > position.x) &&
		(Camera::position.y - SCALEFACTOR - system_size < position.y) && (Camera::position.y + SCALEFACTOR + system_size > position.y)) {
		options |= ACTIVE;

		float newParticlesUnrounded = (max_particles*dt / (particle_life));
		int new_particles = (int)newParticlesUnrounded;

		if (new_particles <= 0) {
			newParticlePart += newParticlesUnrounded;
			if (newParticlePart >= 1.0f) {
				new_particles = 1;
				newParticlePart -= 1.0f;
			}
		}

		if (new_particles > 32)
			new_particles = 32;

		for (int i = 0; i < new_particles; ++i) {
			int index = getLastUnused();
			if (index == -1) continue;

			setNewParticle(index);
		}

		particle_count = 0;
		float Constant = sqrt(particle_life);

		for (int i = 0; i < max_particles; ++i) {

			if (particles[i].life <= 0.0f) {
				continue;
			}

			particle_count++;

			
			if (isSpinning() && !isEmitting()) {
				Vector2f vel = (position - particles[i].position);
				particles[i].velocity = vel * particle_speed;
				//TODO: work on calculation optimization
				//looks like additional optimization will have to cut down on vel.magnitude()
				particles[i].velocity = ((particles[i].velocity) + (Vector2f(vel.y, -vel.x) * particle_speed * Constant)) / vel.magnitude();
			}
			else if (isSpinning() && isEmitting()) {
				particles[i].velocity += 1 * dt*Vector2f(particles[i].velocity.y, -particles[i].velocity.x);
			}

			else if (isSin()){
				particles[i].velocity = Vector2f(128, 128*sin( particles[i].position.x / 16)) ;
			}
			
			if (isRandomVel()) {
				Vector2f randomVelocity = particles[i].velocity %= Vector2f(8, 8);
				particles[i].velocity = randomVelocity.normalize() * particle_speed * ((float)rand() / RAND_MAX / 2 + .5f);
			}

			particles[i].position += dt* particles[i].velocity;
			particles[i].life -= dt;

		}

		updateBuffers();
	}
	else {
		options &= !ACTIVE;
	}
	//if (active) {
	//	
	//}
	

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
	particles[index].color = color;
	particles[index].position = position;


	if (isEmitting()) {
		particles[index].velocity = Vector2f((
			((float)rand() / RAND_MAX) - .5f),
			(((float)rand() / RAND_MAX) - .5f)).normalize() * particle_speed * ((float)rand() / RAND_MAX / 2 + .5f);

		
		particles[index].position = position;
	}
	
	else {
		Vector2f vel = Vector2f((
			((float)rand() / RAND_MAX) - .5f),
			(((float)rand() / RAND_MAX) - .5f)).normalize() * particle_speed * ((float)rand() / RAND_MAX / 2 + .5f);

		particles[index].velocity = -1 * vel;

		//particles[index].color = (ColorHSV(0, 1.0, 1.0) % 60);
		//particles[index].position = position + particle_life*vel % positionDev;
	}

	if (isRandomVel()) {
		particles[index].position = position %= Vector2f(128, 128);
	}

	if (isRandomColor()) {
		particles[index].color = color % colorDev;
	}

	if (isColorHSV()) {
		particles[index].color = ((ColorHSV(color.x, color.y, color.z) % 60));
	}
	
	if (isSin()) {
		particles[index].position = position %= Vector2f(4,4);
	}
	

}

void ParticleSystem::draw() {

	if (Input::testVar) {
		glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer("LightFBO"));
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	Res::getShader(particleShader);
	Res::getTexture("Light")->bind();

	glBindVertexArray(this->VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, particle_count);


	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer("WorldFBO"));

}

bool ParticleSystem::isSpinning(){		return (options & SPIN) >>				0 == 0x0001;}
bool ParticleSystem::isEmitting(){		return (options & EMIT) >>				1 == 0x0001;}
bool ParticleSystem::isActive(){		return (options & ACTIVE) >>			2 == 0x0001;}
bool ParticleSystem::isRandomVel(){		return (options & RANDOM_VELOCITY) >>	3 == 0x0001;}
bool ParticleSystem::isRandomColor(){	return (options & RANDOM_COLOR) >>		4 == 0x0001;}
bool ParticleSystem::isColorHSV(){		return (options & COLOR_HSV) >>			5 == 0x0001;}
bool ParticleSystem::isSin(){			return (options & SIN) >>				6 == 0x0001;}

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

	max_particles = 16;
	system_size = 1.0f;
	particle_speed = 1.0f;
	particle_life = system_size/particle_speed;
	color = Color(0,0,0);
	position = Vector2f(0, 0);
}

ParticleSystem::ParticleSystem(Vector2f pos, Color col,float speed, float size, int max, int op)
{
	options = op | ACTIVE;

	particle_count = 0;
	last_unused_particle = 0;

	position = Vector2f(pos);
	positionDev = Vector2f(0,0);
	color = Color(col.x, col.y, col.z);
	colorDev = Color(.5, .5, .5);
	system_size = size;
	particle_speed = speed;
	particle_life = size/speed;
	max_particles = max;

	init();
}


ParticleSystem::~ParticleSystem()
{
	if (systemInitiated) {
		delete[] particles;
	}
}
