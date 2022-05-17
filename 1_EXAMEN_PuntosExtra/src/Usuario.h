#ifndef USUARIO_H_
#define USUARIO_H_
#include <stdio.h>
#include <stdlib.h>
#include "UTN4.h"

//Estados Producto/Usuario
#define LIBRE 0
#define ALTA 1
#define BAJA 2

//Tipos Usuario
#define ADMIN 0
#define USER 1

//TAMS STRINGS
#define TAM_CORREO 25
#define TAM_PASSWORD 10
#define TAM_DIRECCION 50

struct {
	int PK_idUsuario;
	short int isEmpty;

	short int tipo;
	char correo[TAM_CORREO];
	char password[TAM_PASSWORD];
	char direccion[TAM_DIRECCION];
	int codPostal;
}typedef eUsuario;


/*****     ABM BÁSICO     *****/

int eUsuario_init(eUsuario arrayUsuarios[], int tam);
int eUsuario_findEmptyIndex(eUsuario arrayUsuarios[], int tam);
int eUsuario_findIndexById(eUsuario arrayUsuarios[], int tam, int optId);
int eUsuario_loadUsuario(eUsuario *u);
int eUsuario_alta(eUsuario arrayUsuarios[], int tamUsuarios);
int eUsuario_baja(eUsuario arrayUsuarios[], int tam, int optId, int * idBaja);
int addUsuario(eUsuario* arrayUsuariosItem, int tamUsuarios, int tipo, int id, char correo[], char password[], char direccion[], int codigoPostal);
int eUsuario_findIndexByCorreo(eUsuario arrayUsuarios[], int tam, char correoToFind[]);
int eUsuario_printMult(eUsuario arrayUsuarios[], int tam, int estado);
void eUsuario_printOne(eUsuario u);
int eUsuario_getUserIDbyMail(eUsuario arrayUsuarios[],int tamUsuarios, char correo[]);
int eUsuario_printMultNoLIBRE(eUsuario arrayUsuarios[], int tam);

void eUsuario_hardcode(eUsuario arrayUsuarios[],int tamUsuarios);

#endif /* USUARIO_H_ */
