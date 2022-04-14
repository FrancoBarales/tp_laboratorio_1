/*
 * funcionesPrint.c
 *
 *  Created on: 14 abr. 2022
 *      Author: Franco
 */

#include <stdio.h>
#include <stdlib.h>

void mostrarAerolineas(float precio, float debito, float credito, float bitcoin, float precioUnitario){
	printf("\nPrecio Aerolineas: %.2f", precio);
	printf("\na) Precio con tarjeta de débito: $%.2f", debito);
	printf("\nb) Precio con tarjeta de crédito: $%.2f", credito);
	printf("\nc) Precio pagando con bitcoin : %f BTC", bitcoin);
	printf("\nd) Mostrar precio unitario: $%.2f", precioUnitario);
}

void mostrarLatam(float precio, float debito, float credito, float bitcoin, float precioUnitario){
	printf("\n\nPrecio Latam: %.2f", precio);
	printf("\na) Precio con tarjeta de débito: $%.2f", debito);
	printf("\nb) Precio con tarjeta de crédito: $%.2f", credito);
	printf("\nc) Precio pagando con bitcoin : %f BTC", bitcoin);
	printf("\nd) Mostrar precio unitario: $%.2f", precioUnitario);
}
