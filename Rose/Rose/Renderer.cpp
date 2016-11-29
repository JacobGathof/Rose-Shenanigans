#include "Renderer.h"

#include "WorldManager.h"
#include "Screen.h"


void Renderer::renderText(Text * text){

	ShaderProgram * currentShader = Res::getShader(textShader);

	glActiveTexture(GL_TEXTURE0);
	Res::getTexture("Font")->bind();

	glBindVertexArray(text->VAO);

	currentShader->loadVector2f("pos", text->position);
	currentShader->loadVector2f("scale", text->scale);

	glDrawArrays(GL_TRIANGLES, 0, text->charsToRender);

}

void Renderer::renderTerrainChunk(Terrain::TerrainChunk * chunk){

	Res::getTexture("Grass")->bind();

	ShaderProgram * shader = Res::getShader(terrainShader);
	shader->loadVector2f("scale", Vector2f(chunk->scale, chunk->scale));

	shader->loadVector2f("pos", chunk->position*(chunk->tilesPerChunk*chunk->scale));

	glBindVertexArray(chunk->VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, chunk->tilesPerChunk*chunk->tilesPerChunk);

}

void Renderer::renderObject(Object * object){

	object->tex->bind();
	ShaderProgram * shader = Res::getShader(staticShader);
	shader->loadVector2f("scale", object->scale);
	shader->loadVector2f("pos", object->position);

	Res::stdModel->bind();
	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

	renderHitbox(object);

}

void Renderer::renderEntity(Entity * entity){

	entity->tex->bind();

	ShaderProgram * shader = Res::getShader(entityShader);
	shader->loadVector2f("scale", entity->scale);
	shader->loadVector2f("pos", entity->position);
	shader->loadFloat("animTimer", entity->internalTime);
	shader->loadInteger("direction", entity->direction);

	shader->loadInteger("rows", entity->tex->numberOfRows);
	shader->loadInteger("cols", entity->tex->numberOfColumns);

	Res::stdModel->bind();

	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

	renderHitbox(entity);
}

void Renderer::renderDefaultUIElement(UIElement * element){

	if (element->isVisible) {
		element->tex->bind();
		ShaderProgram * shader = Res::getShader(uiShader);
		shader->loadVector2f("scale", -1 * element->topLeft + element->botRight);
		shader->loadVector2f("pos", element->topLeft);

		Res::stdModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);
	}

}

void Renderer::renderTextbox(Textbox * box){
	renderDefaultUIElement(box);
	renderText(box->text);
}

void Renderer::renderStatbox(Statbox * box){
	renderDefaultUIElement(box);
	renderText(box->text);
}

void Renderer::renderSkill(Skill *s, int i) {
	s->icon->bind();
	ShaderProgram * shader = Res::getShader(uiShader);
	shader->loadVector2f("scale", Vector2f(SkillScale, -SkillScale));
	shader->loadVector2f("pos", Vector2f(-20 + SkillScale * i, 60));

	Res::stdModel->bind();
	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);
}


void Renderer::renderHitbox(Object * object){

	ShaderProgram * shader = Res::getShader(staticShader);
	shader->loadInteger("useTexture", 0);
	shader->loadVector2f("scale", object->hitbox.scale);
	shader->loadVector2f("pos", object->hitbox.position + object->position);
	glDrawArrays(GL_LINE_LOOP, 0, Res::stdModel->numberOfVertices);
	shader->loadInteger("useTexture", 1);

}


void Renderer::renderScreen() {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	Res::getModel("ScreenVAO")->bind();
	ShaderProgram * shader = Res::getShader(screenShader);
	shader->loadFloat("black", Screen::black);
	shader->loadFloat("white", Screen::white);
	

	glActiveTexture(GL_TEXTURE0);
	Res::getTexture("WorldTexture")->bind();
	glActiveTexture(GL_TEXTURE1);
	Res::getTexture("LightTexture")->bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glActiveTexture(GL_TEXTURE0);

}

void Renderer::render() {

	WorldManager::drawWorld();
	LightManager::drawLights();

}

void Renderer::prepareToRender() {

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer("WorldFBO"));
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer("LightFBO"));
	glClear(GL_COLOR_BUFFER_BIT);

}

