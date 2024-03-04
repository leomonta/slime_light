#include "renderer.hpp"

#include "constants.hpp"
#include "logger/logger.hpp"

void initVulkan(VkState &vk) {
	vk.win = std::make_unique<glfwWindow>();

	vk.win->initWindow({SCREEN_WIDTH, SCREEN_HEIGHT});

	//
	// -------------------------------------------------------------------------------------------- instance
	// the basis of vulkan

	auto vki = vksym::createInstance(vk.win.get());
	if (!vki.has_value()) {
		logger::log("[INIT] Vulkan Instance could not be created");
		return;
	}

	vk.instance = vki.value();

	//
	// -------------------------------------------------------------------------------------------- debug Messanger
	// to redirect vulkan errors to out logger

	auto dbm = vksym::setupDebugMessenger(vk.instance);

	if (!dbm.has_value()) {
		logger::log("[INIT] Debug Messanger, vulkan debug callbakc, could not be created");
	}

	vk.debugMsg = dbm.value();

	//
	// -------------------------------------------------------------------------------------------- surface
	// glfw - vulkan window communications

	vk.surface = {};
	vk.win->createSurface(vk.instance, &vk.surface);

	if (vk.surface == VK_NULL_HANDLE) {
		logger::log("[INIT] Could not create surface");
		return;
	}

	//
	// -------------------------------------------------------------------------------------------- physical device
	// aka which GPU, if any, to use

	auto dev = vksym::pickPhysicalDevice(vk.instance, vk.surface);

	if (!dev.has_value()) {
		logger::log("[INIT] Could not get a physicalDevice to render on");
		return;
	}

	vk.phyDev  = dev.value().first;
	vk.devInfo = dev.value().second;

	logger::log("[INIT] Picked device '", vk.devInfo.name,
	            "'\n\tSupported api version = ", VK_VERSION_MAJOR(vk.devInfo.apiVersion), ".", VK_VERSION_MINOR(vk.devInfo.apiVersion), ".", VK_VERSION_PATCH(vk.devInfo.apiVersion),
	            "\n\tDriver version        = ", VK_VERSION_MAJOR(vk.devInfo.driverVersion), ".", VK_VERSION_MINOR(vk.devInfo.driverVersion), ".", VK_VERSION_PATCH(vk.devInfo.driverVersion));

	//
	// -------------------------------------------------------------------------------------------- logical device
	// aka how are we gonna use this device

	auto lde = vksym::createLogicalDevice(vk.phyDev, vk.surface);

	if (!lde.has_value()) {
		logger::log("[INIT] Could not create a logical device");
		return;
	}

	vk.logDev = lde.value().first;
	vk.queues = lde.value().second;

	//
	// -------------------------------------------------------------------------------------------- VMA
	// A Vulkan Memory Allocator to efficiently allocate memory for vulkan (duh)

	auto vma = vksym::createVMA(vk.instance, vk.phyDev, vk.logDev);

	if (!vma.has_value()) {
		logger::log("[INIT] Could not create the logical device");
		return;
	}
	
	//
	// -------------------------------------------------------------------------------------------- SwapChain
	// How to display stuff to the screen

	vk.vma = vma.value();

	auto swc = vksym::createSwapchain(vk.logDev, vk.phyDev, vk.surface, vk.win.get());

	if (!swc.has_value()) {
		logger::log("[INIT] Could not create the swap chain");
		return;
	}

	vk.swapchain = swc.value().first;
	vk.scImages  = swc.value().second;

	//
	// -------------------------------------------------------------------------------------------- SwapChain Viwes
	// How the framebuffer should are formatted and treated

	auto scv = vksym::createSwapchainViews(vk.logDev, vk.scImages);
	
	if (!scv.has_value()) {
		logger::log("[INIT] Could not create the swap chain views");
		return;
	}

	vk.scImageViews = scv.value();

	//
	// -------------------------------------------------------------------------------------------- Render pass
	// How to connnect the pipeline to the framebuffer

	auto rdp = vksym::createRenderPass(vk.logDev, vk.scImages);

	if (!rdp.has_value()) {
		logger::log("[INIT] Could not create the render pass");
		return;
	}

	vk.renderPass = rdp.value();

	//
	// -------------------------------------------------------------------------------------------- Drescriptor set layout
	// aka uniforms and their types

	auto dsl = vksym::createDescriptorSetLayout(vk.logDev);
	
	if (!dsl.has_value()) {
		logger::log("[INIT] Could not create the descriptor set layout");
		return;
	}

	vk.descSetLayout = dsl.value();

	//
	// -------------------------------------------------------------------------------------------- graphics pipeline
	// attach the shaders to the correct stages of the pipeline

	// kinda useless tbh
	std::vector<uint8_t> fragSource, vertSource;
	
	auto ppl = vksym::createGraphicsPipeline(vk.logDev, vk.scImages, vk.descSetLayout, vk.renderPass, vertSource, fragSource, sizeof(pushConstantData));

	/*
	if(!tryAssign<vksym::createCommandPool>(commandPool, device, physicalDevice, surface)) return false;
	if(!tryAssign<vksym::createFramebuffers>(framebuffers, device, swapchainImages, swapchainImageViews, renderPass)) return false;

	if(!tryAssign<vksym::createSampler>(sampler, device, physicalDevice)) return false;
	if(!tryAssign<vksym::createVertexBuffers>(vertexBuffers, device, allocator, commandPool, queue.graphicsQueue)) return false;
	if(!tryAssign<vksym::createIndexBuffers>(indexBuffers, device, allocator, commandPool, queue.graphicsQueue)) return false;
	if(!tryAssign<vksym::createUniformBuffers>(uniformBuffers, device, allocator)) return false;
	if(!tryAssign<vksym::createDescriptorPool>(descriptorPool, device)) return false;
	if(deviceProperties.timestampQuarries)
	    if(!tryAssign<vksym::createQueryPool>(queryPool, device)) return false;
	if(!tryAssign<vksym::createDescriptorSets>(descriptorSets, device, descriptorPool, descriptorSetLayouts, uniformBuffers, textures, sampler)) return false;
	if(!tryAssign<vksym::createCommandBuffers>(commandBuffers, device, commandPool)) return false;
	if(!tryAssign<vksym::createSyncObjects>(syncObjects, device)) return false;

	logger::log("Renderer note: phase 2 completed successfully");
	return true;
	*/
}

void termVulkan(VkState &vk) {
	/*
	vkDeviceWaitIdle(device);
	for(auto& o : syncObjects){
	    tryNotVkNull<vkDestroySemaphore>(o.imageAvailableSem, device, o.imageAvailableSem, nullptr);
	    tryNotVkNull<vkDestroySemaphore>(o.imageAvailableSem, device, o.renderFinishedSem, nullptr);
	    tryNotVkNull<vkDestroyFence>(o.inFlightFence, device, o.inFlightFence, nullptr);
	}
	tryNotVkNull<vkDestroyCommandPool>(commandPool, device, commandPool, nullptr);
	for(auto framebuffer : framebuffers){
	    tryNotVkNull<vkDestroyFramebuffer>(framebuffer, device, framebuffer, nullptr);
	}
	tryNotVkNull<vkDestroyPipeline>(pipeline, device, pipeline, nullptr);
	tryNotVkNull<vkDestroyPipelineLayout>(pipelineLayout, device, pipelineLayout, nullptr);
	for(size_t i=0;i<vksym::MAX_FRAMES_IN_FLIGHT;i++){
	    tryNotVkNull<vmaUnmapMemory>(uniformBuffers[i].bufferMemory, allocator, uniformBuffers[i].bufferMemory);
	    tryNotVkNull<vmaDestroyBuffer>(uniformBuffers[i].buffer, allocator, uniformBuffers[i].buffer, uniformBuffers[i].bufferMemory);
	}

	for(unsigned int i=0;i<indexBuffers.size();i++)
	    if(indexBuffers[i].buffer != VK_NULL_HANDLE)
	        tryNotVkNull<vmaDestroyBuffer>(indexBuffers[i].buffer, allocator, indexBuffers[i].buffer, indexBuffers[i].bufferMemory);

	for(unsigned int i=0;i<vertexBuffers.size();i++)
	    if(vertexBuffers[i].buffer != VK_NULL_HANDLE)
	        tryNotVkNull<vmaDestroyBuffer>(vertexBuffers[i].buffer, allocator, vertexBuffers[i].buffer, vertexBuffers[i].bufferMemory);

	tryNotVkNull<vkDestroySampler>(sampler, device, sampler, nullptr);
	for(auto& o : textures)
	    o->cleanup(device, allocator);

	tryNotVkNull<vkDestroyDescriptorPool>(descriptorPool, device, descriptorPool, nullptr);

	if(deviceProperties.timestampQuarries)
	    tryNotVkNull<vkDestroyQueryPool>(queryPool, device, queryPool, nullptr);

	for(auto& o : descriptorSetLayouts)
	    tryNotVkNull<vkDestroyDescriptorSetLayout>(o, device, o, nullptr);

*/
	vkDestroyRenderPass(vk.logDev, vk.renderPass, nullptr);

	for(auto o : vk.scImageViews){
		vkDestroyImageView(vk.logDev, o, nullptr);
	}

	vkDestroySwapchainKHR(vk.logDev, vk.swapchain, nullptr);

	vmaDestroyAllocator(vk.vma);

	vkDestroyDevice(vk.logDev, nullptr);

	vkDestroySurfaceKHR(vk.instance, vk.surface, nullptr); // >(surface, instance, surface, nullptr);

	vksym::DestroyDebugUtilsMessengerEXT(vk.instance, vk.debugMsg, nullptr);

	vkDestroyInstance(vk.instance, nullptr);

	vk.win->destroyWindow();
}
