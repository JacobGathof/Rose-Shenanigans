#include "Renderer.h"

#include "WorldManager.h"
#include "Screen.h"
#include "UI_Manager.h"

#define SkillScale 5

void Renderer::renderText(Text * text){

	ShaderProgram * currentShader = Res::getShader(textShader);

	glActiveTexture(GL_TEXTURE0);
	Res::getTexture(Font)->bind();

	glBindVertexArray(text->VAO);

	currentShader->loadVector2f("pos", text->position);
	currentShader->loadVector2f("scale", text->scale);
	currentShader->loadColor("color", text->color);
	currentShader->loadFloat("opacity", text->opacity);


	glDrawArrays(GL_TRIANGLES, 0, text->charsToRender);

}

void Renderer::renderTerrain(Terrain * terrain){

	Res::getTexture(Grass)->bind();

	ShaderProgram * shader = Res::getShader(terrainShader);
	shader->loadVector2f("scale", Vector2f(terrain->tileScale, terrain->tileScale));

	shader->loadVector2f("pos", Vector2f(0,0));

	glBindVertexArray(terrain->VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, terrain->worldScaleX*terrain->worldScaleY);

}

void Renderer::renderObject(Object * object){

	object->tex->bind();
	ShaderProgram * shader = Res::getShader(staticShader);
	shader->loadVector2f("scale", object->scale);
	shader->loadVector2f("pos", object->position);
	shader->loadInteger("useTexture", 1);

	Res::stdModel->bind();
	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

	//renderHitbox(object);

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

	//renderHitbox(entity);
}

void Renderer::renderProjectile(Projectile * proj){

	proj->tex->bind();

	ShaderProgram * shader = Res::getShader(entityShader);
	shader->loadVector2f("scale", proj->scale);
	shader->loadVector2f("pos", proj->position);
	shader->loadFloat("animTimer", proj->internalTime);
	shader->loadInteger("direction", proj->direction);

	shader->loadInteger("rows", proj->tex->numberOfRows);
	shader->loadInteger("cols", proj->tex->numberOfColumns);

	Res::stdModel->bind();

	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

	//renderHitbox(proj);

	//proj->system->draw();

}

void Renderer::renderParticleSystem(ParticleSystem * sys){

	/*
	if (Input::testVar) {
		glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer("LightFBO"));
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	*/

	ShaderProgram* shader = Res::getShader(particleShader);
	Res::getTexture(Light_Tex)->bind();
	shader->loadFloat("opacity", 1.0f);
	shader->loadFloat("size", 4.0f);

	glBindVertexArray(sys->VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, sys->particle_count);


	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer(WorldFBO));

}

void Renderer::renderDefaultUIElement(UI_Element * element){

	if (element->isVisible) {
		element->tex->bind();
		ShaderProgram * shader = Res::getShader(uiShader);
		shader->loadInteger("textured", element->textured);
		shader->loadVector2f("scale", -1 * element->topLeft + element->botRight);
		shader->loadVector2f("pos", element->topLeft);
		shader->loadFloat("opacity", element->opacity);

		Res::stdModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);
	}

}

void Renderer::renderTextbox(UI_Textbox * box){
	renderDefaultUIElement(box);
	renderText(box->text);
}

void Renderer::renderTitle(UI_Title * box) {
	renderDefaultUIElement(box);
	renderText(box->text);
}

void Renderer::renderStatbox(UI_Statbox * box){
	renderDefaultUIElement(box);
	renderText(box->text);
}

void Renderer::renderInventoyScreen(Weapon * weapons, Texture *backdrop, int size)
{
	backdrop->bind();
	ShaderProgram * shader = Res::getShader(uiShader);
	shader->loadVector2f("scale", Vector2f(128, 128));
	shader->loadVector2f("pos", Vector2f(-64, -64));

	Res::stdModel->bind();
	glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

	for (int i = 0; i < size; i++) {
		weapons[i].tex->bind();
		ShaderProgram * shader = Res::getShader(uiShader);
		shader->loadVector2f("scale", Vector2f(WeaponScale, WeaponScale));
		shader->loadVector2f("pos", Vector2f(WeaponScale * i, 0));

		Res::stdModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);
	}
}

void Renderer::renderSkill(Skill *s, int i) {
	s->icon->bind();
	ShaderProgram * shader = Res::getShader(uiShader);
	shader->loadVector2f("scale", Vector2f(SkillScale, -SkillScale)*SCALEFACTOR/64);
	shader->loadVector2f("pos", Utils::toScreenCoordinates(-20 + SkillScale * i, 60));

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
	Res::getTexture(WorldTexture)->bind();
	glActiveTexture(GL_TEXTURE1);
	Res::getTexture(LightTexture)->bind();

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
	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer(WorldFBO));
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, Res::getFramebuffer(LightFBO));
	glClear(GL_COLOR_BUFFER_BIT);

}
