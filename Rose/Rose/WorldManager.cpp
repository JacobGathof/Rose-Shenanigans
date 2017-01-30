#include "WorldManager.h"
#include "World.h"
#include "Slime.h"
#include "Enemy.h"


#pragma region WORLDMANAGER

World * WorldManager::currentWorld;
std::map<std::string, World*> WorldManager::worlds;
bool WorldManager::freeze;

void WorldManager::init() {
	freeze = false;
	World * world = new World("Town of Beginnings");
	//world->AddObject(new Object(Vector2f(32, 32), Vector2f(90, 90), "House"));
	//world->AddSystem(new ParticleSystem(Vector2f(0, 0), ColorRGB(1, 1, 1), 64.0f, 512.0f, 500));
	
	/*
	for (int i = 0; i < 40; i++) {
		Vector2f pos = 200.0f*Vector2f(cos(i / 40.0f * 3.14159 * 2), sin(i / 40.0f * 3.14159 * 2));
		world->AddObject(new Entity(pos, Vector2f(64, 128), Fire));
	}
	
	for (int i = 0; i < 20; i++) {
		Vector2f pos = 20.0f*Vector2f(0, i-10);
		world->AddObject(new Entity(pos, Vector2f(64/4, 128/4), Fire));
	}
	*/

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			world->AddObject(new Object(Vector2f(-30 + 40 * i, 0 + -40 * j), Vector2f(20, 20), Candle));
			world->AddLight(new Light(Vector2f(-20 + 40 * i, -40 * j + 20 - 3), ColorRGB(1,.5,0), 64.0f));
		}
	}

	world->addTerrain(new Terrain("Town of Beginnings"));


	World * world2 = new World("Carpenter House");
	//world2->AddEntity(new Entity(Vector2f(0, 10), Vector2f(10, 10), "Edwin", 20));
	world2->AddLight(new Light(Vector2f(10, 0), ColorRGB(1, 0, 1), 16.0f));
	world2->addTerrain(new Terrain("Carpenter House"));


	World * world3 = new World("Library of Aventheim");
	//world3->AddSystem(new ParticleSystem(Vector2f(64, 64), ColorRGB(0, 0, 0), 64.0f, 128.00f, 2000, SPIN | RANDOM_COLOR));
	//world3->AddSystem(new ParticleSystem(Vector2f(64, 64), ColorRGB(0, 0, 0), 32.0f, 96.00f, 3000, SPIN | RANDOM_COLOR));
	world3->AddLight(new Light(Vector2f(10, 0), ColorRGB(1, 0, 1), 16.0f));
	world3->addTerrain(new Terrain("Library of Aventheim"));


	//world->AddLoadZone(LoadZone(world, world2, Vector2f(50, 80), Vector2f(10, 10)));
	//world->AddLoadZone(LoadZone(world, world3, Vector2f(50, 50), Vector2f(10, 10)));
	world3->AddLoadZone(LoadZone(world3, world, Vector2f(0, 0), Vector2f(10, 10)));
	world2->AddLoadZone(LoadZone(world2, world, Vector2f(-50, 0), Vector2f(10, 10)));


	addWorld(world);
	addWorld(world2);
	addWorld(world3);
	makeWorldCurrent("Town of Beginnings");

}

void WorldManager::addToAllWorlds(Entity * e) {
	for (auto w : worlds) {
		w.second->AddEntity(e);
	}
}

void WorldManager::addWorld(World* w) {
	worlds[w->name] = w;
}

void WorldManager::loadWorld(World w) {
	//Dynamic loading, if we get around to it
}

World* WorldManager::getWorld(std::string name) {
	return worlds[name];
}

World* WorldManager::getCurrentWorld() {
	return currentWorld;
}

void WorldManager::makeWorldCurrent(std::string name) {
	currentWorld = worlds[name];
	currentWorld->loadWorldResources();
}

void WorldManager::drawWorld() {
	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer(WorldFBO));
	currentWorld->draw();
}

void WorldManager::destroy() {
	for (auto w : worlds) {
		w.second->unloadWorld();
		delete w.second;
	}
}

bool WorldManager::collide(Object o) {
	return currentWorld->terrain->getSolid(o);
}

NPC * WorldManager::findClosestNPC(Vector2f pos)
{
	return currentWorld->findClosestNPC(pos);
}

void WorldManager::checkEnemyCollisions(Player * player){

	return currentWorld->checkEnemyCollisions(player);
}

void WorldManager::checkWorld(Player* player) {
	World * world = currentWorld->checkLoad(player);
	if (world != 0) {
		makeWorldCurrent(world->name);
	}
}

void WorldManager::tick() {
	if (!freeze) {
		currentWorld->tick();
	}
}

void WorldManager::update(float dt) {
	if (!freeze) {
		currentWorld->update(dt);
	}
}

#pragma endregion


#pragma region LIGHTMANAGER
std::vector<Light*> LightManager::lights;
int LightManager::numberOfLights;


void LightManager::addLight(Light * light) {

	lights.push_back(light);
	numberOfLights++;
	//updateLights(entityShader);
	//updateLights(staticShader);
	//updateLights(terrainShader);
}

void LightManager::clearLights() {
	numberOfLights = 0;
	lights.clear();
}

void LightManager::updateLights(float gameTime) {

	/*
	ShaderProgram * currentShader = Res::getShader(shader);

	currentShader->loadInteger("numLights", numberOfLights);

	currentShader->loadVector2f((char *)("pointLights[" + std::to_string(numberOfLights - 1) + "].position").c_str(), lights[numberOfLights - 1]->position);
	currentShader->loadColor((char *)("pointLights[" + std::to_string(numberOfLights - 1) + "].color").c_str(), lights[numberOfLights - 1]->color);
	currentShader->loadFloat((char *)("pointLights[" + std::to_string(numberOfLights - 1) + "].intensity").c_str(), lights[numberOfLights - 1]->intensity);
	*/

	ShaderProgram * ls = Res::getShader(lightShader);
	ls->loadFloat("gameTime", gameTime);


}

void LightManager::reloadLights(ShaderType shader)
{

	ShaderProgram * currentShader = Res::getShader(shader);

	currentShader->loadInteger("numLights", numberOfLights);

	for (int i = 0; i < lights.size(); i++) {

		currentShader->loadVector2f((char *)("pointLights[" + std::to_string(i) + "].position").c_str(), lights[i]->position);
		currentShader->loadColor((char *)("pointLights[" + std::to_string(i) + "].color").c_str(), lights[i]->color);
		currentShader->loadFloat((char *)("pointLights[" + std::to_string(i) + "].intensity").c_str(), lights[i]->intensity);
	}

}

void LightManager::drawLights(){


	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer(LightFBO));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	Res::getModel("CenteredModel")->bind();
	Res::getTexture(Light_Tex)->bind();

	ShaderProgram * current = Res::getShader(lightShader);

	for(auto l : lights) {

		current->loadVector2f("pos", l->position);
		current->loadVector2f("scale", Vector2f(l->intensity, l->intensity));
		current->loadColor("color", l->color);

		glDrawArrays(GL_TRIANGLES, 0, 6);

	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


void LightManager::cleanUp()
{
	for (auto l : lights) {
		delete l;
	}
}

LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}
#pragma endregion


#pragma region NPCMANAGER
std::map<std::string, NPC*> NPCManager::npcs;



void NPCManager::init(Player* player) {
	
	NPC* echo = new Echo();
	NPC* jibril = new Jibril();

	npcs["Rose"] = echo;
	npcs["Jibril"] = jibril;

	
	WorldManager::currentWorld->addNPC(echo);
	WorldManager::currentWorld->addNPC(jibril);


	World * world = WorldManager::getWorld("Town of Beginnings");
	//world->AddEntity(new Enemy(player, world, Vector2f(-100, 0), Vector2f(36, 36), Edwin, 100.0f));

	world->AddEntity(new Entity(Vector2f(-100, 50), Vector2f(36, 36), Mavis));
	//world->AddEntity(new Entity(Vector2f(-50, 50), Vector2f(36, 36), "Yuno"));
	//world->AddEntity(new Entity(Vector2f(0, 50), Vector2f(36, 36), "Lucy"));
	//world->AddEntity(new Entity(Vector2f(50, 50), Vector2f(36, 36), "Lizbeth"));

	//world->AddEntity(new Entity(Vector2f(-30, 30), Vector2f(20, 20), "Rain", 20));

	for (int i = 0; i < 0; i++) {
		Vector2f random = Vector2f(250 * (-.5 + (float)(rand()) / RAND_MAX), 250 * (-.5 + (float)(rand()) / RAND_MAX));
		
		Entity * slime;
		if (i == 0) {
			slime = new Slime(random, Vector2f(30, 30), GreenSlime, 15.0f, 0);
		}
		if (i == 1) {
			slime = new Slime(random, Vector2f(30, 30), FireSlime, 10.0f, 0);
		}
		if (i == 2) {
			slime = new Slime(random, Vector2f(30 * 2, 30), SkySlime, 25.0f, 0);
		}

		world->AddEntity(slime);
	}


	
}

void NPCManager::destroy()
{
	for (auto n : npcs) {
		delete n.second;
	}
}

#pragma endregion



