#pragma once
#include "gl3w.h"
//#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "opengl-wrapper\SFML\include\SFML\Graphics.hpp"
#include "Game.h"
#include "Res.h"
#include "Input.h"
#include <iostream>


int main();

/*
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void window_resize_callback(GLFWwindow* window, int width, int height);
void error_callback(int error, const char* desc);
void window_refresh_callback(GLFWwindow* window);
*/

void processKeyEvent(sf::Event event);

//void setCallbacks(GLFWwindow *window);
//void initializeGLFW();
void initializeSFML();
void initializeOGL();

Game game;

