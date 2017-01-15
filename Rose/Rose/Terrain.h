#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "Res.h"
#include "Object.h"
#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>


class Terrain
{
public:


	enum TileType;
	class TerrainChunk;

	struct Tile {
		int texture = 0;
		TileType type = TileType::GRASS_FULL;
	};

	Tile * tiles;
	int worldScaleX, worldScaleY;

	GLuint VAO;
	GLuint VBO_vertices, VBO_textures, VBO_inst_pos, VBO_inst_tex;


	void draw();

	float tileScale;

	Terrain();
	Terrain(std::string str);
	~Terrain();

	void addTerrain(Vector2f position = Vector2f(0,0));

	bool isWalkable(Tile tile);
	void setTile(Vector2f pos, int i);
	void deleteChunk(Vector2f pos);
	bool getSolid(Object o);
	bool getSolid(Vector2f pos);
	void loadTerrain(std::string filename);
	void saveTerrain(std::string filename);

	void generateBuffers();
	void buildTerrain(int type[]);
	void rebuildAll();

	enum TileType {
		GRASS_FULL,
		DIRT_FULL,

		GRASS_BOTTOM_RIGHT_DIRT,
		GRASS_BOTTOM_LEFT_DIRT,
		GRASS_TOP_RIGHT_DIRT,
		GRASS_TOP_LEFT_DIRT,

		GRASS_TOP_DIRT,
		GRASS_BOTTOM_DIRT,
		GRASS_LEFT_DIRT,
		GRASS_RIGHT_DIRT,

	};


};


