#pragma once

#include "window/glfwWindow.hpp"

#include <memory>

typedef struct {
	std::unique_ptr<glfwWindow> win;
	VkInstance                  instance;
	VkDebugUtilsMessengerEXT    debugMsg;
} VkState;

void initVulkan(VkState &vk);

void termVulkan(VkState &vk);
