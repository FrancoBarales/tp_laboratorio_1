/*
 ============================================================================
 Name        : TP_1.c
 Author      : Franco Barales Illia
 Version     : 1.1
 Copyright   : Your copyright notice
 Description : Trabajo Practico N?1 - Laboratorio 1 - UTN FRA 2022
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionesGet.h"
#include "funcionesMath.h"
#include "funcionesPrint.h"

#define TRUE 1
#define FALSE 0

int main(void){
	setbuf(stdout, NULL);

	int opcion;
	int flag1 = FALSE;
	int flag2 = FALSE;
	int flag3 = FALSE;
	float kilometros = 0;
	float precioAerolineas = 0;
	float precioAerolineasDebito, precioAerolineasCredito, precioAerolineasEnBitcoin, precioUnidadAerolineas;
	float precioLatam = 0;
	float precioLatamDebito, precioLatamCredito, precioLatamEnBitcoin, precioUnidadLatam;
	float diferencia = 0;

	do{
		opcion = menu();
		switch(opcion){
			case 1:
				getFloat(&kilometros, "\nIngresar cantidad de kilometros: ", "Error. cantidad de kilometros invalida.", 100000, 100, 5);
				flag1 = TRUE; // si se ingresaron correctamente los kilometros, se levanta la primera flag.
				break;
			case 2:
				getFloat(&precioAerolineas, "\nIngresar precio del pasaje de Aerolineas: ", "Error. Precio invalido. ", 10000000, 20000, 5);
				getFloat(&precioLatam, "\nIngresar precio del pasaje de Latam: ", "Error. Precio invalido. ", 10000000, 20000, 5);
				flag2 = TRUE; // si se ingresaron correctamente los precios, se levanta la segunda flag.
				break;
			case 3:
				if(flag1 == TRUE && flag2 == TRUE){
					precioAerolineasDebito = multiplicar(precioAerolineas, 0.9); // precio con Debito para Aerolineas
					precioAerolineasCredito = multiplicar( precioAerolineas, 1.25); // precio con Credito para Aerolineas
					precioAerolineasEnBitcoin = dividir(precioAerolineas, 4606954.55); // precio en Bitcoin para Aerolineas
					precioUnidadAerolineas = dividir(precioAerolineas, kilometros); // precio unitario de Aerolineas
					precioLatamDebito = multiplicar(precioLatam, 0.9); // precio con Debito para Latam
					precioLatamCredito = multiplicar(precioLatam, 1.25); // precio con Credito para Latam
					precioLatamEnBitcoin = dividir(precioLatam, 4606954.55); // precio en Bitcoin para Latam
					precioUnidadLatam = dividir(precioLatam, kilometros); // precio unitario Latam
					diferencia = calcularDiferencia(precioLatam, precioAerolineas); // diferencia de precio entre pasajes de Aerolineas y Latam
					flag3 = TRUE;
					printf("Calculos Realizados.\n");
				}
				else if(flag1 == TRUE && flag2 == FALSE){ // si no se ingresaron correctamente los precios, aparece el siguiente mensaje de error.
					printf("ERROR: Faltan ingresar los precios de los vuelos.\n");
				}
				else if(flag1 == FALSE && flag2 == TRUE){ // si no se ingresaron correctamente los kilometros, aparece el siguiente mensaje de error.
					printf("ERROR: Faltan ingresar los kilometros.\n");
				}
				else{ // si precios y kilometros se ingresaron incorrectamente, aparece el siguiente mensaje de error.
					printf("ERROR: Faltan ingresar los kilometros y los precios de los vuelos.\n");
				}
				system("pause");
				break;
			case 4:
				if(flag3 == TRUE){
					printf("\nKMs Ingresados: %.2f km\n", kilometros);
					mostrarAerolineas(precioAerolineas, precioAerolineasDebito, precioAerolineasCredito, precioAerolineasEnBitcoin, precioUnidadAerolineas);
					mostrarLatam(precioLatam, precioLatamDebito, precioLatamCredito, precioLatamEnBitcoin, precioUnidadLatam);
					printf("\n\nLa diferencia de precio es : %.2f\n\n", diferencia);
				}
				else if(flag1 == FALSE || flag2 == FALSE){
					printf("ERROR: No estan ingresados todos los datos necesarios (Opcion 1 y 2 / Opcion 5).\n");
				}
				else if(flag3 == FALSE){
					printf("ERROR: No estan calculados los costos (Opcion 3).\n");
				}
				system("pause");
				break;
			case 5:
				kilometros = 7090;
				flag1 = TRUE;
				precioAerolineas= 162965;
				precioLatam = 159339;
				flag2 = TRUE;
				printf("Carga forzada de datos completada.\n");
				system("pause");
				break;
		}
	}while(opcion != 6);

	printf("Fin del programa...\n");
	system("pause");

	return EXIT_SUCCESS;
}
