/*
 * UTN3.h
 *
 *  Created on: 29 abr. 2022
 *      Author: rodri
 */

#ifndef UTN4_H_
#define UTN4_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int utn_getInt(char mensaje[], char mensajeError[], int minimo, int maximo,
		int reintentos, int *pResultado); //getInt pero con reintentos y mensajes
int myGets(char pResultado[], int length); //o getString, toma cualquier input de fgets, removiendo enter y limitado por length
int getInt(int *pNumeroTomado); //revisa que sea int, usa myGets e isInt
int isInt(char arrayPosiblesNumeros[]); //revisa que el string obtenido sea Int, contempla signo "-", usa atoi.

//utn_getString ambas dependen de getString que corrige última posición de enter de fgets
int utn_getStringWONum(char *mensaje, char *mensajeError, int reintentos,
		int longitud, char *pResultado); //usa myGets pero falla si contiene números (usa allChars)
int utn_getStringWNum(char *mensaje, char *mensajeError, int reintentos,
		int longitud, char *pResultado); //usa myGets, devuelve string, agrega mensajes y reintentos
int allChars(char *cadena, int longitud); //verifica que el contenido de fgets sean todos caracteres, ningún número

int getFloat(float *pFloatTomado); //utiliza myGets y esFloat, devuelve float usando atof
int esFloat(char cadena[]); //verifica que sea float, revisando un solo punto y contemplando inicio con + o -
int utn_getFloat(float *pResultado, char mensaje[], char mensajeError[],
		float minimo, float maximo, int reintentos); //getFloat con reintentos y mensajes

int utn_getChar(char *mensaje, char *mensajeError, int reintentos,
		char *pResultado); //myGets limitado a length=1, devuelve un char

int getValidChar(char mensaje[], char mensajeError[], char charsValidos[],
		int reintentos, char *pResultado);

int utn_getStringWONumFirstUpper(char *mensaje, char *mensajeError, int reintentos,
		int longitud, char *pResultado);

int printMenuGetOption(char title[], char content[], char mensajeError[], int reintentos, int cantOpciones);
int valid_siNo(char mensaje[], char mensajeError[], int reintentos);

int utn_getShortInt(char mensaje[], char mensajeError[], int minimo, int maximo,
		int reintentos, short int *pResultado);

int getShortInt(short int *pNumeroTomado);

int utn_getEmail(char *mensaje, char *mensajeError, int reintentos, int longitud, char *pResultado);
int getEmail(char *pResultado, int longitud);
int esEmail(char cadena[],int longitud);


#endif /* UTN4_H_ */
