#pragma once

#include "CAPista.h"

class CAPista_2 : public CAPista
{
protected:
	float a, b, c, ang,r_m;
	float dis_Slot1, dis_Slot2;
	glm::vec3 t;

	float angulo_objetivo = 0.0f; // angulo para la camara.
	float s = 0.0f; // radio de ranura.
public: 
	CAPista_2(float r1, float r2, float ang);
	glm::mat4 getFinalLocation();
    bool estaDentro(CAEstado_Coche &est);
    glm::mat4 getCarLocation(CAEstado_Coche est);
	float getLongitud(int slot);
	float getAngulo(CAEstado_Coche est);
	float devolverRadio(int slot);
	glm::mat4 getLocArcoFinal();
};

