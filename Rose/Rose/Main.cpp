#include "Main.h"
#include <time.h>
#include "Timer.h"
#include "Menu.h"


int main() {

	srand((unsigned int)time(NULL));

	initializeGLFW();

	GLFWwindow * window = glfwCreateWindow(800, 800, "Default Title", 0, 0);
	glfwMakeContextCurrent(window);

	setCallbacks(window);
	initializeOGL();


	game.init();
	Menu::init(&game);
	Input::game = &game;

	glfwSetTime(0);

	//Timer::slow = true;

	while (!glfwWindowShouldClose(window)) {

		Timer::wait();


		game.loop(0);
		game.render();

		if (game.state == CLOSING)
			break;


		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	Res::cleanResources();
	Menu::clean();

	glfwTerminate();

	return 0;

}

void initializeGLFW() {
	std::cout << "Initializing GLFW" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, 0);

}

void initializeOGL() {
	std::cout << "Initializing OpenGL" << std::endl;
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
		std::cout << "Error:" << glewGetErrorString(err) << std::endl;

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SIZE);
	glClearColor(0, 0, 0, 1);
	std::cout << "Initializing OpenGL Complete" << std::endl;
}

void setCallbacks(GLFWwindow* window) {
	glfwSetWindowSizeCallback(window, window_resize_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetErrorCallback(error_callback);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {


	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if (action == GLFW_PRESS) {
		Input::turnKeyOn(key);
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

void window_resize_callback(GLFWwindow* window, int width, int height) {
	Res::resizeWindow(width, height);
}

void error_callback(int error, const char* desc) {

	std::cout << desc << std::endl;

}

void window_refresh_callback(GLFWwindow* window){

	glfwSwapBuffers(window);
}