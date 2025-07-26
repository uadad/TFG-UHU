#include "CACircuito.h"
#include "CAPista_1.h"
#include "CAPista_2.h"
#include "CAPista_3.h"
#include "CAPista_f.h"
#include "CAPista_CambioCarril.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "../Clases_coches/CAEstado_Coche.h"

//
// FUNCIÓN: CACircuito::~Circuito()
//
// PROPÓSITO: Destruye las pistas y el array que almacena el nombre.
//

CACircuito::~CACircuito()
{
	int count = pistas.size();
	for (int i = 0; i < count ; i++) delete pistas[i];
	nombre_pistas.clear();

}
//
// FUNCIÓN:  CACircuito::initialize(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
//
// PROPÓSITO: Invocar a los método para crear el vertex Buffer de cada pista de la lista pistas
//
void CACircuito::initialize(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
{
	int count = pistas.size();
	for (int i = 0; i < count; i++) pistas[i]->initialize(vulkan, layout);
}

//
// FUNCIÓN: CACircuito::finalize(CAVulkanState* vulkan)
//
// PROPÓSITO: Invocar a los método para liberar los buffers de cada pista de la lista pistas
//
void CACircuito::finalize(CAVulkanState* vulkan)
{
	int count = pistas.size();
	for (int i = 0; i < count; i++) pistas[i]->finalize(vulkan);
}

//
// FUNCIÓN: CACircuito::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CACircuito::addCommands(VkPipelineLayout layout, VkCommandBuffer commandBuffer, int index)
{
	int count = pistas.size();
	for (int i = 0; i < count; i++) pistas[i]->addCommands(layout, commandBuffer, index);
}

//
// FUNCIÓN: CACircuito::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void CACircuito::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
{
	int count = pistas.size();
	for (int i = 0; i < count; i++) pistas[i]->updateUniformBuffers(vulkan, view, projection);
}

//
// FUNCIÓN: CACircuito::crearPista(std::string nom)
//
// PROPÓSITO: crear una pista a partir de los parametros recibidos nombre y numero de pista.
//
CAPista* CACircuito::crearPista(std::string nom)
{
	float r_s = 0.350f, c_1 = 0.058f, c_2 = 0.214f, c_3 = 0.370f,
		c_4 = 0.526f, c_5 = 0.682f;
	CAPista* pista=nullptr;
	if (nom == "Recta_std")   // Recta_estandar
		pista = new CAPista_1(r_s);
	else if (nom == "Recta_media")  // Media_Recta
		pista = new CAPista_1((r_s / 2.0f));
	else if (nom == "Recta_cuarto") // Cuarto_Recta
		pista = new CAPista_1((r_s / 4.0f));
	else if (nom == "Recta_Cambio_Carril")  // Cambio_Carril
		pista = new CAPista_CambioCarril(r_s);
	else if (nom == "Curva_izq_int")  // Curva_interior_izquierda
		pista = new CAPista_2(c_1, c_2, 45.0f);
	else if (nom == "Curva_izq_std") // Curva_estandar_izquierda
		pista = new CAPista_2(c_2, c_3, 45.0f);
	else if (nom=="Curva_izq_ext") // Curva_exterior_izquierda
		pista = new CAPista_2(c_3, c_4, 22.5f);
	else if (nom == "Curva_izq_sup_ext") // Curva_superior_exterior_izquierda
		pista = new CAPista_2(c_4, c_5, 22.5f);
	else if (nom == "Curva_der_int")  // Curva_interior_der
		pista = new CAPista_3(c_1, c_2, 45.0f);
	else if (nom == "Curva_der_std")// Curva_estandar_der
		pista = new CAPista_3(c_2, c_3, 45.0f);
	else if (nom == "Curva_der_ext") // Curva_exterior_der
		pista = new CAPista_3(c_3, c_4, 22.5f);
	else if (nom == "Curva_der_sup_ext") // Curva_superior_exterior_der
		pista = new CAPista_3(c_4, c_5, 22.5f);
	else if (nom == "Pista_final") 
	    pista = new CAPista_1(r_s);

	if (pista != nullptr) pista->setNombre(nom);
	return pista;
}

//
// FUNCIÓN: CACircuito::AsignarTexturas(std::vector<CATexture> textures, CALight light, CAMaterial material)
//
// PROPÓSITO: Asigna las textureas, propiedades de la luz y el material para cada una de las pistas.
//

void CACircuito::AsignarTexturas(std::vector<CATexture> textures, CALight light, CAMaterial material) {

	int num = pistas.size();
	for (int i = 0; i < num; i++)
	{
		std::string nom = pistas[i]->getNombre();
		if (nom == "Recta_std") pistas[i]->setTexture(textures[0]);
		else if (nom == "Recta_media") pistas[i]->setTexture(textures[1]);
		else if (nom == "Recta_cuarto") pistas[i]->setTexture(textures[2]);
		else if (nom == "Recta_Cambio_Carril") pistas[i]->setTexture(textures[3]);

		else if (nom == "Curva_izq_int") pistas[i]->setTexture(textures[4]);
		else if (nom == "Curva_izq_std") pistas[i]->setTexture(textures[5]);
		else if (nom == "Curva_izq_ext") pistas[i]->setTexture(textures[6]);
		else if (nom == "Curva_izq_sup_ext") pistas[i]->setTexture(textures[10]);

		else if (nom == "Curva_der_int") pistas[i]->setTexture(textures[7]);
		else if (nom == "Curva_der_std") pistas[i]->setTexture(textures[8]);
		else if (nom == "Curva_der_ext") pistas[i]->setTexture(textures[9]);
		else if (nom == "Curva_der_sup_ext") pistas[i]->setTexture(textures[11]);
		else if (nom == "Pista_final") pistas[i]->setTexture(textures[0]);
		pistas[i]->setLight(light);
		pistas[i]->setMaterial(material);
	}
}


// FUNCIÓN: CACircuito::DefinirLoc(glm::vec3 l,CAVulkanState* vulkan, VkDescriptorSetLayout layout)
//
// PROPÓSITO: Definir las localizaciones de todas las pistas y crear la pista_final.
//
void CACircuito::DefinirLoc(glm::vec3 l,CAVulkanState* vulkan, VkDescriptorSetLayout layout) {
	pistas[0]->translate(l);
	int num_p = pistas.size();
	glm::mat4 loc;
	for (int i = 1; i < num_p; i++) {
		loc= pistas[i - 1]->getFinalLocation();
		pistas[i]->setLocation(loc);
	}
	CAPista_f* p = new CAPista_f(loc[3], l);
	p->setTexture(pistas[num_p - 1]->getTexture());
	p->initialize(vulkan, layout);
	p->setLocation(pistas[num_p - 1]->getLocation());
	p->setMaterial(pistas[num_p - 1]->getMaterial());
	p->setLight(pistas[num_p - 1]->getLight());
	pistas[num_p - 1] = p;

}

float cons = 0.04375f; // factor de translación del coche, se añade para que la localización del coche este en el eje delantero del coche en vez del centro.

// FUNCIÓN: CACircuito::devolverLocCoche(CAObject* &coche)
//
// PROPÓSITO: Devolver la localizacion del coche segun la información del estado actual (distancia recorrida y la pista en la que se encuentra..etc)
//
glm::mat4 CACircuito::devolverLocCoche(CAObject* &coche) {

	CAEstado_Coche est = coche->GetEstado();
	int num_p = pistas.size();

	glm::mat4 loc;
	if (pistas[est.pistaAct]->estaDentro(est)) {
		loc = pistas[est.pistaAct]->getCarLocation(est);
	}
	else {
		est.distancia -= pistas[est.pistaAct]->getLongitud(est.slot);
		est.pistaAct++;
		if (est.pistaAct == num_p) est.pistaAct = 0;
		if (est.pistaAct == est.pistaIni) est.numVueltas++;
		while (!pistas[est.pistaAct]->estaDentro(est)) {
			est.distancia -= pistas[est.pistaAct]->getLongitud(est.slot);
			est.pistaAct++;
			if (est.pistaAct == num_p) est.pistaAct = 0;
			if (est.pistaAct == est.pistaIni) est.numVueltas++;
		}
		coche->SetEstado(est);
		loc = pistas[est.pistaAct]->getCarLocation(est);
	}
	loc = glm::translate(loc, glm::vec3(0.0f, 0.0f, +cons)); // añadir el factor de translación para que la localización del coche este en el eje delantero del coche en vez del centro.
	return loc;

}

// FUNCIÓN: CACircuito::devolverAngulo(CAObject* &coche)
//
// PROPÓSITO: Devolver el angulo según el estado actual del coche para la posición de la cámara.
//
float CACircuito::devolverAngulo(CAObject* &coche)
{
	CAEstado_Coche est = coche->GetEstado();
	int num_p = pistas.size();

	glm::mat4 loc;
	if (pistas[est.pistaAct]->estaDentro(est)) {
		return pistas[est.pistaAct]->getAngulo(est);
	}
	else {
		est.distancia -= pistas[est.pistaAct]->getLongitud(est.slot);
		est.pistaAct++;
		if (est.pistaAct == num_p) est.pistaAct = 0;
		if (est.pistaAct == est.pistaIni) est.numVueltas++;
		while (!pistas[est.pistaAct]->estaDentro(est)) {
			est.distancia -= pistas[est.pistaAct]->getLongitud(est.slot);
			est.pistaAct++;
			if (est.pistaAct == num_p) est.pistaAct = 0;
			if (est.pistaAct == est.pistaIni) est.numVueltas++;
		}
		coche->SetEstado(est);
		return pistas[est.pistaAct]->getAngulo(est);
	}
}

// FUNCIÓN: CACircuito::devolverRadio(CAObject* &coche)
//
// PROPÓSITO: Devolver el radio de la pista en la que se encuentra el coche.
//
float CACircuito::devolverRadio(CAObject* &coche) {
	CAEstado_Coche est = coche->GetEstado();
	int num_p = pistas.size();

	glm::mat4 loc;
	if (!pistas[est.pistaAct]->estaDentro(est)) {
		est.distancia -= pistas[est.pistaAct]->getLongitud(est.slot);
		est.pistaAct++;
		if (est.pistaAct == num_p) est.pistaAct = 0;
		if (est.pistaAct == est.pistaIni) est.numVueltas++;
		while (!pistas[est.pistaAct]->estaDentro(est)) {
			est.distancia -= pistas[est.pistaAct]->getLongitud(est.slot);
			est.pistaAct++;
			if (est.pistaAct == num_p) est.pistaAct = 0;
			if (est.pistaAct == est.pistaIni) est.numVueltas++;
		}
		coche->SetEstado(est);
	}

	if(pistas[est.pistaAct]->getNombre()=="Curva_izq_std" || pistas[est.pistaAct]->getNombre() == "Curva_izq_int" || pistas[est.pistaAct]->getNombre() == "Curva_izq_ext" || pistas[est.pistaAct]->getNombre() == "Curva_izq_sup_ext") {
		return ((CAPista_2*)pistas[est.pistaAct])->devolverRadio(est.slot);
	}
	else if (pistas[est.pistaAct]->getNombre() == "Curva_der_std" || pistas[est.pistaAct]->getNombre() == "Curva_der_int" || pistas[est.pistaAct]->getNombre() == "Curva_der_ext" || pistas[est.pistaAct]->getNombre() == "Curva_der_sup_ext") {
		return ((CAPista_3*)pistas[est.pistaAct])->devolverRadio(est.slot);
	}
	else {
		return 0.0f;
	}
}

// FUNCIÓN: CACircuito::getNumPistas()
//
// PROPÓSITO: Devolver el numero de pistas que tiene el circuito.
//
int CACircuito::getNumPistas() {
	return pistas.size();
}


// FUNCIÓN: CACircuito::getPista(int i)
//
// PROPÓSITO: Devolver la pista i-esima del circuito.
//
CAPista* CACircuito::getPista(int i) {
	return pistas[i];
}

// FUNCIÓN: CACircuito::devLocArcoFinal()
//
// PROPÓSITO: Devolver la localización del arco final de la pista.
//
glm::mat4 CACircuito::devLocArcoFinal()
{
	//return pistas[0]->getLocArcoFinal();
	return pistas[0]->getLocArcoFinal();
}