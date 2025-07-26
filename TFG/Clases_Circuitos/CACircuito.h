#pragma once

#include <vector>
#include "CAPista.h"
#include <string>
#include "../CAVulkanState.h"
#include "../CALight.h"
#include "../CAMaterial.h"
#include "../Clases_coches/CAObject.h"

class CACircuito
{
protected:
	glm::mat4 location;
	std::vector<CAPista*> pistas;
	std::vector<std::string> nombre_pistas;
	int num_pistas;

	std::string nombre; // nombre del circuito para definir la ventana del juego
public:
	~CACircuito();
	void initialize(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	void finalize(CAVulkanState* vulkan);
	void addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index);
	void updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);

	CAPista* crearPista(std::string nom);
	void AsignarTexturas(std::vector<CATexture> textures, CALight light, CAMaterial material);
	void DefinirLoc(glm::vec3 loc, CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	
	glm::mat4 devolverLocCoche(CAObject* &coche);  // devolver la localización del coche y el numro de vueltas

	float devolverAngulo(CAObject*& coche); // devuelve el angulo de la pista en la ranura s y distancia d

	float devolverRadio(CAObject*& coche);  // devuelve el radio de la pista en la que se encuentra el coche

	int getNumPistas();

	CAPista* getPista(int i);

	std::string getNombre() { return nombre; }

	glm::mat4 devLocArcoFinal();
};

