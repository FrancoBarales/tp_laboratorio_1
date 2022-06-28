/*
 * ArrayPassenger.c
 *
 *  Created on: 4 may. 2022
 *      Author: Franco
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayPassenger.h"
#include "miBiblioteca.h"
#include "utn.h"

int initPassengers(Passenger *list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}
	return retorno;
}

int addPassenger(Passenger *list, int len, int id, char name[], char lastName[], float price, int typePassenger, int statusFlight, char flycode[])
{
	int retorno = -1;
	int index;

	index = buscarEspacioVacio(list, len);

	if(index != -1 && list != NULL && len > 0)
	{
		list[index].id = id;
		strcpy(list[index].name, name);
		strcpy(list[index].lastName, lastName);
		list[index].price = price;
		list[index].typePassenger = typePassenger;
		list[index].statusFlight = statusFlight;
		strcpy(list[index].flycode, flycode);
		list[index].isEmpty = 0;
		retorno = 0;
	}
	return retorno;
}

int loadPassenger(Passenger *list, int len, int contadorId)
{
	int flag1 = 0;
	char respuesta;
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flyCode[10];
	int typePassenger;
	int statusFlight;

	do
	{
		if(flag1 == 0)
		{
			id = contadorId;
		}
		else
		{
			id++;
		}
		if(list != NULL && len > 0)
		{
			utn_getNombre(name, 1, 51, "\nIngrese el nombre del pasajero: ", "\nERROR. Datos no validos.", 30);
			utn_getNombre(lastName, 1, 51, "\nIngrese el apellido del pasajero: ", "\nERROR. Datos no validos.", 30);
			utn_getNumeroFlotante(&price,"\nIngrese el precio del ticket (MAX $500.000, MIN $20.000): ","\nERROR. Datos no validos.", 20000, 500000, 30);
			utn_getCadena(flyCode, 1, 11, "\nIngrese el codigo de vuelo (hasta 10 caracteres): ","\nERROR. Datos no validos.", 30);
			utn_getNumero(&typePassenger,"\nIngrese el tipo de pasajero (0.Economy 1.Executive): ","\nERROR. Opcion incorrecta.",0, 1, 30);
			utn_getNumero(&statusFlight,"\nIngrese el estado de vuelo (0.INACTIVO 1.ACTIVO): ","\nERROR. Opcion incorrecta.",0, 1, 30);

			if(addPassenger(list, len, id, name, lastName, price, typePassenger, statusFlight, flyCode) == -1)
			{
				printf("\n\nERROR. No se pudo cargar el pasajero.\n");
			}
			else
			{
				printf("\nPasajero cargado exitosamente.\n");
			}
		}

		do{
			printf("\nDesea cargar otro pasajero? (S/N)?: ");
			fflush(stdin);
			scanf("%c", &respuesta);
			respuesta = tolower(respuesta);
		}while(respuesta != 's' && respuesta != 'n');

		flag1 = 1;
	}while(respuesta != 'n');

	return id;
}


int findPassengerById(Passenger *list, int len, int id)
{
	int retorno = -1;

	for(int i = 0; i < len; i++)
	{
		if(list[i].isEmpty == 0)
		{
			if(list[i].id == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

int removePassenger(Passenger* list, int len, int id)
{
	int retorno = -1;

	if(list != NULL && len > 0 && id > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].id == id)
			{
				list[i].isEmpty = 1;
				retorno = 0;
				break;
			}
		}
	}

	return retorno;
}

int deletePassenger(Passenger *list, int len)
{
	int retorno = -1;
	int index;
	int auxID;

	if(list != NULL && len > 0)
	{
		do
		{
			utn_getNumero(&auxID,"\nIngrese el ID del pasajero que desea eliminar: ","\nERROR. Numero de ID invalido. ", 1, 2000, 3);
			index = findPassengerById(list, len, auxID);

			if(index == -1)
			{
				printf("\nERROR. No se pudo encontrar el index especificado.\n");
			}
			else
			{
				removePassenger(list, len, auxID);
				printf("\nEl pasajero especificado fue dado de baja.\n");
				retorno = 0;
			}
		}while(auxID < 1 || index == -1);
	}

	return retorno;
}

int sortPassengers(Passenger *list, int len, int order)
{
	int retorno = -1;
	Passenger auxPassenger;

	if(list != NULL && len > 0 && (order == 0 || order == 1))
	{
		switch(order)
		{
			case 0: // ordenar de A a Z
				for(int i = 0; i < len - 1; i++)
				{
					for(int j = i + 1; j < len; j++)
					{
						if(strcmp(list[i].lastName,list[j].lastName) > 0)
						{
							auxPassenger = list[i];
							list[i] = list[j];
							list[j] = auxPassenger;
						}
						else if(strcmp(list[i].lastName, list[j].lastName) == 0)
						{
							if(list[i].typePassenger > list[j].typePassenger)
							{
								auxPassenger = list[i];
								list[i] = list[j];
								list[j] = auxPassenger;
							}
						}
					}
				}
				retorno = 0;
				printListHeader();
				printPassenger(list, len);
				break;
			case 1: // ordenar de Z a A
				for(int i = 0; i < len - 1; i++)
				{
					for(int j = i + 1; j < len; j++)
					{
						if(strcmp(list[i].lastName,list[j].lastName) < 0)
						{
							auxPassenger = list[i];
							list[i] = list[j];
							list[j] = auxPassenger;
						}
						else if(strcmp(list[i].lastName, list[j].lastName) == 0)
						{
							if(list[i].typePassenger > list[j].typePassenger)
							{
								auxPassenger = list[i];
								list[i] = list[j];
								list[j] = auxPassenger;
							}
						}
					}
				}
				retorno = 0;
				printListHeader();
				printPassenger(list, len);
				break;
		}
	}
	return retorno;
}

void printListHeader(void)
{
	printf("+--------------------------------------------------------------------------------------------------------+");
	printf("\n|%4s |%15s |%15s |%12s |%13s |%15s |%15s|\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO DE VUELO", "TIPO DE PASAJERO", "ESTADO DE VUELO");
	printf("+-----+----------------+----------------+-------------+----------------+-----------------+---------------+\n");
}

int printPassenger(Passenger *list, int len)
{
	int retorno = -1;
	char auxTipoPasajero[50];
	char auxEstadoVuelo[50];

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				tipoPasajeroAChar(list[i].typePassenger, auxTipoPasajero);
				estadoVueloAChar(list[i].statusFlight, auxEstadoVuelo);
				printf("|%4d |%15s |%15s |%12.2f |%15s |%16s |%15s|\n",
						list[i].id,
						list[i].name,
						list[i].lastName,
						list[i].price,
						list[i].flycode,
						auxTipoPasajero,
						auxEstadoVuelo);
			}
		}
		printf("+-----+----------------+----------------+-------------+----------------+-----------------+---------------+\n");
		retorno = 0;
	}
	return retorno;
}

int modifyPassenger(Passenger *list, int len)
{
	int retorno = -1;
	int auxID;
	int index;

	if(list != NULL && len > 0)
	{
		do
		{
			printListHeader();
			printPassenger(list, len);
			utn_getNumero(&auxID, "\nIngrese el id del pasajero que desea modificar: ","\nERROR. Opcion incorrecta.", 1, 100000, 3);
			index = findPassengerById(list, len, auxID);

			if(index == -1)
			{
				printf("\nERROR. No se pudo encontrar el ID especificado.\n");
			}
			else
			{
				if(menu_modificaciones(list, index, 51) == -1)
				{
					printf("\nERROR. No se pudo modificar el pasajero.\n");
				}
			}
		}while(index == -1);
	}
	return retorno;
}

int cargaForzada(Passenger* list, int len, int* contadorId)
{
	int retorno = -1;
	int idAux[5] = {*contadorId + 1,*contadorId + 2,*contadorId + 3,*contadorId + 4,*contadorId + 5};

	if(list != NULL && len > 0)
	{
		addPassenger(list, len, idAux[0], "Filippo", "Inzaghi", 58000, 0, 1, "ITA873");
		addPassenger(list, len, idAux[1], "Cristiano", "Ronaldo", 186500, 0, 0, "POR285");
		addPassenger(list, len, idAux[2], "Lionel", "Messi", 175000, 1, 1, "ARG687");
		addPassenger(list, len, idAux[3], "Ronaldinho", "Gaucho", 149000,1, 0,"BRA380");
		addPassenger(list, len, idAux[4], "Gerd", "Muller", 95000, 0, 1, "ALE145");

		retorno = calcularMayorId(idAux, 5);
	}
	return retorno;
}




int tipoPasajeroAChar(int tipoPasajeroInt, char* tipoPasajero)
{
	int retorno = -1;

	switch(tipoPasajeroInt)
	{
		case 0:
			strcpy(tipoPasajero, "Economy");
			retorno = 0;
			break;
		case 1:
			strcpy(tipoPasajero, "Executive");
			retorno = 0;
			break;
	}

	return retorno;
}

int estadoVueloAChar(int estadoVueloInt, char* estadoVuelo)
{
	int retorno = -1;

	switch(estadoVueloInt)
	{
		case 0:
			strcpy(estadoVuelo, "INACTIVO");
			retorno = 0;
			break;
		case 1:
			strcpy(estadoVuelo, "ACTIVO");
			retorno = 0;
			break;
	}

	return retorno;
}



