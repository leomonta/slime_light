#pragma once

#include "vulkan.hpp"
#include "window/glfwWindow.hpp"

#include <memory>

typedef struct {
	std::unique_ptr<glfwWindow> win;
	VkInstance                  instance;
	VkDebugUtilsMessengerEXT    debugMsg;
	VkSurfaceKHR                surface;
	VkPhysicalDevice            phyDev;
	vksym::deviceProperties     devInfo;
	VkDevice                    logDev;
	vksym::queues               queues;
	VmaAllocator                vma;
} VkState;

void initVulkan(VkState &vk);

void termVulkan(VkState &vk);
