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

	Terrain();
	Terrain(std::string str);
	~Terrain();

	void addTerrain();
	void addTerrain(Vector2f position);

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

			TerrainChunk(Vector2f pos, int tpc, float sc) {
				position = pos;
				tilesPerChunk = tpc;
				scale = Vector2f(sc, sc);
			};

			~TerrainChunk() {
				delete[] tilePosition;
				delete[] tileTexture;
			};

			void generateBuffers();
			void loadBuffers();
			void buildTerrain(int textures[]);
			void draw();

	};


};


