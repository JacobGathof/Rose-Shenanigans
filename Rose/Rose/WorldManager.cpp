#include "WorldManager.h"


World * WorldManager::currentWorld;
std::map<std::string, World*> WorldManager::worlds;



void WorldManager::init(){

	World * world = new World("Town of Beginnings");
	world->AddEntity(new Entity(Vector2f(-30, 30), Vector2f(20, 20), "Rain", 20));

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {
			world->AddObject(new Object(Vector2f(-30 + 40 * i, 0+-40*j), Vector2f(20, 20), "Candle"));
			world->AddLight(new Light(Vector2f(-20 + 40 * i, -40*j + 20 - 3), Color(1, i / 4.0, j / 4.0), 2.0f));
		}
	}

	world->addTerrain(new Terrain("Town of Beginnings"));


	World * world2 = new World("World 2");
	world2->AddEntity(new Entity(Vector2f(0, 10), Vector2f(10, 10), "Edwin", 20));
	world2->AddLight(new Light(Vector2f(10, 0), Color(1, 0, 1), 16.0f));
	world2->addTerrain(new Terrain("World 2"));


	World * world3 = new World("World 3");
	//world3->AddSystem(new ParticleSystem(Vector2f(64, 64), Color(0, 0, 0), true, 128.0f, 2.00f, 10000, false, false));
	world3->AddLight(new Light(Vector2f(10, 0), Color(1, 0, 1), 16.0f));
	world3->addTerrain(new Terrain("World 3"));
	

	world->AddLoadZone(LoadZone(world, world2, Vector2f(50,80), Vector2f(10,10)));

	world->AddLoadZone(LoadZone(world, world3, Vector2f(50, 50), Vector2f(10, 10)));

	world3->AddLoadZone(LoadZone(world3, world, Vector2f(0, 0), Vector2f(10, 10)));

	world2->AddLoadZone(LoadZone(world2, world, Vector2f(-50, 0), Vector2f(10, 10)));


	addWorld(world);
	addWorld(world2);
	addWorld(world3);
	makeWorldCurrent("Town of Beginnings");

}

void WorldManager::addToAllWorlds(Entity * e){
	for (auto w : worlds) {
		w.second->AddEntity(e);
	}
}

void WorldManager::addWorld(World* w) {
	worlds[w->name] = w;
}

void WorldManager::loadWorld(World w){
	//Dynamic loading, if we get around to it
}

World* WorldManager::getWorld(std::string name){
	return worlds[name];
}

World* WorldManager::getCurrentWorld(){
	return currentWorld;
}

void WorldManager::makeWorldCurrent(std::string name){
	currentWorld = worlds[name];
	currentWorld->loadWorldResources();
}

void WorldManager::drawWorld(){
	currentWorld->draw();
}

void WorldManager::destroy(){
	for (auto w : worlds) {
		w.second->unloadWorld();
		delete w.second;
	}
}

void WorldManager::checkWorld(Player* player) {
	World * world = currentWorld->checkLoad(player);
	if (world != 0) {
		makeWorldCurrent(world->name);
	}
}

void WorldManager::tick(){
	currentWorld->tick();
}

void WorldManager::update(float dt){
	currentWorld->update(dt);
}
