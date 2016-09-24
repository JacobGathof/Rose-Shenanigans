#include "Terrain.h"
#include <sstream>


void Terrain::draw() {
	for (auto t : terrain) {
		t->draw();
	}
}

void Terrain::setTile(Vector2f pos, int i){

	TerrainChunk * t = terrain[0];

	int index = tilesPerChunk*(int)(pos.x / tileScale) + ((int)(pos.y / tileScale) % tilesPerChunk);

	int data[] = { i };

	t->tileTexture[index] = i;

	glBindVertexArray(t->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, t->VBO_inst_tex);
	glBufferSubData(GL_ARRAY_BUFFER, index * 4, 4, data);

}

void Terrain::loadTerrain(std::string filename){


	std::ifstream file;
	file.open(filename, file.in);

	char buffer[8192];

	while (!file.eof()) {

		std::stringstream line;

		file.getline(buffer, 64);
		if (buffer[0] == '\0') break;
		line << buffer;

		char b1[4];
		char b2[4];

		line.getline(b1, 64, ',');
		line.getline(b2, 64, ' ');

		Vector2f pos(std::stoi(b1), std::stoi(b2));
		TerrainChunk * chunk = new TerrainChunk(pos, tilesPerChunk, tileScale);


		file.getline(buffer, 8192);
		line.str(buffer);

		line.seekg(line.beg);

		int ptr = 0;
		int * tileTextures = new int[tilesPerChunk*tilesPerChunk];
		while (!line.eof()) {

			line.getline(buffer, 64, ',');
			if (buffer[0] == '\0') continue;
			if (buffer[0] == 'a') {}
			int i = std::stoi(buffer);
			tileTextures[ptr++] = i;
		}

		line.str("");

		chunk->buildTerrain(tileTextures);

		terrain.push_back(chunk);

	}

}

void Terrain::saveTerrain(std::string filename){

	std::ofstream file;
	file.open(filename, file.out);

	for (auto t : terrain) {
		std::string s(t->position.toString()+"\n");
		file.write((s).c_str(), std::strlen(s.c_str()));

		for (int i = 0; i < tilesPerChunk; i++) {
			for (int j = 0; j < tilesPerChunk; j++) {
				int v = (t->tileTexture[tilesPerChunk*i + j]);
				std::string q = std::to_string(v) + ",";
				file.write(q.c_str(), q.length());
			}
		}

		file.write("\n", 1);
	}

	file.close();

}

void Terrain::TerrainChunk::buildTerrain(int textures[]) {

	tilePosition = new float[tilesPerChunk*tilesPerChunk*2];
	tileTexture = new int[tilesPerChunk*tilesPerChunk];

	for (int i = 0; i < tilesPerChunk; i++) {
		for (int j = 0; j < tilesPerChunk; j++) {
			tilePosition[2 * i*tilesPerChunk + 2 * j + 0] = i*1.0f;
			tilePosition[2 * i*tilesPerChunk + 2 * j + 1] = j*1.0f;

			tileTexture[i*tilesPerChunk + j] = textures[i*tilesPerChunk+j];

		}
	}

	delete[] textures;

	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0 };
	float texures[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	
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
	glBufferData(GL_ARRAY_BUFFER, tilesPerChunk * tilesPerChunk * 4 * 2, tilePosition, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_tex);
	glBufferData(GL_ARRAY_BUFFER, tilesPerChunk * tilesPerChunk * 4, tileTexture, GL_STATIC_DRAW);
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

	ShaderProgram * shader = Res::getShader(terrainShader);
	shader->loadVector2f("scale", scale);
	shader->loadVector2f("pos", position);

	glBindVertexArray(VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, tilesPerChunk*tilesPerChunk);

}