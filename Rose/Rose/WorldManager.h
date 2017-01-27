#pragma once
#include "UI_Element.h"
#include <vector>


/*---------------------------------------
				Light
----------------------------------------*/
class Light {
public:
	Vector2f position;
	ColorRGB color;
	float intensity;

	Light(Vector2f pos, ColorRGB color, float intensity) : position(pos), color(color), intensity(intensity) {}
};


class World;

class WorldManager
{
public:

	/*---------------------------------------
				WorldManager
	----------------------------------------*/
	static void init();
	static void addToAllWorlds(Entity * e);
	static void addWorld(World * w);
	static void loadWorld(World w);
	static World* getWorld(std::string name);
	static World* getCurrentWorld();
	static void makeWorldCurrent(std::string name);
	static void drawWorld();
	static void destroy();
	static bool collide(Object o);
	static NPC* findClosestNPC(Vector2f pos);
	static bool freeze;

	static void checkEnemyCollisions(Player * player);
	//static void addPlayerToSlimes(Entity * player);

	static World * currentWorld;
	static std::map<std::string, World*> worlds;

	static void checkWorld(Player* player);
	static void tick();
	static void update(float dt);



};






/*---------------------------------------
			LightManager
----------------------------------------*/
class LightManager {
public:

	static int numberOfLights;

	static std::vector<Light*> lights;

	static void addLight(Light* light);
	static void clearLights();
	static void updateLights(float gameTime);
	static void reloadLights(ShaderType shader);
	static void drawLights();

	static void cleanUp();

	LightManager();
	~LightManager();

};


/*---------------------------------------
			NPCManager
----------------------------------------*/
class NPCManager
{
public:
	NPCManager();
	~NPCManager();

	static std::map<std::string, NPC*> npcs;
	static void init(Player* player);
	static void destroy();
};

