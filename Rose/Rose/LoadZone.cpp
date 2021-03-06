#include "LoadZone.h"
#include "Res.h"

LoadZone::LoadZone()
{
}


LoadZone::~LoadZone()
{
}

LoadZone::LoadZone(World * currentWorld, World * targetWorld, Vector2f position, Vector2f scale){
	this->currentWorld = currentWorld;
	this->targetWorld = targetWorld;
	this->position = position;
	this->scale = scale;

	movePlayer = false;
}

LoadZone::LoadZone(World * currentWorld, World * targetWorld, Vector2f targetPosition, Vector2f position, Vector2f scale) {
	this->currentWorld = currentWorld;
	this->targetWorld = targetWorld;
	this->targetPosition = targetPosition;
	this->position = position;
	this->scale = scale;

	movePlayer = true;
}

void LoadZone::draw(){

	Res::getTexture(Default)->bind();
	ShaderProgram * shader = Res::getShader(staticShader);
	shader->loadVector2f("scale", scale);
	shader->loadVector2f("pos", position);

	Res::stdModel->bind();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
