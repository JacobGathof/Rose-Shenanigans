#include "Main.h"


int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(800, 800, "Default Title", 0, 0);
	glfwMakeContextCurrent(window);

	
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
		std::cout << "Error:" << glewGetErrorString(err);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1, 1, 1, 1);

	game.init();
	Input::game = &game;

	glfwSetTime(0);
	float dt = 0;
	float last_second = 0;
	float last_time = 0;
	float current_time = 0;

	while (!glfwWindowShouldClose(window)) {
		try {
			current_time = glfwGetTime();
			dt = current_time - last_time;
			last_time = current_time;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Input::processInput(dt);

			game.loop(dt);
			game.render();

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
		catch (exception e) {
			std::cout << e.what();
		}
	}

	Res::cleanResources();

	glfwTerminate();

	return 0;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {


	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if (action == GLFW_PRESS) {
		Input::keys[key] = true;
	}
	if (action == GLFW_RELEASE) {
		Input::keys[key] = false;
	}
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	if (action == GLFW_PRESS) {
		Input::mouse[button] = true;
	}
	if (action == GLFW_RELEASE) {
		Input::mouse[button] = false;
	}

}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	return;
}