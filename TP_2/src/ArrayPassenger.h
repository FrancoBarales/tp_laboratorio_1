/*
 * ArrayPassenger.h
 *
 *  Created on: 3 may. 2022
 *      Author: Franco
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_

struct
{
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flycode[10];
	int typePassenger;
	int statusFlight;
	int isEmpty;
}typedef Passenger;

/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initPassengers(Passenger* list, int len);

/** \brief add in a existing list of passengers the values received as parameters
* in the first empty position
* \param list passenger*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param price float
* \param typePassenger int
* \param statusFlight int
* \param flycode[] char
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok*/

int addPassenger(Passenger *list, int len, int id, char name[], char lastName[], float price, int typePassenger, int statusFlight, char flycode[]);

/** \brief loads the passenger data to the list.
* \param list passenger*
* \param len int
* \param contadorId int
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/

int loadPassenger(Passenger *list, int len, int contadorId);

/** \brief find a Passenger by Id en returns the index position in array.
*
* \param list Passenger*
* \param len int
* \param id int
* \return Return passenger index position or (-1) if [Invalid length or
NULL pointer received or passenger not found]
*/

int findPassengerById(Passenger* list, int len,int id);

/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
*
* \param list Passenger*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*/

int removePassenger(Passenger* list, int len, int id);

/** \brief Remove a Passenger from the list
*
* \param list Passenger*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*/

int deletePassenger(Passenger *list, int len);

/** \brief Sort the elements in the array of passengers, the argument order
indicate UP or DOWN order
*
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/

int sortPassengers(Passenger* list, int len, int order);

/** \brief print the list header
*
* \return void
*/

void printListHeader(void);

/** \brief print the content of passengers array
*
* \param list Passenger*
* \param length int
* \return int
*/

int printPassenger(Passenger *list, int length);

/** \brief To modify the passenger data in a list index
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \param contadorId int Id number
* \return int Return (-1) if Error - (0) if Ok
*/

int modifyPassenger(Passenger *list, int len);

/** \brief loads a preselected set of passengers, each with
* its own unique data to the list array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error - (0) if Ok
*/

int cargaForzada(Passenger* list, int len, int* contadorId);

/** \brief Convierte el tipo de pasajero de un int a un string
 *
 * \param tipoPasajeroInt int
 * \param tipoPasajero char*
 * \return Retorna 0 si el proceso se realizo con exito, o -1 si hubo un error.
 */
int tipoPasajeroAChar(int tipoPasajeroInt, char* tipoPasajero);

/** \brief Convierte el estado de vuelo de un int a un string
 *
 * \param estadoVueloInt int
 * \param estadoVuelo char*
 * \return Retorna 0 si el proceso se realizo con exito, o -1 si hubo un error.
 */
int estadoVueloAChar(int estadoVueloInt, char* estadoVuelo);



#endif /* ARRAYPASSENGER_H_ */
