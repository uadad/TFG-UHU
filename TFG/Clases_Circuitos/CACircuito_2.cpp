#include "CACircuito_2.h"

// CACircuito_2::CACircuito_2()
// 
// PROPÓSITO:  Definir el numero de pistas que forman el circuito y invocar a ls funcion crear_Circuito.
//
CACircuito_2::CACircuito_2()
{
	nombre = "CACircuito_2";
	num_pistas = 42;    
	pistas.resize(num_pistas);
	crear_Circuito();

	// 8 pistas de recta estandar
	// 2 pistas de recta media
	// 20 pistas de curva izquierda estandar
	// 12 pistas de curva derecha estandar
}

// FUNCIÓN: CACircuito_2::crear_Circuito()
//
// PROPÓSITO:  Crear las pistas que forman el circuito.
//
void CACircuito_2::crear_Circuito()
{
	int cont = 0;
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	for (int i = 0; i < 5; i++) pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 6; i++) pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 5; i++) pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Recta_std");
	for (int i = 0; i < 5; i++) pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 6; i++) pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 5; i++) pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_std");

}
