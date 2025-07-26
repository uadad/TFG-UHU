#include "CACircuito_946.h"

// CACircuito_946::CACircuito_946()
// 
// PROPÓSITO:  Definir el numero de pistas que forman el circuito y invocar a ls funcion crear_Circuito.
//
CACircuito_946::CACircuito_946()
{
	nombre = "CACircuito_946";
	num_pistas = 74;    
	pistas.resize(num_pistas);
	crear_Circuito();
}

// FUNCIÓN: CACircuito_946::crear_Circuito()
//
// PROPÓSITO:  Crear las pistas que forman el circuito.
//
void CACircuito_946::crear_Circuito() {
	int cont = 0;
	for (int i = 0; i < 6; i++) pistas[cont++] = crearPista("Recta_std");
	for (int i = 0; i < 8; i++) pistas[cont++] = crearPista("Curva_izq_ext");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_der_ext");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_sup_ext");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Recta_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_sup_ext");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_izq_ext");
	pistas[cont++] = crearPista("Recta_cuarto");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	pistas[cont++] = crearPista("Recta_std");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	for (int i = 0; i < 8; i++) pistas[cont++] = crearPista("Curva_izq_ext");
	for (int i = 0; i < 7; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Curva_izq_sup_ext");
	for (int i = 0; i < 2; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_cuarto");
	for (int i = 0; i < 4; i++) pistas[cont++] = crearPista("Curva_izq_sup_ext");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Recta_std");

}