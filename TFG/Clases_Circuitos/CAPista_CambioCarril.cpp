#include "CAPista_CambioCarril.h"
#include <glm/gtc/matrix_transform.hpp>


// FUNCI�N: CAPista_CambioCarril::CAPista_CambioCarril(float longitud)
//
// PROP�SITO: Crear la pistas estandar, media y cuarta recta diferenciadas por el parametro recibido.
//
CAPista_CambioCarril::CAPista_CambioCarril(float longitud)
{
	float ancho = 0.078;
	this->longitud = longitud;

	// ajustar la tectutura segun el tipo de pista
	a.x = 144.0f / 512.0f;   a.y = 0.0f;
	b.x = 144.0f / 512.0f;   b.y = 1.0f;
	c.x = 369.0f / 512.0f;   c.y = 1.0f;
	d.x = 369.0f / 512.0f;   d.y = 0.0f;

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

	 dist_Slot11 = glm::radians(angulo) * (C + f);
	 dist = abs(dist_Slot11) * 2.0f;
}

// FUNCI�N: CAPista_CambioCarril::getFinalLocation()
//
// PROP�SITO: Devolver la localizacion final de la pista para la siguiente pista.
//
glm::mat4 CAPista_CambioCarril::getFinalLocation()
{
	glm::mat4 loc = getLocation();
	glm::vec3 t = glm::vec3(0.0f, 0.0f, -longitud);
	loc = glm::translate(loc, t);
	return loc;
}

// FUNCI�N: CAPista_CambioCarril::estaDentro(int slot, float distancia)
//
// PROP�SITO: Comprobar si el coche esta dentro de unas de las rarunas de la pista mediante la distancia.
//
bool CAPista_CambioCarril::estaDentro(CAEstado_Coche &est)
{

	if (!est.peticionCambioCarril)
	{
		if (est.distancia < longitud) return true;
		else return false;
	}
	else {
		if (est.distancia < dist) return true;
		else {
			est.slot = (est.slot + 1) % 2;
			est.distancia -= (dist - longitud);
			est.peticionCambioCarril = false;
			return false;
		}
	}
}


// FUNCI�N: CAPista_CambioCarril::getCarLocation(int slot, float distancia)
//
// PROP�SITO: Devolver la localizacion del coche en la pista.
//
glm::mat4 CAPista_CambioCarril::getCarLocation(CAEstado_Coche est)
{
	glm::mat4 loc = getLocation();
	if (!est.peticionCambioCarril) {
		glm::vec3 t;
		if (est.slot == 0)
			t = glm::vec3(-f, 0.0f, -est.distancia);
		else
			t = glm::vec3(+f, 0.0f, -est.distancia);
		loc = glm::translate(loc, t);
	}
	else {
		float s = C+f;
		float AA = (float) sin(dist_Slot11 / s) * s;
		float ang;
		glm::vec3 r;
		if (est.slot == 0) {
			if (est.distancia <= dist_Slot11) {
			    ang = est.distancia / s;
				float Cos_ang = (float)cos(ang);
				float Sin_ang = (float)sin(ang);
				r = glm::vec3(C-(s * Cos_ang), 0.0f, -s * Sin_ang);
				ang = -ang;
			}
			else {
				ang = (2*dist_Slot11 - est.distancia) / s;
				float Cos_ang = (float)cos(ang);
				float Sin_ang = (float)sin(ang);
				r = glm::vec3((s * Cos_ang)-C, 0.0f, -(2.0f*AA)+(Sin_ang*s));
				ang = -ang;
			}
		}
		else {

			if (est.distancia <= dist_Slot11) {
				ang = est.distancia / s;
				float Cos_ang = (float)cos(ang);
				float Sin_ang = (float)sin(ang);
				r = glm::vec3((s * Cos_ang)-C, 0.0f, -s * Sin_ang);
			}
			else {
				ang = (2 * dist_Slot11 - est.distancia) / s;
				float Cos_ang = (float)cos(ang);
				float Sin_ang = (float)sin(ang);
				r = glm::vec3(C - (s * Cos_ang), 0.0f, -(2.0f * AA) + (Sin_ang * s));
			}
		}
		loc = glm::translate(loc, r);
		loc = glm::rotate(loc, ang, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	return loc;
}


// FUNCI�N: CAPista_CambioCarril::getLongitud()
//
// PROP�SITO: Devolver la longitud de la pista.
//
float CAPista_CambioCarril::getLongitud(int slot)
{
		return longitud;	
}


// FUNCI�N: CAPista_CambioCarril::getAngulo()
//
// PROP�SITO: Devolver el angulo objetivo correspondiente a la pista.
//
float CAPista_CambioCarril::getAngulo(CAEstado_Coche est)
{
	float angulo = 35.0f;
	if (!est.peticionCambioCarril)
		return 0.0f;
	else
		if (est.distancia <= dist_Slot11) {
			if (est.slot == 0)
				return angulo;
			else
				return -angulo;
		}
		else {
			if (est.slot == 0)
				return -angulo;
			else
				return angulo;
		}
}

// FUNCI�N: CAPista_CambioCarril::getDistancia()
//
// PROP�SITO: Devolver la diferencia entre cambiar de carril y seguir en el mismo.
//
float CAPista_CambioCarril::getDistancia()
{
	return dist - longitud;
}

// FUNCI�N: CAPista_CambioCarril::getLocArcoFinal()
//
// PROP�SITO: Devolver la localizacion del arco final de la pista.
//
glm::mat4 CAPista_CambioCarril::getLocArcoFinal()
{
	glm::mat4 loc = getLocation();
	return loc;
}