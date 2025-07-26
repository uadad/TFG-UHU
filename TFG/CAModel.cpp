#include "CAModel.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "resource.h"
#include "CAVertexFigure.h"
#include "CAVertexSkybox.h"
#include "CATransformFigure.h"
#include "CATransformSkybox.h"
#include "Clases_Coches/CAObject.h"
#include "Clases_coches/CAEstado_Coche.h"

//
// FUNCIÓN: CAModel::CAModel(CAVulkanState* vulkan)
//
// PROPÓSITO: Initializa el modelo 3D
//
CAModel::CAModel(CAVulkanState* vulkan, int circuito, int car1, int car2, int tiempoTotal)
{
	view = glm::mat4(1.0f);
	this->vulkan = vulkan;

	createPipelines();

	this->skybox = new CASkybox(vulkan, skybox_pipeline.descriptorSetLayout);
	this->scene = new CAScene(vulkan, scene_pipeline.descriptorSetLayout, circuito, car1, car2);

	coches = scene->getCoches();

	tiempo = time(0); // inicializa el tiempo de la carrera a 0	
	if (tiempoTotal <= 0) {
		timeTotal = 120; // si el tiempo total es menor o igual a 0, se establece un tiempo por defecto de 2 minutos
	}
	else {
		timeTotal = tiempoTotal;
	}
}

//
// FUNCIÓN: CAModel::~CAModel()
//
// PROPÓSITO: Libera los recursos del modelo 3D
//
CAModel::~CAModel()
{
	skybox->finalize(vulkan);
	scene->finalize(vulkan);
	destroyPipelines();
	delete skybox;
	delete scene;
}

//
// FUNCIÓN: CAModel::createPipelines()
//
// PROPÓSITO: Crea los Pipelines de renderizado
//
void CAModel::createPipelines()
{
	CAShadersInfo skybox_shadersInfo = {};
	skybox_shadersInfo.vertex_shader = IDR_HTML1;
	skybox_shadersInfo.fragment_shader = IDR_HTML2;
	skybox_shadersInfo.depthTestEnable = VK_FALSE;


	std::vector<int> skybox_offsets = { offsetof(CAVertexSkybox,pos) };
	std::vector<VkFormat> skybox_formats = { VK_FORMAT_R32G32B32_SFLOAT };
	CAAttribInfo skybox_attribInfo = {};
	skybox_attribInfo.stride = sizeof(CAVertexSkybox);
	skybox_attribInfo.offsets = skybox_offsets;
	skybox_attribInfo.formats = skybox_formats;

	std::vector<VkDescriptorType> skybox_type = { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER };
	std::vector<VkShaderStageFlags> skybox_stage = { VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_FRAGMENT_BIT };
	CADescriptorInfo skybox_descriptorInfo = {};
	skybox_descriptorInfo.type = skybox_type;
	skybox_descriptorInfo.stage = skybox_stage;

	vulkan->createPipeline(skybox_shadersInfo, skybox_attribInfo, skybox_descriptorInfo, &skybox_pipeline);

	CAShadersInfo scene_shadersInfo = {};
	scene_shadersInfo.vertex_shader = IDR_HTML3;
	scene_shadersInfo.fragment_shader = IDR_HTML4;
	scene_shadersInfo.depthTestEnable = VK_TRUE;

	std::vector<int> scene_offsets = { offsetof(CAVertexFigure,pos), offsetof(CAVertexFigure,norm), offsetof(CAVertexFigure,tex) };
	std::vector<VkFormat> scene_formats = { VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32_SFLOAT };
	CAAttribInfo scene_attribInfo = {};
	scene_attribInfo.stride = sizeof(CAVertexFigure);
	scene_attribInfo.offsets = scene_offsets;
	scene_attribInfo.formats = scene_formats;

	std::vector<VkDescriptorType> scene_type = { 
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 
		VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER };
	std::vector<VkShaderStageFlags> scene_stage = { 
		VK_SHADER_STAGE_ALL_GRAPHICS, 
		VK_SHADER_STAGE_FRAGMENT_BIT, 
		VK_SHADER_STAGE_FRAGMENT_BIT, 
		VK_SHADER_STAGE_FRAGMENT_BIT };
	CADescriptorInfo scene_descriptorInfo = {};
	scene_descriptorInfo.type = scene_type;
	scene_descriptorInfo.stage = scene_stage;

	vulkan->createPipeline(scene_shadersInfo, scene_attribInfo, scene_descriptorInfo, &scene_pipeline);
}

//
// FUNCIÓN: CAModel::destroyPipelines()
//
// PROPÓSITO: Destruye los pipelines de renderizado
//
void CAModel::destroyPipelines()
{
	vulkan->destroyPipeline(skybox_pipeline);
	vulkan->destroyPipeline(scene_pipeline);
}

//
// FUNCIÓN: CAModel::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAModel::addCommands(VkCommandBuffer commandBuffer, int index)
{
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, skybox_pipeline.graphicsPipeline);
	skybox->addCommands(skybox_pipeline.pipelineLayout, commandBuffer, index);

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, scene_pipeline.graphicsPipeline);
	scene->addCommands(scene_pipeline.pipelineLayout, commandBuffer, index);
}

// FUNCIÓN: CAModel::aspect_ratio(double)
//
// PROPÓSITO: Modifica la relación anchura/altura del modelo
//
void CAModel::aspect_ratio(double aspect)
{
	double fov = glm::radians(30.0f);
	double sin_fov = sin(fov);
	double cos_fov = cos(fov);
	float wHeight = (float)(sin_fov * 0.2 / cos_fov);
	float wWidth = (float)(wHeight * aspect);

	//projection = glm::frustum(-wWidth, wWidth, -wHeight, wHeight, 0.2f, 400.0f);
	projection = glm::perspective((float)fov, (float)aspect, 0.02f, 400.0f);
	projection[1][1] *= -1.0f;
}

//
// FUNCIÓN: CAModel::update()
//
// PROPÓSITO: Actualiza la información para generar la imagen 
//
void CAModel::update()
{
	ViewCamara();  // actualización de la matriz de view
	std::vector<bool> mostrar = { mostrar_cocheParado, mostrar_PeticionCambioCarril, true, mostrar_Choque, mostrar_final, mostrar_ganador, true};
	for (int i = 0; i < 10; i++) {
		mostrar.push_back(mostrar_etiqueta_0[i]);
	}
	for (int i = 0; i < 10; i++) {
		mostrar.push_back(mostrar_etiqueta_1[i]);
	}
	for (int i = 0; i < 10; i++) {
		mostrar.push_back(mostrar_etiqueta_m0[i]);
	}
	for (int i = 0; i < 10; i++) {
		mostrar.push_back(mostrar_etiqueta_m1[i]);
	}
	for (int i = 0; i < 10; i++) {
		mostrar.push_back(mostrar_etiqueta_s0[i]);
	}
	for (int i = 0; i < 10; i++) {
		mostrar.push_back(mostrar_etiqueta_s1[i]);
	}

	int etiq = 68; // 67 es el id de la etiqueta del punto rojo para reservarla para el coche que se esta manejando en un determinado momento.
	for (int i = 0; i < coches.size(); i++) {
		CAEstado_Coche est = coches[i]->GetEstado();
		if (est.id == coche) {
			calcular_posPunto(coches[i], 67);
			mostrar.push_back(true);
		}
		else {
			calcular_posPunto(coches[i], etiq++);
			mostrar.push_back(true);
		}
	}

	//actualiza la etiqueta de la velocidad
	mostrar.push_back(true);
	for (int i = 0; i < 10; i++) mostrar.push_back(mostrar_etiqueta_v_0[i]);
	for (int i = 0; i < 10; i++) mostrar.push_back(mostrar_etiqueta_v_1[i]);
	for (int i = 0; i < 2; i++) mostrar.push_back(mostrar_etiqueta_v_2[i]);


	skybox->updateUniformBuffers(vulkan, view, projection);
	scene->update(vulkan, view, projection, mostrar);


	for (int i = 0; i < coches.size(); i++) {
		CAEstado_Coche est = coches[i]->GetEstado();
		if (est.coche_pausado) est.coche_pausa_cont++;
		if (est.coche_pausa_cont > 400) {
				est.coche_pausado = false;
				est.coche_pausa_cont = 0;
		}
		else if (est.coche_pausa_cont > 20) {
			est.velocidad = 0.0f;
		}
		if (est.choque_coche) est.choque_coche_cont++;
		if (est.choque_coche_cont > 400) {
			est.choque_coche = false;
			est.choque_coche_cont = 0;
		}
		coches[i]->SetEstado(est);
	}
	comprobarChoque(); // comprueba si hay choque entre coches
	actualiza(); // actualiza el estado de coches
	actualiza_Etiqueta_NumVuelta_Tiempo(); // actualiza la etiqueta de la vuelta y el tiempo
	actualiza_Etiqueta_Velocidad(); // actualiza la etiqueta de la velocidad

	fin = contador_Tiempo >= timeTotal;  // finaliza la carrera si el tiempo es mayor a un nunmmero definido en minutos.
	// reiniciar la carrera una vez finalizado el juego
	if (fin) {
		int numVueltasMax = 0, id = 0;
		for (int i = 0; i < coches.size(); i++) {
			CAEstado_Coche est = coches[i]->GetEstado();
			if (est.numVueltas > numVueltasMax) numVueltasMax = est.numVueltas;
			if (est.id == coche) id = i;
		}
		for (int i = 0; i < coches.size(); i++) {
			CAEstado_Coche est = coches[i]->GetEstado();
			if (est.numVueltas == numVueltasMax && numVueltasMax > 0) {
				est.mostrar_Gandor = true;
				est.mostrar_final = false;
			}
			else {
				est.mostrar_Gandor = false;
				est.mostrar_final = true;
			}
			coches[i]->SetEstado(est);
		}
		
		for (int i = 0; i < coches.size(); i++){
			CAEstado_Coche est = coches[i]->GetEstado();
			est.velocidad = 0.0f;
			est.pistaAct = est.pistaIni;
			est.distancia = 0.0f;
			est.coche_pausado = false;
			est.coche_pausa_cont = 0;	
			est.choque_coche = false;
			est.choque_coche_cont = 0;
			est.peticionCambioCarril = false;
			coches[i]->SetEstado(est);
	    }
	}
	contador_Tiempo = time(0) - tiempo; // actualiza el contador de tiempo de la carrera

	//printf("Contador de tiempo: %d\n", contador_Tiempo);

}

const float lapso = 1 / 60.0f;
//
// FUNCIÓN: CAModel::key_pressed(int)
//
// PROPÓSITO: Respuesta a acciones de teclado
//
void CAModel::key_pressed(int key)
{
	CAEstado_Coche est;
	int j;
	for (int i = 0; i < coches.size(); i++) {
		if (coches[i]->GetEstado().id == coche) {
			est = coches[i]->GetEstado();
			j = i;
			break;
		}
   }
	switch (key)
	{
	case GLFW_KEY_DOWN:  // frenar coche
	case GLFW_KEY_S:
		if (!fin) {
			if (!(est.coche_pausado && est.coche_pausa_cont >= 20) && !est.choque_coche) {
				if (est.velocidad > 0.02f) est.velocidad -= 0.02;
			}
			else est.velocidad = 0.0f;
		}
		break;
	case GLFW_KEY_UP:  // acelerar coche
	case GLFW_KEY_W:
		if (!fin) {
			if (!(est.coche_pausado && est.coche_pausa_cont >= 20) && !est.choque_coche) {
				if (est.velocidad < 1.2f) est.velocidad += 0.02;
			}
			else est.velocidad = 0.0f;
		}
		break;
	case GLFW_KEY_SPACE:  // cambiar de coche
		if (coche >= coches.size())
			coche = 1;
		else
			coche++;
		break;

	case GLFW_KEY_LEFT:  // solicitar el cambio de carril
	case GLFW_KEY_A:
		if (!fin) {
			est.peticionCambioCarril = true;
			mostrar_PeticionCambioCarril = true;
		}
		break;
	case GLFW_KEY_RIGHT: // cancelar el cambio de carril 
	case GLFW_KEY_D:
		if (!fin) {
			est.peticionCambioCarril = false;
			mostrar_PeticionCambioCarril = false;
		}
		break;
	}
	coches[j]->SetEstado(est);
}

void CAModel::actualiza()
{
	for (int i = 0; i < coches.size(); i++) {
		CAEstado_Coche est = coches[i]->GetEstado();
		est.distancia += est.velocidad * lapso;
		coches[i]->SetEstado(est);
		scene->actualizaCoche(coches[i]);
		float R = scene->getCircuito()->devolverRadio(coches[i]);
		float aceleracion_centripta = (est.velocidad * est.velocidad) / R;
		if (aceleracion_centripta > limite_Curva && R != 0.0f) {
			est.coche_pausado = true;
		}

		if (coche == est.id) {  // solo se actualiza el coche seleccionado con la peticion de cambio de carril, y el resto de etiquetas
			mostrar_PeticionCambioCarril = est.peticionCambioCarril;
			mostrar_Choque = est.choque_coche;
			mostrar_cocheParado = est.coche_pausado;
			mostrar_ganador = est.mostrar_Gandor;
			mostrar_final = est.mostrar_final;
		}

		coches[i]->SetEstado(est);
		if (est.coche_pausa_cont > 0) { 
			float a = 20.0f / 90.0f;
			float y = a * est.coche_pausa_cont;
			std::string nom = scene->getCircuito()->getPista(est.pistaAct)->getNombre();
			if (nom == "Curva_der_std" || nom == "Curva_der_int" || nom == "Curva_der_ext" || nom == "Curva_der_sup_ext")
			{
				y = -y;
			}
			coches[i]->Rotate(y, glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
}


// FUNCIÓN: CAModel::ViewCamara()
//	
// PROPÓSITO: Actualiza la matriz de view para que la camara siga al coche
// 
void CAModel::ViewCamara()
{
	int j = -1;
	for (int i = 0; i < coches.size(); i++) {
		if (coches[i]->GetEstado().id == coche) j = i;
	}
	glm::mat4 loc = coches[j]->GetLocation();
	loc = glm::rotate(loc, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	loc = glm::rotate(loc, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	angulo_objetivo = scene->getCircuito()->devolverAngulo(coches[j]);

	if ((angulo_objetivo - angulo)>0) angulo += angulo_step;
	else if ((angulo_objetivo - angulo) < 0) angulo -= angulo_step;

	loc = glm::rotate(loc, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
	loc = glm::translate(loc, glm::vec3(0.045f, 0.05f, 0.3f));
	view = glm::inverse(loc);
}

//
//  FUNCIÓN: CAModel:::mouse_button(int button, int action)
//
//  PROPÓSITO: Respuesta del modelo a un click del ratón.
//
void CAModel::mouse_button(int button, int action)
{
//	std::cout << "Model mouse button" << std::endl;
}

//
//  FUNCIÓN: CAModel::mouse_move(double xpos, double ypos)
//
//  PROPÓSITO: Respuesta del modelo a un movimiento del ratón.
//
void CAModel::mouse_move(double xpos, double ypos)
{
//	std::cout << "Model mouse move(" << xpos << "," << ypos << ")" << std::endl;
}


// FUNCIÓN: CAModel::signoPunto(glm::vec2 a, glm::vec2 b, glm::vec2 z)
//
// PROPÓSITO: Devuelve el signo del punto z respecto a la recta que pasa por a y b
//
int CAModel::signoPunto(glm::vec2 a, glm::vec2 b, glm::vec2 z)
{
	float A = b.y - a.y;
	float B = a.x - b.x;
	float C = (b.x * a.y) - (a.x * b.y);
	float val = A * z.x + B * z.y + C;
	if (val >= 0) return 1;
	else return -1;
}

// FUNCIÓN: CAModel::signoDosCohe(glm::mat4 coche1, glm::mat4 coche2)
//
// PROPÓSITO: Comprobar que los dos coches no se solapen, es decir que ningun punto de un coche este dentro de las rectas del rectanguo que forma el otro coche
//
bool CAModel::signoDosCoche(glm::mat4 coche1, glm::mat4  coche2)
{
	float anchoc = 0.018f;
	float largoc = 0.07f - 0.04375f, largo1 = 0.07f + 0.04375f;
	glm::vec4 v1 = glm::vec4(-anchoc, largo1, 0.0f, 1.0f);
	glm::vec4 v2 = glm::vec4(anchoc, largo1, 0.0f, 1.0f);
	glm::vec4 v3 = glm::vec4(anchoc, - largoc, 0.0f, 1.0f);
	glm::vec4 v4 = glm::vec4(- anchoc, - largoc, 0.0f, 1.0f);

	glm::vec4 A = coche1 * v1;
	glm::vec4 B = coche1 * v2;
	glm::vec4 C = coche1 * v3;
	glm::vec4 D = coche1 * v4;

	glm::vec4 E = coche2 * v1;
	glm::vec4 F = coche2 * v2;
	glm::vec4 G = coche2 * v3;
	glm::vec4 H = coche2 * v4;

	glm::vec2 a = glm::vec2(A.x, A.z); glm::vec2 b = glm::vec2(B.x, B.z);
	glm::vec2 c = glm::vec2(C.x, C.z); glm::vec2 d = glm::vec2(D.x, D.z);
	glm::vec2 e = glm::vec2(E.x, E.z); glm::vec2 f = glm::vec2(F.x, F.z); 
	glm::vec2 g = glm::vec2(G.x, G.z); glm::vec2 h = glm::vec2(H.x, H.z);

	int s1, s2, s3, s4;
	glm::vec2 z;
	for (int i = 0; i < 4; i++) {
		if (i == 0) z = e;
		else if (i == 1) z = f;
		else if (i == 2) z = g;
		else z = h;
		s1 = signoPunto(a, b, z);
		s2 = signoPunto(b, c, z);
		s3 = signoPunto(c, d, z);
		s4 = signoPunto(d, a, z);
		if (s1 < 0 && s2 < 0 && s3 < 0 && s4 < 0) {
			return true;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (i == 0) z = a;
		else if (i == 1) z = b;
		else if (i == 2) z = c;
		else z = d;
		s1 = signoPunto(e, f, z);
		s2 = signoPunto(f, g, z);
		s3 = signoPunto(g, h, z);
		s4 = signoPunto(h, e, z);
		if (s1 < 0 && s2 < 0 && s3 < 0 && s4 < 0) {
			return true;
		}
	}

	return false;
}

// FUNCIÓN: CAModel::comprobarChoque()
//
// PROPÓSITO: Comprobar si hay choque entre los coches
//
void CAModel::comprobarChoque()
{
	for (int i = 0; i < coches.size(); i++) {
		for (int j = 0; j < coches.size(); j++) {
			if (j == i) continue;
			glm::mat4 coche1 = coches[i]->GetLocation();
			glm::mat4 coche2 = coches[j]->GetLocation();
			CAEstado_Coche est1 = coches[i]->GetEstado();
			CAEstado_Coche est2 = coches[j]->GetEstado();
			if (signoDosCoche(coche1,coche2) && (!est1.choque_coche && !est2.choque_coche)) {
				est1.choque_coche = true;
				est2.choque_coche = true;
				if (est1.velocidad >= est2.velocidad) {
					est2.distancia += 0.3f;
					est1.velocidad = 0.0f;	
				}
				else {
					est1.distancia += 0.3f;
					est2.velocidad = 0.0f;

				}
				coches[i]->SetEstado(est1);
				coches[j]->SetEstado(est2);
			}
		}
	}
}

// FUNCIÓN: CAModel::actualiza_Etiqueta_NumVuelta_Tiempo()
//
// PROPÓSITO: Actualiza la etiqueta de la vuelta y el tiempo
//
void CAModel::actualiza_Etiqueta_NumVuelta_Tiempo()
{
	// actualizacion del cronómetro:
	if (contador_Tiempo > contador_actual) {
		contador_actual = contador_Tiempo;
		for (int i = 0; i < 10; i++) {
			mostrar_etiqueta_s0[i] = false;
			mostrar_etiqueta_s1[i] = false;
		}
		int s3 = (int) contador_actual;
		int s4 = (int) s3 % 10;
		if (s3 > 9) {
			int dec = (s3 / 10) % 6;
			mostrar_etiqueta_s1[s4] = true;
			mostrar_etiqueta_s0[dec] = true;
		}
		else {
			mostrar_etiqueta_s1[s4] = true;
			mostrar_etiqueta_s0[0] = true;
		}

		for (int i = 0; i < 10; i++) {
			mostrar_etiqueta_m0[i] = false;
			mostrar_etiqueta_m1[i] = false;
		}

		int s5 = (int) contador_actual / 60;
		int s6 = (int) s5 % 10;
		if (s5 > 9) {
			int dec = (s5 / 10) % 6;
			mostrar_etiqueta_m1[s6] = true;
			mostrar_etiqueta_m0[dec] = true;
		}
		else {
			mostrar_etiqueta_m1[s6] = true;
			mostrar_etiqueta_m0[0] = true;
		}
	}

	// actualizacion del numero de vueltas
	for (int i = 0; i < coches.size(); i++) {
		CAEstado_Coche est = coches[i]->GetEstado();
		if (est.id == coche) {
			for (int i = 0; i < 10; i++) {
				mostrar_etiqueta_0[i] = false;
				mostrar_etiqueta_1[i] = false;
			}
			if (est.numVueltas > est.contador_etqieuta_Num_Vuelta) {
				est.contador_etqieuta_Num_Vuelta++;
				coches[i]->SetEstado(est);
				if (est.numVueltas <= 9) {
					mostrar_etiqueta_0[0] = true;
					mostrar_etiqueta_1[est.numVueltas] = true;
				}
				else {
					int dec = est.numVueltas / 10;
					int inc = est.numVueltas % 10;
					mostrar_etiqueta_0[dec] = true;
					mostrar_etiqueta_1[inc] = true;
				}
			}
			else {
				if (est.numVueltas <= 9) {
					mostrar_etiqueta_0[0] = true;
					mostrar_etiqueta_1[est.numVueltas] = true;
				}
				else {
					int dec = est.numVueltas / 10;
					int inc = est.numVueltas % 10;
					mostrar_etiqueta_0[dec] = true;
					mostrar_etiqueta_1[inc] = true;
				}
			}
		}
	}
}

// FUNCIÓN: CAModel::calcular_posPunto(CAObject* coche)
//
// PROPÓSITO: Calcula la posición de un punto en la pantalla en coordenada clip.
//
void CAModel::calcular_posPunto(CAObject* coche, int i)
{
	glm::vec4 loc = coche->GetLocation()[3];
	//glm::vec2 AB = glm::vec2(-0.92775f, -1.41f); // (256/980) * 2 - 1

	float escalaX, escalaY, despX, despY;
	if (scene->getCircuito()->getNombre() == "CACircuito_jerez") {
		escalaX = 2.33f;   escalaY = 2.025f; despX = -0.475f;    despY = -0.75f;
	}
	else if (scene->getCircuito()->getNombre() ==  "CACircuito_1") {
		escalaX = 1.325f;   escalaY = 0.7f;  despX = -0.285f;    despY = 0.36f;
	}
	else if (scene->getCircuito()->getNombre() == "CACircuito_2") {
		escalaX = 1.485f;   escalaY = 1.1f;  despX = -0.28f;    despY = 0.6f;
	}
	else if (scene->getCircuito()->getNombre() == "CACircuito_3") {
		escalaX = 0.915f;   escalaY = 0.965f; despX = 0.12f;    despY = 0.74f;
	}
	else if (scene->getCircuito()->getNombre() == "CACircuito_4") {
		escalaX = 1.775f;   escalaY = 0.985f;  despX = -0.325f;    despY = 0.46f;
	}
	else if (scene->getCircuito()->getNombre() == "CACircuito_293") {
		escalaX = 1.42f;   escalaY = 0.875f;  despX = -0.3f;    despY = -0.62f;
	}
	else if (scene->getCircuito()->getNombre() == "CACircuito_380") {
		escalaX = 2.55f;   escalaY = 1.75f;  despX = -0.54f;    despY = 0.75f;
	}
	else if (scene->getCircuito()->getNombre() == "CACircuito_946") {
		escalaX = 2.1f;   escalaY = 1.45f;  despX = -0.3f;    despY = 0.62f;
	}
	glm::vec2 pos;
	// pos.x = -loc.z/ escalaX + AB.x / 2.0f;
	// pos.y =  loc.x/ escalaY + AB.y / 2.0f;

	pos.x = -loc.z / escalaX + despX;
	pos.y = loc.x / escalaY + despY;

	glm::vec2 centro = glm::vec2(0.725f , -0.725);
	glm::vec2 punto = centro + pos * 0.225f;
	scene->getEtiqueta(i)->setG(punto);

}


// FUNCIÓN: CAModel::actualiza_Etiqueta_Velocidad()
//
// PROPÓSITO: Actualizar la etiqueta de la velocidad
//
void CAModel::actualiza_Etiqueta_Velocidad() {

	float velocidad = 0.0f;
	for (int i = 0; i < coches.size(); i++) {
		if (coches[i]->GetEstado().id == coche) {
			velocidad = coches[i]->GetEstado().velocidad;
			break;
		}
	}

	for (int i = 0; i < 10; i++) {
		mostrar_etiqueta_v_0[i] = false;
		mostrar_etiqueta_v_1[i] = false;
		if (i < 2) mostrar_etiqueta_v_2[i] = false;
	}

	int s1 = (int)(velocidad * 100) % 100;
	int indV1 = s1 / 10;
	int indV0 = s1 % 10;

	mostrar_etiqueta_v_0[indV0] = true;
	mostrar_etiqueta_v_1[indV1] = true;

	if ((velocidad / 1.0f) >= 1.0f) mostrar_etiqueta_v_2[1] = true;
	else mostrar_etiqueta_v_2[0] = true;
}
