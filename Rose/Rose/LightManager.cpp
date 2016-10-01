#include "LightManager.h"
#include <iostream>


std::vector<Light*> LightManager::lights;
int LightManager::numberOfLights;


void LightManager::addLight(Light * light) {

	lights.push_back(light);
	numberOfLights++;
	updateLights(entityShader);
	updateLights(staticShader);
	updateLights(terrainShader);
}

void LightManager::clearLights(){
	numberOfLights = 0;
	lights.clear();
}

void LightManager::updateLights(ShaderType shader) {

	ShaderProgram * currentShader = Res::getShader(shader);

	currentShader->loadInteger("numLights", numberOfLights);

	currentShader->loadVector2f((char *)("pointLights[" + std::to_string(numberOfLights - 1) + "].position").c_str(), lights[numberOfLights - 1]->position);
	currentShader->loadColor((char *)("pointLights[" + std::to_string(numberOfLights - 1) + "].color").c_str(), lights[numberOfLights - 1]->color);
	currentShader->loadFloat((char *)("pointLights[" + std::to_string(numberOfLights - 1) + "].intensity").c_str(), lights[numberOfLights - 1]->intensity);


}

void LightManager::reloadLights(ShaderType shader)
{

	ShaderProgram * currentShader = Res::getShader(shader);

	currentShader->loadInteger("numLights", numberOfLights);

	for (int i = 0; i < lights.size(); i++) {

		currentShader->loadVector2f((char *)("pointLights[" + std::to_string(i) + "].position").c_str(), lights[i]->position);
		currentShader->loadColor((char *)("pointLights[" + std::to_string(i) + "].color").c_str(), lights[i]->color);
		currentShader->loadFloat((char *)("pointLights[" + std::to_string(i) + "].intensity").c_str(), lights[i]->intensity);
	}

}


void LightManager::cleanUp()
{
	for (auto l : lights) {
		delete l;
	}
}

LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}
