#include "CAPista_CambioCarril.h"

#include <glm/gtc/matrix_transform.hpp>


// FUNCIÓN: CAPista_CambioCarrl::CAPista_CambioCarrl(float longitud)
//
// PROPÓSITO: Crear la pistas estandar, media y cuarta recta diferenciadas por el parametro recibido.
//
CAPista_CambioCarrl::CAPista_CambioCarrl(float longitud)
{
	float ancho = 0.078;
	this->longitud = longitud;

	// ajustar la tectutura segun el tipo de pista
		a.x = 142.0f / 512.0f;     a.y = 1.0f - (500.0f / 512.0f);
		b.x = 143.0f / 512.0f;     b.y = 1.0f - (6.0f / 512.0f);
		c.x = 374.0f / 512.0f;     c.y = 1.0f - (6.0f / 512.0f);
		.x = 374.0f / 512.0f;     d.y = 1.0f - (500.0f / 512.0f);

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

// FUNCIÓN: CAPista_CambioCarrl::getFinalLocation()
//
// PROPÓSITO: Devolver la localizacion final de la pista para la siguiente pista.
//
glm::mat4 CAPista_CambioCarrl::getFinalLocation()
{
	glm::mat4 loc = getLocation();
	glm::vec3 t = glm::vec3(0.0f, 0.0f, -longitud);
	loc = glm::translate(loc, t);
	return loc;
}

// FUNCIÓN: CAPista_CambioCarrl::estaDentro(int slot, float distancia)
//
// PROPÓSITO: Comprobar si el coche esta dentro de unas de las rarunas de la pista mediante la distancia.
//
bool CAPista_CambioCarrl::estaDentro(int slot, float distancia)
{
	if (!peticionCambioCarril)
	{
		if (distancia < longitud) return true;
		else return false;
	}
	else {
		return false;
	}
}

// FUNCIÓN: CAPista_CambioCarrl::getCarLocation(int slot, float distancia)
//
// PROPÓSITO: Devolver la localizacion del coche en la pista.
//
glm::mat4 CAPista_CambioCarrl::getCarLocation(int slot, float distancia)
{

	glm::mat4 loc = getLocation();
	if (!peticionCambioCarril) {
		glm::vec3 t;
		float f = 0.039;
		if (slot == 0)
			t = glm::vec3(-f, 0.0f, -distancia);
		else
			t = glm::vec3(+f, 0.0f, -distancia);
		loc = glm::translate(loc, t);
		return loc;
	}
	else {
		return loc;
	}
}


// FUNCIÓN: CAPista_CambioCarrl::getLongitud()
//
// PROPÓSITO: Devolver la longitud de la pista.
//
float CAPista_CambioCarrl::getLongitud(int slot)
{
	if (!peticionCambioCarril)
		return longitud;
	else
		return 0.0f;
}

// FUNCIÓN: CAPista_CambioCarrl::ajustaTex()
//
// PROPÓSITO: Ajustar la textura de la pista.
//
void CAPista_CambioCarrl::ajustaTex(bool esCambioCarril) {
	if (!esCambioCarril) {
		if (longitud == 0.350f) {             // recta estandar
			a.x = 146.0f / 512.0f;
			a.y = 0.0f;
			b.x = 146.0f / 512.0f;
			b.y = 1.0f;
			c.x = 369.0f / 512.0f;
			c.y = 1.0f;
			d.x = 369.0f / 512.0f;
			d.y = 0.0f;
		}
		else if (longitud == 0.35f / 2.0f) { // recta media
			a.x = 144.0f / 512.0f;
			a.y = 1.0f - (325.0f / 512.0f);
			b.x = 144.0f / 512.0f;
			b.y = 1.0f - (186.0f / 512.0f);
			c.x = 366.0f / 512.0f;
			c.y = 1.0f - (186.0f / 512.0f);
			d.x = 366.0f / 512.0f;
			d.y = 1.0f - (325.0f / 512.0f);
		}
		else {                              // recta cuarta
			a.x = 144.0f / 512.0f;
			a.y = 1.0f - (325.0f / 512.0f);
			b.x = 144.0f / 512.0f;
			b.y = 1.0f - (186.0f / 512.0f);
			c.x = 366.0f / 512.0f;
			c.y = 1.0f - (186.0f / 512.0f);
			d.x = 366.0f / 512.0f;
			d.y = 1.0f - (325.0f / 512.0f);
		}
	}
	else {                                // cambio de carril
		a.x = 142.0f / 512.0f;
		a.y = 1.0f - (500.0f / 512.0f);
		b.x = 143.0f / 512.0f;
		b.y = 1.0f - (6.0f / 512.0f);
		c.x = 374.0f / 512.0f;
		c.y = 1.0f - (6.0f / 512.0f);
		d.x = 374.0f / 512.0f;
		d.y = 1.0f - (500.0f / 512.0f);
	}

}

// FUNCIÓN: CAPista_CambioCarrl::setPeticionCambioCarril()
//
// PROPÓSITO: Establecer la peticion de cambio de carril.
//
void CAPista_CambioCarrl::setPeticionCambioCarril(bool p)
{
	peticionCambioCarril = p;
}


// FUNCIÓN: CAPista_CambioCarrl::getAngulo()
//
// PROPÓSITO: Devolver el angulo objetivo correspondiente a la pista.
//
float CAPista_CambioCarrl::getAngulo()
{
	return 0.0f;
}
