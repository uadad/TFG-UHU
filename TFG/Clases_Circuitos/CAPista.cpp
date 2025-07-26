#include "CAPista.h"

#include "CAPista.h"
#include "../CAVertexFigure.h"
#include "../CATransformFigure.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

//
// FUNCIÓN: CAPista::initialize(CAVulkanState* vulkan)
//
// PROPÓSITO: Crea el Vertex Buffer
//
void CAPista::initialize(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
{
	location = glm::mat4(1.0f);

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
// FUNCIÓN: CAPista::finalize(CAVulkanState* vulkan)
//
// PROPÓSITO: Libera los buffers de la pista
//
void CAPista::finalize(CAVulkanState* vulkan)
{
	vulkan->destroyVertexBuffer(vbo);
	vulkan->destroyIndexBuffer(ibo);
	vulkan->destroyUniformBuffer(transformBuffer);
	vulkan->destroyUniformBuffer(lightBuffer);
	vulkan->destroyUniformBuffer(materialBuffer);
	vulkan->destroyDescriptorSets(descriptorPool, descriptorSets);
}

//
// FUNCIÓN: CAPista::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAPista::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vbo.buffer, &offset);
	vkCmdBindIndexBuffer(commandBuffer, ibo.buffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &descriptorSets[index], 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t)indices.size(), 1, 0, 0, 0);
}

//
// FUNCIÓN: CAPista::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void CAPista::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
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
// FUNCIÓN: CAPista::setLight(CALight l)
//
// PROPÓSITO: Asigna las propiedades de la luz que incide en la pista
//
void CAPista::setLight(CALight l)
{
	this->light = l;
}

//
// FUNCIÓN: CAPista::getLight()
//
// PROPÓSITO: devulve las propiedades de la luz que incide en la pista
//
CALight CAPista::getLight()
{
	return this->light;
}

//
// FUNCIÓN: CAPista::setMaterial(CAMaterial m)
//
// PROPÓSITO: Asigna las propiedades del material del que está formada la pista
//
void CAPista::setMaterial(CAMaterial m)
{
	this->material = m;
}

//
// FUNCIÓN:  CAPista::getMaterial()
//
// PROPÓSITO: devuelve las propiedades del material del que está formada la pista
//
CAMaterial CAPista::getMaterial()
{
	return this->material;
}

//
// FUNCIÓN: CAPista::setTexture(CATexture* tex)
//
// PROPÓSITO: Asigna la textura de la pista
//
void CAPista::setTexture(CATexture tex)
{
	this->texture = tex;
}

//
// FUNCIÓN:  CAPista::getTexture() 
//
// PROPÓSITO: devuelve la textura de la pista
//
CATexture CAPista::getTexture()
{
	return this->texture;
}
//
// FUNCIÓN: CAPista::resetLocation()
//
// PROPÓSITO: Resetea la matriz de localización (Model).
//
void CAPista::resetLocation()
{
	location = glm::mat4(1.0f);
}

//
// FUNCIÓN: CAPista::setLocation()
//
// PROPÓSITO: Resetea la matriz de localización (Model).
//
void CAPista::setLocation(glm::mat4 m)
{
	location = glm::mat4(m);
}

glm::mat4 CAPista::getLocation()
{
	return location;
}


//
// FUNCIÓN: CAPista::translate(glm::vec3 t)
//
// PROPÓSITO: Añade un desplazamiento la matriz de localización (Model).
//
void CAPista::translate(glm::vec3 t)
{
	location = glm::translate(location, t);
}

//
// FUNCIÓN: CAPista::rotate(float angle, glm::vec3 axis)
//
// PROPÓSITO: Añade una rotación la matriz de localización (Model).
//
void CAPista::rotate(float angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
}

//
// FUNCIÓN: CAPista::setNombre(std::string nombre)
//
// PROPÓSITO: Asigna el nombre de la pista
//

void CAPista::setNombre(std::string nombre)
{
	this->nombre = nombre;
}

//
// FUNCIÓN: CAPista::getNombre()
//
// PROPÓSITO: devuelve el nombre de la pista
//

std::string CAPista::getNombre()
{
	return this->nombre;
}