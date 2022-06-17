/*
 * Passenger.c
 *
 *  Created on: 19 may. 2022
 *      Author: Maru
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Passenger.h"
#include "Controller.h"
#include "LinkedList.h"
#include "parser.h"
#include "menus.h"
#include "utn.h"

Passenger* Passenger_new()
{
	Passenger* pUnPasajero;
	pUnPasajero = (Passenger*) malloc(sizeof(Passenger));
	return pUnPasajero;
}

Passenger* Passenger_newParametros(char* idStr, char* nombreStr, char* apellidoStr, char* precioStr, char* codigoVueloStr, char* tipoPasajeroStr, char* estadoVueloStr)
{
	int auxIdStr;
	float auxPrecioStr;
	int auxTipoPasajeroStr;
	int auxEstadoVueloStr;
	Passenger* nuevoPasajero = NULL;

	nuevoPasajero = Passenger_new();

	if(nuevoPasajero != NULL && idStr != NULL && nombreStr != NULL && apellidoStr != NULL && precioStr != NULL && tipoPasajeroStr != NULL && codigoVueloStr != NULL && estadoVueloStr != NULL)
	{
		auxIdStr = atoi(idStr);
		auxPrecioStr = atof(precioStr);
		auxTipoPasajeroStr = Passenger_TipoPasajeroAInt(tipoPasajeroStr);
		auxEstadoVueloStr = Passenger_EstadoVueloAInt(estadoVueloStr);

		if(Passenger_setId(nuevoPasajero, auxIdStr) == -1 ||
			Passenger_setNombre(nuevoPasajero, nombreStr) == -1 ||
			Passenger_setApellido(nuevoPasajero, apellidoStr) == -1 ||
			Passenger_setCodigoVuelo(nuevoPasajero, codigoVueloStr) == -1 ||
			Passenger_setTipoPasajero(nuevoPasajero, auxTipoPasajeroStr) == -1 ||
			Passenger_setPrecio(nuevoPasajero, auxPrecioStr) == -1 ||
			Passenger_setEstadoVuelo(nuevoPasajero, auxEstadoVueloStr) == -1)
		{
			Passenger_delete(nuevoPasajero);
		}
	}
	return nuevoPasajero;
}


int Passenger_encontrarID(LinkedList* listaPasajeros, int id)
{
	int len;
	int index;
	Passenger* auxiliar;

	if(listaPasajeros!=NULL)
	{
		len = ll_len(listaPasajeros);

		if(len > 0)
		{
			for(int i = 0; i < len; i++)
			{
				auxiliar = (Passenger*)ll_get(listaPasajeros,i);
				if(auxiliar->id == id)
				{
					index = i;
					break;
				}
			}
		}
	}

	return index;
}

int Passenger_encontrarUltimoID(LinkedList* listaPasajeros)
{
	int auxId;
	int lastId = 0;
	int flag = 0;
	Passenger* auxPasajero = NULL;

	if(listaPasajeros != NULL)
	{
		for(int i = 0; i < ll_len(listaPasajeros); i++)
		{
			auxPasajero = (Passenger*)ll_get(listaPasajeros, i);
			Passenger_getId(auxPasajero, &auxId);

			if(auxId > lastId || flag == 0)
			{
				lastId = auxId;
				flag = 1;
			}
		}
	}
	return lastId;
}

void Passenger_delete(Passenger* this)
{
	if(this!=NULL)
	{
		free(this);
		this = NULL;
	}
}

void Passenger_deleteAll(LinkedList* pArrayListPassenger)
{
	int len;
	Passenger* auxPasajero = NULL;

	if(pArrayListPassenger != NULL)
	{
		len = ll_len(pArrayListPassenger);
		for(int i = 0; i < len; i++)
		{
			auxPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
			if(auxPasajero != NULL)
			{
				Passenger_delete(auxPasajero);
			}
		}
	}
}

int Passenger_edit(LinkedList* listaPasajeros)
{
	int retorno = -1;
	int auxId;
	int lastId;
	int index;
	char auxNombre[128];
	char auxApellido[128];
	float auxPrecio;
	int auxTipoPasajero;
	char auxCodigoVuelo[128];
	int auxEstadoVuelo;
	int opcion;
	Passenger* auxPasajero = NULL;

	lastId = Passenger_encontrarUltimoID(listaPasajeros);

	if(listaPasajeros != NULL)
	{
		controller_ListPassenger(listaPasajeros);
		utn_getNumero(&auxId, "\n\nIndique el ID que desea modificar: ", "\nERROR. Dato invalido.\n", 1, lastId, 2);
		index = Passenger_encontrarID(listaPasajeros, auxId);

		if(index != -1)
		{
			printListHeader();
			Passenger_printPassenger(listaPasajeros, index);
			auxPasajero = (Passenger*)ll_get(listaPasajeros, index);
			do
			{
				opcion = menu_ModifyPassenger();
				switch(opcion)
				{
					case 1:
						if(!utn_getNombre(auxNombre, 2, 128, "\nIndique el nombre del pasajero: ", "\nERROR. Nombre invalido.\n", 3))
						{
							Passenger_setNombre(auxPasajero, auxNombre);
							printf("\nNombre modificado exitosamente.\n");
						}
						break;
					case 2:
						if(!utn_getNombre(auxApellido, 2, 128, "\nIndique el apellido del pasajero: ", "\nERROR. Apellido invalido.\n", 3))
						{
							Passenger_setApellido(auxPasajero, auxApellido);
							printf("\nApellido modificado exitosamente.\n");
						}
						break;
					case 3:
						if(!utn_getNumeroFlotante(&auxPrecio, "\nIndique el precio del pasaje (Min: $10000, Max: $100000): $", "\nERROR. Precio invalido.\n", 10000, 1000000, 3))
						{
							Passenger_setPrecio(auxPasajero, auxPrecio);
							printf("\nPrecio modificado exitosamente.\n");
						}
						break;
					case 4:
						if(!utn_getNumero(&auxTipoPasajero, "\nIndique el tipo de pasajero (1.FirstClass, 2.ExecutiveClass, 3.EconomyClass): ", "\nERROR. Tipo de pasajero invalido.\n", 1, 3, 3))
						{
							Passenger_setTipoPasajero(auxPasajero, auxTipoPasajero);
							printf("\nTipo de pasajero modificado exitosamente.\n");
						}
						break;
					case 5:
						if(!utn_getCadena(auxCodigoVuelo, 8, 8, "Indique codigo de vuelo. (Hasta 8 caracteres): ", "\nERROR. Codigo de vuelo invalido.\n", 3))
						{
							Passenger_setCodigoVuelo(auxPasajero, auxCodigoVuelo);
							printf("\nCodigo de vuelo modificado exitosamente.\n");
						}
						break;
					case 6:
						if(!utn_getNumero(&auxEstadoVuelo, "\nIndique el estado del vuelo (1.En horario, 2.Aterrizado, 3.En vuelo, 4.Demorado): ", "\nERROR. Estado de vuelo invalido.\n", 1, 4, 2))
						{
							Passenger_setEstadoVuelo(auxPasajero, auxEstadoVuelo);
							printf("\nEstado de vuelo modificado exitosamente.\n");
						}
						break;
					case 7:
						printf("Regresando al menu principal...\n");
						retorno = 0;
						break;
				}
			}while(opcion != 7);
		}
	}
	return retorno;
}

int Passenger_sort(LinkedList* listaPasajeros)
{
	int retorno = -1;
	int opcion;
	int orden;

	if(listaPasajeros != NULL)
	{
		do
		{
			opcion = menu_PassengerOrder();
			switch(opcion)
			{
				case 1:
					if(!utn_getNumero(&orden, "\nIndique tipo de orden (0. Descendente, 1.Ascendente): ", "\nERROR. Opcion incorrecta.\n", 0, 1, 2))
					{
						printf("Ordenando...");
						ll_sort(listaPasajeros, Passenger_sortById, orden);
						controller_ListPassenger(listaPasajeros);
					}
					break;
				case 2:
					if(!utn_getNumero(&orden, "\nIndique tipo de orden (0. Descendente, 1.Ascendente): ", "\nERROR. Opcion incorrecta.\n", 0, 1, 2))
					{
						printf("Ordenando...");
						ll_sort(listaPasajeros, Passenger_sortByNombre, orden);
						controller_ListPassenger(listaPasajeros);
					}
					break;
				case 3:
					if(!utn_getNumero(&orden, "\nIndique tipo de orden (0. Descendente, 1.Ascendente): ", "\nERROR. Opcion incorrecta.\n", 0, 1, 2))
					{
						printf("Ordenando...");
						ll_sort(listaPasajeros, Passenger_sortByApellido, orden);
						controller_ListPassenger(listaPasajeros);
					}
					break;
				case 4:
					if(!utn_getNumero(&orden, "\nIndique tipo de orden (0. Descendente, 1.Ascendente): ", "\nERROR. Opcion incorrecta.\n", 0, 1, 2))
					{
						printf("Ordenando...");
						ll_sort(listaPasajeros, Passenger_sortByPrecio, orden);
						controller_ListPassenger(listaPasajeros);
					}
					break;
				case 5:
					if(!utn_getNumero(&orden, "\nIndique tipo de orden (0. Descendente, 1.Ascendente): ", "\nERROR. Opcion incorrecta.\n", 0, 1, 2))
					{
						printf("Ordenando...");
						ll_sort(listaPasajeros, Passenger_sortByCodigoVuelo, orden);
						controller_ListPassenger(listaPasajeros);
					}
					break;
				case 6:
					if(!utn_getNumero(&orden, "\nIndique tipo de orden (0. Descendente, 1.Ascendente): ", "\nERROR. Opcion incorrecta.\n", 0, 1, 2))
					{
						printf("Ordenando...");
						ll_sort(listaPasajeros, Passenger_sortByTipoPasajero, orden);
						controller_ListPassenger(listaPasajeros);
					}
					break;
				case 7:
					if(!utn_getNumero(&orden, "\nIndique tipo de orden (0. Descendente, 1.Ascendente): ", "\nERROR. Opcion incorrecta.\n", 0, 1, 2))
					{
						printf("Ordenando...");
						ll_sort(listaPasajeros, Passenger_sortByEstadoVuelo, orden);
						controller_ListPassenger(listaPasajeros);
					}
					break;
				case 8:
					printf("Regresando al menu principal...\n");
					retorno = 0;
					break;
				}
			}while(opcion != 8);
		}
	return retorno;
}

int Passenger_sortById(void* primerPasajero, void* segundoPasajero)
{
	int retorno = 0;
	int idUno;
	int idDos;
	Passenger* pasajeroUno = NULL;
	Passenger* pasajeroDos = NULL;

	if(primerPasajero != NULL && segundoPasajero != NULL)
	{
		pasajeroUno = (Passenger*) primerPasajero;
		pasajeroDos = (Passenger*) segundoPasajero;
		Passenger_getId(pasajeroUno, &idUno);
		Passenger_getId(pasajeroDos, &idDos);
		if(idUno > idDos)
		{
			retorno = 1;
		}
		else if(idUno < idDos)
		{
			retorno = -1;
		}
	}

	return retorno;
}

int Passenger_sortByNombre(void* primerPasajero, void* segundoPasajero)
{
	int retorno = 0;
	char nombreUno[128];
	char nombreDos[128];
	Passenger* pasajeroUno = NULL;
	Passenger* pasajeroDos = NULL;

	if(primerPasajero != NULL && segundoPasajero != NULL)
	{
		pasajeroUno = (Passenger*) primerPasajero;
		pasajeroDos = (Passenger*) segundoPasajero;
		Passenger_getNombre(pasajeroUno, nombreUno);
		Passenger_getNombre(pasajeroDos, nombreDos);
		if(strcmp(nombreUno, nombreDos) > 0)
		{
			retorno = 1;
		}
		else if(strcmp(nombreUno, nombreDos) < 0)
		{
			retorno = -1;
		}
	}
	return retorno;
}

int Passenger_sortByApellido(void* primerPasajero, void* segundoPasajero)
{
	int retorno = 0;
	char apellidoUno[128];
	char apellidoDos[128];
	Passenger* pasajeroUno = NULL;
	Passenger* pasajeroDos = NULL;

	if(primerPasajero != NULL && segundoPasajero != NULL)
	{
		pasajeroUno = (Passenger*) primerPasajero;
		pasajeroDos = (Passenger*) segundoPasajero;
		Passenger_getApellido(pasajeroUno, apellidoUno);
		Passenger_getApellido(pasajeroDos, apellidoDos);
		if(strcmp(apellidoUno, apellidoDos) > 0)
		{
			retorno = 1;
		}
		else if(strcmp(apellidoUno, apellidoDos) < 0)
		{
			retorno = -1;
		}
	}

	return retorno;
}

int Passenger_sortByPrecio(void* primerPasajero, void* segundoPasajero)
{
	int retorno = 0;
	float precioUno;
	float precioDos;
	Passenger* pasajeroUno = NULL;
	Passenger* pasajeroDos = NULL;

	if(primerPasajero != NULL && segundoPasajero != NULL)
	{
		pasajeroUno = (Passenger*) primerPasajero;
		pasajeroDos = (Passenger*) segundoPasajero;
		Passenger_getPrecio(pasajeroUno, &precioUno);
		Passenger_getPrecio(pasajeroDos, &precioDos);
		if(precioUno > precioDos)
		{
			retorno = 1;
		}
		else if(precioUno < precioDos)
		{
			retorno = -1;
		}
	}
	return retorno;
}

int Passenger_sortByCodigoVuelo(void* primerPasajero, void* segundoPasajero)
{
	int retorno = 0;
	char codigoVueloUno[128];
	char codigoVueloDos[128];
	Passenger* pasajeroUno = NULL;
	Passenger* pasajeroDos = NULL;

	if(primerPasajero != NULL && segundoPasajero != NULL)
	{
		pasajeroUno = (Passenger*) primerPasajero;
		pasajeroDos = (Passenger*) segundoPasajero;
		Passenger_getCodigoVuelo(pasajeroUno, codigoVueloUno);
		Passenger_getCodigoVuelo(pasajeroDos, codigoVueloDos);
		if(strcmp(codigoVueloUno, codigoVueloDos) > 0)
		{
			retorno = 1;
		}
		else if(strcmp(codigoVueloUno, codigoVueloDos) < 0)
		{
			retorno = -1;
		}
	}

	return retorno;
}

int Passenger_sortByTipoPasajero(void* primerPasajero, void* segundoPasajero)
{
	int retorno = 0;
	int tipoPasajeroUno;
	int tipoPasajeroDos;
	Passenger* pasajeroUno = NULL;
	Passenger* pasajeroDos = NULL;

	if(primerPasajero != NULL && segundoPasajero != NULL)
	{
		pasajeroUno = (Passenger*) primerPasajero;
		pasajeroDos = (Passenger*) segundoPasajero;
		Passenger_getTipoPasajero(pasajeroUno, &tipoPasajeroUno);
		Passenger_getTipoPasajero(pasajeroDos, &tipoPasajeroDos);
		if(tipoPasajeroUno > tipoPasajeroDos)
		{
			retorno = 1;
		}
		else if(tipoPasajeroUno < tipoPasajeroDos)
		{
			retorno = -1;
		}
	}
	return retorno;
}

int Passenger_sortByEstadoVuelo(void* primerPasajero, void* segundoPasajero)
{
	int retorno = 0;
	int estadoVueloUno;
	int estadoVueloDos;
	Passenger* pasajeroUno = NULL;
	Passenger* pasajeroDos = NULL;

	if(primerPasajero != NULL && segundoPasajero != NULL)
	{
		pasajeroUno = (Passenger*) primerPasajero;
		pasajeroDos = (Passenger*) segundoPasajero;
		Passenger_getEstadoVuelo(pasajeroUno, &estadoVueloUno);
		Passenger_getEstadoVuelo(pasajeroDos, &estadoVueloDos);
		if(estadoVueloUno > estadoVueloDos)
		{
			retorno = 1;
		}
		else if(estadoVueloUno < estadoVueloDos)
		{
			retorno = -1;
		}
	}
	return retorno;
}

void printListHeader()
{
	printf("+--------------------------------------------------------------------------------------------------------+");
	printf("\n|%4s |%15s |%15s |%12s |%13s |%15s |%15s|\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO DE VUELO", "TIPO DE PASAJERO", "ESTADO DE VUELO");
	printf("+-----+----------------+----------------+-------------+----------------+-----------------+---------------+\n");
}

int Passenger_printPassenger(LinkedList* pArrayListPassenger, int index)
{
	int retorno = -1;
	int id;
	char nombre[128];
	char apellido[128];
	float precio;
	int tipoPasajero;
	char auxTipoPasajero[128];
	char codigoVuelo[128];
	int estadoVuelo;
	char auxEstadoVuelo[128];
	Passenger* auxPasajero = NULL;

	if(pArrayListPassenger != NULL)
	{
		auxPasajero = (Passenger*)ll_get(pArrayListPassenger, index);
		Passenger_getId(auxPasajero, &id);
		Passenger_getNombre(auxPasajero, nombre);
		Passenger_getApellido(auxPasajero, apellido);
		Passenger_getPrecio(auxPasajero, &precio);
		Passenger_getCodigoVuelo(auxPasajero, codigoVuelo);
		Passenger_getTipoPasajero(auxPasajero, &tipoPasajero);
		Passenger_getEstadoVuelo(auxPasajero, &estadoVuelo);

		Passenger_TipoPasajeroAChar(tipoPasajero, auxTipoPasajero);
		Passenger_EstadoVueloAChar(estadoVuelo, auxEstadoVuelo);

		printf("|%4d |%15s |%15s |%12.2f |%15s |%16s |%15s|\n", id, nombre, apellido, precio, codigoVuelo, auxTipoPasajero, auxEstadoVuelo);
		retorno = 0;
	}
	return retorno;
}

int Passenger_TipoPasajeroAChar(int tipoPasajeroInt, char* tipoPasajero)
{
	int retorno = -1;

	switch(tipoPasajeroInt)
	{
		case 1:
			strcpy(tipoPasajero, "FirstClass");
			retorno = 0;
			break;
		case 2:
			strcpy(tipoPasajero, "ExecutiveClass");
			retorno = 0;
			break;
		case 3:
			strcpy(tipoPasajero, "EconomyClass");
			retorno = 0;
			break;
	}

	return retorno;
}

int Passenger_TipoPasajeroAInt(char* tipoPasajero)
{
	int auxTypePassenger;

	if(tipoPasajero != NULL)
	{
		if(stricmp(tipoPasajero, "FirstClass") == 0)
		{
			auxTypePassenger = 1;
		}
		else
		{
			if(stricmp(tipoPasajero, "ExecutiveClass") == 0)
			{
				auxTypePassenger = 2;

			}
			else
			{
				if(stricmp(tipoPasajero, "EconomyClass") == 0)
				{
					auxTypePassenger = 3;
				}
			}
		}
	}

	return auxTypePassenger;
}

int Passenger_EstadoVueloAChar(int estadoVueloInt, char* estadoVuelo)
{
	int retorno = -1;

	switch(estadoVueloInt)
	{
		case 1:
			strcpy(estadoVuelo, "En horario");
			retorno = 0;
			break;
		case 2:
			strcpy(estadoVuelo, "Aterrizado");
			retorno = 0;
			break;
		case 3:
			strcpy(estadoVuelo, "En vuelo");
			retorno = 0;
			break;
		case 4:
			strcpy(estadoVuelo, "Demorado");
			retorno = 0;
			break;
	}

	return retorno;
}

int Passenger_EstadoVueloAInt(char* estadoVuelo)
{
	int auxEstadoVuelo;

	if(estadoVuelo != NULL)
	{
		if(stricmp(estadoVuelo, "En horario") == 0)
		{
			auxEstadoVuelo = 1;

		}
		else
		{
			if(stricmp(estadoVuelo, "Aterrizado") == 0)
			{
				auxEstadoVuelo = 2;

			}
			else
			{
				if(stricmp(estadoVuelo, "En vuelo") == 0)
				{
					auxEstadoVuelo = 3;
				}
				else
				{
					if(stricmp(estadoVuelo, "Demorado") == 0)
					{
						auxEstadoVuelo = 4;
					}
				}
			}
		}
	}

	return auxEstadoVuelo;
}



int Passenger_setId(Passenger* this,int id)
{
	int retorno = -1;

	if(this != NULL && id > 0)
	{
		this->id = id;
		retorno = 0;
	}

	return retorno;
}

int Passenger_getId(Passenger* this,int* id)
{
	int retorno = -1;

	if(this != NULL && id != NULL)
	{
		*id = this->id;
		retorno = 0;
	}

	return retorno;
}

int Passenger_setNombre(Passenger* this,char* nombre)
{
	int retorno = -1;

	if(this != NULL && nombre != NULL)
	{
		strcpy(this->nombre, nombre);
		retorno = 0;
	}

	return retorno;
}

int Passenger_getNombre(Passenger* this,char* nombre)
{
	int retorno = -1;

	if(this != NULL && nombre != NULL)
	{
		strcpy(nombre, this->nombre);
		retorno = 0;
	}

	return retorno;
}

int Passenger_setApellido(Passenger* this,char* apellido)
{
	int retorno = -1;

	if(this != NULL && apellido != NULL)
	{
		strcpy(this->apellido, apellido);
		retorno = 0;
	}

	return retorno;
}

int Passenger_getApellido(Passenger* this,char* apellido)
{
	int retorno = -1;

	if(this != NULL && apellido != NULL)
	{
		strcpy(apellido, this->apellido);
		retorno = 0;
	}

	return retorno;
}

int Passenger_setPrecio(Passenger* this, float precio)
{
	int retorno = -1;

	if(this != NULL && precio > 0)
	{
		this->precio = precio;
		retorno=0;
	}

	return retorno;
}

int Passenger_getPrecio(Passenger* this, float* precio)
{
	int retorno = -1;

	if(this != NULL && precio > 0)
	{
		*precio = this->precio;
		retorno=0;
	}

	return retorno;
}

int Passenger_setTipoPasajero(Passenger* this, int tipoPasajero)
{
	int retorno = -1;

	if(this != NULL)
	{
		this->tipoPasajero = tipoPasajero;
		retorno = 0;
	}

	return retorno;
}

int Passenger_getTipoPasajero(Passenger* this, int* tipoPasajero)
{
	int retorno = -1;

	if(this != NULL && tipoPasajero != NULL)
	{
		*tipoPasajero = this->tipoPasajero;
		retorno = 0;
	}

	return retorno;
}

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo)
{
	int retorno = -1;

	if(this != NULL && codigoVuelo != NULL)
	{
		strcpy(this->codigoVuelo,codigoVuelo);
		retorno = 0;
	}

	return retorno;
}

int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo)
{
	int retorno = -1;

	if(this != NULL && codigoVuelo != NULL)
	{
		strcpy(codigoVuelo, this->codigoVuelo);
		retorno = 0;
	}

	return retorno;
}

int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo)
{
	int retorno = -1;

	if(this != NULL)
	{
		this->estadoVuelo = estadoVuelo;
		retorno=0;
	}

	return retorno;
}

int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo)
{
	int retorno = -1;

	if(this != NULL && estadoVuelo != NULL)
	{
		*estadoVuelo = this->estadoVuelo;
		retorno = 0;
	}

	return retorno;
}


