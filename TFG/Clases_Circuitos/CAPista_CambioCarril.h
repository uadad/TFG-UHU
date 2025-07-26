#pragma once

#include "CAPista.h"

class CAPista_CambioCarril : public CAPista
{
protected:
	float longitud, dist, dist_Slot11;
	glm::vec2 a, b, c, d;
	bool peticionCambioCarril_s1 = false, peticionCambioCarril_s2=false, ha_pasado = false;

	float f = 0.039f, angulo = 24.41f, C = 0.386f;
public:
	CAPista_CambioCarril(float longitud);
	glm::mat4 getFinalLocation();
	bool estaDentro(CAEstado_Coche &est);
	glm::mat4 getCarLocation(CAEstado_Coche est);
	float getLongitud(int slot);
	float getAngulo(CAEstado_Coche est);

	int n_veces = 0;
	float getDistancia();

	glm::mat4 getLocArcoFinal();

};

