#include "Terrain.h"
#include <sstream>


Terrain::Terrain() {
	tilesPerChunk = 4;
	tileScale = 16.0f;
	loadTerrain("Town of Beginnings");
};

Terrain::Terrain(std::string str) {
	tilesPerChunk = 4;
	tileScale = 16.0f;
	loadTerrain(str);
};

Terrain::~Terrain() {
	for (auto t : terrain) {
		delete t.second;
	}
};


void Terrain::addTerrain(Vector2f pos) {
	TerrainChunk * c = new TerrainChunk(pos, tilesPerChunk, tileScale);
	c->buildTerrain(0);
	terrain[pos] = c;
}

void Terrain::draw() {
	for (auto t : terrain) {
		t.second->draw();
	}
}

void Terrain::setTile(Vector2f pos, int i){

	Vector2f cPos = pos / (tileScale*tilesPerChunk);
	cPos = cPos.round();

	if (terrain.find(cPos) == terrain.end()) {
		addTerrain(cPos);
		return;
	}

	TerrainChunk * t = terrain[cPos];
	Vector2f pPos = pos - (cPos*tileScale*tilesPerChunk);

	int index = tilesPerChunk*(int)(pPos.x / tileScale) + ((int)(pPos.y / tileScale) % tilesPerChunk);

	int data[] = { i };

	t->tileTexture[index] = i;

	glBindVertexArray(t->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, t->VBO_inst_tex);
	glBufferSubData(GL_ARRAY_BUFFER, index * 4, 4, data);

}

bool Terrain::getSolid(Object o)
{
	return getSolid(o.position + Vector2f(0+4,0)) || getSolid(o.position + Vector2f(o.scale.x-4, 0)) || getSolid(o.position + Vector2f(4, .3*o.scale.y)) || getSolid(o.position + Vector2f(o.scale.x-4, .3*o.scale.y));
}

bool Terrain::getSolid(Vector2f pos){

	Vector2f cPos = pos / (tileScale*tilesPerChunk);
	cPos = cPos.round();

	if (terrain.find(cPos) == terrain.end()) {
		return false;
	}

	TerrainChunk * t = terrain[cPos];
	Vector2f pPos = pos - (cPos*tileScale*tilesPerChunk);

	int index = tilesPerChunk*(int)(pPos.x / tileScale) + ((int)(pPos.y / tileScale) % tilesPerChunk);

	return t->tileTexture[index] == 13;
	
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
			int i = std::stoi(buffer);
			tileTextures[ptr++] = i;
		}

		line.str("");

		chunk->buildTerrain(tileTextures);
		terrain[pos] = chunk;
	}

}

void Terrain::saveTerrain(std::string filename){

	std::ofstream file;
	file.open(filename, file.out);

	for (auto t : terrain) {
		std::string s(t.second->position.toIntString()+"\n");
		file.write((s).c_str(), std::strlen(s.c_str()));

		for (int i = 0; i < tilesPerChunk; i++) {
			for (int j = 0; j < tilesPerChunk; j++) {
				int v = (t.second->tileTexture[tilesPerChunk*i + j]);
				std::string q = std::to_string(v) + ",";
				file.write(q.c_str(), q.length());
			}
		}

		file.write("\n", 1);
	}

	file.close();

}

void Terrain::TerrainChunk::generateBuffers(){

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO_vertices);
	glGenBuffers(1, &VBO_textures);
	glGenBuffers(1, &VBO_inst_pos);
	glGenBuffers(1, &VBO_inst_tex);

}

void Terrain::TerrainChunk::loadBuffers()
{
}

void Terrain::TerrainChunk::buildTerrain(int textures[]) {

	tilePosition = new float[tilesPerChunk*tilesPerChunk*2];
	tileTexture = new int[tilesPerChunk*tilesPerChunk];

	for (int i = 0; i < tilesPerChunk; i++) {
		for (int j = 0; j < tilesPerChunk; j++) {
			tilePosition[2 * i*tilesPerChunk + 2 * j + 0] = i*1.0f;
			tilePosition[2 * i*tilesPerChunk + 2 * j + 1] = j*1.0f;

			if (textures == 0) tileTexture[i*tilesPerChunk + j] = 0;
			else tileTexture[i*tilesPerChunk + j] = textures[i*tilesPerChunk+j];

		}
	}

	delete[] textures;

	float vertices[] = { 0,0, 0,1, 1,1 , 1,1, 1,0, 0,0 };
	float texures[] = { 0,1, 0,0, 1,0 , 1,0, 1,1, 0,1 };

	generateBuffers();

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
	shader->loadVector2f("scale", Vector2f(scale, scale));

	shader->loadVector2f("pos", position*(tilesPerChunk*scale));

	glBindVertexArray(VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, tilesPerChunk*tilesPerChunk);
	
}