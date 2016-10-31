#pragma once
#include "Building.h"
#include "UIElement.h"
#include <vector>


/*---------------------------------------
				Light
----------------------------------------*/
class Light {
public:
	Vector2f position;
	Color color;
	float intensity;

	Light(Vector2f pos, Color color, float intensity) : position(pos), color(color), intensity(intensity) {}
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

	static void checkEnemyCollisions(Player * player);
	static void addPlayerToSlimes(Entity * player);

	static World * currentWorld;
	static std::map<std::string, World*> worlds;

	static void checkWorld(Player* player);
	static void tick();
	static void update(float dt);



};

/*---------------------------------------
			UIManager
----------------------------------------*/ 
class UIManager {
public:

	static Textbox textbox;
	static Statbox statbox;
	static UIElement tilebox;

	static void init();
	static void destroy();
	static void update();
	static void tick();
	static void drawTextured();

	UIManager();
	~UIManager();
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
	static void init();
	static void destroy();
};

