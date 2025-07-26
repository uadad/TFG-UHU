#pragma once

#include "CAPista.h"

class CAPista_f : public CAPista
{
protected:
	float longitud,x;
public:
	CAPista_f(glm::vec3 ini, glm::vec3 fin);
	bool estaDentro(CAEstado_Coche &est);
	glm::mat4 getFinalLocation();
	float getLongitud(int slot);
	float getAngulo(CAEstado_Coche est);
	glm::mat4 getCarLocation(CAEstado_Coche est);

	glm::mat4 getLocArcoFinal();
};

