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

			tileTexture[i*tilesPerChunk + j] = rand() % 3;

		}
	}

	float * dividedTilePositions = new float[tilesPerChunk*tilesPerChunk * 4 * 2];
	int * dividedTileTextures = new int[tilesPerChunk*tilesPerChunk * 4];

	int pptr = 0;
	int vptr = 0;
	for (int i = 0; i < tilesPerChunk; i++) {
		for (int j = 0; j < tilesPerChunk; j++) {
			for (int k = 0; k < 4; k++) {
				dividedTilePositions[pptr++] = i*3.0f + 1.1*(k/2);
				dividedTilePositions[pptr++] = j*3.0f + 1.1*(k%2);

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