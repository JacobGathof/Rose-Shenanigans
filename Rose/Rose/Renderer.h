#pragma once
#include "Res.h"
#include "Entity.h"
#include "UIElement.h"
#include "Terrain.h"

/*
	Static class holding the drawing methods for everything in the game. 
	"Draw()" methods will only perform a call to the appropriate function in this class
*/

class Renderer
{
public:

	/*Render function for any Object*/
	static void renderObject(Object * object);

	/*Render function for Hitboxes*/
	static void renderHitbox(Object * object);

	/*Render function for any Entity*/
	static void renderEntity(Entity* entity);

	/*Render function for any UIElement*/
	static void renderDefaultUIElement(UIElement* element);

	/*Render function for the Textbox*/
	static void renderTextbox(Textbox * box);

	/*Render function for the Statbox*/
	static void renderStatbox(Statbox * box);

	/*Render function for any piece of Text*/
	static void renderText(Text* text);


	static void renderSkill(Skill *s, int i);

	/*Render function for a single TerrainChunk*/
	static void renderTerrainChunk(Terrain::TerrainChunk* chunk);

	/*Combine framebuffers and display to the monitor*/
	static void renderScreen();


	/*Initiate rendering calls in WorldManager and LightManager*/
	static void render();

	/*Clear all necessary components before actually rendering*/
	static void prepareToRender();

};

