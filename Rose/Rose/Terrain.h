#pragma once
#include "Vector2f.h"
#include "Res.h"
#include <iostream>
#include <vector>

class Terrain
{
public:

	enum TileType {

		TOP_RIGHT_CORNER,
		TOP_LEFT_CORNER,
		BOT_RIGHT_CORNER,
		BOT_LEFT_CORNER,

		TOP_PATH,
		BOT_PATH,
		LEFT_PATH,
		RIGHT_PATH,

		DIRT,



	};


	class TerrainChunk;

	std::vector<TerrainChunk*> terrain;
	void draw();

	int tilesPerChunk;
	float tileScale;

	Terrain() {
		tilesPerChunk = 8;
		tileScale = 10.0f;
	};

	void addTerrain() {
		terrain.push_back(new TerrainChunk(Vector2f(0, 0), tilesPerChunk, tileScale));
	}

	~Terrain() {
		for (auto t : terrain) {
			delete t;
		}
	};



	class TerrainChunk {

		public:
			GLuint VAO;
			int tilesPerChunk;
			Vector2f scale;
			Vector2f position;
			float * tilePosition;
			int * tileTexture;

			TerrainChunk(Vector2f pos, int tpc, int sc) {
				position = pos;
				tilesPerChunk = tpc;
				scale = Vector2f(sc, sc);
				buildTerrain();
			};
			~TerrainChunk() {
				delete[] tilePosition;
				delete[] tileTexture;
			};
			void buildTerrain();
			void draw();

	};
};


