#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "ShaderProgram.h"
#include "ModelLoader.h"
#include <iostream>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(800, 800, "Default Title", 0, 0);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
		std::cout << "Error:" << glewGetErrorString(err);


	glClearColor(1, 1, 1, 1);

	glfwSetTime(0);

	ShaderProgram pro;
	pro.compileShader("simpleVertexShader.txt", NULL, "simpleFragmentShader.txt");
	pro.loadFloat("height", 1);
	pro.loadFloat("width", 1);

	float vertices[] = { 0,0, 0,1, 1,1 };
	float tex[] = { 0,0, 0,1, 1,1 };

	Model *m = ModelLoader::loadModel(vertices, tex, 6);
	glBindVertexArray(m->VAO);

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, m->numberOfVertices);


		glfwPollEvents();
		glfwSwapBuffers(window);


	}
	delete m;

	glfwTerminate();

	return 0;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {


	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

}

