#include "CACircuito_jerez.h"

// FUNCIÓN: CACircuito_jerez::Circuito_jerez()
//
// PROPÓSITO: Definir el numero de pistas que forman el circuito y invocar a ls funcion crear_Circuito.
//
CACircuito_jerez::CACircuito_jerez()
{
	nombre = "CACircuito_jerez";
	num_pistas = 74;
	pistas.resize(num_pistas);
	crear_Circuito();


}

// FUNCIÓN: CACircuito_jerez::crear_Circuito()
//
// PROPÓSITO: Crear todas las pistas que forman el circuito llamando a la fucnion crearPista 
//            de la clase Circuito padre.
//
void CACircuito_jerez::crear_Circuito() {
	int cont = 0;
	for (int i = 0; i < 6; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_der_ext");
	pistas[cont++] = crearPista("Recta_std");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Curva_izq_ext");
	pistas[cont++] = crearPista("Recta_media");
	for (int i = 0; i < 5; i++) pistas[cont++] = crearPista("Curva_izq_ext");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_ext");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Curva_der_ext");
	pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Recta_cuarto");
	pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Curva_izq_ext");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_media");
	pistas[cont++] = crearPista("Curva_der_std");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_izq_ext");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_int");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	for (int i = 0; i < 6; i++) pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_ext");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont++] = crearPista("Curva_der_int");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Recta_std");
	pistas[cont++] = crearPista("Recta_Cambio_Carril");
	pistas[cont++] = crearPista("Curva_izq_std");
	pistas[cont++] = crearPista("Curva_izq_std");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Recta_std");
	for (int i = 0; i < 3; i++) pistas[cont++] = crearPista("Curva_der_std");
	pistas[cont] = crearPista("Pista_final");
}