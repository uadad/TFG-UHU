#pragma once

#include "CAVulkanState.h"
#include "CAVertexFigure.h"
#include "CATransformFigure.h"
#include "CAIndexBuffer.h"
#include "CAVertexBuffer.h"
#include "CAUniformBuffer.h"
#include "CATexture.h"
#include <glm/glm.hpp>
#include <vector>

class CAEtiqueta_Abstracta
{
	protected:
		std::vector<CAVertexFigure> vertices;
		std::vector<uint16_t> indices;
		CATexture texture;
		glm::vec2 g;
	public:
		void initialize(CAVulkanState * vulkan, VkDescriptorSetLayout layout);
		void finalize(CAVulkanState * vulkan);
		void addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index);
		void updateUniformBuffers(CAVulkanState* vulkan, bool mostrar);
		void setTexture(CATexture& tex);
		void setG(glm::vec2 g) { this->g = g; }

		CATexture getTexture();

	private:
		CAVertexBuffer vbo;
		CAIndexBuffer ibo;
		CAUniformBuffer transformBuffer;
		CAUniformBuffer lightBuffer;
		CAUniformBuffer materialBuffer;
		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;
};

