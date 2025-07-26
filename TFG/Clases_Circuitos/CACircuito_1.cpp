#include "CACircuito_1.h"

// FUNCIÓN: CACircuito_1::crear_Circuito()
//
// PROPÓSITO: Definir el numero de pistas que forman el circuito y invocar a ls funcion crear_Circuito.
//            
CACircuito_1::CACircuito_1()
{
	nombre = "CACircuito_1";
	num_pistas = 16;
	pistas.resize(num_pistas);
	crear_Circuito();
}

// FUNCIÓN: CACircuito_1::crear_Circuito()
//
// PROPÓSITO: Crear todas las pistas que forman el circuito llamando a la fucnion crearPista
//            de la clase Circuito padre.
//
void CACircuito_1::crear_Circuito() {
	int cont = 0;
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");	
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_std");
}


