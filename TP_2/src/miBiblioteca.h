/*
 * menus.h
 *
 *  Created on: 27 jun. 2022
 *      Author: Franco
 */

#ifndef MENUS_H_
#define MENUS_H_

int menu_principal(void);

int menu_modificaciones(Passenger* list, int index, int buffer);

int buscarEspacioVacio(Passenger* list, int len);

int comprobacionListaVacia(Passenger* list, int len);

int calcularMayorId(int id[], int len);

float calcularPrecioTotal(Passenger* list, int len);

float calcularPromedio(Passenger* list, int len, float total);

int cantidadPasajerosActivo(Passenger* list, int len);

int mayoresAlPrecioPromedio(Passenger* list, int len, float promedio);

int informePrecios(Passenger* list, int len);

int printPassengersByFlycode(Passenger* list, int len);

int sortPassengersByFlycode(Passenger* list, int len, int order);

#endif /* MENUS_H_ */
