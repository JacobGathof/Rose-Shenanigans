#include "Projectile.h"
#include "Renderer.h"


Projectile::Projectile(Vector2f pos, Vector2f scale, TextureName texName, float speed, Vector2f dir) : Entity(pos, scale, texName, speed)
{
	system = new ParticleSystem(Vector2f(0, 0), ColorRGB(1, 1, 1), 16.0f, 16.0f, 100);
	this->dir = dir;
}


Projectile::~Projectile()
{
}

void Projectile::draw() {
	Renderer::renderProjectile(this);

}

void Projectile::update(float dt){
	Entity::update(dt);

	life -= dt;
	system->update(dt);
	if (life <= 0.0f) {
		this->destroy();
		delete system;
	}
	this->position += dir * speed;
	system->position = this->centerOfMass;
}
