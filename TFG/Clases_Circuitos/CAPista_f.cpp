#include "CAPista_f.h"
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/matrix_transform.hpp>


// FUNCIÓN: CAPista_f::CAPista_f(glm::vec3 ini, glm::vec3 fin)
//
// PROPÓSITO: Crear la pista final como un rectangulo entre la localizacionde la
//            penultima pista y la primer del circuito.
//
CAPista_f::CAPista_f(glm::vec3 ini, glm::vec3 fin){
	float ancho = 0.078;
	this->longitud = (fin.z - ini.z);
	if (longitud < 0) longitud *= -1.0f;
    x = (fin.x - ini.x);

	// ajustar la tectutura segun el tipo de pista
	glm::vec2 a, b, c, d;
	a.x = 146.0f / 512.0f; a.y = 1.0f;
	b.x = 369.0f / 512.0f; b.y = 1.0f;
	c.x = 146.0f / 512.0f; c.y = 0.0f;
	d.x = 369.0f / 512.0f; d.y = 0.0f;

	vertices = {
				{{ancho, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f}, b },
				{ {-ancho, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f}, a },
				{{ x+ancho, 0.0f, -longitud }, {1.0f, 0.0f, 0.0f}, d },
				{{ x-ancho, 0.0f, -longitud }, {1.0f, 0.0f, 0.0f}, c }
	};

	indices = {
		0, 2, 1,
		1,2,3

	};
}

// FUNCIÓN: CAPista_f::getCarLocation(int slot, float distancia)
//
// PROPÓSITO: Devolver la localizacion del coche en la pista.
//
glm::mat4 CAPista_f::getCarLocation(CAEstado_Coche est)
{
	glm::mat4 loc = getLocation();
	glm::vec3 t;
	float f = 0.039f;
	float ang = glm::atan(x,longitud);
	if (x < 0.0f) ang *= -1;
	if (est.slot == 0) {
		t = glm::vec3(x-f, 0.0f,  -est.distancia);
	}
	else {
		t = glm::vec3(x+f, 0.0f,  -est.distancia);
	}
	loc = glm::translate(loc, t);

	loc = glm::rotate(loc, ang, glm::vec3(0.0f, 1.0f, 0.0f));
	return loc;
}


// FUNCIÓN: CAPista_f::estaDentro(int slot, float distancia)
//
// PROPÓSITO: Comprobar si el coche esta dentro de unas de las rarunas de la pista mediante la distancia.
//
bool CAPista_f::estaDentro(CAEstado_Coche &est)
{
	if (est.distancia < longitud) return true;
	else return false;
}

// FUNCIÓN: CAPista_f::getFinalLocation()
//
// PROPÓSITO: Devolver la localizacion del coche en la pista.
//
glm::mat4 CAPista_f::getFinalLocation()
{
	glm::mat4 loc = getLocation();
	glm::vec3 t = glm::vec3(x, 0.0f, longitud);
	loc = glm::translate(loc, t);
	return loc;
}

// FUNCION: CAPista_F::getLongitud()
//
// PROPÓSITO: Devolver la longitud de la pista.
//
float CAPista_f::getLongitud(int slot)
{
	return longitud;
}

// FUNCIÓN: CAPista_f::getAngulo()
//
// PROPÓSITO: Devolver el angulo correspondiente a la pista.
//
float CAPista_f::getAngulo(CAEstado_Coche est)
{
	return 0.0f;
}


// FUNCIÓN: CAPista_f::getLocArcoFinal()
//
// PROPÓSITO: Devolver la localizacion del arco final de la pista.
//
glm::mat4 CAPista_f::getLocArcoFinal()
{
	glm::mat4 loc = getLocation();
	return loc;
}