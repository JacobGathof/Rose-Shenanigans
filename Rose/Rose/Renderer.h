#pragma once
#include "Res.h"
#include "Entity.h"
#include "Projectile.h"
//#include "UI_Manager.h"
#include "Terrain.h"

#define WeaponScale 5

/*
	Static class holding the drawing methods for everything in the game. 
	"Draw()" methods will only perform a call to the appropriate function in this class
*/

class UI_Textbox;
class UI_Statbox;
class UI_Element;
class UI_Title;
class Skill;
class Weapon;

class Renderer
{
public:

	
	static void renderObject(Object * object);
	static void renderHitbox(Object * object);
	static void renderEntity(Entity* entity);


	static void renderProjectile(Projectile* proj);
	static void renderParticleSystem(ParticleSystem* sys);


	static void renderDefaultUIElement(UI_Element* element);
	static void renderTextbox(UI_Textbox * box);
	static void renderTitle(UI_Title * title);
	static void renderStatbox(UI_Statbox * box);


	static void renderText(Text* text);
	static void renderInventoyScreen(Weapon * weapons, Texture *backdrop, int size);
	static void renderSkill(Skill *s, int i);

	static void renderTerrain(Terrain* terrain);
	static void renderScreen();

	static void renderMenu();

	static void render();

	static void prepareToRender();

};

