#include "CAScene.h"

#include "CATransformFigure.h"
#include "CAGround.h"
#include "CAMaterial.h"
#include "CATexture.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Includes_Scene.h"
#include "Clases_coches/CAEstado_Coche.h"
#include "CAEtiqueta_Abstracta.h"
#include "CAEtiqueta.h"
#include "CAArco_final.h"


//
// FUNCIÓN: CAScene::CAScene(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CAScene::CAScene(CAVulkanState* vulkan, VkDescriptorSetLayout layout, int circuito2, int car1, int car2)
{

	CALight light = {};
	light.Ldir = glm::normalize(glm::vec3(1.0f, -0.8f, -0.7f));
	light.La = glm::vec3(0.7f, 0.7f, 0.7f);
	light.Ld = glm::vec3(0.3f, 0.3f, 0.3f);
	light.Ls = glm::vec3(1.0f, 1.0f, 1.0f);

	CAMaterial material = {};
	material.Ka = glm::vec3(1.0f, 1.0f, 1.0f);
	material.Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	material.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	material.Shininess = 16.0f;

	switch (circuito2) {
	case 1:
		circuito = new CACircuito_1();
		break;
	case 2:
		circuito = new CACircuito_2();
		break;
	case 3:
		circuito = new CACircuito_3();
		break;
	case 4:
		circuito = new CACircuito_4();
		break;
	case 293:
		circuito = new CACircuito_293();
		break;
	case 380:
		circuito = new CACircuito_380();
		break;
	case 946:
		circuito = new CACircuito_946();
		break;
	case 999:
		circuito = new CACircuito_jerez();
		break;
	default:
		circuito = new CACircuito_1();
	}
	// circuito = new CACircuito_jerez();
	// circuito = new CACircuito_380();
	// circuito = new CACircuito_1();
	// circuito = new CACircuito_2();  
	//circuito = new CACircuito_946();
	//circuito = new CACircuito_3();
	//circuito = new CACircuito_4();   
	//circuito = new CACircuito_293();
	crearTexturas(vulkan);
	circuito->AsignarTexturas(textures, light, material);
	circuito->initialize(vulkan, layout);
	circuito->DefinirLoc(glm::vec3(0.0f, 0.02f, 0.0f), vulkan, layout);


	CAMaterial groundMat = {};
	groundMat.Ka = glm::vec3(1.0f, 1.0f, 1.0f);
	groundMat.Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	groundMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	groundMat.Shininess = 16.0f;

	CAFigure* ground = new CAGround(25.0f, 25.0f);
	ground->setTexture(textures[12]);
	ground->initialize(vulkan, layout);
	ground->setLight(light);
	ground->setMaterial(groundMat);

	CAFigure* arcoFinal = new CAArco_final();
	arcoFinal->setTexture(textures[32]);
	arcoFinal->initialize(vulkan, layout);
	arcoFinal->setLight(light);
	arcoFinal->setMaterial(groundMat);


	glm::mat4 loc = circuito->devLocArcoFinal();
	arcoFinal->setLocation(loc);

    figures.resize(2);
	figures[0] = ground;
	figures[1] = arcoFinal;

	CAObject* coche = nullptr;
	CAObject* coche2 = nullptr;

	switch (car1) {
	case 1:
		coche = new CAForceIndia(vulkan, layout);
		break;	
	case 2:
		coche = new CAMercedes(vulkan, layout);
		break;				
	case 3:
		coche = new CARedbull(vulkan, layout);
		break;
	case 4:
		coche = new CATororosso(vulkan, layout);
		break;
	case 5:
		coche = new CAWilliams(vulkan, layout);
		break;
	case 6:
		coche = new CAMclaren(vulkan, layout);
		break;
	case 7:
		coche = new CARenault(vulkan, layout);
		break;
	case 8:
		coche = new CAVirgin(vulkan, layout);
		break;
	case 9:
		coche = new CAHrt(vulkan, layout);
		break;
	case 10:
		coche = new CALotus(vulkan, layout);
		break;
	case 11:
		coche = new CASauber(vulkan, layout);
		break;
	case 12:
		coche = new CAFerrari(vulkan, layout);
		break;
	default:
		coche = new CAFerrari(vulkan, layout);
		break;
	}

	switch (car2) {
	case 1:
		coche2 = new CAForceIndia(vulkan, layout);
		break;
	case 2:
		coche2 = new CAMercedes(vulkan, layout);
		break;
	case 3:
		coche2 = new CARedbull(vulkan, layout);
		break;
	case 4:
		coche2 = new CATororosso(vulkan, layout);
		break;
	case 5:
		coche2 = new CAWilliams(vulkan, layout);
		break;
	case 6:
		coche2 = new CAMclaren(vulkan, layout);
		break;
	case 7:
		coche2 = new CARenault(vulkan, layout);
		break;
	case 8:
		coche2 = new CAVirgin(vulkan, layout);
		break;
	case 9:
		coche2 = new CAHrt(vulkan, layout);
		break;
	case 10:
		coche2 = new CALotus(vulkan, layout);
		break;
	case 11:
		coche2 = new CASauber(vulkan, layout);
		break;
	case 12:
		coche2 = new CAFerrari(vulkan, layout);
		break;
	default:
		coche2 = new CATororosso(vulkan, layout);
		break;
	}


	coches.resize(2);
	coches[0] = coche;
	coches[1] = coche2;
//	coches[2] = coche3;
//	coches[3] = coche4;
//	coches[4] = coche5;
//	coches[5] = coche6;
//	coches[6] = coche7;
//	coches[7] = coche8;
//	coches[8] = coche9;
//	coches[9] = coche10;
//	coches[10] = coche11;

	// bucle para inicializar los coches
	int j = 2;
	int num_pistas = circuito->getNumPistas();
	for (int i = 0; i < coches.size(); i++) {
		coches[i]->initalize(vulkan, layout);
		coches[i]->setLight(light);
		coches[i]->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		coches[i]->Rotate(-180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		
		CAEstado_Coche est = {};
		est.slot = i % 2;
		est.distancia = 0.0f;
		est.id = i+1;
		est.numVueltas = 0;
		if(i >= j) {  // por si hay mas de dos coches situarlos en las pistas anteriores por orden
			est.pistaIni = (num_pistas-1) - (int)(j / 2);
			if (i == j+1) j += 2;
		}
		else {
			est.pistaIni = 0;
		}
		est.pistaAct = est.pistaIni;
		est.velocidad = 0.0f;
		est.peticionCambioCarril = false;
		est.coche_pausado = false;
		est.coche_pausa_cont = 0;
		est.choque_coche = false;
		est.choque_coche_cont = 0;
		est.contador_etqieuta_Num_Vuelta = 0;
		est.mostrar_Gandor = false;
		est.mostrar_final = false;
		coches[i]->SetEstado(est);
	}


	// creacion de etiquetas
	CAEtiqueta_Abstracta* salida_pista = new CAEtiqueta(glm::vec2(-0.5,-0.2), glm::vec2(0.5,0.2));
	salida_pista->setTexture(textures[13]);
	salida_pista->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* peticion_Cambio_Carril = new CAEtiqueta(glm::vec2(-0.95, 0.75), glm::vec2(-0.75, 0.95));
	peticion_Cambio_Carril->setTexture(textures[14]);
	peticion_Cambio_Carril->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* ventana_Circuito = new CAEtiqueta(glm::vec2(0.5, -0.95), glm::vec2(0.95, -0.5));
	ventana_Circuito->setTexture(textures[15]);
	ventana_Circuito->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* choque_coche = new CAEtiqueta(glm::vec2(-0.5, -0.2), glm::vec2(0.5, 0.2));
	choque_coche->setTexture(textures[16]);
	choque_coche->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* final_juego = new CAEtiqueta(glm::vec2(-0.5, -0.2), glm::vec2(0.5, 0.2));
	final_juego->setTexture(textures[17]);
	final_juego->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* campeon = new CAEtiqueta(glm::vec2(-0.5, -0.2), glm::vec2(0.5, 0.2));
	campeon->setTexture(textures[18]);
	campeon->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* vuelta_tiempo = new CAEtiqueta(glm::vec2(-0.95, -0.95), glm::vec2(-0.3, -0.5));
	vuelta_tiempo->setTexture(textures[19]);
	vuelta_tiempo->initialize(vulkan, layout);

	etiquetas.push_back(salida_pista);
	etiquetas.push_back(peticion_Cambio_Carril);
	etiquetas.push_back(ventana_Circuito);
	etiquetas.push_back(choque_coche);
	etiquetas.push_back(final_juego);
	etiquetas.push_back(campeon);
	etiquetas.push_back(vuelta_tiempo);

	// etiquetas de numeros de 7 segmentos;
	crear_etiquetas7segmentos(vulkan, layout);

	// etiquetas de los puntos de las pistas
	for (int i = 0; i < coches.size(); i++) {
		//CAEtiqueta_Abstracta* etiqueta = new CAEtiqueta(glm::vec2(0.6375f, -0.65f), glm::vec2(0.65f, -0.6375f));
		CAEtiqueta_Abstracta* etiqueta = new CAEtiqueta(glm::vec2(-0.015f, -0.015f), glm::vec2(0.015f, 0.015f));
		if(i==0) etiqueta->setTexture(textures[30]);
		else etiqueta->setTexture(textures[31]);
		etiqueta->initialize(vulkan, layout);
		etiquetas.push_back(etiqueta);
	}

	// etiqueta de control de velocidad
	CAEtiqueta_Abstracta* etiquetaVelocidad = new CAEtiqueta(glm::vec2(0.54, 0.5), glm::vec2(0.99, 0.95));
	etiquetaVelocidad->setTexture(textures[33]);
	etiquetaVelocidad->initialize(vulkan, layout);
	etiquetas.push_back(etiquetaVelocidad);

	crear_etiquetasVelocidad(vulkan, layout);

}


// FUNCIÓN: CAScene::~CAScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CAScene::~CAScene()
{
	int count = (int) figures.size();
	for(int i=0; i<count; i++) delete figures[i];
	delete circuito;
	for (int i = 0; i < coches.size(); i++) delete coches[i];
	for (int i = 0; i < etiquetas.size(); i++) delete etiquetas[i];
}

// FUNCIÓN: CAScene::finalize(CAVulkanState* vulkan)
//
// PROPÓSITO: Destruye los buffers de las figuras que forman la escena
//
void CAScene::finalize(CAVulkanState* vulkan)
{
	int count = (int)figures.size();
	for (int i = 0; i < count; i++) figures[i]->finalize(vulkan);
	int num = textures.size();
	for (int i = 0; i < num; i++) vulkan->destroyTexture(textures[i]);
	circuito->finalize(vulkan);
	for (int i = 0; i < coches.size(); i++) coches[i]->finalize(vulkan);
	for (int i = 0; i < etiquetas.size(); i++) etiquetas[i]->finalize(vulkan);
	
}


// FUNCIÓN: CAScene::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAScene::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
{
	int count = (int)figures.size();
	for (int i = 0; i < count; i++)  figures[i]->addCommands(layout, commandBuffer, index);
	circuito->addCommands(layout, commandBuffer, index);
	for (int i = 0; i < coches.size(); i++) coches[i]->addCommands(layout, commandBuffer, index);
	for (int i = 0; i < etiquetas.size(); i++) etiquetas[i]->addCommands(layout, commandBuffer, index);
}


//
// FUNCIÓN: CAScene::update(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection, std::vector<bool> mostrar)
// 
// PROPÓSITO: Actualiza los datos para dibujar la escena
//
void CAScene::update(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection, std::vector<bool> mostrar)
{

	int count = (int)figures.size();
	for (int i = 0; i < count; i++)  figures[i]->updateUniformBuffers(vulkan, view, projection);
	circuito->updateUniformBuffers(vulkan, view, projection);
	for (int i = 0; i < coches.size(); i++) coches[i]->updateUniformBuffers(vulkan, view, projection);
	for (int i = 0; i < etiquetas.size(); i++) etiquetas[i]->updateUniformBuffers(vulkan, mostrar[i]);
}


//  FUNCIÓN: CAScene::actualizaCoche(CAObject* &coche)
//
//  PROPÓSITO: Actualizar la posición de un coche en el circuito en función de su estado actual 
//
void CAScene::actualizaCoche(CAObject* &coche)
{
	glm::mat4 t = circuito->devolverLocCoche(coche);
	coche->SetLocation(t);
	coche->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	coche->Rotate(-180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}


// FUNCIÓN: CAScene::crearTexturas(CAVulkanState* vulkan)
//
// PROPÓSITO: Crear todas las texturas de la escena
//
void CAScene::crearTexturas(CAVulkanState* vulkan)
{
	textures.resize(34);

	vulkan->createTexture("textures/entorno/Recta_1.png", &textures[0]);
	vulkan->createTexture("textures/entorno/Recta_2.png", &textures[1]);
	vulkan->createTexture("textures/entorno/Recta_3.png", &textures[2]);
	vulkan->createTexture("textures/entorno/Cambio_Carril.png", &textures[3]);
	vulkan->createTexture("textures/entorno/Curva1.png", &textures[4]);
	vulkan->createTexture("textures/entorno/Curva3.png", &textures[5]);
	vulkan->createTexture("textures/entorno/Curva5.png", &textures[6]);
	vulkan->createTexture("textures/entorno/Curva2.png", &textures[7]);
	vulkan->createTexture("textures/entorno/Curva4.png", &textures[8]);
	vulkan->createTexture("textures/entorno/Curva6.png", &textures[9]);
	vulkan->createTexture("textures/entorno/Curva7.png", &textures[10]);
	vulkan->createTexture("textures/entorno/Curva8.png", &textures[11]);
	vulkan->createTexture("textures/entorno/wood.jpg", &textures[12]);
	vulkan->createTexture("textures/entorno/Salida_Pista.png", &textures[13]);
	vulkan->createTexture("textures/entorno/PeticionCambioCarril.png", &textures[14]);

	if (circuito->getNombre() == "CACircuito_1")
		vulkan->createTexture("textures/entorno/Circuito_1.png", &textures[15]);
	else if (circuito->getNombre() == "CACircuito_2")
		vulkan->createTexture("textures/entorno/Circuito_2.png", &textures[15]);
	else if (circuito->getNombre() == "CACircuito_3")
		vulkan->createTexture("textures/entorno/Circuito_3.png", &textures[15]);
	else if (circuito->getNombre() == "CACircuito_380")
		vulkan->createTexture("textures/entorno/Circuito_380.png", &textures[15]);
	else if (circuito->getNombre() == "CACircuito_946")
		vulkan->createTexture("textures/entorno/Circuito_946.png", &textures[15]);
	else if (circuito->getNombre() == "CACircuito_jerez")
		vulkan->createTexture("textures/entorno/Circuito_jerez.png", &textures[15]);
	else if (circuito->getNombre() == "CACircuito_4")
		vulkan->createTexture("textures/entorno/Circuito_4.png", &textures[15]);
	else if (circuito->getNombre() == "CACircuito_293")
		vulkan->createTexture("textures/entorno/Circuito_293.png", &textures[15]);
	vulkan->createTexture("textures/entorno/Choque.png", &textures[16]);
	vulkan->createTexture("textures/entorno/Final.png", &textures[17]);
	vulkan->createTexture("textures/entorno/Campeon.png", &textures[18]);
	vulkan->createTexture("textures/entorno/Time_LAP2.png", &textures[19]);
	vulkan->createTexture("textures/entorno/etiqueta_0.png", &textures[20]);
	vulkan->createTexture("textures/entorno/etiqueta_1.png", &textures[21]);
	vulkan->createTexture("textures/entorno/etiqueta_2.png", &textures[22]);
	vulkan->createTexture("textures/entorno/etiqueta_3.png", &textures[23]);
	vulkan->createTexture("textures/entorno/etiqueta_4.png", &textures[24]);
	vulkan->createTexture("textures/entorno/etiqueta_5.png", &textures[25]);
	vulkan->createTexture("textures/entorno/etiqueta_6.png", &textures[26]);
	vulkan->createTexture("textures/entorno/etiqueta_7.png", &textures[27]);
	vulkan->createTexture("textures/entorno/etiqueta_8.png", &textures[28]);
	vulkan->createTexture("textures/entorno/etiqueta_9.png", &textures[29]);

	vulkan->createTexture("textures/entorno/punto_principal.png", &textures[30]);
	vulkan->createTexture("textures/entorno/punto_auxiliar.png", &textures[31]);

	vulkan->createTexture("textures/entorno/Finish_F.png", &textures[32]);

	vulkan->createTexture("textures/entorno/etiqueta_velocidad.png", &textures[33]);
}


// FUNCIÓN: CAScene::crear_etiquetas7segmentos(CAVulkanState* vulkan, VkDescriptorSetLayout layout)	
//
// PROPÓSITO: Crear las etiquetas correspondientes a los digitos de la etiqueta número de vueltas y cronómetro
//
void CAScene::crear_etiquetas7segmentos(CAVulkanState* vulkan, VkDescriptorSetLayout layout) 
{
	CAEtiqueta_Abstracta* etiqueta_00;  CAEtiqueta_Abstracta* etiqueta_01; CAEtiqueta_Abstracta* etiqueta_02;  CAEtiqueta_Abstracta* etiqueta_03;  CAEtiqueta_Abstracta* etiqueta_04;  CAEtiqueta_Abstracta* etiqueta_05;  CAEtiqueta_Abstracta* etiqueta_06;  CAEtiqueta_Abstracta* etiqueta_07;  CAEtiqueta_Abstracta* etiqueta_08;  CAEtiqueta_Abstracta* etiqueta_09;
	CAEtiqueta_Abstracta* etiqueta_10;  CAEtiqueta_Abstracta* etiqueta_11;  CAEtiqueta_Abstracta* etiqueta_12;  CAEtiqueta_Abstracta* etiqueta_13;  CAEtiqueta_Abstracta* etiqueta_14;  CAEtiqueta_Abstracta* etiqueta_15;  CAEtiqueta_Abstracta* etiqueta_16;  CAEtiqueta_Abstracta* etiqueta_17;  CAEtiqueta_Abstracta* etiqueta_18;  CAEtiqueta_Abstracta* etiqueta_19;

	etiqueta_00 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_00->setTexture(textures[20]);
	etiqueta_00->initialize(vulkan, layout);

	etiqueta_01 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_01->setTexture(textures[21]);
	etiqueta_01->initialize(vulkan, layout);

	etiqueta_02 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_02->setTexture(textures[22]);
	etiqueta_02->initialize(vulkan, layout);

	etiqueta_03 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_03->setTexture(textures[23]);
	etiqueta_03->initialize(vulkan, layout);

	etiqueta_04 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_04->setTexture(textures[24]);
	etiqueta_04->initialize(vulkan, layout);

	etiqueta_05 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_05->setTexture(textures[25]);
	etiqueta_05->initialize(vulkan, layout);

	etiqueta_06 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_06->setTexture(textures[26]);
	etiqueta_06->initialize(vulkan, layout);

	etiqueta_07 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_07->setTexture(textures[27]);
	etiqueta_07->initialize(vulkan, layout);

	etiqueta_08 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_08->setTexture(textures[28]);
	etiqueta_08->initialize(vulkan, layout);

	etiqueta_09 = new CAEtiqueta(glm::vec2(-0.725, -0.90), glm::vec2(-0.645, -0.75));
	etiqueta_09->setTexture(textures[29]);
	etiqueta_09->initialize(vulkan, layout);


	etiqueta_10 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_10->setTexture(textures[20]);
	etiqueta_10->initialize(vulkan, layout);

	etiqueta_11 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_11->setTexture(textures[21]);
	etiqueta_11->initialize(vulkan, layout);

	etiqueta_12 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_12->setTexture(textures[22]);
	etiqueta_12->initialize(vulkan, layout);

	etiqueta_13 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_13->setTexture(textures[23]);
	etiqueta_13->initialize(vulkan, layout);

	etiqueta_14 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_14->setTexture(textures[24]);
	etiqueta_14->initialize(vulkan, layout);

	etiqueta_15 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_15->setTexture(textures[25]);
	etiqueta_15->initialize(vulkan, layout);

	etiqueta_16 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_16->setTexture(textures[26]);
	etiqueta_16->initialize(vulkan, layout);

	etiqueta_17 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_17->setTexture(textures[27]);
	etiqueta_17->initialize(vulkan, layout);

	etiqueta_18 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_18->setTexture(textures[28]);
	etiqueta_18->initialize(vulkan, layout);

	etiqueta_19 = new CAEtiqueta(glm::vec2(-0.625, -0.90), glm::vec2(-0.545, -0.75));
	etiqueta_19->setTexture(textures[29]);
	etiqueta_19->initialize(vulkan, layout);


	CAEtiqueta_Abstracta* etiqueta_m00; CAEtiqueta_Abstracta* etiqueta_m01; CAEtiqueta_Abstracta* etiqueta_m02; CAEtiqueta_Abstracta* etiqueta_m03; CAEtiqueta_Abstracta* etiqueta_m04; CAEtiqueta_Abstracta* etiqueta_m05; CAEtiqueta_Abstracta* etiqueta_m06; CAEtiqueta_Abstracta* etiqueta_m07; CAEtiqueta_Abstracta* etiqueta_m08; CAEtiqueta_Abstracta* etiqueta_m09;
	CAEtiqueta_Abstracta* etiqueta_m10; CAEtiqueta_Abstracta* etiqueta_m11; CAEtiqueta_Abstracta* etiqueta_m12; CAEtiqueta_Abstracta* etiqueta_m13; CAEtiqueta_Abstracta* etiqueta_m14; CAEtiqueta_Abstracta* etiqueta_m15; CAEtiqueta_Abstracta* etiqueta_m16; CAEtiqueta_Abstracta* etiqueta_m17; CAEtiqueta_Abstracta* etiqueta_m18; CAEtiqueta_Abstracta* etiqueta_m19;
	CAEtiqueta_Abstracta* etiqueta_s00; CAEtiqueta_Abstracta* etiqueta_s01; CAEtiqueta_Abstracta* etiqueta_s02; CAEtiqueta_Abstracta* etiqueta_s03; CAEtiqueta_Abstracta* etiqueta_s04; CAEtiqueta_Abstracta* etiqueta_s05; CAEtiqueta_Abstracta* etiqueta_s06; CAEtiqueta_Abstracta* etiqueta_s07; CAEtiqueta_Abstracta* etiqueta_s08; CAEtiqueta_Abstracta* etiqueta_s09;
	CAEtiqueta_Abstracta* etiqueta_s10; CAEtiqueta_Abstracta* etiqueta_s11; CAEtiqueta_Abstracta* etiqueta_s12; CAEtiqueta_Abstracta* etiqueta_s13; CAEtiqueta_Abstracta* etiqueta_s14; CAEtiqueta_Abstracta* etiqueta_s15; CAEtiqueta_Abstracta* etiqueta_s16; CAEtiqueta_Abstracta* etiqueta_s17; CAEtiqueta_Abstracta* etiqueta_s18; CAEtiqueta_Abstracta* etiqueta_s19;


	etiqueta_m00 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m00->setTexture(textures[20]);
	etiqueta_m00->initialize(vulkan, layout);

	etiqueta_m01 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m01->setTexture(textures[21]);
	etiqueta_m01->initialize(vulkan, layout);

	etiqueta_m02 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m02->setTexture(textures[22]);
	etiqueta_m02->initialize(vulkan, layout);

	etiqueta_m03 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m03->setTexture(textures[23]);
	etiqueta_m03->initialize(vulkan, layout);

	etiqueta_m04 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m04->setTexture(textures[24]);
	etiqueta_m04->initialize(vulkan, layout);

	etiqueta_m05 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m05->setTexture(textures[25]);
	etiqueta_m05->initialize(vulkan, layout);

	etiqueta_m06 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m06->setTexture(textures[26]);
	etiqueta_m06->initialize(vulkan, layout);

	etiqueta_m07 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m07->setTexture(textures[27]);
	etiqueta_m07->initialize(vulkan, layout);

	etiqueta_m08 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m08->setTexture(textures[28]);
	etiqueta_m08->initialize(vulkan, layout);

	etiqueta_m09 = new CAEtiqueta(glm::vec2(-0.725, -0.715), glm::vec2(-0.645, -0.55));
	etiqueta_m09->setTexture(textures[29]);
	etiqueta_m09->initialize(vulkan, layout);


	etiqueta_m10 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m10->setTexture(textures[20]);
	etiqueta_m10->initialize(vulkan, layout);

	etiqueta_m11 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m11->setTexture(textures[21]);
	etiqueta_m11->initialize(vulkan, layout);

	etiqueta_m12 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m12->setTexture(textures[22]);
	etiqueta_m12->initialize(vulkan, layout);

	etiqueta_m13 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m13->setTexture(textures[23]);
	etiqueta_m13->initialize(vulkan, layout);

	etiqueta_m14 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m14->setTexture(textures[24]);
	etiqueta_m14->initialize(vulkan, layout);

	etiqueta_m15 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m15->setTexture(textures[25]);
	etiqueta_m15->initialize(vulkan, layout);

	etiqueta_m16 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m16->setTexture(textures[26]);
	etiqueta_m16->initialize(vulkan, layout);

	etiqueta_m17 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m17->setTexture(textures[27]);
	etiqueta_m17->initialize(vulkan, layout);

	etiqueta_m18 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m18->setTexture(textures[28]);
	etiqueta_m18->initialize(vulkan, layout);

	etiqueta_m19 = new CAEtiqueta(glm::vec2(-0.625, -0.715), glm::vec2(-0.545, -0.55));
	etiqueta_m19->setTexture(textures[29]);
	etiqueta_m19->initialize(vulkan, layout);


	etiqueta_s00 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s00->setTexture(textures[20]);
	etiqueta_s00->initialize(vulkan, layout);

	etiqueta_s01 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s01->setTexture(textures[21]);
	etiqueta_s01->initialize(vulkan, layout);

	etiqueta_s02 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s02->setTexture(textures[22]);
	etiqueta_s02->initialize(vulkan, layout);

	etiqueta_s03 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s03->setTexture(textures[23]);
	etiqueta_s03->initialize(vulkan, layout);

	etiqueta_s04 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s04->setTexture(textures[24]);
	etiqueta_s04->initialize(vulkan, layout);

	etiqueta_s05 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s05->setTexture(textures[25]);
	etiqueta_s05->initialize(vulkan, layout);

	etiqueta_s06 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s06->setTexture(textures[26]);
	etiqueta_s06->initialize(vulkan, layout);

	etiqueta_s07 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s07->setTexture(textures[27]);
	etiqueta_s07->initialize(vulkan, layout);

	etiqueta_s08 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s08->setTexture(textures[28]);
	etiqueta_s08->initialize(vulkan, layout);

	etiqueta_s09 = new CAEtiqueta(glm::vec2(-0.5, -0.715), glm::vec2(-0.42, -0.55));
	etiqueta_s09->setTexture(textures[29]);
	etiqueta_s09->initialize(vulkan, layout);


	etiqueta_s10 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s10->setTexture(textures[20]);
	etiqueta_s10->initialize(vulkan, layout);

	etiqueta_s11 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s11->setTexture(textures[21]);
	etiqueta_s11->initialize(vulkan, layout);

	etiqueta_s12 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s12->setTexture(textures[22]);
	etiqueta_s12->initialize(vulkan, layout);

	etiqueta_s13 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s13->setTexture(textures[23]);
	etiqueta_s13->initialize(vulkan, layout);

	etiqueta_s14 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s14->setTexture(textures[24]);
	etiqueta_s14->initialize(vulkan, layout);

	etiqueta_s15 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s15->setTexture(textures[25]);
	etiqueta_s15->initialize(vulkan, layout);

	etiqueta_s16 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s16->setTexture(textures[26]);
	etiqueta_s16->initialize(vulkan, layout);

	etiqueta_s17 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s17->setTexture(textures[27]);
	etiqueta_s17->initialize(vulkan, layout);

	etiqueta_s18 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s18->setTexture(textures[28]);
	etiqueta_s18->initialize(vulkan, layout);

	etiqueta_s19 = new CAEtiqueta(glm::vec2(-0.4, -0.715), glm::vec2(-0.32, -0.55));
	etiqueta_s19->setTexture(textures[29]);
	etiqueta_s19->initialize(vulkan, layout);

	etiquetas.push_back(etiqueta_00);
	etiquetas.push_back(etiqueta_01);
	etiquetas.push_back(etiqueta_02);
	etiquetas.push_back(etiqueta_03);
	etiquetas.push_back(etiqueta_04);
	etiquetas.push_back(etiqueta_05);
	etiquetas.push_back(etiqueta_06);
	etiquetas.push_back(etiqueta_07);
	etiquetas.push_back(etiqueta_08);
	etiquetas.push_back(etiqueta_09);
	etiquetas.push_back(etiqueta_10);
	etiquetas.push_back(etiqueta_11);
	etiquetas.push_back(etiqueta_12);
	etiquetas.push_back(etiqueta_13);
	etiquetas.push_back(etiqueta_14);
	etiquetas.push_back(etiqueta_15);
	etiquetas.push_back(etiqueta_16);
	etiquetas.push_back(etiqueta_17);
	etiquetas.push_back(etiqueta_18);
	etiquetas.push_back(etiqueta_19);
	etiquetas.push_back(etiqueta_m00);
	etiquetas.push_back(etiqueta_m01);
	etiquetas.push_back(etiqueta_m02);
	etiquetas.push_back(etiqueta_m03);
	etiquetas.push_back(etiqueta_m04);
	etiquetas.push_back(etiqueta_m05);
	etiquetas.push_back(etiqueta_m06);
	etiquetas.push_back(etiqueta_m07);
	etiquetas.push_back(etiqueta_m08);
	etiquetas.push_back(etiqueta_m09);
	etiquetas.push_back(etiqueta_m10);
	etiquetas.push_back(etiqueta_m11);
	etiquetas.push_back(etiqueta_m12);
	etiquetas.push_back(etiqueta_m13);
	etiquetas.push_back(etiqueta_m14);
	etiquetas.push_back(etiqueta_m15);
	etiquetas.push_back(etiqueta_m16);
	etiquetas.push_back(etiqueta_m17);
	etiquetas.push_back(etiqueta_m18);
	etiquetas.push_back(etiqueta_m19);
	etiquetas.push_back(etiqueta_s00);
	etiquetas.push_back(etiqueta_s01);
	etiquetas.push_back(etiqueta_s02);
	etiquetas.push_back(etiqueta_s03);
	etiquetas.push_back(etiqueta_s04);
	etiquetas.push_back(etiqueta_s05);
	etiquetas.push_back(etiqueta_s06);
	etiquetas.push_back(etiqueta_s07);
	etiquetas.push_back(etiqueta_s08);
	etiquetas.push_back(etiqueta_s09);
	etiquetas.push_back(etiqueta_s10);
	etiquetas.push_back(etiqueta_s11);
	etiquetas.push_back(etiqueta_s12);
	etiquetas.push_back(etiqueta_s13);
	etiquetas.push_back(etiqueta_s14);
	etiquetas.push_back(etiqueta_s15);
	etiquetas.push_back(etiqueta_s16);
	etiquetas.push_back(etiqueta_s17);
	etiquetas.push_back(etiqueta_s18);
	etiquetas.push_back(etiqueta_s19);
}


// FUNCIÓN: CAScene::crear_etiquetasVelocidad(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
//
// PROPÓSITO: Crear las etiquetas que representan los digitos de la velocidad
//
void CAScene::crear_etiquetasVelocidad(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
{
	CAEtiqueta_Abstracta* etiqueta_00 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_00->setTexture(textures[20]);
	etiqueta_00->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_01 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_01->setTexture(textures[21]);
	etiqueta_01->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_02 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_02->setTexture(textures[22]);
	etiqueta_02->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_03 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_03->setTexture(textures[23]);
	etiqueta_03->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_04 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_04->setTexture(textures[24]);
	etiqueta_04->initialize(vulkan, layout);
	
	CAEtiqueta_Abstracta* etiqueta_05 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_05->setTexture(textures[25]);
	etiqueta_05->initialize(vulkan, layout);
    
	CAEtiqueta_Abstracta* etiqueta_06 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_06->setTexture(textures[26]);
	etiqueta_06->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_07 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_07->setTexture(textures[27]);
	etiqueta_07->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_08 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_08->setTexture(textures[28]);
	etiqueta_08->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_09 = new CAEtiqueta(glm::vec2(0.865, 0.75), glm::vec2(0.945, 0.9));
	etiqueta_09->setTexture(textures[29]);
	etiqueta_09->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_10 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_10->setTexture(textures[20]);
	etiqueta_10->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_11 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_11->setTexture(textures[21]);
	etiqueta_11->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_12 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_12->setTexture(textures[22]);
	etiqueta_12->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_13 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_13->setTexture(textures[23]);
	etiqueta_13->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_14 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_14->setTexture(textures[24]);
	etiqueta_14->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_15 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_15->setTexture(textures[25]);
	etiqueta_15->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_16 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_16->setTexture(textures[26]);
	etiqueta_16->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_17 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_17->setTexture(textures[27]);
	etiqueta_17->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_18 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_18->setTexture(textures[28]);
	etiqueta_18->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_19 = new CAEtiqueta(glm::vec2(0.765, 0.75), glm::vec2(0.845, 0.9));
	etiqueta_19->setTexture(textures[29]);
	etiqueta_19->initialize(vulkan, layout);


	
	CAEtiqueta_Abstracta* etiqueta_20 = new CAEtiqueta(glm::vec2(0.625, 0.75), glm::vec2(0.705, 0.9));
	etiqueta_20->setTexture(textures[20]);
	etiqueta_20->initialize(vulkan, layout);

	CAEtiqueta_Abstracta* etiqueta_21 = new CAEtiqueta(glm::vec2(0.625, 0.75), glm::vec2(0.705, 0.9));
	etiqueta_21->setTexture(textures[21]);
	etiqueta_21->initialize(vulkan, layout);

	etiquetas.push_back(etiqueta_00);
	etiquetas.push_back(etiqueta_01);
	etiquetas.push_back(etiqueta_02);
	etiquetas.push_back(etiqueta_03);
	etiquetas.push_back(etiqueta_04);
	etiquetas.push_back(etiqueta_05);
	etiquetas.push_back(etiqueta_06);
	etiquetas.push_back(etiqueta_07);
	etiquetas.push_back(etiqueta_08);
	etiquetas.push_back(etiqueta_09);
	etiquetas.push_back(etiqueta_10);
	etiquetas.push_back(etiqueta_11);
	etiquetas.push_back(etiqueta_12);
	etiquetas.push_back(etiqueta_13);
	etiquetas.push_back(etiqueta_14);
	etiquetas.push_back(etiqueta_15);
	etiquetas.push_back(etiqueta_16);
	etiquetas.push_back(etiqueta_17);
	etiquetas.push_back(etiqueta_18);
	etiquetas.push_back(etiqueta_19);
	etiquetas.push_back(etiqueta_20);
	etiquetas.push_back(etiqueta_21);

}
