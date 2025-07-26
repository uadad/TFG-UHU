#pragma once

#include "CAPiece.h"
#include "CAEstado_Coche.h"

class CAObject
{
public:
	void initalize(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	void finalize(CAVulkanState* vulkan);
	void addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index);
	void updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);
	void ResetLocation();
	void SetLocation(glm::mat4 loc);
	glm::mat4 GetLocation();
	void Translate(glm::vec3 t);
	void Rotate(GLfloat angle, glm::vec3 axis);

	void setLight(CALight l);

	virtual int GetNumPieces() =0;
	virtual CAPiece* GetPiece(int i) =0;

	void SetEstado(CAEstado_Coche e);
	CAEstado_Coche GetEstado();

protected:
	glm::mat4 model,view,projection;
	CAVulkanState* vulkan;
	CAEstado_Coche estado;

};

