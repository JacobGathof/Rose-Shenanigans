#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "Res.h"
#include <iostream>
#include <vector>


class Terrain
{
public:

	class TerrainChunk;

	std::vector<TerrainChunk*> terrain;
	void draw();

	int tilesPerChunk;
	float tileScale;

	Terrain() {
		tilesPerChunk = 16;
		tileScale = 16.0f;
		loadTerrain("Town of Beginnings");
	};

	Terrain(std::string str) {
		tilesPerChunk = 16;
		tileScale = 16.0f;
		loadTerrain(str);
	};

	~Terrain() {
		for (auto t : terrain) {
			delete t;
		}
	};

	void addTerrain() {
		terrain.push_back(new TerrainChunk(Vector2f(0, 0), tilesPerChunk, tileScale));
	}

	void setTile(Vector2f pos, int i);
	void loadTerrain(std::string filename);
	void saveTerrain(std::string filename);

	class TerrainChunk {

		public:
			GLuint VAO;
			GLuint VBO_vertices, VBO_textures, VBO_inst_pos, VBO_inst_tex;
			int tilesPerChunk;
			Vector2f scale;
			Vector2f position;
			float * tilePosition;
			int * tileTexture;

			TerrainChunk(Vector2f pos, int tpc, int sc) {
				position = pos;
				tilesPerChunk = tpc;
				scale = Vector2f(sc, sc);
			};

			~TerrainChunk() {
				delete[] tilePosition;
				delete[] tileTexture;
			};

			void buildTerrain(int textures[]);
			void draw();

	};


};


