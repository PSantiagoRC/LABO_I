/*
 * Librería básica para Inputs
 */

#include "UTN4.h"


int printMenuGetOption(char title[], char content[], char mensajeError[], int reintentos, int cantOpciones){
	/// @fn int printMenu(char[], char[], char[], int, int)
	/// @param title
	/// @param content
	/// @param mensajeError
	/// @param reintentos
	/// @param cantOpciones
	/// @return
	///
	/// Imprime menu y obtiene opción escogida por el usuario como retorno.

	int opcion = -1;

	if(title != NULL && content != NULL && reintentos >0 && cantOpciones >0){
		printf("\n%s", title);
		printf("%s", content);
		utn_getInt("Ingrese selección:\n", mensajeError, 1, cantOpciones, reintentos, &opcion);
	}
	return opcion;
}

int valid_siNo(char mensaje[], char mensajeError[], int reintentos){
	int opcion = -1;
	char bufferChar;
	int ret_validChar;

	if(mensaje != NULL && mensajeError != NULL && reintentos >0){
		ret_validChar = getValidChar(mensaje, mensajeError, "SsNn", reintentos, &bufferChar);
		if(ret_validChar == 0){
			if(bufferChar == 'S' || bufferChar == 's')
			{
				opcion = 1;
			}else{
				if(bufferChar == 'N' || bufferChar == 'n')
				{
					opcion = 0;
				}
			}
		}
	}
	return opcion;
}

int getValidChar(char mensaje[], char mensajeError[], char charsValidos[],
		int reintentos, char *pResultado) {
	/// @fn int utn_getValidChars(char[], char[], char[], int, char*)
	/// @param mensaje
	/// @param mensajeError
	/// @param charsValidos
	/// @param reintentos
	/// @param pResultado
	/// @return
	///
	/// Recibe mensaje para pedido, mensaje de error y caracteres válidos (deben escribirse tanto en MAY como en MIN)
	/// Devuelve el CHAR validado, asignado a una dirección de memoria, y -1 de ret (error) o 0 si está OK.
	int retorno = -1;
	char bufferChar;
	int retorno_myGets;

	if (mensaje != NULL && mensajeError != NULL && pResultado != NULL
			&& reintentos > 0) {
		printf("%s", mensaje);
		retorno_myGets = myGets(&bufferChar, 1);
		do {
			if (retorno_myGets == -1 || strchr(charsValidos, bufferChar) == NULL) {
				printf("%s", mensajeError);
				reintentos--;
				printf("Quedan %d reintentos.\n", reintentos);
				printf("%s", mensaje);
				retorno_myGets = myGets(&bufferChar, 1);
			} else {
				reintentos = 0;
				*pResultado = bufferChar;
				retorno = 0;
			}
		} while (reintentos > 0);
	}
	return retorno;
}

int utn_getInt(char mensaje[], char mensajeError[], int minimo, int maximo,
		int reintentos, int *pResultado) {
	/// @fn int utn_getInt(char[], char[], int, int, int, int*)
	/// @param mensaje
	/// @param mensajeError
	/// @param minimo
	/// @param maximo
	/// @param reintentos
	/// @param pResultado
	/// @return
	///
	/// Utiliza getInt, agrega control por minimo y maximo, reintentos y mensajes
	int retorno = -1;
	int bufferInt;
	int retorno_getInt;

	if (mensaje != NULL && minimo <= maximo && mensajeError != NULL
			&& pResultado != NULL && reintentos > 0) {
		printf("%s", mensaje);
		retorno_getInt = getInt(&bufferInt);
		do {
			if (retorno_getInt == -1 || bufferInt > maximo
					|| bufferInt < minimo) {
				printf("%s", mensajeError);
				reintentos--;
				printf("Quedan %d reintentos.", reintentos);
				printf("%s", mensaje);
				retorno_getInt = getInt(&bufferInt);
			} else {
				reintentos = 0; //funciona como break
				*pResultado = bufferInt;
				retorno = 0;
			}
		} while (reintentos > 0);
	}
	return retorno;
}

int getInt(int *pNumeroTomado) {
	/// @fn int getInt(int*)
	/// @param pNumeroTomado
	/// @return
	///
	/// Utiliza myGets, verifica que el string obtenido es Int, aplica ATOI.

	int retorno = -1;
	char bufferNum[200];

	if (myGets(bufferNum, sizeof(bufferNum)) == 0 && isInt(bufferNum) == 0) {
		*pNumeroTomado = atoi(bufferNum);
		retorno = 0;
	}
	return retorno;
}

int getShortInt(short int *pNumeroTomado) {
	/// @fn int getInt(int*)
	/// @param pNumeroTomado
	/// @return
	///
	/// Utiliza myGets, verifica que el string obtenido es Int, aplica ATOI.

	int retorno = -1;
	char bufferNum[200];

	if (myGets(bufferNum, sizeof(bufferNum)) == 0 && isInt(bufferNum) == 0) {
		*pNumeroTomado = atoi(bufferNum);
		retorno = 0;
	}
	return retorno;
}

int isInt(char cadena[]) {
	/// @fn int isInt(char[])
	/// @param cadena
	/// @return
	///
	/// Revisa que sea un número entre 0 y 9. Valida último caracter \n al igual que myGets.

	int retorno = 0;
	int i;

	if (cadena != NULL) {
		i = 0;

		if (cadena[strlen(cadena) - 1] == '\n') {
			cadena[strlen(cadena) - 1] = '\0'; //Porque toma el "enter" como último caracter.
		}
		if (cadena[0] == '-') {
			i++; // Para que empiece el while en 2da posición a chequear que sean todos números (luego de pasar el signo menos)
		}
		while (cadena[i] != '\0') {
			if (cadena[i] < '0' || cadena[i] > '9') {
				retorno = -1;
				break;
			}
			i++;
		}
	} else {
		retorno = -1;
	}
	return retorno;
}

int myGets(char pResultado[], int length) {
	int retorno = -1;
	/// @fn int myGets(char[], int)
	/// @param pResultado
	/// @param length
	/// @return
	///
	/// Aplica fgets, limita en length, sustituye último enter.

	char bufferString[1020];

	if (pResultado != NULL && length > 0) {
		if (fgets(bufferString, sizeof(bufferString), stdin) != NULL) {
			if (bufferString[strnlen(bufferString,sizeof(bufferString)) - 1] == '\n') {
				bufferString[strnlen(bufferString,sizeof(bufferString)) - 1] = '\0';
			}
			if (strnlen(bufferString, sizeof(bufferString)) <= length) {
				strncpy(pResultado, bufferString, length);
				retorno = 0;
			}
		}
	}
	return retorno;
}

int get_allChars(char *pResultado, int longitud) {
	/// @fn int get_allChars(char*, int)
	/// @param pResultado
	/// @param longitud
	/// @return

	int retorno = -1;
	char buffer[4096];

	if (pResultado != NULL) {
		if (myGets(buffer, sizeof(buffer)) == 0
				&& allChars(buffer, sizeof(buffer))
				&& strnlen(buffer, sizeof(buffer)) < longitud) {
			strncpy(pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}

int allChars(char *cadena, int longitud) {
	/// @fn int allChars(char*, int)
	/// @param cadena
	/// @param longitud
	/// @return
	///
	/// Recibe cadena, verifica que cada componente sea caracter, no número.

	int i = 0;
	int retorno = 1;

	if (cadena != NULL && longitud > 0) {
		for (i = 0; cadena[i] != '\0' && i < longitud; i++) {
			if ((cadena[i] < 'A' || cadena[i] > 'Z')
					&& (cadena[i] < 'a' || cadena[i] > 'z')
					&& cadena[i] != ' '
					&& cadena[i] != '-'
					&& cadena[i] != 'Á'
					&& cadena[i] != 'É'
					&& cadena[i] != 'Í'
					&& cadena[i] != 'Ó'
					&& cadena[i] != 'Ú'
					&& cadena[i] != 'á'
					&& cadena[i] != 'é'
					&& cadena[i] != 'í'
					&& cadena[i] != 'ó'
					&& cadena[i] != 'ú') {
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int utn_getStringWONum(char *mensaje, char *mensajeError, int reintentos,
		int longitud, char *pResultado) {
	/// @fn int utn_getStringWONum(char*, char*, int, int, char*)
	/// @param mensaje
	/// @param mensajeError
	/// @param reintentos
	/// @param longitud
	/// @param pResultado
	/// @return

	char bufferString[4096];
	int retorno = -1;
	while (reintentos >= 0) {
		reintentos--;
		printf("%s", mensaje);
		if (get_allChars(bufferString, sizeof(bufferString)) == 0
				&& strnlen(bufferString, sizeof(bufferString)) < longitud) {
			strncpy(pResultado, bufferString, longitud);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

int utn_getStringWONumFirstUpper(char *mensaje, char *mensajeError, int reintentos,
		int longitud, char *pResultado) {
	/// @fn int utn_getStringWONum(char*, char*, int, int, char*)
	/// @param mensaje
	/// @param mensajeError
	/// @param reintentos
	/// @param longitud
	/// @param pResultado
	/// @return
	///
	/// Verifica que la primera letra sea mayúscula

	char bufferString[4096];
	int retorno = -1;
	while (reintentos >= 0) {
		reintentos--;
		printf("%s", mensaje);
		if (get_allChars(bufferString, sizeof(bufferString)) == 0
				&& strnlen(bufferString, sizeof(bufferString)) < longitud && bufferString[0]>='A' && bufferString[0]<='Z') {
			strncpy(pResultado, bufferString, longitud);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

int utn_getStringWNum(char *mensaje, char *mensajeError, int reintentos,
		int longitud, char *pResultado) {
	/// @fn int utn_getStringWNum(char*, char*, int, int, char*)
	/// @param mensaje
	/// @param mensajeError
	/// @param reintentos
	/// @param longitud
	/// @param pResultado
	/// @return
	///
	/// Equivalente a myGets pero con mensajes y reintentos.

	char bufferString[4096];
	int retorno = -1;
	while (reintentos >= 0) {
		reintentos--;
		printf("%s", mensaje);
		if (myGets(bufferString, sizeof(bufferString)) == 0 && strnlen(bufferString, sizeof(bufferString)) < longitud) {
			strncpy(pResultado, bufferString, longitud);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

int utn_getFloat(float *pResultado, char mensaje[], char mensajeError[],
		float minimo, float maximo, int reintentos) {
	/// @fn int utn_getFloat(float*, char[], char[], float, float, int)
	/// @param pResultado
	/// @param mensaje
	/// @param mensajeError
	/// @param minimo
	/// @param maximo
	/// @param reintentos
	/// @return
	///
	/// Recibe mensaje, mensaje de error, minimo, maximo y reintentos. LLama a getFloat, verifica que esté en rango, asigna a dirección de memoria.
	int retorno = -1;
	float bufferFloat;
	int retorno_getFloat;

	if (mensaje != NULL && minimo < maximo && mensajeError != NULL
			&& pResultado != NULL && reintentos > 0) {
		printf("%s", mensaje);
		do {
			retorno_getFloat = getFloat(&bufferFloat);
			if (retorno_getFloat == -1 || bufferFloat > maximo
					|| bufferFloat < minimo) {
				printf("%s", mensajeError);
				reintentos--;
				printf("Quedan %d reintentos.", reintentos);
			} else {
				reintentos = 0;
				*pResultado = bufferFloat;
				retorno = 0;
			}
		} while (reintentos > 0);
	}
	return retorno;
}

int getFloat(float *pFloatTomado) {
	/// @fn int getFloat(float*)
	/// @param pFloatTomado
	/// @return
	///
	/// Llama a myGets para pedir un string, analiza que sea float. En caso de que sea, lo asigna a dirección de memoria.
	int retorno = -1;
	char bufferString[200];

	if (myGets(bufferString, sizeof(bufferString)) == 0
			&& esFloat(bufferString) == 0) {
		*pFloatTomado = atof(bufferString);
		retorno = 0;
	}
	return retorno;
}

int esFloat(char cadena[]) {
	/// @fn int esFloat(char[])
	/// @param cadena
	/// @return
	///
	/// Recibe cadena, verifica que sea float (un solo punto, caracteres entre 0 y 9, puede empezar con + o -.
	///
	int retorno = 0; //favorable
	int i = 0;
	int contadorPuntos = 0;

	if (cadena[0] == '+' || cadena[0] == '-') { //Permitimos que inicie con + o -
		i++;
	}
	while (cadena[i] != '\0' ) //No hay nada menor a cero en ASCII?
	{
		if((cadena[i]<'0'||cadena[i]>'9')&&cadena[i]!='.')
		{
			retorno = -1;
			puts("Error, no es un número.");
			break;
		}
		if (cadena[i] == '.') {
			contadorPuntos++;
		}
		if (contadorPuntos > 1) {
			retorno = -1; //error
			puts("Error: más de un punto en número.");
			break;
		}
		i++;
	}
	return retorno;
}

int utn_getChar(char mensaje[], char mensajeError[], int reintentos,
		char *pResultado) {
	/// @fn int utn_getChar(char*, char*, int, char*)
	/// @param mensaje
	/// @param mensajeError
	/// @param reintentos
	/// @param pResultado
	/// @return
	///
	/// Llama a la función get_AllChars, que pide un string y verifica que todos sus componentes sean letras.
	/// Verifica que la longitud sea 1, es decir, un caracter individual.
	///
	char bufferString[128];
	int retorno = -1;
	while (reintentos >= 0) {
		reintentos--;
		printf("%s", mensaje);
		if (get_allChars(bufferString, sizeof(bufferString)) == 0
				&& strnlen(bufferString, sizeof(bufferString)) <= 1) {
			strncpy(pResultado, bufferString, 1);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
		printf("Quedan %d reintentos.", reintentos);
	}
	return retorno;
}

int utn_getShortInt(char mensaje[], char mensajeError[], int minimo, int maximo,
		int reintentos, short int *pResultado) {
	/// @fn int utn_getInt(char[], char[], int, int, int, int*)
	/// @param mensaje
	/// @param mensajeError
	/// @param minimo
	/// @param maximo
	/// @param reintentos
	/// @param pResultado
	/// @return
	///
	/// Utiliza getInt, agrega control por minimo y maximo, reintentos y mensajes
	int retorno = -1;
	short int bufferShortInt;
	int retorno_getShortInt;

	if (mensaje != NULL && minimo < maximo && mensajeError != NULL
			&& pResultado != NULL && reintentos > 0) {
		printf("%s", mensaje);
		retorno_getShortInt = getShortInt(&bufferShortInt);
		do {
			if (retorno_getShortInt == -1 || bufferShortInt > maximo
					|| bufferShortInt < minimo) {
				printf("%s", mensajeError);
				reintentos--;
				printf("Quedan %d reintentos.", reintentos);
				printf("%s", mensaje);
				retorno_getShortInt = getShortInt(&bufferShortInt);
			} else {
				reintentos = 0; //funciona como break
				*pResultado = bufferShortInt;
				retorno = 0;
			}
		} while (reintentos > 0);
	}
	return retorno;
}

int utn_getEmail(char *mensaje, char *mensajeError, int reintentos,
		int longitud, char *pResultado) {

	char bufferString[4096];
	int retorno = -1;
	while (reintentos > 0) {
		reintentos--;
		printf("%s", mensaje);
		if (getEmail(bufferString, sizeof(bufferString)) == 0
				&& strnlen(bufferString, sizeof(bufferString)) < longitud) {
			strncpy(pResultado, bufferString, longitud);
			retorno = 0;
			reintentos = 0;
		}else{
			printf("%s", mensajeError);
			printf("Quedan %d reintentos.", reintentos);
		}
	}
	return retorno;
}


int getEmail(char *pResultado, int longitud) {
	int retorno = -1;
	char buffer[200];

	if (pResultado != NULL) {
		if (myGets(buffer, sizeof(buffer)) == 0
				&& esEmail(buffer, sizeof(buffer)==0)
				&& strnlen(buffer, sizeof(buffer)) < longitud) {
			strncpy(pResultado, buffer, longitud);
			retorno = 0;
		}
	}else{
		puts("No pasa validación getEmail\n");
	}
	return retorno;
}

int esEmail(char cadena[],int longitud) {
	int retorno = -2;
	int i = 0;
	int contadorArrobas = 0;
	int contadorPuntosPostArroba = 0;

	for(i = 0; cadena[i] != '\0' && i < longitud;i++)
	{
		if((cadena[i]<'0'||cadena[i]>'9')&&
		   (cadena[i]<'a'||cadena[i]>'z')&&
		   (cadena[i]<'A'||cadena[i]>'Z')&&
			cadena[i]!='.'&&
			cadena[i]!='@'&&
			cadena[i]!='_'&&
			cadena[i]!='-')
		{
			puts("Se introdujo un caracter erroneo.");
			retorno = -1;
			break;
		}
		if (cadena[i] == '@') {
			contadorArrobas++;
		}
		if (contadorArrobas > 1) {
			retorno = -1; //error
			puts("Error: más de un @.\n");
			break;
		}
		if (contadorArrobas>0 && cadena[i] == '.') {
			contadorPuntosPostArroba++;
		}
		if (contadorPuntosPostArroba > 2) {
			retorno = -1; //error
			puts("Error: más de un punto luego del @. Ingrese un correo valido.\n.");
			break;
		}
		if(contadorArrobas>0 && contadorPuntosPostArroba >0 && contadorPuntosPostArroba <3 && i>6)
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}
