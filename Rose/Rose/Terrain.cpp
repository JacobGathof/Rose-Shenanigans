#include "Terrain.h"



void Terrain::draw() {
	for (auto t : terrain) {
		t->draw();
	}
}

void Terrain::TerrainChunk::buildTerrain() {

	tilePosition = new float[tilesPerChunk*tilesPerChunk*2];
	tileTexture = new int[tilesPerChunk*tilesPerChunk];

	int pptr = 0;
	int vptr = 0;
	for (int i = 0; i < tilesPerChunk*tilesPerChunk; i++) {
		tilePosition[pptr++] = i/tilesPerChunk;
		tilePosition[pptr++] = i%tilesPerChunk;

		tileTexture[vptr++] = 2;
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
	glBufferData(GL_ARRAY_BUFFER, pptr*4, tilePosition, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_tex);
	glBufferData(GL_ARRAY_BUFFER, vptr*4, tileTexture, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(3, 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Terrain::TerrainChunk::draw() {

	Res::getTexture("Grass")->bind();

	ShaderProgram * shader = Res::getShader("terrainShader");
	shader->loadVector2f("scale", scale);
	shader->loadVector2f("pos", position);

	glBindVertexArray(VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, tilesPerChunk*tilesPerChunk);

}