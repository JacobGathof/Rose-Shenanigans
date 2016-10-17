#include "Main.h"
#include <time.h>

int main() {

	srand((unsigned int)time(NULL));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, 0);

	//GLFWwindow * window = glfwCreateWindow(800, 800, "Default Title", glfwGetPrimaryMonitor(), 0);
	GLFWwindow * window = glfwCreateWindow(800, 800, "Default Title", 0, 0);
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, window_resize_callback);
	glfwSetJoystickCallback(joystick_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetErrorCallback(error_callback);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);

	if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_TRUE) {
		Input::isUsingJoystick = true;
		Input::joystick = GLFW_JOYSTICK_1;
	}


	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
		std::cout << "Error:" << glewGetErrorString(err);

	glEnable(GL_BLEND);
	glClearColor(0, 0, 0, 1);

	game.init();
	Input::game = &game;

	glfwSetTime(0);
	float dt = 0;
	float last_second = 0;
	float last_tick = 0;
	float last_time = 0;
	float current_time = 0;
	int framesPerSecond = 0;

	while (!glfwWindowShouldClose(window)) {
		try {
			current_time = (float)glfwGetTime();
			dt = current_time - last_time;

			while (dt < 2.0/120) {
				current_time = (float)glfwGetTime();
				dt = current_time - last_time;
			}

			last_time = current_time;
			framesPerSecond++;

			if (current_time - last_second >= 1.0f) {
				last_second = current_time;
				//std::cout << "FPS : " << std::to_string((framesPerSecond)) << std::endl;
				framesPerSecond = 0;
			}

			if (current_time - last_tick >= 0.05f) {
				game.gameTick = true;
				last_tick = current_time;
			}

			Input::processInput(dt);

			game.loop(dt);
			game.render();


			glfwPollEvents();
			glfwSwapBuffers(window);

			//_sleep(8.33333333333333 - dt);
		}
		catch (exception e) {
			std::cout << "Caught error: " << e.what() << endl;
		}
	}

	Res::cleanResources();

	glfwTerminate();

	//PopUpManager::showMessage(L"You quit the game. Why would you do that?!?!?", L"Really?");
	//MessageBox(NULL, L"You quit the game. Why would you do that?!?!?", L"Really?", MB_ICONASTERISK);

	return 0;

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

void joystick_callback(int joystick, int action) {
	if (action == GLFW_CONNECTED) {
		Input::isUsingJoystick = true;
		Input::joystick = joystick;
	}

	if (action == GLFW_DISCONNECTED) {
		Input::isUsingJoystick = false;
	}
}

void error_callback(int error, const char* desc) {

	std::cout << desc << std::endl;

}

void window_refresh_callback(GLFWwindow* window){

	glfwSwapBuffers(window);
}