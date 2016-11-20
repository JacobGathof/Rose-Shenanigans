#pragma once
#include "Res.h"
#include "Entity.h"
#include "UIElement.h"
#include "Terrain.h"


class Renderer
{
public:

	static void renderObject(Object * object);
	static void renderHitbox(Object * object);
	static void renderEntity(Entity* entity);

	static void renderDefaultUIElement(UIElement* element);
	static void renderTextbox(Textbox * box);
	static void renderStatbox(Statbox * box);
	static void renderText(Text* text);

	static void renderTerrainChunk(Terrain::TerrainChunk* chunk);
	static void renderScreen();


	static void render();
	static void prepareToRender();

};

