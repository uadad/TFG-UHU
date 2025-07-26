#pragma once

#include "CAPista.h"

class CAPista_CambioCarril : public CAPista
{
protected:
	float longitud;
	glm::vec2 a, b, c, d;
	bool peticionCambioCarril = false;
public:
	CAPista_CambioCarril(float longitud, bool esCambioCarril);
	glm::mat4 getFinalLocation();
	bool estaDentro(int slot, float distancia);
	glm::mat4 getCarLocation(int slot, float distancia);
	float getLongitud(int slot);
	void ajustaTex(bool esCambioCarril);
	void setPeticionCambioCarril(bool p);
	float getAngulo();

};

