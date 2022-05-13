/*
 * utn.h
 *
 *  Created on: 12 may. 2022
 *      Author: Franco
 */

#ifndef UTN_H_
#define UTN_H_

int mostrarMenuPrincipal(void);

int mostrarMenuModif(void);

int mostrarMenuInformes(void);

int getInt(int *pResultado);

int utn_getNumero(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int reintentos);

int getFloat(float *pResultado);

int utn_getNumeroFlotante(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int reintentos);

int getString(char *cadena, int len);

int getCadena(char* pResultado, int longitud);

int utn_getCadena(char *pResultado, int longitud, char *mensaje, char *mensajeError, int reintentos);

int getNombre(char* pResultado, int longitud);

int utn_getNombre(char* pResultado, int longitud, char* mensaje, char* mensajeError, int reintentos);

int esNumerica(char *cadena, int len);

int esFlotante(char *cadena);

int esCadena(char *cadena, int longitud);

int esNombre(char *cadena, int len);

void strEnMayuscula(char cadena[]);

void strEnMinuscula(char cadena[]);

void uppercaseInitial(char string[]);

float sumatoriaPrecio(Passenger *list, int len);

int cantidadPasajerosActivo(Passenger *list, int len);

float calculateAverage(float suma, int cantidad);

int aboveAverage(Passenger *list, int len, float promedio);

int informePrecios(Passenger *list, int len);

int informeFlyCodeAndStatus(Passenger *list, int len);


#endif /* UTN_H_ */
