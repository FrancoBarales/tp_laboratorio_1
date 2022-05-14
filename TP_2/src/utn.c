/*
 * utn.c
 *
 *  Created on: 12 may. 2022
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


int mostrarMenuPrincipal(void)
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

int mostrarMenuModif(void)
{
	int opcion;
	printf("\n\nQue dato desea modificar?\n");
	printf("\n1.Nombre");
	printf("\n2.Apellido");
	printf("\n3.Precio de vuelo");
	printf("\n4.Codigo de vuelo");
	printf("\n5.Tipo de pasajero");
	printf("\n6.Estado del vuelo");
	printf("\n7.Salir\n");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Seleccione una opcion correcta.", 1, 7, 3);
	return opcion;
}

int mostrarMenuInformes(void)
{
	int opcion;
	printf("\n\nMenu de Informes\n");
	printf("1) Listado de pasajeros (por apellido y tipo de pasajero)\n");
	printf("2) Informe de Precios\n");
	printf("3) Listado de pasajeros (por Código de vuelo y estados de vuelos 'ACTIVOS')\n");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Opcion Incorrecta.", 1, 3, 3);
	return opcion;
}


int getInt(int *pResultado)
{
	int retorno = -1;
	char bufferString[50];
	if(pResultado != NULL && getString(bufferString, sizeof(bufferString)) == 0 && esNumerica(bufferString, sizeof(bufferString)))
	{
		retorno = 0;
		*pResultado = atoi(bufferString);
	}
	return retorno;
}


int utn_getNumero(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	do
	{
		printf("%s", mensaje);
		if (getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
		{
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}
		printf("%s", mensajeError);
		reintentos--;
	}while(reintentos >= 0);

	return retorno;
}

int getFloat(float *pResultado)
{
	int retorno = -1;
	char buffer[64];

	if (pResultado != NULL)
	{
		if (getString(buffer, sizeof(buffer)) == 0 && esFlotante(buffer))
		{
			*pResultado = atof(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

int utn_getNumeroFlotante(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;
	while (reintentos >= 0)
	{
		reintentos--;
		printf("%s", mensaje);
		if (getFloat(&bufferFloat) == 0)
		{
			if (bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

int getString(char *cadena, int len)
{
	int retorno = -1;
	char bufferString[4096];

	if (cadena != NULL && len > 0)
	{
		fflush(stdin);
		if (fgets(bufferString, sizeof(bufferString), stdin) != NULL)
		{
			if (bufferString[strnlen(bufferString, sizeof(bufferString)) - 1] == '\n')
			{
				bufferString[strnlen(bufferString, sizeof(bufferString)) - 1] = '\0';
			}
			if (strnlen(bufferString, sizeof(bufferString)) <= len)
			{
				strncpy(cadena, bufferString, len);
				retorno = 0;
			}
		}
	}
	return retorno;
}

int getCadena(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(getString(buffer, sizeof(buffer)) == 0 && esCadena(buffer, sizeof(buffer)) && strnlen(buffer, sizeof(buffer)) < longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

int utn_getCadena(char* pResultado, int lenMin, int lenMax, char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while (reintentos >= 0)
	{
		reintentos--;
		printf("%s", mensaje);
		if (getCadena(bufferString, sizeof(bufferString)) == 0 && strnlen(bufferString, sizeof(bufferString)) < lenMax && strnlen(bufferString, sizeof(bufferString)) > lenMin)
		{
			strncpy(pResultado, bufferString, lenMax);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

int getNombre(char* pResultado, int len)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL){
    	if(getString(buffer,sizeof(buffer)) == 0 && esNombre(buffer,sizeof(buffer)) && strnlen(buffer,sizeof(buffer)) < len)
    	{
    		strncpy(pResultado, buffer, len);
			retorno = 0;
		}
    }
    return retorno;
}

int utn_getNombre(char* pResultado, int lenMin, int lenMax, char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s", mensaje);
		if(getNombre(bufferString, sizeof(bufferString)) == 0 && strnlen(bufferString, sizeof(bufferString)) < lenMax && strnlen(bufferString, sizeof(bufferString)) > lenMin)
		{
			uppercaseInitial(bufferString);
			strncpy(pResultado, bufferString, lenMax);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

// PARA VALIDAR

int esNumerica(char *cadena, int len)
{
	int retorno = 1; // VERDADERO

	for (int i = 0; i < len && cadena[i] != '\0'; i++)
	{
		if (i == 0 && (cadena[i] == '+' || cadena[i] == '-'))
		{
			continue;
		}
		if (cadena[i] > '9' || cadena[i] < '0') {
			retorno = 0;
			break;
		}
	}
	return retorno;
}

int esFlotante(char *cadena)
{
	int retorno = 1;
	int contador = 0;

	if (cadena != NULL && strlen(cadena) > 0)
	{
		for (int i = 0; cadena[i] != '\0'; i++)
		{
			if (i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if (cadena[i] < '0' || cadena[i] > '9')
			{
				if (cadena[i] == '.' && contador == 0)
				{
					contador++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

int esCadena(char *cadena, int longitud)
{
	int retorno = 1;

	if (cadena != NULL && longitud > 0)
	{
		for (int i = 0; cadena[i] != '\0' && i < longitud; i++)
		{
			if ((cadena[i] < '0' || cadena[i] > '9') && (cadena[i] < 'A' || cadena[i] > 'Z') && (cadena[i] < 'a' || cadena[i] > 'z'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


int esNombre(char *cadena, int len)
{
	int retorno = 1;

	if (cadena != NULL && len > 0)
	{
		for (int i = 0; cadena[i] != '\0' && i < len; i++)
		{
			if ((cadena[i] < 'A' || cadena[i] > 'Z') && (cadena[i] < 'a' || cadena[i] > 'z'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


// MINUSCULA Y MAYUSCULA

void strEnMayuscula(char string[])
{
	int i = 0;
	while (string[i] != '\0')
	{
		string[i] = toupper(string[i]);
		i++;
	}
}

void strEnMinuscula(char string[])
{
	int i = 0;
	while (string[i] != '\0')
	{
		string[i] = tolower(string[i]);
		i++;
	}
}

void uppercaseInitial(char string[])
{
	int cantidad;

	strEnMinuscula(string);
	string[0] = toupper(string[0]);
	cantidad = strlen(string);

	for (int i = 0; i < cantidad; i++)
	{
		if (string[i] == ' ')
		{
			string[i + 1] = toupper(string[i + 1]);
		}
	}
	puts(string);
}

// PARA REALIZAR CALCULOS E INFORMES

float sumatoriaPrecio(Passenger *list, int len)
{
	float suma = 0;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty != VACIO)
			{
				suma += list[i].price;
			}
		}
	}
	return suma;
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

float calculateAverage(float suma, int cantidad)
{
	float promedio = 0;
	if (cantidad > 0)
	{
		promedio = suma / cantidad;
	}
	return promedio;
}

int aboveAverage(Passenger *list, int len, float promedio)
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
	int aboveAvgPassenger;
	int amountOfPassengers;
	float suma;
	float promedio;
	if (list != NULL && len > 0)
	{
		suma = sumatoriaPrecio(list, len);
		amountOfPassengers = cantidadPasajerosActivo(list, len);
		promedio = calculateAverage(suma, amountOfPassengers);

		printf("\nEl total de los pasajes fue: $%.2f.", suma);
		printf("\nEl precio promedio de los pasajes es: $%.2f.", promedio);
		if (promedio > 0)
		{
			aboveAvgPassenger = aboveAverage(list, len, promedio);
			printf("\nHay %d pasajeros que superan el precio promedio.",aboveAvgPassenger);
		}
		retorno = 0;
	}
	return retorno;
}

int informeFlyCodeAndStatus(Passenger *list, int len)
{
	int retorno = -1;

	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty != VACIO && list[i].statusFlight == ACTIVO)
			{
				showPassengerData(list[i]);
			}
		}
		retorno = 0;
	}
	return retorno;
}

