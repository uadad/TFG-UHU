#include "CAPiece.h"
#include "../CAVertexFigure.h"
#include "../CATransformFigure.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

//
// FUNCI�N: CAPiece::initialize(VulkanState* vulkan)
//
// PROP�SITO: Crea el Vertex Buffer
//
void CAPiece::initialize(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
{

	size_t vertexSize = sizeof(CAVertexFigure) * vertices.size();
	vulkan->createVertexBuffer(vertexSize, vertices.data(), &vbo);

	size_t indexSize = sizeof(indices[0]) * indices.size();
	vulkan->createIndexBuffer(indexSize, indices.data(), &ibo);

	size_t transformBufferSize = sizeof(CATransformFigure);
	vulkan->createUniformBuffer(transformBufferSize, &transformBuffer);

	size_t lightBufferSize = sizeof(CALight);
	vulkan->createUniformBuffer(lightBufferSize, &lightBuffer);

	size_t materialBufferSize = sizeof(CAMaterial);
	vulkan->createUniformBuffer(materialBufferSize, &materialBuffer);


	CAUniformBuffer* buffers[] = { &transformBuffer, &lightBuffer, &materialBuffer };
	size_t sizes[] = { transformBufferSize, lightBufferSize, materialBufferSize };

	vulkan->createDescriptorSets(layout, &descriptorPool, &descriptorSets, buffers, sizes, 3, &texture);
}

//
// FUNCI�N: CAPiece::finalize(VulkanState* vulkan)
//
// PROP�SITO: Libera los buffers de la pieza
//
void CAPiece::finalize(CAVulkanState* vulkan)
{
	vulkan->destroyVertexBuffer(vbo);
	vulkan->destroyIndexBuffer(ibo);
	vulkan->destroyUniformBuffer(transformBuffer);
	vulkan->destroyUniformBuffer(lightBuffer);
	vulkan->destroyUniformBuffer(materialBuffer);
	vulkan->destroyDescriptorSets(descriptorPool, descriptorSets);
}

//
// FUNCI�N: CAPiece::addCommands(VulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
//
// PROP�SITO: A�ade los comandos de renderizado al command buffer
//
void CAPiece::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vbo.buffer, &offset);
	vkCmdBindIndexBuffer(commandBuffer, ibo.buffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &descriptorSets[index], 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t)indices.size(), 1, 0, 0, 0);
}

//
// FUNCI�N: CAPiece::updateUniformBuffers(VulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
//
// PROP�SITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void CAPiece::updateUniformBuffers(CAVulkanState* vulkan,glm::mat4 location, glm::mat4 view, glm::mat4 projection)
{
	CATransformFigure transform;
	transform.MVP = projection * view * location;
	transform.ModelViewMatrix = view * location;
	transform.ViewMatrix = view;

	vulkan->updateUniformBuffer(sizeof(CATransformFigure), &transform, transformBuffer);
	vulkan->updateUniformBuffer(sizeof(CALight), &light, lightBuffer);
	vulkan->updateUniformBuffer(sizeof(CAMaterial), &material, materialBuffer);
}

//
// FUNCI�N: CAPiece::setLight(Light l)
//
// PROP�SITO: Asigna las propiedades de la luz que incide en la pieza
//
void CAPiece::setLight(CALight l)
{
	this->light = l;
}

//
// FUNCI�N: CAPiece::setMaterial(Material m)
//
// PROP�SITO: Asigna las propiedades del material del que est� formada la pieza
//
void CAPiece::setMaterial(CAMaterial m)
{
	this->material = m;
}

//
// FUNCI�N: CAPiece::setTexture(Texture* tex)
//
// PROP�SITO: Asigna la textura de la pieza
//
void CAPiece::setTexture(CATexture tex)
{
	this->texture = tex;
}
