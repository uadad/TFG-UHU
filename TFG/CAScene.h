#pragma once

#include "CAVulkanState.h"
#include "CAFigure.h"
#include "CATexture.h"
#include "Clases_Coches/CAObject.h"
#include "Clases_Circuitos/CACircuito.h"
#include "Clases_Circuitos/CAPista.h"
#include "CAEtiqueta_Abstracta.h"



class CAScene {
public:
	CAScene(CAVulkanState* vulkan, VkDescriptorSetLayout layout, int circuito2, int car1, int car2);
	~CAScene();
	void finalize(CAVulkanState* vulkan);
	void addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index);
	void update(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection, std::vector<bool> mostrar);
	void actualizaCoche(CAObject* &coche);
	void crearTexturas(CAVulkanState* vulkan);
	void crear_etiquetas7segmentos(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	void crear_etiquetasVelocidad(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	std::vector<CAObject*> getCoches() { return coches; }
	CACircuito* getCircuito() { return circuito; }
	CAEtiqueta_Abstracta* getEtiqueta(int i) { return etiquetas[i]; }
	CATexture& getTexture(int i) { return textures[i]; }

private:
	std::vector<CAFigure*> figures;
	std::vector<CATexture> textures,textures1;
	std::vector<CAPista*>  pistas;
	CACircuito* circuito;
	std::vector<CAObject*> coches;

	std::vector<CAEtiqueta_Abstracta*> etiquetas;
};

