#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "Res.h"
#include <iostream>
#include <vector>

class Terrain
{
public:

	enum TileType {

	};


	class TerrainChunk;

	std::vector<TerrainChunk*> terrain;
	void draw();

	int tilesPerChunk;
	float tileScale;

	Terrain() {
		tilesPerChunk = 16;
		tileScale = 16.0f;
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


