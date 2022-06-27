/*
 * menus.c
 *
 *  Created on: 27 jun. 2022
 *      Author: Franco
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayPassenger.h"
#include "utn.h"
#include "menus.h"

#define VACIO 0
#define LLENO 1

int menu_principal(void)
{
	int opcion;
	printf("\nMenu de Opciones\n");
	printf("\n1) Agregar pasajero");
	printf("\n2) Modificar pasajero");
	printf("\n3) Eliminar pasajero");
	printf("\n4) Informe de pasajeros");
	printf("\n5) Carga forzada de pasajeros");
	printf("\n6) Salir");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Opcion incorrecta.", 1, 6, 3);
	return opcion;
}

int menu_modificaciones(Passenger* list, int index, int buffer)
{
	int opcion;
	int retorno = -1;

	if(list != NULL && index > -1 && buffer > 0)
	{
		do
		{
			printf("\n\nQue dato desea modificar?\n");
			printf("\n1.Nombre");
			printf("\n2.Apellido");
			printf("\n3.Precio de vuelo");
			printf("\n4.Codigo de vuelo");
			printf("\n5.Tipo de pasajero");
			printf("\n6.Estado del vuelo");
			printf("\n7.Salir\n");
			utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Seleccione una opcion correcta.", 1, 7, 3);

			switch(opcion)
			{
				case 1:
					utn_getNombre(list[index].name, 1, 51, "\nIngrese el nombre del pasajero: ","\nERROR. Ingrese solamente letras. ", 3);
					break;
				case 2:
					utn_getNombre(list[index].lastName, 1, 51, "\nIngrese el apellido del pasajero: ", "\nERROR. Ingrese solamente letras.", 3);
					break;
				case 3:
					utn_getNumeroFlotante(&list[index].price, "\nIngrese el precio del ticket (MAX $500.000, MIN $20.000): ", "\nERROR. Datos incorrectos.", 20000, 500000, 3);
					break;
				case 4:
					utn_getNumero(&list[index].typePassenger,"\nIngrese el tipo de pasajero (0.Economy, 1.Excecutive): ", "\nERROR. Ingrese una opcion correcta.", 0, 2, 3);
					break;
				case 5:
					utn_getCadena(list[index].flycode, 1, 11,"\nIngrese el codigo del vuelo (hasta 10 caracteres): ","\nERROR. Codigo incorrecto.", 3);
					break;
				default:
					system("pause");
					break;
			}
		}while(opcion != 6);
		retorno = 0;
	}

	return retorno;
}

// PARA REALIZAR CALCULOS E INFORMES

float calcularPrecioTotal(Passenger *list, int len)
{
	float retorno = -1;

	if(list != NULL && len > 0)
	{
		retorno = 0;

		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				retorno += list[i].price;
			}
		}
	}
	return retorno;
}

float calcularPromedio(Passenger* list, int len, float total)
{
	float retorno = -1;
	int contador = 0;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				contador++;
			}
		}

		if(contador != 0)
		{
			retorno = total / contador;
		}
	}
	return retorno;
}

int cantidadPasajerosActivo(Passenger *list, int len)
{
	int suma = 0;

	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty != VACIO)
			{
				suma++;
			}
		}
	}
	return suma;
}

int mayoresAlPrecioPromedio(Passenger *list, int len, float promedio)
{
	int retorno = 0;

	if (list != NULL && len > 0 && promedio > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty != VACIO && list[i].price > promedio)
			{
				retorno++;
			}
		}
	}
	return retorno;
}


int informePrecios(Passenger *list, int len)
{
	int retorno = -1;
	int cantidadMayoresAlPromedio;
	int orden;
	float suma;
	float promedio;

	if(list != NULL && len > 0)
	{
		utn_getNumero(&orden,"Que orden alfabetico desea? (0.A a Z, 1.Z a A): ", "\nOpcion Incorrecta\n. ", 0, 1, 30);
		sortPassengers(list, len, orden);
		printPassenger(list, len);

		suma = calcularPrecioTotal(list, len);
		promedio = calcularPromedio(list, len, suma);
		cantidadMayoresAlPromedio = mayoresAlPrecioPromedio(list, len, promedio);
		printf("\nEl total de los pasajes fue: $%.2f.", suma);
		printf("\nEl precio promedio de los pasajes es: $%.2f.", promedio);
		printf("\nHay %d pasajeros que superan el precio promedio.", cantidadMayoresAlPromedio);

		utn_getNumero(&orden,"Que orden por codigo de vuelo desea? (0.A a Z, 1.Z a A): ", "\nOpcion Incorrecta\n. ", 0, 1, 30);
		sortPassengersByFlycode(list, len, orden);
		printPassengersByFlycode(list, len);

		retorno = 0;
	}
	return retorno;
}

int printPassengersByFlycode(Passenger* list, int len)
{
    int result = -1;

    if(list != NULL && len > 0)
    {
        printf("\n");
        for(int i = 0; i < len; i++)
        {
        	if(list[i].isEmpty == 0 && list[i].statusFlight == 1)
        	{
        		showPassengerData(list[i]);
        	}
        }
        result = 0;
    }

    return result;
}

int sortPassengersByFlycode(Passenger *list, int len, int order)
{
	int retorno = -1;
	Passenger auxPassenger;

	if(list != NULL && len > 0 && (order == 0 || order == 1))
	{
		switch(order)
		{
			case 0: // ordenar de mayor a menor
				for(int i = 0; i < len - 1; i++)
				{
					for(int j = i + 1; j < len; j++)
					{
						if(strcmp(list[i].flycode,list[j].flycode) > 0)
						{
							auxPassenger = list[i];
							list[i] = list[j];
							list[j] = auxPassenger;
						}else if(strcmp(list[i].flycode, list[j].flycode) == 0){
							if(list[i].statusFlight < list[j].statusFlight){
								auxPassenger = list[i];
								list[i] = list[j];
								list[j] = auxPassenger;
							}
						}
					}
				}
				retorno = 0;
				break;
			case 1: // ordenar de menor a mayor
				for(int i = 0; i < len - 1; i++)
				{
					for(int j = i + 1; j < len; j++)
					{
						if(strcmp(list[i].flycode,list[j].flycode) < 0)
						{
							auxPassenger = list[i];
							list[i] = list[j];
							list[j] = auxPassenger;
						}
						else if(strcmp(list[i].flycode, list[j].flycode) == 0)
						{
							if(list[i].statusFlight > list[j].statusFlight)
							{
								auxPassenger = list[i];
								list[i] = list[j];
								list[j] = auxPassenger;
							}
						}
					}
				}
				retorno = 0;
				break;
		}
	}
	return retorno;
}


