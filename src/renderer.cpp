#include "renderer.hpp"

#include "constants.hpp"
#include "logger/logger.hpp"
#include "vulkan.hpp"

void initVulkan(VkState &vk) {
	vk.win = std::make_unique<glfwWindow>();

	vk.win->initWindow({SCREEN_WIDTH, SCREEN_HEIGHT});

	auto vki = vksym::createInstance(vk.win.get());
	if (!vki.has_value()) {
		logger::log("[INIT] Vulkan Instance could not be created");
		return;
	}

	vk.instance = vki.value();

	auto dbm = vksym::setupDebugMessenger(vk.instance);

	if (!dbm.has_value()) {
		logger::log("[INIT] Debug Messanger, vulkan debug callbakc, could not be created");
	}

	vk.debugMsg = dbm.value();
}

void termVulkan(VkState &vk) {
	
	vksym::DestroyDebugUtilsMessengerEXT(vk.instance, vk.debugMsg, nullptr);

	vkDestroyInstance(vk.instance, nullptr);

	vk.win->destroyWindow();
}
