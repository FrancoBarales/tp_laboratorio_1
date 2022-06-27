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
#include "menus.h"
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
	int index = buscarEspacioVacio(list, len);

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
	int retorno = -1;
	int flag1 = 0;
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flyCode[10];
	int typePassenger;
	int statusFlight;
	char respuesta;

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
		utn_getCadena(flyCode, 1, 11, "\nIngrese el codigo del vuelo (hasta 10 caracteres): ","\nERROR. Datos no validos.", 30);
		utn_getNumero(&typePassenger,"\nIngrese el tipo de pasajero (1.Infante 2.Adulto 3.Jubilado): ","\nERROR. Opcion incorrecta.",1, 3, 30);

		if(addPassenger(list, len, id, name, lastName, price, typePassenger, statusFlight, flyCode) == -1)
		{
			printf("\n\nERROR. No se pudo cargar el pasajero.\n");
		}
		else
		{
			printf("\nPasajero cargado exitosamente.\n");
			retorno = 0;
			flag1 = 0;
		}
	}

	return retorno;
}


int findPassengerById(Passenger *list, int len, int id)
{
	int retorno = -1;

	for (int i = 0; i < len; i++)
	{
		if (list[i].id == id)
		{
			retorno = i;
			break;
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
			utn_getNumero(&auxID,"\nIngrese el ID del pasajero que desea eliminar: ","\nERROR. ID no encontrado. ", 0, 2000, 3);
			index = findPassengerById(list, len, auxID);

			if(index < 1)
			{
				printf("\nERROR. El ID debe ser mayor a cero.\n");
			}
			else
			{
				index = findPassengerById(list, len, index);
				if(index == -1)
				{
					printf("\nERROR. No se pudo encontrar el index especificado.\n");
				}
				else
				{
					removePassenger(list, len, index);
					printf("\nEl pasajero seleccioando fue dado de baja.\n");
					retorno = 0;
				}
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
				printPassenger(list, len);
				break;
		}
	}
	return retorno;
}

int printPassenger(Passenger *list, int len)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				showPassengerData(list[i]);
			}
		}
		retorno = 0;
	}

	return retorno;
}

int buscarEspacioVacio(Passenger* list, int len)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 1)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

int modifyPassenger(Passenger *list, int len)
{
	int retorno = -1;
	int auxID;
	int opcion;
	int index;
	int verifyIndex;

	if(list != NULL && len > 0)
	{
		do
		{
			printPassenger(list, len);
			utn_getNumero(&auxID, "\nIngrese el id del pasajero que desea modificar: ","\nERROR. Opcion incorrecta.", 1, 100000, 3);
			verifyIndex = findPassengerById(list, len, auxID);

			if(verifyIndex == -1)
			{
				printf("\nERROR. No se pudo encontrar el ID especificado.\n");
			}
			else
			{
				if(menu_modificaciones(list, index, 51) == -1)
				{
					printf("\nERROR. No se pudo modificar el pasajero.\n");
				}
				else
				{
					printf("\nPasajero modificado exitosamente.\n");
				}
			}
		}while(verifyIndex == -1);
	}
	return retorno;
}

void showPassengerData(Passenger list)
{
	printf("\n Id: %d, Nombre: %s,\t\t Apellido: %s,\t Precio: $%.2f, \t Codigo de vuelo: %s,\t Tipo de pasajero: %d,\t Estado del vuelo: %d",
			list.id,
			list.name,
			list.lastName,
			list.price,
			list.flycode,
			list.typePassenger,
			list.statusFlight);

}

int cargaForzada(Passenger* list, int len, int* contadorId)
{
	int retorno = -1;
	int idAux[5] = {*contadorId + 1, *contadorId + 2, *contadorId + 3, *contadorId + 4, *contadorId + 5};
	char nameAux[5][50] = {"Filippo", "Cristiano", "Lionel", "Ronaldinho", "Gerd"};
	char lastNameAux[5][50] = {"Inzaghi", "Ronaldo", "Messi", "Gaucho", "Muller"};
	int priceAux[5] = {58000, 186500, 175000, 149000, 95000};
	char flyCodeAux[5][50] = {"IT1430","PT8431","AR4462","BR2658","AL3179"};
	int typePassengerAux[5] = {1,1,0,0,1};
	int statusFlightAux[5] = {1,0,1,1,1};
	int isEmptyAux[5] = {0,0,0,0,0};
	int result = -1;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < 5; i++)
		{
			list[i].id = idAux[i];
			strcpy(list[i].name, nameAux[i]);
			strcpy(list[i].lastName, lastNameAux[i]);
			list[i].price = priceAux[i];
			strcpy(list[i].flycode, flyCodeAux[i]);
			list[i].typePassenger = typePassengerAux[i];
			list[i].statusFlight = statusFlightAux[i];
			list[i].isEmpty = isEmptyAux[i];
		}
		retorno = 0;
	}
	return retorno;
}



