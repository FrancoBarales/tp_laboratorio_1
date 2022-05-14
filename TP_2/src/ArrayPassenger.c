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
#include "utn.h"

#define VACIO 0
#define LLENO 1
#define ACTIVO 1
#define INACTIVO 0

int initPassengers(Passenger *list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			list[i].isEmpty = VACIO;
		}
		retorno = 0;
	}
	return retorno;
}


int addPassenger(Passenger *list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flycode[])
{
	int retorno = -1;
	int index = buscarIndexPorIsEmpty(list, len);
	Passenger newPassenger;

	if (index != -1 && list != NULL && len > 0)
	{
		newPassenger.id = id;
		strcpy(newPassenger.name, name);
		strcpy(newPassenger.lastName, lastName);
		newPassenger.price = price;
		newPassenger.typePassenger = typePassenger;
		strcpy(newPassenger.flycode, flycode);
		newPassenger.statusFlight = ACTIVO;
		newPassenger.isEmpty = LLENO;
		list[index] = newPassenger;
		retorno = 0;
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

int removePassenger(Passenger *list, int len, int id)
{
	char respuesta[3];
	int retorno = -1;
	int index;

	index = findPassengerById(list, len, id);
	if(index == 0)
	{
		utn_getNombre(respuesta, 1, 3, "\n Esta seguro de eliminar al pasajero? (si/no):", "ERROR.\n" , 3);
		strEnMinuscula(respuesta);
		if (index != -1 && strcmp(respuesta, "si") == 0)
		{
			list[index].isEmpty = VACIO;
			retorno = 0;
		}
	}
	else
	{
		puts("\nERROR. No se pudo encontrar el index especificado.\n");
	}

	return retorno;
}

int sortPassengers(Passenger *list, int len, int order)
{
	int retorno = -1;
	int i, j;
	Passenger auxPassenger;

	if (list != NULL && len > 0)
	{
		switch (order)
		{
		case -1: // menor a mayor
			for (i = 0; i < len - 1; i++)
			{
				for (j = i + 1; j < len; j++)
				{
					if (list[i].isEmpty == LLENO && list[j].isEmpty == LLENO)
					{
						if (strcmp(list[i].lastName, list[j].lastName) > 0)
						{
							auxPassenger = list[i];
							list[i] = list[j];
							list[j] = auxPassenger;
						}
						else if (strcmp(list[i].lastName, list[j].lastName) == 0 && list[i].typePassenger > list[j].typePassenger)
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
		case 1: // mayor a menor
			for (i = 0; i < len - 1; i++)
			{
				for (j = i + 1; j < len; j++)
				{
					if (list[i].isEmpty == LLENO && list[j].isEmpty == LLENO)
					{
						if (strcmp(list[i].lastName, list[j].lastName) < 0)
						{
							auxPassenger = list[i];
							list[i] = list[j];
							list[j] = auxPassenger;
						}
						else if (strcmp(list[i].lastName, list[j].lastName) == 0 && list[i].typePassenger < list[j].typePassenger)
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

	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty != VACIO)
			{
				showPassengerData(list[i]);
			}
		}
		retorno = 0;
	}

	return retorno;
}

int buscarIndexPorIsEmpty(Passenger list[], int len)
{
	int retorno = -1;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == VACIO)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

int loadPassengerData(Passenger *list, int len)
{
	int retorno = -1;
	int verifyPassenger;

	Passenger newPassenger;

	if(list != NULL && len > 0)
	{
		newPassenger.id = incrementarId();
		utn_getNombre(newPassenger.name, 1, 51, "\nIngrese el nombre del pasajero: ", "\nERROR. Datos no validos.", 30);
		utn_getNombre(newPassenger.lastName, 1, 51, "\nIngrese el apellido del pasajero: ", "\nERROR. Datos no validos.", 30);
		utn_getNumeroFlotante(&newPassenger.price,"\nIngrese el precio del ticket (MAX $200.000, MIN $20.000): ","\nERROR. Datos no validos.", 20000, 200000, 30);
		utn_getCadena(newPassenger.flycode, 1, 11, "\nIngrese el codigo del vuelo (hasta 10 caracteres): ","\nERROR. Datos no validos.", 30);
		utn_getNumero(&newPassenger.typePassenger,"\nIngrese el tipo de pasajero (1.Infante 2.Adulto 3.Jubilado): ","\nERROR. Opcion incorrecta.",1, 3, 30);

		verifyPassenger = addPassenger(list, len, newPassenger.id, newPassenger.name, newPassenger.lastName, newPassenger.price, newPassenger.typePassenger, newPassenger.flycode);
		if(verifyPassenger != -1)
		{
			puts("\nDatos cargados exitosamente.");
			retorno = 0;
		}
		else
		{
			puts("\nERROR. No se pudieron cargar los datos.\n");
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

	printPassenger(list, len);
	verifyIndex = utn_getNumero(&auxID, "\nIngrese el id del pasajero que desea modificar: ","\nERROR. Opcion incorrecta.", 5000, 7000, 3);

	if(verifyIndex == 0)
	{
		index = findPassengerById(list, len, auxID);
		if (index != -1)
		{
			opcion = mostrarMenuModif();
			switch (opcion)
			{
				case 1:
					utn_getNombre(list[index].name, 1, 51, "\nIngrese el nombre del pasajero: ","\nERROR. Ingrese solamente letras. ", 3);
					break;
				case 2:
					utn_getNombre(list[index].lastName, 1, 51, "\nIngrese el apellido del pasajero: ", "\nERROR. Ingrese solamente letras.", 3);
					break;
				case 3:
					utn_getNumeroFlotante(&list[index].price, "\nIngrese el precio del ticket (MAX $200.000, MIN $20.000): ", "\nERROR. Datos incorrectos.", 20000, 200000, 3);
					break;
				case 4:
					utn_getCadena(list[index].flycode, 1, 11,"\nIngrese el codigo del vuelo (hasta 10 caracteres): ","\nERROR. Codigo incorrecto.", 3);
					break;
				case 5:
					utn_getNumero(&list[index].typePassenger,"\nIngrese el tipo de pasajero (1.Infante, 2.Adulto, 3.Jubilado): ", "\nERROR. Ingrese una opcion correcta.",1, 3, 3);
					break;
				case 6:
					utn_getNumero(&list[index].statusFlight,"\nIngrese el estado del vuelo (0.Inactivo, 1.Activo)\n","\nERROR. Ingrese una opcion correcta.\n", 1, 2, 3);
			}
			retorno = 0;

		}
	}

	else
	{
		printf("\nNo se pudo encontrar el ID especificado.");
	}
	return retorno;
}


int incrementarId()
{
    static int id = 5000;
    id++;
    return id;
}

void showPassengerData(Passenger list)
{
	printf("\n Id: %d, Nombre: %s,\t\t Apellido: %s,\t Precio: $%.2f, \t Codigo de vuelo: %s,\t Tipo de pasajero: %d,\t Estado del vuelo: %d",
			list.id, list.name, list.lastName, list.price,
			list.flycode, list.typePassenger, list.statusFlight);

}



int cargaForzada(Passenger list[], int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		addPassenger(list, len, 6001, "Filippo", "Inzaghi", 58000, 3, "italia");
		addPassenger(list, len, 6002, "Cristiano", "Ronaldo", 186500, 2,"portugal");
		addPassenger(list, len, 6003, "Lionel", "Messi", 175000, 1,"argentina");
		addPassenger(list, len, 6004, "Ronaldinho", "Gaucho", 149000, 2,"brasil");
		addPassenger(list, len, 6005, "Gerd", "Muller", 95000, 3,"alemania");
		retorno = 0;
	}

	return retorno;
}




