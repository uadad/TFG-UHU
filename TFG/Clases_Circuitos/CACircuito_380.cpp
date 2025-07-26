#include "CACircuito_380.h"

// CACircuito_380::CACircuito_380()
// 
// PROPÓSITO:  Definir el numero de pistas que forman el circuito y invocar a ls funcion crear_Circuito.
//
CACircuito_380::CACircuito_380()
{
	nombre = "CACircuito_380";
	num_pistas = 170;    
	pistas.resize(num_pistas);
	crear_Circuito();

	// 65 pistas de recta estandar
	// 10 pistas de recta media
	// 9 pistas de recta cuarto
	// 23 pistas de curva izquierda estandar
	// 24 pistas de curva izquierda interna
	// 25 pistas de curva derecha estandar
	// 14 pistas de curva derecha interna
}

// FUNCIÓN: CACircuito_380::crear_Circuito()
//
// PROPÓSITO:  Crear las pistas que forman el circuito.
//
void CACircuito_380::crear_Circuito() {
	int cont = 0;
	for (int i = 0; i < 6; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	pistas[cont++] = crearPista("Curva_izq_int");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Curva_der_int");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 5; i++) pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 6; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_izq_int");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Curva_izq_int");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Recta_cuarto");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Recta_cuarto");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Recta_cuarto");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_int");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 10; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Recta_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 11; i++) pistas[cont++] = crearPista("Recta_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_std");
}