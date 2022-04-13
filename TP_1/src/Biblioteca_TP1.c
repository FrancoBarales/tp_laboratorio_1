/*
 * Biblioteca_TP1.c
 *
 *  Created on: 11 abr. 2022
 *      Author: Franco Barales
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

float calcularDiferencia(float operador1, float operador2){
	float resultado;

	resultado = operador1 - operador2;
	if(resultado < 0){
		resultado = resultado * -1;
	}

	return resultado;
}

float multiplicar(float precio, float porcentaje){
	float resultado;

	resultado = precio * porcentaje;

	return resultado;
}

float dividir(float precio, float dividendo){
	float resultado;

	resultado = precio / dividendo;

	return resultado;
}

void mostrarAerolineas(float precio, float debito, float credito, float bitcoin, float precioUnitario){
	printf("\nPrecio Aerolineas: %.2f", precio);
	printf("\na) Precio con tarjeta de d�bito: $%.2f", debito);
	printf("\nb) Precio con tarjeta de cr�dito: $%.2f", credito);
	printf("\nc) Precio pagando con bitcoin : %f BTC", bitcoin);
	printf("\nd) Mostrar precio unitario: $%.2f", precioUnitario);
}

void mostrarLatam(float precio, float debito, float credito, float bitcoin, float precioUnitario){
	printf("\n\nPrecio Latam: %.2f", precio);
	printf("\na) Precio con tarjeta de d�bito: $%.2f", debito);
	printf("\nb) Precio con tarjeta de cr�dito: $%.2f", credito);
	printf("\nc) Precio pagando con bitcoin : %f BTC", bitcoin);
	printf("\nd) Mostrar precio unitario: $%.2f", precioUnitario);
}





