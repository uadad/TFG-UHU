#include "CAEtiqueta_Abstracta.h"
#include "CAVertexFigure.h"
#include "CATransformFigure.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "CAModel.h"

//
// FUNCIÓN: CAEtiqueta_Abstracta::initialize(CAVulkanState* vulkan)
//
// PROPÓSITO: Crea el Vertex Buffer
//
void CAEtiqueta_Abstracta::initialize(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
{
	this->g = glm::vec2(0.0f, 0.0f);

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
// FUNCIÓN: CAEtiqueta_Abstracta::finalize(CAVulkanState* vulkan)
//
// PROPÓSITO: Libera los buffers de la etiqueta
//
void CAEtiqueta_Abstracta::finalize(CAVulkanState* vulkan)
{
	vulkan->destroyVertexBuffer(vbo);
	vulkan->destroyIndexBuffer(ibo);
	vulkan->destroyUniformBuffer(transformBuffer);
	vulkan->destroyUniformBuffer(lightBuffer);
	vulkan->destroyUniformBuffer(materialBuffer);
	vulkan->destroyDescriptorSets(descriptorPool, descriptorSets);
}

//
// FUNCIÓN: CAEtiqueta_Abstracta::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAEtiqueta_Abstracta::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vbo.buffer, &offset);
	vkCmdBindIndexBuffer(commandBuffer, ibo.buffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &descriptorSets[index], 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t)indices.size(), 1, 0, 0, 0);
}

//
// FUNCIÓN: CAEtiqueta_Abstracta::updateUniformBuffers(CAVulkanState* vulkan,bool mostrar)
//
// PROPÓSITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void CAEtiqueta_Abstracta::updateUniformBuffers(CAVulkanState* vulkan,bool mostrar)
{
	CATransformFigure transform;
	if (mostrar) {
		transform.MVP = glm::mat4(1.0f);
	}
	else {
		transform.MVP = glm::mat4(1.0f);
		transform.MVP[3][0] = -2.0f;
	}
	transform.MVP = glm::translate(transform.MVP, glm::vec3(g.x, g.y, 0.0f));
	transform.ModelViewMatrix = glm::mat4(1.0f);
	transform.ViewMatrix = glm::mat4(1.0f);

	CALight light = {};
	light.La = glm::vec3(1.0f, 1.0f, 1.0f);
	light.Ld = glm::vec3(0.0f, 0.0f, 0.0f);
	light.Ls = glm::vec3(0.0f, 0.0f, 0.0f);

	CAMaterial material = {};
	material.Ka = glm::vec3(1.0f, 1.0f, 1.0f);
	material.Kd = glm::vec3(0.0f, 0.0f, 0.0f);
	material.Ks = glm::vec3(0.0f, 0.0f, 0.0f);
	material.Shininess = 2.0f;
	vulkan->updateUniformBuffer(sizeof(CATransformFigure), &transform, transformBuffer);
	vulkan->updateUniformBuffer(sizeof(CALight), &light, lightBuffer);
	vulkan->updateUniformBuffer(sizeof(CAMaterial), &material, materialBuffer);
}
//
// FUNCIÓN: CAEtiqueta_Abstracta::setTexture(CATexture* tex)
//
// PROPÓSITO: Asigna la textura de la etiqueta
//
void CAEtiqueta_Abstracta::setTexture(CATexture &tex)
{
	this->texture = tex;
}

//
// FUNCIÓN: CAEtiqueta_Abstracta::getTexture()
//
// PROPÓSITO: devolver la textura de la etiqueta
//
CATexture CAEtiqueta_Abstracta::getTexture()
{
	return this->texture;
}
