#include "Enemy.h"
#include "Timer.h"
#include "UI_Manager.h"


Enemy::Enemy(Entity* target, World* world, Vector2f pos, Vector2f scale, std::string texName, float speed) : Entity(pos, scale, texName, speed)
{
	this->target = target;
	this->world = world;
}



Enemy::~Enemy()
{
}

void Enemy::update(float dt){

	if (current_cooldown <= 0.0f) {
		shoot(dt);
		current_cooldown = cooldown;
	}
	current_cooldown -= dt;


	if (current_predict_cooldown <= 0.0f) {
		shootPrediction(dt);
		current_predict_cooldown = predict_cooldown;
	}
	current_predict_cooldown -= dt;

}

void Enemy::tick(){
	analyze();
}

void Enemy::analyze(){
	prediction.v2 = prediction.v1;
	prediction.v1 = target->centerOfMass;
	prediction.d2 = prediction.d1;
	prediction.d1 = target->position^this->position;
	prediction.time2 = prediction.time1;
	prediction.time1 = Timer::currentTime;
}

void Enemy::shoot(float dt){

	//std::cout << "Creating new Projectile";

	
	
	for (int i = 0; i < 10; i++) {
		Vector2f position = this->centerOfMass + Vector2f(0, 64 * (2 * ((float)rand() / RAND_MAX) - 1.0f)) + Vector2f(16 * 4 * (2*((float)rand() / RAND_MAX)-1.0f), 0);
		Vector2f direction = ((target->position - position) + Vector2f(8*(2 * ((float)rand() / RAND_MAX) - 1.0f), 8*(2 * ((float)rand() / RAND_MAX) - 1.0f))).normalize();
		world->AddEntity(new Projectile(position, Vector2f(4, 4), "FireSlime", 2.0f, direction));

	}
	//world->AddEntity(new Projectile(this->centerOfMass, Vector2f(10, 10), "GreenSlime", 1.0f, (target->centerOfMass - this->centerOfMass).normalize()));

}

void Enemy::shootPrediction(float dt){

	UIManager::textbox.print("Mongrel");

	Vector2f direction = ((target->centerOfMass + (prediction.v1 - prediction.v2)*(prediction.time2 - prediction.time1)) - this->centerOfMass).normalize();

	world->AddEntity(new Projectile(this->centerOfMass, Vector2f(4, 4), "FireSlime", 1.0f, direction));

}
