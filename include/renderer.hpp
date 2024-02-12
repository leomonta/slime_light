#pragma once

#include "window/glfwWindow.hpp"

std::unique_ptr<glfwWindow> createWindow();

void destroyWindow(std::unique_ptr<glfwWindow> &glfwWin);
