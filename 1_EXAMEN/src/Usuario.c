#include "Usuario.h"

/*****     ABM BÁSICO     *****/

//Genera el ID autoincremental para usurios
static int idAutoUsu = 10000;
static int eUsuario_getId(void);
static int eUsuario_getId() {
	return idAutoUsu++;
}

/// @fn int eUsuario_init(eUsuario[], int)
/// @param arrayUsuarios
/// @param tam
/// @return Inicializa array eUsuario. 0 éxito, <0 problema
int eUsuario_init(eUsuario arrayUsuarios[], int tam) {
	int retorno = 0;
	int i;
	if (arrayUsuarios != NULL) {
		if (tam > 0) {
			for (i = 0; i < tam; i++) {
				arrayUsuarios[i].isEmpty = LIBRE;
			}
		} else {
			retorno = -2; //tam <=0
		}
	} else {
		retorno = -1; //NULL array
	}
	return retorno;
}

/// @fn int eUsuario_findEmptyIndex(eUsuario[], int)
/// @param arrayUsuarios
/// @param tam
/// @return encuentra posición libre en array eUsuario. Retorna el index o negativo si no lo encuentra.
int eUsuario_findEmptyIndex(eUsuario arrayUsuarios[], int tam) {
	int retorno = 0;
	int flag = 0;
	int i;

	if (arrayUsuarios != NULL) {
		if (tam > 0) {
			for (i = 0; i < tam; i++) {
				if (arrayUsuarios[i].isEmpty == LIBRE) {
					flag = 1;
					retorno = i;
					break;
				}
			}
			if (flag == 0) {
				retorno = -1;
			}
		} else {
			retorno = -2; //tam <=0
		}
	} else {
		retorno = -3; //NULL array
	}
	return retorno;
}

/// @fn void eUsuario_printOne(eUsuario)
/// @param u
/// Imprime un usuario
void eUsuario_printOne(eUsuario u) {
	printf("|%6d|%-25s|", u.PK_idUsuario, u.correo); //con tam correo 25
	switch(u.isEmpty){
		case 0:
			printf("%-12s|\n","LIBRE");
			break;
		case 1:
			printf("%-12s|\n","ALTA");
			break;
		case 2:
			printf("%-12s|\n","BAJA");
			break;
	}
}

/// @fn int eUsuario_printMult(eUsuario[], int, int)
/// @param arrayUsuarios
/// @param tam
/// @param estado
/// @return Imprime múltiples usuarios condicional a su campo isEmpty (estado), retorna 1 o negativo de haber problemas.
int eUsuario_printMult(eUsuario arrayUsuarios[], int tam, int estado) {
	int retorno = 1;
	int i;

	if (arrayUsuarios != NULL) {
		if (tam > 0) { //OK
			puts("|------+-------------------------+------------|");
			puts("|  ID  |         CORREO          |   ESTADO   |");
			puts("|------+-------------------------+------------|");
			puts("|------+-------------------------+------------|");
			for(i = 0; i < tam; i++) {
				if (arrayUsuarios[i].isEmpty == estado) {
					eUsuario_printOne(arrayUsuarios[i]);
					puts("|------+-------------------------+------------|");
				}
			}
		} else {
			retorno = -2;
		}
	} else {
		retorno = -1;
	}

	return retorno;
}

/// @fn int eUsuario_printMultNoLIBRE(eUsuario[], int)
/// @param arrayUsuarios
/// @param tam
/// @return imprime múltiples usuarios de un array siempre que el campo isEmpty no sea "LIBRE" (ALTA, BAJA)
/// retorna 1 si éxito, negativo si fracasa.
int eUsuario_printMultNoLIBRE(eUsuario arrayUsuarios[], int tam) {
	int retorno = 1;
	int i;

	if (arrayUsuarios != NULL) {
		if (tam > 0) { //OK
			puts("|------+-------------------------+------------|");
			puts("|  ID  |         CORREO          |   ESTADO   |");
			puts("|------+-------------------------+------------|");
			puts("|------+-------------------------+------------|");
			for(i = 0; i < tam; i++) {
				if (arrayUsuarios[i].isEmpty != LIBRE) {
					eUsuario_printOne(arrayUsuarios[i]);
					puts("|------+-------------------------+------------|");
				}
			}
		} else {
			retorno = -2;
		}
	} else {
		retorno = -1;
	}

	return retorno;
}

/// @fn int eUsuario_findIndexById(eUsuario[], int, int)
/// @param arrayUsuarios
/// @param tam
/// @param optId
/// @return Index correspondiente al ID
int eUsuario_findIndexById(eUsuario arrayUsuarios[], int tam, int optId) {
	int retorno = 0;
	int flag = 0;
	int i;
	int IDtoFind = optId;
	if (arrayUsuarios != NULL) {
		if (tam > 0) {
			eUsuario_printMult(arrayUsuarios, tam, ALTA);
			if(optId <=0)
			{
				utn_getInt("Ingrese ID seleccionado\nIngrese 0 para cancelar.",
									"Error. Reingrese.\n", 0, 99999, 3, &IDtoFind);
			}//Pide Id a usuario, si no se pasó por parámetro
			if (IDtoFind == 0) {
				retorno = -5; //Operación cancelada
			} else {
				if (IDtoFind <= -1) {
					retorno = -4; //Se ingresó un ID negativo
				} else {
					for (i = 0; i < tam; i++) {
						if (arrayUsuarios[i].isEmpty == ALTA) {
							if (arrayUsuarios[i].PK_idUsuario == IDtoFind) {
								flag = 1;
								return i; //retorna index (posición en array) para el ID ingresado
								break;
							}
						}
					}
				}
			}
			if (flag == 0) {
				retorno = -3; //No se encontró
			}
		} else {
			retorno = -2; //Tamaño array <=0
		}
	} else {
		retorno = -1; //Array es NULL
	}
	return retorno;
}

/// @fn int eUsuario_findIndexByCorreo(eUsuario[], int, char[])
/// @param arrayUsuarios
/// @param tam
/// @param correoToFind
/// @return devuelve una posición en un array, correspondiente a una dirección de eMail que recibe como parámetro.
int eUsuario_findIndexByCorreo(eUsuario arrayUsuarios[], int tam, char correoToFind[]) {
	int retorno = -1;
	int flag = 0;

	if (arrayUsuarios != NULL) {
		if (tam > 0) {
			for (int i = 0; i < tam; i++) {
				if (arrayUsuarios[i].isEmpty == ALTA) {
					if (strcmp(arrayUsuarios[i].correo, correoToFind)==0) {
						flag = 1;
						retorno = i; //retorna index (posición en array) para el ID ingresado
						break;
					}
				}
			}
		}else{
			retorno = -2; //Tamaño array <=0
		}
	}else{
		retorno = -3; //Array es NULL
	}
	if (flag == 0) {
		retorno = -4;
		puts("No se encontró mail en la base");//No se encontró
	}
	return retorno;
}

/// @fn int eUsuario_loadUsuario(eUsuario*)
/// @param u
/// @return carga los datos de un usuario pidiendo por consola. Retorna 0 si éxito, -1 si fracaso.
int eUsuario_loadUsuario(eUsuario *u) {
	int ret = 1;
	do{
		if(ret == 1 && utn_getEmail("Ingrese su correo.\n", "Error. Ingrese direccion valida.", 3, TAM_CORREO, u->correo)==0)
		{
			ret = 1;
		}else{
			ret = -1;
		}
		if(ret == 1 && utn_getStringWNum("Ingrese su password\n", "Error. Reingrese.\n", 3, TAM_PASSWORD, u->password)==0){
			ret = 1;
		}else{
			ret = -1;
		}
		if(ret == 1 && utn_getStringWNum("Ingrese su direccion\n", "Error. Reingrese.\n", 3, TAM_DIRECCION, u->direccion)==0){
			ret = 1;
		}else{
			ret = -1;
		}
		if(ret == 1 && utn_getInt("Ingrese codigo postal: \n", "Error. Reingrese.\n", 0, 9999, 3,
				&u->codPostal)==0){
			ret=0;
		}else{
			ret = -1;
		}
		}while(ret == 1);
		return ret;
}

/// @fn int addUsuario(eUsuario*, int, int, int, char[], char[], char[], int)
/// @param arrayUsuariosItem
/// @param tamUsuarios
/// @param tipo
/// @param id
/// @param correo
/// @param password
/// @param direccion
/// @param codigoPostal
/// @return agrega todos los datos de un usuario, pasados por parámetro, excepto el isEmpty que se establece en ALTA en la función.
int addUsuario(eUsuario* arrayUsuariosItem, int tamUsuarios, int tipo, int id, char correo[], char password[], char direccion[], int codigoPostal)
{
	int rtn = -1;
	if(arrayUsuariosItem->isEmpty == ALTA || tamUsuarios <= 0)
	{
		puts("No hay espacio en array.");
	}else{
		arrayUsuariosItem->tipo = USER;
		arrayUsuariosItem->PK_idUsuario = id;
		strncpy(arrayUsuariosItem->correo,correo,TAM_CORREO);
		strncpy(arrayUsuariosItem->password,password,TAM_PASSWORD);
		strncpy(arrayUsuariosItem->direccion,direccion,TAM_DIRECCION);
		arrayUsuariosItem->codPostal = codigoPostal;
		arrayUsuariosItem->isEmpty = ALTA;
		rtn = 0;
	}
	return rtn;
}

/// @fn int eUsuario_alta(eUsuario[], int)
/// @param arrayUsuarios
/// @param tamUsuarios
/// @return carga los datos de un usuario al array usuarios. Retorna 0 si es USER, 1 si es ADMIN, negativo si fracasa.
int eUsuario_alta(eUsuario arrayUsuarios[], int tamUsuarios) {
	int retorno = -1;
	int emptyIndexUsuarios;
	int retLoad;
	eUsuario usuarioBuffer;

	emptyIndexUsuarios = eUsuario_findEmptyIndex(arrayUsuarios, tamUsuarios); //Ret index libre o -1 si no hay

	if (arrayUsuarios != NULL) {
		if (tamUsuarios > 0) {
			if (emptyIndexUsuarios >= 0) {
				retLoad = eUsuario_loadUsuario(&usuarioBuffer); //Carga datos a puntero
				if (retLoad == 0) {
					if (eUsuario_findIndexByCorreo(arrayUsuarios, tamUsuarios,
							usuarioBuffer.correo) >= 0) {
						puts("El correo ya existe!");
						retorno = -9;
					} else {
						usuarioBuffer.PK_idUsuario = eUsuario_getId();
						usuarioBuffer.isEmpty = ALTA; //Switch state a ALTA.

						if (valid_siNo(
								"ESTÁ SEGURO DE QUE DESEA REALIZAR EL ALTA? S/N\n",
								"Error. Ingrese S o N.\n", 3)) {
							if (addUsuario(&arrayUsuarios[emptyIndexUsuarios],
									tamUsuarios, usuarioBuffer.tipo,
									usuarioBuffer.PK_idUsuario,
									usuarioBuffer.correo,
									usuarioBuffer.password,
									usuarioBuffer.direccion,
									usuarioBuffer.codPostal) == 0) {
								if (usuarioBuffer.tipo == ADMIN) {
									puts("Carga de ADMIN exitosa!");
									retorno = 1;
								} else {
									if (usuarioBuffer.tipo == USER) {
										puts("Carga de USER exitosa!");
										retorno = 0;
									} else {
										retorno = -8; //No es ni admin ni user
										puts("Ni ADMIN ni USER");
									}
								}
							} else {
								puts("Problema al agregar usuario");
								retorno = -7; //Falla en addUsuario
							}
						} else {
							puts("Se decidió no dar el alta");
							retorno = -6; //No quiso dar el alta
						}
					}
				} else {
					puts("Falla en la carga");
					retorno = -5; //Falla en loadUsuario
				}
			} else {
				puts("Base completa");
				retorno = -4; //Array lleno
			}
		} else {
			puts("Tamaño de base insuficiente.");
			retorno = -3; // Len mal definido
		}
	} else {
		puts("Error en base provista.");
		retorno = -2; // Array Null
	}
	return retorno;
}

/// @fn int eUsuario_baja(eUsuario[], int, int)
/// @param arrayUsuarios
/// @param tam
/// @param optId
/// @return da de baja un usuario. Opcionalmente se puede pasar el Id a dar de baja, caso contrario la función pide por consola. Retorna 0 éxito, negativo fracaso.
int eUsuario_baja(eUsuario arrayUsuarios[], int tam, int optId, int * idBaja) {
	int retorno = 0;
	int indexBaja = optId;

	if (arrayUsuarios != NULL) {
		if (tam > 0) {
			if(optId<=0)
			{
				indexBaja = eUsuario_findIndexById(arrayUsuarios, tam, optId); //-1 si no encuentra index a dar de baja, caso contrario index buscado.
			}
			if (indexBaja < 0) {
				retorno = -1;
			} else {
				printf("Index seleccionado: %d\n", indexBaja);
				if (valid_siNo(
						"ESTÁ SEGURO DE QUE DESEA DAR DE BAJA AL USUARIO? S/N\n",
						"Error. Ingrese S o N\n", 3)) {

					arrayUsuarios[indexBaja].isEmpty = BAJA;
					*idBaja = arrayUsuarios[indexBaja].PK_idUsuario;

					puts("\n\nSE DIO DE BAJA EL USUARIO.\n\n");
				} else {
					retorno = -4; // USUARIO NO ESTÁ SEGURO
				}
			}
		} else {
			retorno = -3; // LEN MAL DEFINIDO
		}
	} else {
		retorno = -2; // ARRAY NULO
	}
	return retorno;
}

/// @fn int eUsuario_getUserIDbyMail(eUsuario[], int, char[])
/// @param arrayUsuarios
/// @param tamUsuarios
/// @param correo
/// @return recibe una direccion de mail, devuelve un id de usuario si éxito, número negativo si fracaso.
int eUsuario_getUserIDbyMail(eUsuario arrayUsuarios[],int tamUsuarios, char correo[]){
	int retorno = 0;
	int flagEncontro=0;
	if(arrayUsuarios!= NULL && tamUsuarios > 0)
	{
		for(int i = 0;i<tamUsuarios;i++){
			if(strcmp(arrayUsuarios[i].correo,correo)==0){
				flagEncontro=1;
				retorno = arrayUsuarios[i].PK_idUsuario;
			}
		}
		if(flagEncontro==0)
		{
			retorno = -1;
			puts("No se encontro el usuario con el mail ingresado");
		}
	}else{
		retorno = -2; //array null o tam<=0
	}
	return retorno;
}

/***** ADICIONALES *****/
/// @fn void eUsuario_hardcode(eUsuario[], int)
/// @param arrayUsuarios
/// @param tamUsuarios
/// Usada para hardcodear usuarios en el array de usuarios
void eUsuario_hardcode(eUsuario arrayUsuarios[],int tamUsuarios){

	int id_0 = eUsuario_getId();
	addUsuario(&arrayUsuarios[0], tamUsuarios, ADMIN, id_0,"admin@admin.com", "admin", "calle de sancho 100", 1000);
	arrayUsuarios[0].tipo = ADMIN; //OVERRIDE

	int id_1 = eUsuario_getId();
	addUsuario(&arrayUsuarios[1], tamUsuarios, USER, id_1,"sancho@gmail.com", "sanchito", "calle de sanchola 100", 500);

	int id_2 = eUsuario_getId();
	addUsuario(&arrayUsuarios[2], tamUsuarios, USER, id_2,"pedro@sinectis.net", "pedrito", "calle de pedro 100", 3000);

	int id_3 = eUsuario_getId();
	addUsuario(&arrayUsuarios[3], tamUsuarios, USER, id_3,"pablo@yahoo.com.ar", "pablito", "calle de pablo 100", 4000);

	int id_4 = eUsuario_getId();
	addUsuario(&arrayUsuarios[4], tamUsuarios, USER, id_4,"nico@gmail.com", "niquito", "calle de nico 100", 5000);
}

/*
//										idUsu  isEmpty tipo  correo				clave		domicilio		codigo postal
eUsuario arrayUsuarios[CANT_USUARIOS] =	{{10000, ALTA, ADMIN, "sancho@gmail.com", "sanchito", "sanchilandia 100", 1000},
									   {10001, ALTA, USER, "sanchola@gmail.com", "sanchola", "sancholalaandia 100", 500}, //tarda 200seg entrega
									   {10002, ALTA, USER, "pedro@gmail.com", "pepito", "pedrolandia 100", 3000},
									   {10003, ALTA, USER, "pablo@gmail.com", "pepito", "pablolandia 100", 4000},
									   {10004, ALTA, USER, "nico@gmail.com", "pepito", "nicolandia 100", 5000}};
puts("Hardcode usuarios");
*/

