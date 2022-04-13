/*
 * Biblioteca_TP1.h
 *
 *  Created on: 11 abr. 2022
 *      Author: Franco Barales
 */

#ifndef BIBLIOTECA_TP1_H_
#define BIBLIOTECA_TP1_H_

int menu(void);

/*
 *  menu es la funcion que muestra la interfaz principal del programa. Pide al usuario
 *	que ingrese la opcion que desea, y retorna el numero de la opcion que el usuario selecciono.
*/

/*
 * getFloat recibe un rango, un numero de reintentos, un mensaje a mostrar,
 * y un mensaje de error en caso de que algo falle, asignando un valor
 * a la variable puntero pNumero.
*/

float getFloat(float * pNumero, char * mensaje, char * mensajeError, float maximo, float minimo, float reintentos);

/*
 * calcularDiferencia calcula la diferencia entre dos operadores,
 * y asigna el resultado a la variable puntero pDiferencia.
*/

float calcularDiferencia(float operador1, float operador2);

/*
 * multiplicar recibe un numero flotante (precio), lo multiplica por un numero flotante (porcentaje)
 * y retorna el resultado de esa operacion.
*/

float multiplicar(float precio, float porcentaje);

/*
 * dividir recibe un numero flotante (precio), lo divide por un numero flotante (dividendo)
 * y retorna el resultado de esa operacion.
*/

float dividir(float precio, float dividendo);


/*
 * mostrarAerolineas muestra los precios para Aerolineas:
 * precio recibe el precio del vuelo
 * debito recibe el precio del vuelo pagando con debito
 * credito recibe el precio del vuelo pagando con credito
 * bitcoin recibe el precio del vuelo expresado en bitcoin
 * precioUnitario recibe el precio unitario del vuelo
*/

void mostrarAerolineas(float precio, float debito, float credito, float bitcoin, float precioUnitario);


/*
 * mostrarLatam muestra los precios para Aerolineas:
 * precio recibe el precio del vuelo
 * debito recibe el precio del vuelo pagando con debito
 * credito recibe el precio del vuelo pagando con credito
 * bitcoin recibe el precio del vuelo expresado en bitcoin
 * precioUnitario recibe el precio unitario del vuelo
*/

void mostrarLatam(float precio, float debito, float credito, float bitcoin, float precioUnitario);

#endif /* BIBLIOTECA_TP1_H_ */
