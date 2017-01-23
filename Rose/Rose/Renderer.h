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

	/*Render function for any Object*/
	static void renderObject(Object * object);

	/*Render function for Hitboxes*/
	static void renderHitbox(Object * object);

	/*Render function for any Entity*/
	static void renderEntity(Entity* entity);


	static void renderProjectile(Projectile* proj);

	static void renderParticleSystem(ParticleSystem* sys);

	/*Render function for any UIElement*/
	static void renderDefaultUIElement(UI_Element* element);

	/*Render function for the Textbox*/
	static void renderTextbox(UI_Textbox * box);

	/*Render function for the Textbox*/
	static void renderTitle(UI_Title * title);

	/*Render function for the Statbox*/
	static void renderStatbox(UI_Statbox * box);

	/*Render function for any piece of Text*/
	static void renderText(Text* text);

	/*Renders Inventory screen*/
	static void renderInventoyScreen(Weapon * weapons, Texture *backdrop, int size);

	static void renderSkill(Skill *s, int i);

	/*Render function for a single TerrainChunk*/
	static void renderTerrain(Terrain* terrain);

	/*Combine framebuffers and display to the monitor*/
	static void renderScreen();


	/*Initiate rendering calls in WorldManager and LightManager*/
	static void render();

	/*Clear all necessary components before actually rendering*/
	static void prepareToRender();

};

