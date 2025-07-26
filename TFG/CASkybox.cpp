#include "CASkybox.h"
#include "CAVertexSkybox.h"
#include "CATransformSkybox.h"
#include "CATexture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//
// FUNCIÓN: CASkybox::CASkybox(CAVulkanState* vulkan)
//
// PROPÓSITO: Crea los buffers
//
CASkybox::CASkybox(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
{
	vertices = {
		{{1.0f, 1.0f, -1.0f}},
		{{1.0f, -1.0f, -1.0f}},
		{{-1.0f, -1.0f, -1.0f}},
		{{-1.0f, 1.0f, -1.0f}}
	};

	indices = {
		0,1,2,
		0,2,3
	};


	size_t vertexSize = sizeof(CAVertexSkybox) * vertices.size();
	vulkan->createVertexBuffer(vertexSize, vertices.data(), &vbo);

	size_t indexSize = sizeof(indices[0]) * indices.size();
	vulkan->createIndexBuffer(indexSize, indices.data(), &ibo);

	size_t transformBufferSize = sizeof(CATransformSkybox);
	vulkan->createUniformBuffer(transformBufferSize, &transformBuffer);

	const char* filenames[6];
	filenames[0] = "textures/entorno/negz.jpg";
	filenames[1] = "textures/entorno/posz.jpg";
	filenames[2] = "textures/entorno/posy.jpg";
	filenames[3] = "textures/entorno/negy.jpg";
	filenames[4] = "textures/entorno/posx.jpg";
	filenames[5] = "textures/entorno/negx.jpg";

	vulkan->createCubemap(filenames, &cubemap);

	CAUniformBuffer* buffers[] = { &transformBuffer };
	size_t sizes[] = { transformBufferSize };

	vulkan->createDescriptorSets(layout, &descriptorPool, &descriptorSets, buffers, sizes, 1, &cubemap);
}

//
// FUNCIÓN: CASkybox::finalize(CAVulkanState* vulkan)
//
// PROPÓSITO: Libera los buffers de la figura
//
void CASkybox::finalize(CAVulkanState* vulkan)
{
	vulkan->destroyTexture(cubemap);
	vulkan->destroyVertexBuffer(vbo);
	vulkan->destroyIndexBuffer(ibo);
	vulkan->destroyUniformBuffer(transformBuffer);
	vulkan->destroyDescriptorSets(descriptorPool, descriptorSets);
}

//
// FUNCIÓN: CAFigure::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CASkybox::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vbo.buffer, &offset);
	vkCmdBindIndexBuffer(commandBuffer, ibo.buffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &descriptorSets[index], 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t)indices.size(), 1, 0, 0, 0);
}

//
// FUNCIÓN: CASkybox::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void CASkybox::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
{
	glm::mat3 rot3 = glm::mat3(view); // Parte rotacional de la matriz View
	glm::mat4 rot4 = glm::mat4(rot3);
	glm::mat4 mvp = projection * rot4; // Transformación del Skybox a coordenadas Clip
	glm::mat4 inv = glm::inverse(mvp); // Transformación de coordenadas Clip a coordenadas de modelo del Skybox

	CATransformSkybox ubo = { inv };

	vulkan->updateUniformBuffer(sizeof(CATransformSkybox), &ubo, transformBuffer);
}
