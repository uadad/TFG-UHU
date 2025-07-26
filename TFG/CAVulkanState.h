#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vector>
#include "CAVertexBuffer.h"
#include "CAIndexBuffer.h"
#include "CAUniformBuffer.h"
#include "CATexture.h"
#include "CAPipeline.h"

class CAModel;

class CAVulkanState
{
public:
	CAVulkanState(GLFWwindow* window);
	~CAVulkanState();
	void windowResized(int width, int height);
	void draw();
	void setModel(CAModel* model);

	// M�todos de gesti�n de buffers
	void createCubemap(const char** filename, CATexture* texture);
	void createTexture(const char* filename, CATexture* texture);
	void destroyTexture(CATexture texture);
	void createVertexBuffer(size_t size, const void* data, CAVertexBuffer* vbo);
	void destroyVertexBuffer(CAVertexBuffer vbo);
	void createIndexBuffer(size_t size, const void* data, CAIndexBuffer* ibo);
	void destroyIndexBuffer(CAIndexBuffer ibo);
	void createUniformBuffer(size_t size, CAUniformBuffer* ubo);
	void updateUniformBuffer(size_t size, const void* data, CAUniformBuffer ubo);
	void destroyUniformBuffer(CAUniformBuffer ubo);
	void createDescriptorSets(VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool* descriptorPool, std::vector<VkDescriptorSet> *descriptorSets, CAUniformBuffer** buffers,size_t* bufferSizes, size_t size, CATexture* texture);
	void destroyDescriptorSets(VkDescriptorPool descriptorPool, std::vector<VkDescriptorSet> descriptorSets);

	// M�todos de creaci�n de pipelines
	void createPipeline(CAShadersInfo shaderInfo, CAAttribInfo attribInfo, CADescriptorInfo descriptors, CAPipeline* pipeline);
	void destroyPipeline(CAPipeline pipeline);

private:
	// Campos internos
	int wWidth;
	int wHeight;
	VkViewport viewport;
	VkRect2D scissor;
	uint32_t imageCount;
	uint32_t frameCount;

	CAModel* model;
	GLFWwindow* window;
	VkSurfaceKHR surface;
	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceMemoryProperties memProperties;
	VkDevice device;
	uint32_t graphicsQueueFamilyIndex;
	uint32_t presentQueueFamilyIndex;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	VkRenderPass renderPass;
	std::vector<VkImage> depthImages;
	std::vector<VkDeviceMemory> depthImageMemories;
	std::vector<VkImageView> depthImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;
	size_t currentFrame = 0;
	uint32_t currentImage = 0;
	bool framebufferResized = false;

	// M�todos de inicializaci�n de Vulkan
	void createInstance();
	void createSurface(GLFWwindow* window);
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createDepthBuffers();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createSyncObjects();
	void recreateSwapChain();
	void fillCommandBuffers();

	// M�todos de definici�n del pipeline de renderizado
	void createPipelineLayout(CADescriptorInfo descriptorInfo, VkDescriptorSetLayout* descriptorSetLayout, VkPipelineLayout* pipelineLayout);
	void createVertexShaderStageCreateInfo(int resource, VkShaderModule* vertShaderModule, VkPipelineShaderStageCreateInfo* vertShaderStageInfo);
	void createFragmentShaderStageCreateInfo(int resource, VkShaderModule* fragShaderModule, VkPipelineShaderStageCreateInfo* fragShaderStageInfo);
	void createPipelineVertexInputStateCreateInfo(CAAttribInfo info, VkPipelineVertexInputStateCreateInfo* vertexInputInfo, VkVertexInputBindingDescription* bindingDescriptions, VkVertexInputAttributeDescription* attributeDescriptions);
	void createPipelineInputAssemblyStateCreateInfo(VkPipelineInputAssemblyStateCreateInfo* inputAssembly);
	void createPipelineViewportStateCreateInfo(VkPipelineViewportStateCreateInfo* viewportState);
	void createPipelineRasterizationStateCreateInfo(VkPipelineRasterizationStateCreateInfo* rasterizer);
	void createPipelineMultisampleStateCreateInfo(VkPipelineMultisampleStateCreateInfo* multisampling);
	void createPipelineDepthStencilStateCreateInfo(VkBool32 depthTestEnable,VkPipelineDepthStencilStateCreateInfo* depthStencil);
	void createPipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* colorBlendAttachment, VkPipelineColorBlendStateCreateInfo* colorBlending);
	void createPipelineDynamicStateCreateInfo(VkPipelineDynamicStateCreateInfo* dynamicState);

	// M�todos de generaci�n de la imagen
	void waitForNextImage();
	void submitGraphicsCommands();
	void submitPresentCommands();

	// M�todos para crear im�genes
	void createStagingBuffer(VkBuffer* buffer, VkDeviceMemory* deviceMemory, size_t size);
	void createImage(uint32_t width, uint32_t height, VkImageUsageFlags usage, VkImage* image);
	void createImageMemory(VkImage image, VkDeviceMemory* imageMemory);
	void createImageView(VkImage image, VkImageView* view);
	void createSampler(VkSampler* sampler);
	void transitionImageLayout(VkImage image, VkFormat format, uint32_t layers, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layers);
	void createCubemapImage(uint32_t width, uint32_t height, VkImageUsageFlags usage, VkImage* image);
	void createCubemapView(VkImage image, VkImageView* view);

	// M�todos auxiliares
	bool isDeviceSuitable(VkPhysicalDevice pDevice);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	std::vector<char> getFileFromResource(int resource);
	VkFormat findDepthFormat();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

