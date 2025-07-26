#include "CAPista_1.h"
#include <glm/gtc/matrix_transform.hpp>


// FUNCIÓN: CAPista_1::CAPista_1(float longitud)
//
// PROPÓSITO: Crear la pistas estandar, media y cuarta recta diferenciadas por el parametro recibido.
//
CAPista_1::CAPista_1(float longitud)
{
	float ancho = 0.078;
	this->longitud = longitud;

	// ajustar la tectutura segun el tipo de pista
	ajustaTex();

	vertices = {
		{{ +ancho, 0.0f, -longitud }, {1.0f, 0.0f, 0.0f}, c },
		{ { +ancho, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f}, d },
		{{ -ancho, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f}, a },
		{{ -ancho, 0.0f, -longitud }, {1.0f, 0.0f, 0.0f}, b }
	};

	indices = {  
		0, 2, 1,
		0,3,2
	
	};


}

// FUNCIÓN: CAPista_1::getFinalLocation()
//
// PROPÓSITO: Devolver la localizacion final de la pista para la siguiente pista.
//
glm::mat4 CAPista_1::getFinalLocation()
{
	glm::mat4 loc = getLocation();
	glm::vec3 t = glm::vec3(0.0f, 0.0f, -longitud);
	loc = glm::translate(loc, t);
	return loc;
}

// FUNCIÓN: CAPista_1::estaDentro(int slot, float distancia)
//
// PROPÓSITO: Comprobar si el coche esta dentro de unas de las rarunas de la pista mediante la distancia.
//
bool CAPista_1::estaDentro(CAEstado_Coche &est)
{
	if (est.distancia < longitud) return true;
	else return false;
}

// FUNCIÓN: CAPista_1::getCarLocation(int slot, float distancia)
//
// PROPÓSITO: Devolver la localizacion del coche en la pista.
//
glm::mat4 CAPista_1::getCarLocation(CAEstado_Coche est)
{

	glm::mat4 loc = getLocation();
	glm::vec3 t;
	float f = 0.039;
	if (est.slot == 0)
		t = glm::vec3(-f, 0.0f,  -est.distancia);
	else
		t = glm::vec3(+f, 0.0f, -est.distancia);
	loc = glm::translate(loc, t);
	return loc;
}


// FUNCIÓN: CAPista_1::getLongitud()
//
// PROPÓSITO: Devolver la longitud de la pista.
//
float CAPista_1::getLongitud(int slot)
{
	    return longitud;
}

// FUNCIÓN: CAPista_1::ajustaTex()
//
// PROPÓSITO: Ajustar la textura de la pista.
//
void CAPista_1::ajustaTex() {
		if (longitud == 0.350f) {             // recta estandar
			a.x = 144.0f / 512.0f;
			a.y = 1.0f;
			b.x = 144.0f/512.0f;
			b.y = 0.0f;
			c.x = 369.0f / 512.0f;
			c.y = 0.0f;
			d.x = 369.0f / 512.0f;
			d.y = 1.0f;
		}
		else if (longitud == 0.350f / 2.0f) { // recta media
		    a.x = 144.0f / 512.0f;
			a.y = 1.0f;
			b.x = 144.0f/512.0f;
			b.y = 256.0f / 512.0f;
			c.x = 366.0f / 512.0f;
			c.y = 256.0f / 512.0f;
			d.x = 366.0f / 512.0f;
			d.y = 1.0f;
		} 
		else {                              // recta cuarta
			a.x = 144.0f / 512.0f;
			a.y = 1.0f;
			b.x = 144.0f / 512.0f;
			b.y = 384.0f / 512.0f;
			c.x = 366.0f / 512.0f;
			c.y = 384.0f / 512.0f;
			d.x = 366.0f / 512.0f;
			d.y = 1.0f ;
		}
}

// FUNCIÓN: CAPista_1::getAngulo()
//
// PROPÓSITO: Devolver el angulo objetivo correspondiente a la pista.
//
float CAPista_1::getAngulo(CAEstado_Coche est)
{
	return 0.0f;
}

// FUNCIÓN: CAPista_1::getLocArcoFinal()
//
// PROPÓSITO: Devolver la localizacion del arco final de la pista.
//
glm::mat4 CAPista_1::getLocArcoFinal()
{
	glm::mat4 loc = getLocation();
	return loc;
}