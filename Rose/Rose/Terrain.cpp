#include "Terrain.h"
#include "Renderer.h"
#include <sstream>


Terrain::Terrain() {
	tileScale = 32.0f;
	loadTerrain("Resources/Town of Beginnings");
}

Terrain::Terrain(std::string str) {
	tileScale = 32.0f;
	loadTerrain("Resources/" + str);
}

Terrain::~Terrain() {

}


void Terrain::addTerrain(Vector2f pos) {
	
}

bool Terrain::isWalkable(Tile tile)
{
	if (tile.type == TileType::DIRT_FULL) return false;
	return false;
}

void Terrain::setTile(Vector2f pos, int i){

	

}


void Terrain::deleteChunk(Vector2f pos){

	

}

bool Terrain::getSolid(Object o)
{
	return getSolid(o.position + Vector2f(0+4,0)) || getSolid(o.position + Vector2f(o.scale.x-4, 0)) || getSolid(o.position + Vector2f(4, .3f*o.scale.y)) || getSolid(o.position + Vector2f(o.scale.x-4, .3f*o.scale.y));
}

bool Terrain::getSolid(Vector2f pos){

	/*
	Vector2f cPos = pos / (tileScale*tilesPerChunk);
	cPos = cPos.round();

	if (terrainChunks.find(cPos) == terrainChunks.end()) {
		return false;
	}

	TerrainChunk * t = terrainChunks[cPos];
	Vector2f pPos = pos - (cPos*tileScale*(float)tilesPerChunk);

	int index = tilesPerChunk*(int)(pPos.x / tileScale) + ((int)(pPos.y / tileScale) % tilesPerChunk);

	return !isWalkable(t->tiles[index]);
	*/ 
	return false;
}

void Terrain::loadTerrain(std::string filename){

	std::cout << "Loading Map" << std::endl;

	std::ifstream file;
	file.open(filename, file.in);

	char lineBuffer[65536];
	char buffer[4];

	std::stringstream line;

	file.getline(lineBuffer, 65536);

//	if (buffer[0] == '\0') break;
	line << lineBuffer;
	//std::cout << line.str();

	char b1[4];
	char b2[4];

	line.getline(b1, 4, ',');
	line.getline(b2, 4, ',');

	worldScaleX = std::stoi(b1);
	worldScaleY = std::stoi(b2);

	tiles = new Tile[worldScaleX*worldScaleY];

	int ptr = 0;
	int * tileTextures = new int[worldScaleX*worldScaleY];

	while (!line.eof()) {

		line.getline(buffer, 4, ',');
		if (buffer[0] == '\0') continue;
		int t = std::stoi(&buffer[0]);
		tileTextures[ptr++] = t;
	}

	line.str("");

	buildTerrain(tileTextures);
	
	std::cout << "Loaded Terrain" << std::endl;

}

void Terrain::saveTerrain(std::string filename){

	std::ofstream file;
	file.open("Resources/" + filename, file.out);

	std::string s(std::to_string(worldScaleX)+","+std::to_string(worldScaleY)+",");
	file.write((s).c_str(), std::strlen(s.c_str()));

	for (int i = 0; i < worldScaleX; i++) {
		for (int j = 0; j < worldScaleY; j++) {
			
			Tile tile = tiles[worldScaleY*i + j];
			int v = tile.texture;
			std::string q = std::to_string(v) + ",";
			file.write(q.c_str(), q.length());

		}
	}

	file.close();

}

void Terrain::generateBuffers(){

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO_vertices);
	glGenBuffers(1, &VBO_textures);
	glGenBuffers(1, &VBO_inst_pos);
	glGenBuffers(1, &VBO_inst_tex);

}

void Terrain::buildTerrain(int type[]) {

	for (int i = 0; i < worldScaleX; i++) {
		for (int j = 0; j < worldScaleY; j++) {

			if (type == 0) tiles[i*worldScaleX + j].type = TileType::GRASS_FULL;
			else tiles[i*worldScaleX + j].type = (TileType)type[i*worldScaleX + j];

		}
	}

	delete[] type;

	float vertices[] = { 0.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f , 1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f };
	float texures[] = { 0.0f,1.0f, 0.0f,0.0f, 1.0f,0.0f , 1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f };

	generateBuffers();

	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, 48, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_textures);
	glBufferData(GL_ARRAY_BUFFER, 48, texures, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_pos);
	glBufferData(GL_ARRAY_BUFFER, worldScaleX * worldScaleY * 4 * 2, 0, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_tex);
	glBufferData(GL_ARRAY_BUFFER, worldScaleX * worldScaleY * 4, 0, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(3, 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	rebuildAll();

}

void Terrain::rebuildAll(){

	float* pos = new float[worldScaleX * worldScaleY * 2];
	int* tex = new int[worldScaleX * worldScaleY];

	int counter = 0;
	for (int i = 0; i < worldScaleX; i++) {
		for (int j = 0; j < worldScaleY; j++) {
			//pos[2 * i*worldScaleY + 2 * j + 0] = i*tileScale;
			//pos[2 * i*worldScaleY + 2 * j + 1] = j*tileScale;

			pos[counter++] = i;
			pos[counter++] = j;

			tex[i*worldScaleY + j] = tiles[i*worldScaleY + j].texture;

		}
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_pos);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4* worldScaleX * worldScaleY *2, pos);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_tex);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * worldScaleX * worldScaleY, tex);

	delete[] pos;
	delete[] tex;

}

void Terrain::draw() {
	Renderer::renderTerrain(this);
}