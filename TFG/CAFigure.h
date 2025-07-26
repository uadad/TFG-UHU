#pragma once

#include "CAVulkanState.h"
#include "CAVertexFigure.h"
#include "CATransformFigure.h"
#include "CALight.h"
#include "CAMaterial.h"
#include "CAIndexBuffer.h"
#include "CAVertexBuffer.h"
#include "CAUniformBuffer.h"
#include "CATexture.h"
#include <glm/glm.hpp>
#include <vector>

class CAFigure
{
protected:
	std::vector<CAVertexFigure> vertices;
	std::vector<uint16_t> indices;
	glm::mat4 location;
	CALight light;
	CAMaterial material;
	CATexture texture;

public:
	void initialize(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	void finalize(CAVulkanState* vulkan);
	void addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index);
	void updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);
	void resetLocation();
	void setLocation(glm::mat4 m);
	glm::mat4 getLocation();
	void translate(glm::vec3 t);
	void rotate(float angle, glm::vec3 axis);
	void setLight(CALight l);
	void setMaterial(CAMaterial m);
	void setTexture(CATexture texture);

private:
	CAVertexBuffer vbo;
	CAIndexBuffer ibo;
	CAUniformBuffer transformBuffer;
	CAUniformBuffer lightBuffer;
	CAUniformBuffer materialBuffer;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
};

