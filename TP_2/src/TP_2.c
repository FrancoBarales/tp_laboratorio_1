/*
 ============================================================================
 Name        : TP_2.c
 Author      : Franco Barales Illia
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayPassenger.h"
#include "utn.h"
#include "miBiblioteca.h"

#define TRUE 1
#define FALSE 0
#define LEN_LIST 2000

int main(void) {
	setbuf(stdout, NULL);

	int contadorId = 0;
	int opcion;
	int flag1 = FALSE;
	int flag2 = FALSE;
	Passenger listaDePasajeros[LEN_LIST];

	initPassengers(listaDePasajeros, LEN_LIST);
	do
	{
		opcion = menu_principal();
		switch (opcion)
		{
			case 1:
				if(buscarEspacioVacio(listaDePasajeros, LEN_LIST) != -1)
				{
					contadorId++;
					contadorId = loadPassenger(listaDePasajeros, LEN_LIST, contadorId);
					flag1 = TRUE;
				}
				else
				{
					printf("\nERROR. No hay mas espacio para nuevos pasajeros.\n");
				}
				break;
			case 2:
				if(flag1 == FALSE || comprobacionListaVacia(listaDePasajeros, LEN_LIST) == 0)
				{
					printf("ERROR. No hay usuarios ingresados. (Opcion 1 o 5)\n");
				}
				else
				{
					modifyPassenger(listaDePasajeros, LEN_LIST);
				}
				break;
			case 3:
				if(flag1 == FALSE || comprobacionListaVacia(listaDePasajeros, LEN_LIST) == 0)
				{
					printf("ERROR. No hay usuarios ingresados. (Opcion 1 o 5)\n");
				}
				else
				{
					printListHeader();
					printPassenger(listaDePasajeros, LEN_LIST);
					deletePassenger(listaDePasajeros, LEN_LIST);
				}
				break;
			case 4:
				if(flag1 == FALSE || comprobacionListaVacia(listaDePasajeros, LEN_LIST) == 0)
				{
					printf("ERROR. No hay datos ingresados. (Opcion 1 o 5)\n");
				}
				else
				{
					informePrecios(listaDePasajeros, LEN_LIST);
				}
				break;
			case 5:
				if(flag2 == FALSE)
				{
					cargaForzada(listaDePasajeros, LEN_LIST, &contadorId);
					contadorId += 5;
					printf("Carga forzada realizada exitosamente.\n");
					flag1 = TRUE;
					flag2 = TRUE;
				}
				else
				{
					printf("\nLa carga forzada ya fue realizada.\n");
				}
				break;
		}
	}while(opcion != 6);

	printf("\nPrograma terminado.");
	return 0;
}
