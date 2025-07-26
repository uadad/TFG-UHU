#pragma once

#include "stdbool.h"

typedef struct {
	int slot;   // la ranura en la que se encuentra el coche
	int id;     // identificador del coche
	float distancia;  // distancia recorrida en la pista actual
	int pistaIni;    // pista en la que se encuentra el coche inicialmente.
	int pistaAct;    // pista en la que se encuentra el coche actualmente.
	float velocidad; // velocidad del coche
	bool peticionCambioCarril; // indica si el coche ha solicitado un cambio de carril
	int numVueltas;    // número de vueltas completadas
	bool coche_pausado; // indica si el coche está pausado
	int coche_pausa_cont; // contador de tiempo de pausa
	bool choque_coche; // indica si el coche ha chocado
	int choque_coche_cont; // contador de tiempo de choque
	int contador_etqieuta_Num_Vuelta; // contador de tiempo de la etiqueta de número de vuelta
	bool mostrar_Gandor; // indica si el coche ha ganado
	bool mostrar_final; // indica si el coche ha llegado a la meta
} CAEstado_Coche;