#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Game.h"
#include "Res.h"
#include "Input.h"
#include <iostream>


int main();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Game game;

