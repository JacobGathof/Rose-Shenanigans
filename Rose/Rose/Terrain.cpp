#include "Terrain.h"



void Terrain::draw() {
	for (auto t : terrain) {
		t->draw();
	}
}

void Terrain::TerrainChunk::buildTerrain() {

	tilePosition = new float[tilesPerChunk*tilesPerChunk*2];
	tileTexture = new int[tilesPerChunk*tilesPerChunk];

	for (int i = 0; i < tilesPerChunk; i++) {
		for (int j = 0; j < tilesPerChunk; j++) {
			tilePosition[2 * i*tilesPerChunk + 2 * j + 0] = i*1.1f;
			tilePosition[2 * i*tilesPerChunk + 2 * j + 1] = j*1.1f;

			tileTexture[i*tilesPerChunk + j] = rand() % 2;

		}
	}

	float * dividedTilePositions = new float[tilesPerChunk*tilesPerChunk * 4 * 2];
	int * dividedTileTextures = new int[tilesPerChunk*tilesPerChunk * 4];

	int pptr = 0;
	int vptr = 0;
	for (int i = 0; i < tilesPerChunk; i++) {
		for (int j = 0; j < tilesPerChunk; j++) {

			for (int k = 0; k < 4; k++) {
				dividedTilePositions[pptr++] = i*2.0f + 1.0*(k / 2);
				dividedTilePositions[pptr++] = j*2.0f + 1.0*(k % 2);
			}

			if (tileTexture[i*tilesPerChunk + j] == 1) {
				int north, south, east, west;

				if (j == tilesPerChunk - 1) north = 0;	else { north = tileTexture[(i + 0)*tilesPerChunk + j + 1];  }
				if (j == 0) south = 0;					else { south = tileTexture[(i + 0)*tilesPerChunk + j - 1]; }
				if (i == tilesPerChunk-1) east = 0;		else { east = tileTexture[(i + 1)*tilesPerChunk + j + 0]; }
				if (i == 0) west = 0;					else { west = tileTexture[(i - 1)*tilesPerChunk + j + 0]; }

				/*Bottom left corner*/
				if (south == 0 && west == 0) {
					dividedTileTextures[vptr++] = 16+3;
				}
				else if (south == 0 && west != 0) {
					dividedTileTextures[vptr++] = 16+7;
				}
				else if (south != 0 && west == 0) {
					dividedTileTextures[vptr++] = 16+2;
				}
				else {
					int sw;
					if (j == 0 || i == 0) sw = 0;	else { sw = tileTexture[(i + -1)*tilesPerChunk + j + -1]; }
					if(sw == 0)
						dividedTileTextures[vptr++] = 33;
					else
						dividedTileTextures[vptr++] = 16+5;
				}
				/*End*/

				
				/*Top left corner*/
				if (north == 0 && west == 0) {
					dividedTileTextures[vptr++] = 16 + 0;
				}
				else if (north == 0 && west != 0) {
					dividedTileTextures[vptr++] = 16 + 4;
				}
				else if (north != 0 && west == 0) {
					dividedTileTextures[vptr++] = 16 + 1;
				}
				else {
					int nw;
					if (j == tilesPerChunk-1 || i == 0) nw = 0;	else { nw = tileTexture[(i + -1)*tilesPerChunk + j + 1]; }
					if (nw == 0)
						dividedTileTextures[vptr++] = 32;
					else
						dividedTileTextures[vptr++] = 16 + 5;
				}
				/*End*/


				/*Bottom Right corner*/
				if (south == 0 && east == 0) {
					dividedTileTextures[vptr++] = 16 + 15;
				}
				else if (south == 0 && east != 0) {
					dividedTileTextures[vptr++] = 16 + 7;
				}
				else if (south != 0 && east == 0) {
					dividedTileTextures[vptr++] = 16 + 13;
				}
				else {
					int se;
					if (j == 0 || i == tilesPerChunk - 1) se = 0;	else { se = tileTexture[(i + 1)*tilesPerChunk + j + -1]; }
					if (se == 0)
						dividedTileTextures[vptr++] = 35;
					else
						dividedTileTextures[vptr++] = 16 + 5;

				}
				/*End*/



				/*Top Right corner*/
				if (north == 0 && east == 0) {
					dividedTileTextures[vptr++] = 16 + 12;
				}
				else if (north == 0 && east != 0) {
					dividedTileTextures[vptr++] = 16 + 4;
				}
				else if (north != 0 && east == 0) {
					dividedTileTextures[vptr++] = 16 + 13;
				}
				else {

					int ne;
					if (j == tilesPerChunk-1 || i == tilesPerChunk - 1) ne = 0;	else { ne = tileTexture[(i + 1)*tilesPerChunk + j + 1]; }
					if (ne == 0)
						dividedTileTextures[vptr++] = 34;
					else
						dividedTileTextures[vptr++] = 16 + 5;
				
				}
				/*End*/

			}

			else {
				dividedTileTextures[vptr++] = tileTexture[i*tilesPerChunk + j];
				dividedTileTextures[vptr++] = tileTexture[i*tilesPerChunk + j];
				dividedTileTextures[vptr++] = tileTexture[i*tilesPerChunk + j];
				dividedTileTextures[vptr++] = tileTexture[i*tilesPerChunk + j];
			}

		}
	}

	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0 };
	float texures[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO_vertices, VBO_textures, VBO_inst_pos, VBO_inst_tex;
	glGenBuffers(1, &VBO_vertices);
	glGenBuffers(1, &VBO_textures);
	glGenBuffers(1, &VBO_inst_pos);
	glGenBuffers(1, &VBO_inst_tex);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, 48, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_textures);
	glBufferData(GL_ARRAY_BUFFER, 48, texures, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_pos);
	glBufferData(GL_ARRAY_BUFFER, tilesPerChunk * tilesPerChunk * 4 * 2 * 4, dividedTilePositions, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_tex);
	glBufferData(GL_ARRAY_BUFFER, tilesPerChunk * tilesPerChunk * 4*4, dividedTileTextures, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(3, 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	delete[] dividedTilePositions;
	delete[] dividedTileTextures;

}

void Terrain::TerrainChunk::draw() {

	Res::getTexture("Grass")->bind();

	ShaderProgram * shader = Res::getShader("terrainShader");
	shader->loadVector2f("scale", scale);
	shader->loadVector2f("pos", position);

	glBindVertexArray(VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, tilesPerChunk*tilesPerChunk*4);

}