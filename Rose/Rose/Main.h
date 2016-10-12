#pragma once
#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "opengl-wrapper\GLFW\include\GLFW\glfw3.h"
#include "Game.h"
#include "Res.h"
#include "Input.h"
#include <iostream>
#include <Windows.h>
//#include "PopUpManager.h"


int main();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void window_resize_callback(GLFWwindow* window, int width, int height);
void joystick_callback(int joy, int action);
void error_callback(int error, const char* desc);
void window_refresh_callback(GLFWwindow* window);

Game game;

