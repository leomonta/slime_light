#pragma once

#include "vulkan.hpp"
#include "window/glfwWindow.hpp"

#include <array>
#include <memory>
#include <vulkan/vulkan_core.h>

// data sent to the shaders
struct pushConstantData {
	int texNumber;
	int mirrorX;
	int mirrorY;
	alignas(16) glm::mat4x4 transform;
	alignas(4) int effectsEnabled;
	alignas(4) float effectVals[4];
};

typedef struct {
	std::unique_ptr<glfwWindow>                                   win;
	VkInstance                                                    instance;
	VkDebugUtilsMessengerEXT                                      debugMsg;
	VkSurfaceKHR                                                  surface;
	VkPhysicalDevice                                              phyDev;
	vksym::deviceProperties                                       devInfo;
	VkDevice                                                      logDev;
	vksym::queues                                                 queues;
	VmaAllocator                                                  vma;
	VkSwapchainKHR                                                swapchain;
	vksym::swapchainImages                                        scImages;
	std::vector<VkImageView>                                      scImageViews;
	VkRenderPass                                                  renderPass;
	std::array<VkDescriptorSetLayout, 2>                          descSetLayout;
	VkPipeline                                                    pipeline;
	VkPipelineLayout                                              pipelineLayout;
	VkCommandPool                                                 commandPool;
	std::vector<VkFramebuffer>                                    framebuffers;
	VkSampler                                                     imageSampler;
	std::array<vksym::vertexBuffer, vksym::MAX_FRAMES_IN_FLIGHT>  vertBuffers;
	std::array<vksym::indexBuffer, vksym::MAX_FRAMES_IN_FLIGHT>   indxBuffers;
	std::array<vksym::uniformBuffer, vksym::MAX_FRAMES_IN_FLIGHT> unifBuffers;

} VkState;

void initVulkan(VkState &vk);

void termVulkan(VkState &vk);
