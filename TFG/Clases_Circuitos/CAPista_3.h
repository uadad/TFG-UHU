#pragma once
#include "CAPista.h"
class CAPista_3 : public CAPista
{
protected:
	float a, b, c, ang, r_m;
	float dis_Slot1, dis_Slot2;
	glm::vec3 t;

	float angulo_objetivo = 0.0f; // angulo objetivo de giro de la camara según la pista del coche
	float s = 0.0f; // radio de ranura.

public:
	CAPista_3(float r1, float r2, float ang);
	glm::mat4 getFinalLocation();
	bool estaDentro(CAEstado_Coche &est);
	glm::mat4 getCarLocation(CAEstado_Coche est);
	float getLongitud(int s);
	float getAngulo(CAEstado_Coche est);
	float devolverRadio(int slot);
	glm::mat4 getLocArcoFinal();
};

