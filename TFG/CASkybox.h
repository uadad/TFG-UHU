#pragma once
#include "CAVulkanState.h"
#include "CAVertexSkybox.h"
#include "CATexture.h"
#include <glm/glm.hpp>
#include <vector>

class CASkybox
{
public:
	CASkybox(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	void finalize(CAVulkanState* vulkan);
	void addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index);
	void updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);
private:
	std::vector<CAVertexSkybox> vertices;
	std::vector<uint16_t> indices;
	CATexture cubemap;

	CAVertexBuffer vbo;
	CAIndexBuffer ibo;
	CAUniformBuffer transformBuffer;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
};

