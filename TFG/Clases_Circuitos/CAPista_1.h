#pragma once

#include "CAPista.h"

class CAPista_1 : public CAPista
{
protected:
	float longitud;
	glm::vec2 a, b, c, d;
public:
	CAPista_1(float longitud);
	glm::mat4 getFinalLocation();
    bool estaDentro(CAEstado_Coche &est);
	glm::mat4 getCarLocation(CAEstado_Coche est);
	float getLongitud(int slot);
	void ajustaTex();
	float getAngulo(CAEstado_Coche est);
	glm::mat4 getLocArcoFinal();
	
};

