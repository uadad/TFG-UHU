#include "CACircuito_3.h"

// CACircuito_380::CACircuito_3()
// 
// PROPÓSITO:  Definir el numero de pistas que forman el circuito y invocar a ls funcion crear_Circuito.
//
CACircuito_3::CACircuito_3()
{
	nombre = "CACircuito_3";
	num_pistas = 30;    
	pistas.resize(num_pistas);
	crear_Circuito();

	// 4 pistas de recta estandar
	// 2 pistas de recta media
	// 16 pistas de curva izquierda estandar
	// 8 pistas de curva derecha estandar
}

// FUNCIÓN: CACircuito_3::crear_Circuito()
//
// PROPÓSITO:  Crear las pistas que forman el circuito.
//
void CACircuito_3::crear_Circuito() {
	int cont = 0;
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	for (int i = 0; i < 5; i++) pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 6; i++) pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 5; i++) pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Recta_std");
}