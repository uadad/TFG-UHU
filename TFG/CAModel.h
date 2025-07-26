#pragma once

#include "CAVulkanState.h"
#include "CAPipeline.h"
#include "CASkybox.h"
#include "CAScene.h"
#include "Clases_coches/CAObject.h"
#include <iostream>


class CAModel
{
private:
	CAVulkanState* vulkan;
	glm::mat4 projection;
	float aspect;

	CAPipeline skybox_pipeline;
	CAPipeline scene_pipeline;
	CASkybox* skybox;
	CAScene* scene;

	glm::mat4 view; // camara

	int coche = 1; // 1->coche1, 2->coche2 control de teclas sobre el coche

	float angulo = 0.0f; // angulo de giro de la camara
	float angulo_objetivo = 0.0f; // angulo objetivo de giro de la camara según la pista del coche
	float angulo_step = 1.0f; // velocidad de giro de la camara

	float aceleracion_centripta = 0.0f; // aceleracion centrípeta del coche
	float limite_Curva = 0.8f; // limite de velocidad del coche para salir de una pista.

	std::vector<CAObject*> coches; // coches de la escena
	 
	bool mostrar_cocheParado = false; // mostrar la etiqueta del coche parado
	bool mostrar_PeticionCambioCarril = false; // mostrar la etiqueta de la peticion de cambio de carril
	bool mostrar_Choque = false; // mostrar la etiqueta de choque
	bool mostrar_ganador = false; // mostrar la etiqueta de ganador
	bool mostrar_final = false; // mostrar la etiqueta de final de carrera
	bool fin = false;

	std::vector<bool> mostrar_etiqueta_0 = { false, false, false, false, false, false, false, false, false, false }; // mostrar la etiqueta de la meta 0
	std::vector<bool> mostrar_etiqueta_1 = { false, false, false, false, false, false, false, false, false, false }; // mostrar la etiqueta de la meta 0
	std::vector<bool> mostrar_etiqueta_m0 = { false, false, false, false, false, false, false, false, false, false }; // mostrar la etiqueta de la meta 0
	std::vector<bool> mostrar_etiqueta_m1 = { false, false, false, false, false, false, false, false, false, false }; // mostrar la etiqueta de la meta 1
	std::vector<bool> mostrar_etiqueta_s0 = { false, false, false, false, false, false, false, false, false, false }; // mostrar la etiqueta de la meta 2
	std::vector<bool> mostrar_etiqueta_s1 = { false, false, false, false, false, false, false, false, false, false }; // mostrar la etiqueta de la meta 3

	std::vector<bool> mostrar_etiqueta_v_0 = { false, false, false, false, false, false, false, false, false, false }; // mostrar la etiqueta de la velocidad 0
	std::vector<bool> mostrar_etiqueta_v_1 = { false, false, false, false, false, false, false, false, false, false }; // mostrar la etiqueta de la velocidad 1
	std::vector<bool> mostrar_etiqueta_v_2 = { false, false }; // mostrar la etiqueta de la velocidad 2

	int contador_Tiempo = 0; // contador de tiempo de la carrera
	int contador_actual_1 = 0, contador_actual_2 = 0, contador_actual_3 = 0, contador_actual_4 = 0;  // contadores actuales del tiempo de la carrera
	int contador_actual = 0; // contador actual del tiempo de la carrera

	int tiempo = 0; // tiempo de la carrera en segundos
	int timeTotal = 0; // tiempo total de la carrera en segundos

public:
	CAModel(CAVulkanState* vulkan, int circuito, int car1, int car2, int tiempoTotal);
	~CAModel();

	void createPipelines();
	void destroyPipelines();
	void addCommands(VkCommandBuffer commandBuffer, int index);
	void update();
	void key_pressed(int key);
	void actualiza();
	void ViewCamara();
	void mouse_move(double xpos, double ypos);
	void mouse_button(int button, int action);
	void aspect_ratio(double aspect);

	int signoPunto(glm::vec2 a, glm::vec2 b, glm::vec2 z);
	bool signoDosCoche(glm::mat4 coche1, glm::mat4 coche2);
	void comprobarChoque();
	void actualiza_Etiqueta_NumVuelta_Tiempo();

	void calcular_posPunto(CAObject* coche, int i);
	void actualiza_Etiqueta_Velocidad();
};


