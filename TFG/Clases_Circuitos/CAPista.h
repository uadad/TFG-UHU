#pragma once

#include "../CAVulkanState.h"
#include "../CAVertexFigure.h"
#include "../CATransformFigure.h"
#include "../CALight.h"
#include "../CAMaterial.h"
#include "../CAIndexBuffer.h"
#include "../CAVertexBuffer.h"
#include "../CAUniformBuffer.h"
#include "../CATexture.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "../Clases_coches/CAEstado_Coche.h"

class CAPista
{
protected:
	std::vector<CAVertexFigure> vertices;
	std::vector<uint16_t> indices;
	glm::mat4 location;
	CALight light;
	CAMaterial material;
	CATexture texture;
	std::string nombre;


public:
	void initialize(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	void finalize(CAVulkanState* vulkan);
	void addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index);
	void updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);
	CATexture getTexture();
	void resetLocation();
	void setLocation(glm::mat4 m);
	void translate(glm::vec3 t);
	void rotate(float angle, glm::vec3 axis);
	void setLight(CALight l);
	CALight getLight();
	void setMaterial(CAMaterial m);
	CAMaterial getMaterial();
	void setTexture(CATexture texture);

	void setNombre(std::string nombre);
	std::string getNombre();
	virtual glm::mat4 getFinalLocation() =0;
	glm::mat4 getLocation();
	virtual bool estaDentro(CAEstado_Coche &est) =0;
	virtual glm::mat4 getCarLocation(CAEstado_Coche est) =0; // 0->slot_izq, 1-->der
	virtual float getLongitud(int slot) = 0;
	virtual float getAngulo(CAEstado_Coche est) = 0;
	virtual glm::mat4 getLocArcoFinal() = 0;

private:
	CAVertexBuffer vbo;
	CAIndexBuffer ibo;
	CAUniformBuffer transformBuffer;
	CAUniformBuffer lightBuffer;
	CAUniformBuffer materialBuffer;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
};

