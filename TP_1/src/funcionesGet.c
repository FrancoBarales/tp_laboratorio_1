/*
 * funcionesGet.c
 *
 *  Created on: 14 abr. 2022
 *      Author: Franco Barales Illia
 */

#include <stdio.h>
#include <stdlib.h>

int menu(void)
{
	int opcion;
	printf("Menu de Opciones\n");
	printf("\n1) Ingresar kilometros");
	printf("\n2) Ingresar Precio de Vuelos");
	printf("\n3) Calcular todos los costos");
	printf("\n4) Informar Resultados");
	printf("\n5) Carga forzada de datos");
	printf("\n6) Salir");
	printf("\n\nElegir opcion: ");
	scanf("%d", &opcion);
	return opcion;
}

float getFloat(float * pNumero, char * mensaje, char * mensajeError, float maximo, float minimo, float reintentos){
	int auxNumero;
	int retorno;
	retorno = -1;

	if(pNumero != NULL && maximo >= minimo){
		do{
			printf("%s", mensaje);
			scanf("%d", &auxNumero);
			reintentos--;
			if(auxNumero >= minimo && auxNumero <= maximo){
				*pNumero = auxNumero;
				retorno = 0;
				break;
			}
			else{
				printf("%s", mensajeError);
			}
		}while(reintentos > 0);
	}
	return retorno;
}
