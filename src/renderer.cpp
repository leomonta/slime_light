#include "constants.hpp"
#include "window/glfwWindow.hpp"
#include <memory>

std::unique_ptr<glfwWindow> createWindow() {
	std::unique_ptr<glfwWindow> win = std::make_unique<glfwWindow>();

	win->initWindow({SCREEN_WIDTH, SCREEN_HEIGHT});

	return win;
}

void destroyWindow(std::unique_ptr<glfwWindow> &glfwWin){
	glfwWin->destroyWindow();
}
