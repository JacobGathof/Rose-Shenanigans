#pragma once
#include <vector>
#include "ShaderProgram.h"
#include "Res.h"


class Light {

public:
	Vector2f position;
	Color color;
	float intensity;

	Light(Vector2f pos, Color color, float intensity) : position(pos), color(color), intensity(intensity) {}

};

class LightManager
{
public:

	static int numberOfLights;

	static std::vector<Light*> lights;

	static void addLight(Light* light);
	static void clearLights();
	//static void removeLightPosition(Vector3f position);
	static void updateLights(ShaderType shader);
	static void reloadLights(ShaderType shader);

	static void cleanUp();

	LightManager();
	~LightManager();

};


