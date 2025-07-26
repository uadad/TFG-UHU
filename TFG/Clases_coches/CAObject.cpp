#include "CAObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CAEstado_Coche.h"

// FUNCIÓN: CAObject::initalize(CAVulkanState* vulkan, VkDescriptorSetLayout layout) 
//
// PROPÓSITO: Asigna el estado de Vulkan para poder llamar a los metodos de las piezas 
//
void CAObject::initalize(CAVulkanState* vulkan, VkDescriptorSetLayout layout) {
	this->vulkan = vulkan;
}

//
// FUNCIÓN: CAObject::finalize(CAVulkanState* vulkan)
//
// PROPÓSITO: Libera los buffers de las piezas que forman el objeto
//
void CAObject::finalize(CAVulkanState* vulkan)
{
	int num = GetNumPieces();
	for (int i = 0; i < num; i++)
	{
		GetPiece(i)->finalize(vulkan);
	}
}


// FUNCION: CAObject::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer para cada pieza del objeto
//
void CAObject::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
{
	int num = GetNumPieces();
	for (int i = 0; i < num; i++)
	{
		GetPiece(i)->addCommands(layout, commandBuffer, index);
	}
}

//
// FUNCIÓN: CAObject::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO:  Actualiza las variables uniformes sobre una imagen del swapchain de cada pieza del objeto
//
void CAObject::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
{
	this->vulkan = vulkan;  this->view = view; this->projection = projection;
	int num = GetNumPieces();
	for (int i = 0; i < num; i++)
	{
		GetPiece(i)->updateUniformBuffers(vulkan, this->model, view, projection);
	}
}


//
// FUNCIÓN: Object::ResetLocation()
//
// PROPÓSITO: Asigna la posición inicial del objecto 
//
void CAObject::ResetLocation()
{
	model = glm::mat4(1.0f);
	this->updateUniformBuffers(vulkan, view, projection);

}

//
// FUNCIÓN: Object::SetLocation(glm::mat4 loc)
//
// PROPÓSITO: Asigna la posición del objecto 
//
void CAObject::SetLocation(glm::mat4 loc)
{
	model = loc;
	this->updateUniformBuffers(vulkan, view, projection);
}

//
// FUNCIÓN: Object::GetLocation()
//
// PROPÓSITO: Obtiene la posición del objecto 
//
glm::mat4 CAObject::GetLocation()
{
	return model;
}

//
// FUNCIÓN: Object::Translate(glm::vec3 t)
//
// PROPÓSITO: Añade un desplazamiento a la matriz de posición del objeto 
//
void CAObject::Translate(glm::vec3 t)
{
	model = glm::translate(model, t);
	this->updateUniformBuffers(vulkan, view, projection);
}

//
// FUNCIÓN: Object::Rotate(GLfloat angle, glm::vec3 axis)
//
// PROPÓSITO: Añade una rotación a la matriz de posición del objeto 
//
void CAObject::Rotate(GLfloat angle, glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(angle), axis);
	this->updateUniformBuffers(vulkan,view,projection);
}

//
// FUNCIÓN: Object::setLight(CALight l)
//
// PROPÓSITO: Asigna las propiedades de la luz que incide en la figura
//
void CAObject::setLight(CALight l)
{
	int num = GetNumPieces();
	for (int i = 0; i < num; i++)
	{
		GetPiece(i)->setLight(l);
	}
}

// FUNCION: CAObject::SetEstado(CAEstado_Coche e)
//
// PROPÓSITO: Asigna el estado del coche
//
void CAObject::SetEstado(CAEstado_Coche e)
{
	estado = e;
}

// FUNCION: CAObject::GetEstado()
//
// PROPÓSITO: Obtiene el estado del coche
//
CAEstado_Coche CAObject::GetEstado()
{
	return estado;
}


