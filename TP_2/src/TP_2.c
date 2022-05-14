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

#define TRUE 1
#define FALSE 0
#define LEN_LIST_PASSENGERS 2000
#define LENSTATUS 3

int main(void) {
	setbuf(stdout, NULL);

	int auxID;
	int opcion;
	int orden;
	int opcionSubMenu;
	int flag1 = FALSE;
	int flag2 = FALSE;
	Passenger listaDePasajeros[LEN_LIST_PASSENGERS];

	initPassengers(listaDePasajeros, 2000);
	do
	{
		opcion = mostrarMenuPrincipal();
		switch (opcion)
		{
			case 1:
				loadPassengerData(listaDePasajeros, LEN_LIST_PASSENGERS);
				flag1 = TRUE;
				break;
			case 2:
				if (flag1 == FALSE)
				{
					printf("ERROR. No hay usuarios ingresados. (Opcion 1 o 5)\n");
				}
				else
				{
					modifyPassenger(listaDePasajeros, LEN_LIST_PASSENGERS);
				}
				break;
			case 3:
				if(flag1 == FALSE)
				{
					printf("ERROR. No hay usuarios ingresados. (Opcion 1 o 5)\n");
				}
				else
				{
					printPassenger(listaDePasajeros, LEN_LIST_PASSENGERS);
					utn_getNumero(&auxID,"\nIngrese el ID del pasajero que desea eliminar: ","\nERROR. ID no encontrado. ", 5000, 7000, 3);
					removePassenger(listaDePasajeros, LEN_LIST_PASSENGERS, auxID);
				}
				break;
			case 4:
				if(flag1 == FALSE)
				{
					printf("ERROR. No hay datos ingresados. (Opcion 1 o 5)\n");
				}
				else
				{
					opcionSubMenu = mostrarMenuInformes();
					switch(opcionSubMenu)
					{
						case 1:
							utn_getNumero(&orden,"Que ordenamiento desea? (-1.Ascedente 1.Descendente): ", "\nOpcion Incorrecta\n. ",-1,1,3);
							sortPassengers(listaDePasajeros, LEN_LIST_PASSENGERS, orden);
							break;
						case 2:
							informePrecios(listaDePasajeros,LEN_LIST_PASSENGERS);
							break;
						case 3:
							informeFlyCodeAndStatus(listaDePasajeros,LEN_LIST_PASSENGERS);
							break;
					}
				}
				break;
			case 5:
				if(flag2 == FALSE)
				{
					cargaForzada(listaDePasajeros, LEN_LIST_PASSENGERS);
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
	}while (opcion != 6);

	printf("\nPrograma terminado.");
	return 0;
}
