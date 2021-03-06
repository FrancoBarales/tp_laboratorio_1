/*
 * funcionesGet.h
 *
 *  Created on: 14 abr. 2022
 *      Author: Franco Barales Illia
 */

#ifndef FUNCIONESGET_H_
#define FUNCIONESGET_H_

/*
 *  menu es la funcion que muestra la interfaz principal del programa. Pide al usuario
 *	que ingrese la opcion que desea, y retorna el numero de la opcion que el usuario selecciono.
*/

int menu(void);

/*
 * getFloat recibe un rango (maximo y minimo), un numero de reintentos, un mensaje a mostrar,
 * y un mensaje de error en caso de que algo falle, asignando un valor a la variable puntero pNumero.
*/

float getFloat(float * pNumero, char * mensaje, char * mensajeError, float maximo, float minimo, float reintentos);

#endif /* FUNCIONESGET_H_ */
