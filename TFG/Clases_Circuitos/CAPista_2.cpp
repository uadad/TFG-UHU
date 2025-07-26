#include "CAPista_2.h"
#include <glm/gtc/matrix_transform.hpp>


// FUNCIÓN: CAPista_2::CAPista_2(float longitud)
//
// PROPÓSITO: Crear la pistas curvas interior, estandar y exterior hacia la izquierda
//            diferenciadas por los radios y los angulos recibido por parametro.
//
CAPista_2::CAPista_2(float r1, float r2, float ang)
{
	this->ang = ang;
	int num_p = 20;
	int numVertices = num_p * 2;
	int numIndices = (num_p * 2) - 2;
	vertices.resize(numVertices);
	indices.resize(numIndices * 3);
	if (ang == 22.5f) {
		if (r1 == 0.37f && r2 == 0.526f){
			a = 2.6411f; b = 0.28608f; c = 2.6446f;
		}
		else {
			a = 2.554f; b = 0.30077f; c = 2.6f;
		}
	  angulo_objetivo = -50.0f;
	}
	else {
		if (r1 == 0.058f && r2 == 0.214f) {
			a = 4.3557f; b = 0.41592f; c = 4.38f;
			angulo_objetivo = -60.0f;
		}
		else {
			a = 3.62f; b = 0.51478f; c = 3.64f;
			angulo_objetivo = -55.0f;
		}
	}
           
    r_m = (r2 + r1) / 2;

	// calculo de las distancias de cada ranura
	dis_Slot1 = glm::radians(ang) * (r_m - 0.039f);
	dis_Slot2 = glm::radians(ang) * (r_m + 0.039f);


	float alfa = 0;
	float p_ang = ang / (num_p-1);
	int verticesIndex = 0;
	float f = 0.039f;
	for (int i = 0; i < num_p; i++) {

		float Cos_alfa = (float)cos(glm::radians(alfa));
		float Sin_alfa = (float)sin(glm::radians(alfa));

		glm::vec3 p1 = { (r1 * Cos_alfa) - r_m, 0.0f, -(r1 * Sin_alfa) };
		float tx1 = a * p1.x + b;
		float ty1 = c * p1.z;
		vertices[verticesIndex] = { p1, {0.0f,1.0f,0.0f}, {tx1,ty1} };
		verticesIndex++;

		glm::vec3 p2 = { (r2 * Cos_alfa) - r_m, 0.0f, -(r2 * Sin_alfa) };
		tx1 = a * p2.x + b;
		ty1 = c * p2.z;
		vertices[verticesIndex] = { p2, {0.0f,1.0f,0.0f}, {tx1,ty1} };
		verticesIndex++;

		alfa += p_ang;
	}

	float Cos_ang = (float)cos(glm::radians(ang));
	float Sin_ang = (float)sin(glm::radians(ang));
	t = glm::vec3(r_m * (1.0f - Cos_ang), 0.0f, -r_m * Sin_ang);



	int indicesIndex = 0;
	for (int i = 0; i < numIndices; i += 2)
	{
		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 1;
		indices[indicesIndex + 2] = i + 3;
		indicesIndex += 3;

		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 3;
		indices[indicesIndex + 2] = i + 2;
		indicesIndex += 3;
	}

}

// FUNCIÓN: CAPista_2::getFinalLocation()
//
// PROPÓSITO: Devolver la localizacion final de la pista para la siguiente pista.
//
glm::mat4 CAPista_2::getFinalLocation()
{
	glm::mat4 loc = getLocation();
	loc= glm::rotate(loc, glm::radians(ang), glm::vec3(0.0f, 1.0f, 0.0f));
	loc = glm::translate(loc, t);
	return loc;
}

// FUNCIÓN: CAPista_2::estaDentro(int slot, float distancia)
//
// PROPÓSITO: Comprobar si el coche esta dentro de unas de las rarunas de la pista mediante la distancia.
//
bool CAPista_2::estaDentro(CAEstado_Coche &est)
{
	float f;
	if (est.slot == 0)
		f = dis_Slot1;
	else
		f = dis_Slot2;
	
	if (f > est.distancia)
		return true;
	return false;
}

// FUNCIÓN: CAPista_2::getCarLocation(int slot, float distancia)
//
// PROPÓSITO: Devolver la localizacion del coche segun la distancia.
//
glm::mat4 CAPista_2::getCarLocation(CAEstado_Coche est)
{
	glm::mat4 loc = getLocation();
	s = 0.0f;
	float f = 0.039f;
	if (est.slot == 0)  s = r_m - f;
	else s = r_m + f;
		
	float angulo = est.distancia / s;
	float Cos_ang = (float)cos(angulo);
	float Sin_ang = (float)sin(angulo);

	glm::vec3 r = glm::vec3((s * Cos_ang) - r_m, 0.0f, -(s * Sin_ang));
	loc = glm::translate(loc, r);

	loc = glm::rotate(loc, angulo, glm::vec3(0.0f, 1.0f, 0.0f));

	return loc;
}


// FUNCIÓN: CAPista_2::getLongitud(int slot)
//
// PROPÓSITO: Devolver la longitud de la pista según la ranura.
//
float CAPista_2::getLongitud(int slot)
{
	if (slot == 0)
		return dis_Slot1;
	else
		return dis_Slot2;
}

// FUNCIÓN: CAPista_2::getAngulo()
//
// PROPÓSITO: Devolver el angulo correspondiente a la pista.
//
float CAPista_2::getAngulo(CAEstado_Coche est)
{
	return angulo_objetivo;
}

// FUNCIÓN: float CAPista_2::devolverRadio(int slot)
//
// PROPÓSITO: devolver el radio de ranura para detecar la salida del coche.
//
float CAPista_2::devolverRadio(int slot) {
	if (slot == 0) return r_m - 0.039f;
	else return (r_m + 0.039f);
}


// FUNCIÓN: CAPista_2::getLocArcoFinal()
//
// PROPÓSITO: Devolver la localizacion del arco final de la pista.
//
glm::mat4 CAPista_2::getLocArcoFinal()
{
	glm::mat4 loc = getLocation();
	return loc;
}