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
		Vector2f position;
		TileType type = TileType::GRASS_FULL;
	};

	std::map<Vector2f, TerrainChunk*> terrainChunks;

	void draw();

	int tilesPerChunk;
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

	class TerrainChunk {

		public:
			GLuint VAO;
			GLuint VBO_vertices, VBO_textures, VBO_inst_pos, VBO_inst_tex;
			int tilesPerChunk;
			float scale;
			Vector2f position;
			Tile * tiles;

			TerrainChunk(Vector2f pos, int tpc, float sc) {
				position = pos;
				tilesPerChunk = tpc;
				scale = sc;
				tiles = new Tile[tpc*tpc];
			};

			~TerrainChunk() {
				delete[] tiles;
			};

			void generateBuffers();
			void loadBuffers();
			void buildTerrain(int textures[], int walkable[]);
			void rebuildAll();
			void draw();


	};

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


