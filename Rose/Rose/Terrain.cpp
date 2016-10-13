#include "Terrain.h"
#include <sstream>


Terrain::Terrain() {
	tilesPerChunk = 16;
	tileScale = 16.0f;
	loadTerrain("Resources/Town of Beginnings");
};

Terrain::Terrain(std::string str) {
	tilesPerChunk = 16;
	tileScale = 16.0f;
	loadTerrain("Resources/" + str);
};

Terrain::~Terrain() {
	for (auto t : terrain) {
		delete t.second;
	}
};


void Terrain::addTerrain(Vector2f pos) {
	TerrainChunk * c = new TerrainChunk(pos, tilesPerChunk, tileScale);
	c->buildTerrain(0, 0);
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

	t->tiles[index].texture = i;

	glBindVertexArray(t->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, t->VBO_inst_tex);
	glBufferSubData(GL_ARRAY_BUFFER, index * 4, 4, data);

}

void Terrain::setTile(Vector2f pos, bool b){
	Vector2f cPos = pos / (tileScale*tilesPerChunk);
	cPos = cPos.round();

	if (terrain.find(cPos) == terrain.end()) {
		addTerrain(cPos);
		return;
	}

	TerrainChunk * t = terrain[cPos];
	Vector2f pPos = pos - (cPos*tileScale*tilesPerChunk);

	int index = tilesPerChunk*(int)(pPos.x / tileScale) + ((int)(pPos.y / tileScale) % tilesPerChunk);

	t->tiles[index].isWalkable = b;
}

void Terrain::deleteChunk(Vector2f pos){

	Vector2f cPos = pos / (tileScale*tilesPerChunk);
	cPos = cPos.round();

	if (terrain.find(cPos) == terrain.end()) {
		return;
	}

	TerrainChunk * t = terrain[cPos];
	terrain.erase(terrain.find(cPos));
	delete t;

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

	return !t->tiles[index].isWalkable;
	
}

void Terrain::loadTerrain(std::string filename){


	std::ifstream file;
	//file.open(filename, file.in);
	//if (file.is_open()) {
	//	int response = MessageBox(NULL, L"Could not open file, Try again?", L"", MB_ICONERROR | MB_ABORTRETRYIGNORE);
	//}
	//std::cout << filename << std::endl;
	int response;
	do {
		response = IDABORT;
		file.open(filename, file.in);
		if (!file.is_open()) {
			response = MessageBox(NULL, L"Could not open terrain file, try again?", L"Terrain Error", MB_ICONERROR | MB_CANCELTRYCONTINUE);
		}
	} while (response == IDTRYAGAIN);

	//if (response == IDCANCEL) {
	//	std::cout << "aborted" << std::endl;
	//	return;
	//}
	//else if (response == IDCONTINUE) {
	//	std::cout << "ignored" << std::endl;
	//}

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
		int * tileWalkable = new int[tilesPerChunk*tilesPerChunk];

		while (!line.eof()) {

			line.getline(buffer, 64, ',');
			if (buffer[0] == '\0') continue;
			int w = (int)(buffer[0]);
			int t = std::stoi(&buffer[1]);
			tileWalkable[ptr] = w;
			tileTextures[ptr++] = t;
		}

		line.str("");

		chunk->buildTerrain(tileTextures, tileWalkable);
		terrain[pos] = chunk;
	}

}

void Terrain::saveTerrain(std::string filename){

	std::ofstream file;
	file.open("Resources/" + filename, file.out);

	for (auto t : terrain) {
		std::string s(t.second->position.toIntString()+"\n");
		file.write((s).c_str(), std::strlen(s.c_str()));

		for (int i = 0; i < tilesPerChunk; i++) {
			for (int j = 0; j < tilesPerChunk; j++) {
				Tile tile = t.second->tiles[tilesPerChunk*i + j];
				int v = tile.texture;
				int w = tile.isWalkable;
				std::string q = std::to_string(w) + std::to_string(v) + ",";
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

void Terrain::TerrainChunk::buildTerrain(int textures[], int walkable[]) {

	for (int i = 0; i < tilesPerChunk; i++) {
		for (int j = 0; j < tilesPerChunk; j++) {
			tiles[i*tilesPerChunk + j].position.x = i*1.0f;
			tiles[i*tilesPerChunk + j].position.y = j*1.0f;

			if (walkable == 0) tiles[i*tilesPerChunk + j].isWalkable = true;
			else tiles[i*tilesPerChunk + j].isWalkable = walkable[i*tilesPerChunk + j];

			if (textures == 0) tiles[i*tilesPerChunk + j].texture = 0;
			else tiles[i*tilesPerChunk + j].texture = textures[i*tilesPerChunk+j];

		}
	}

	delete[] textures;
	delete[] walkable;

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
	glBufferData(GL_ARRAY_BUFFER, tilesPerChunk * tilesPerChunk * 4 * 2, 0, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_tex);
	glBufferData(GL_ARRAY_BUFFER, tilesPerChunk * tilesPerChunk * 4, 0, GL_STATIC_DRAW);
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

void Terrain::TerrainChunk::rebuildAll(){

	float* pos = new float[tilesPerChunk*tilesPerChunk * 2];
	int* tex = new int[tilesPerChunk*tilesPerChunk];

	for (int i = 0; i < tilesPerChunk; i++) {
		for (int j = 0; j < tilesPerChunk; j++) {
			pos[2 * i*tilesPerChunk + 2 * j + 0] = tiles[i*tilesPerChunk + j].position.x;
			pos[2 * i*tilesPerChunk + 2 * j + 1] = tiles[i*tilesPerChunk + j].position.y;

			tex[i*tilesPerChunk + j] = tiles[i*tilesPerChunk + j].texture;

		}
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_pos);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4*tilesPerChunk*tilesPerChunk*2, pos);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_inst_tex);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * tilesPerChunk*tilesPerChunk, tex);

	delete[] pos;
	delete[] tex;

}

void Terrain::TerrainChunk::draw() {

	Res::getTexture("Grass")->bind();

	ShaderProgram * shader = Res::getShader(terrainShader);
	shader->loadVector2f("scale", Vector2f(scale, scale));

	shader->loadVector2f("pos", position*(tilesPerChunk*scale));

	glBindVertexArray(VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, tilesPerChunk*tilesPerChunk);
	
}