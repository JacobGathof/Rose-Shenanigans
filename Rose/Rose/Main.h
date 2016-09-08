#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Game.h"
#include "Res.h"
#include <iostream>


int main();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Game game;

