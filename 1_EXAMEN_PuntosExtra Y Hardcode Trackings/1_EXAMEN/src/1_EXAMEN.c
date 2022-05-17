/*****
Correo ADMIN para pruebas: admin@admin.com
Password: admin
******/

#define CANT_USUARIOS 1000 //CAMBIAR
#define CANT_TRACKINGS 1000 //CAMBIAR
#define CANT_PRODUCTOS 1000 //CAMBIAR

//Estados Tracking
#define LIBRE 0
#define EN_VIAJE 1
#define ENTREGADO 2
#define CANCELADO 3

//Estados Producto/Usuario
#define LIBRE 0
#define ALTA 1
#define BAJA 2

//Tipos Usuario
#define ADMIN 0
#define USER 1

//Tipos Ingreso
#define INGRESO 1
#define REGISTRO 2

#include "UTN4.h"
#include "Tracking_Usuario_Producto.h"

int main(void) {
	setbuf(stdout, NULL);

	int retornoGral = 0;

	/******** DECLARACION E INICIALIZACION DE ARRAYS **********/
	eUsuario arrayUsuarios[CANT_USUARIOS];
	eUsuario_init(arrayUsuarios, CANT_USUARIOS);

	eProducto arrayProductos[CANT_PRODUCTOS];
	eProducto_init(arrayProductos, CANT_PRODUCTOS);

	eTracking arrayTrackings[CANT_TRACKINGS];
	eTracking_init(arrayTrackings, CANT_TRACKINGS);

	/****** COMENTAR LAS SIGUIENTES LINEAS PARA PROBAR EL CÓDIGO SIN HARDCODEO ***********************************/
	/****** HARDCODE *********/

	eUsuario_hardcode(arrayUsuarios, CANT_USUARIOS);
	puts("Hardcode usuarios");

	relProducto_Usu_hardcode(arrayProductos, CANT_PRODUCTOS);
	puts("Hardcode productos");

	relTrackUsuProd_hardcode(arrayTrackings,CANT_TRACKINGS);
	puts("Hardcode trackings (BETA)");
	/****** FIN HARDCODE *********/
	/****** COMENTAR LAS LINEAS ANTERIORES PARA PROBAR EL CÓDIGO SIN HARDCODEO  **********************************/

	//VARIABLES MAIN
	int opcionMenu1;
	int opcionMenuUser;
	int opcionMenuAdmin;
	int opcionMenuEstadoVentas;
	int idSeller;
	int indexSeller;
	int indexUsuCorreoIng;
	int retAltaUsu;
	int idUsuBaja;
	char passwordIng[TAM_PASSWORD];
	char correoIng[TAM_CORREO];
	char nomProd[TAM_NOMPRODUCTO];

	//INTERFAZ
	do {
		int flagIngreso = -1;
		//*** INGRESO / REGISTRACION ***//

		opcionMenu1 = printMenuGetOption(
				"************************\n\n"
				"**** MENU PRINCIPAL ****\n\n"
				"************************\n\n",
				"1) INGRESAR\n"
				"\n"
				"2) REGISTRARSE\n"
				"\n"
				"3) SALIR\n"
				"************************\n\n", "Error. Seleccione opción de 1 a 3.\n", 3, 3);

		switch (opcionMenu1) {

/************* INGRESO **********************************/

			case INGRESO:
				puts("Opción elegida: INGRESAR\n");

				if(utn_getEmail("Ingrese su email\n", "Error, ingrese email válido.\n", 3, TAM_CORREO, correoIng)==0){
					indexUsuCorreoIng = eUsuario_findIndexByCorreo(arrayUsuarios, CANT_USUARIOS, correoIng);
					if(indexUsuCorreoIng>=0 && arrayUsuarios[indexUsuCorreoIng].isEmpty==ALTA){
						puts("Correo verificado");
						if(!utn_getStringWNum("Ingrese su password\n", "Error. Reingrese.\n", 3, TAM_PASSWORD, passwordIng)){
							if(!strcmp(arrayUsuarios[indexUsuCorreoIng].password,passwordIng)){
								if(arrayUsuarios[indexUsuCorreoIng].tipo==ADMIN){
									puts("Login de admin\n");
									flagIngreso = ADMIN;
									break;
								}else{
									if(arrayUsuarios[indexUsuCorreoIng].tipo==USER && arrayUsuarios[indexUsuCorreoIng].isEmpty==ALTA)
									{
										puts("Login de usuario");
										flagIngreso = USER;
										break;
									}else{
										puts("Error. No es ni Admin, ni User.");
										break;
									}
								}
							}else{
								printf("Password %s es erronea.\n",passwordIng); //No coincide con la de registro.
								break;
							}
						}else{
							printf("Password obtenida: %s\n",passwordIng);
							puts("Error con obteniendo password.\n");
							break;
						}
					}else{
						puts("Correo ingresado no se encuentra dado de Alta. Registrese.");
					}
				}else{
					printf("Correo obtenido: %s\n",correoIng);
					puts("Error obteniendo Email.\n");
					break;
				}
				break; //SACAR DESPUES

/************* REGISTRO *********************************/

			case REGISTRO:
				puts("Opción elegida: REGISTRARSE\n");
				retAltaUsu = eUsuario_alta(arrayUsuarios, CANT_USUARIOS);
				if(retAltaUsu==1)
				{
					puts("Alta de Admin efectuada!\n");
				}else{
					if(retAltaUsu==0){
						puts("Alta de User efectuada!\n");
					}else{
						puts("Error en el alta\n");
					}
				}
				break;
			case 3:
				puts("SALIENDO...\n");
				retornoGral = -1;
				break;
			default:
				break;
		}

/*************** MENÚES SEGÚN ADMIN / USUARIO ***************/

		switch(flagIngreso){

/*************** MENÚ USER **********************************/
			case USER:
				do{
					opcionMenuUser = printMenuGetOption(
							"************************\n\n"
							"***** MENU USUARIO *****\n\n"
							"************************\n\n",
							"1) COMPRAR\n"
							"\n"
							"2) VENDER\n"
							"\n"
							"3) ESTADO DE COMPRAS\n"
							"\n"
							"4) ESTADO DE VENTAS\n"
							"\n"
							"5) SALIR\n"
							"************************\n\n", "Error. Seleccione opción de 1 a 5.\n", 3, 5);

					switch(opcionMenuUser){
						case 1:
							puts("Opción elegida: COMPRAR\n");
							puts("Qué desea comprar?\n");
							eProducto_printMult(arrayProductos, CANT_PRODUCTOS, ALTA);
							int idProdComprar;
							utn_getInt("Ingrese ID del producto que desea.\n", "Error,  ID incorrecto.Reingrese.\n", 20000, 20000+CANT_PRODUCTOS, 3, &idProdComprar);
							relTrackUsuProd_alta(arrayTrackings, arrayProductos, arrayUsuarios,	CANT_TRACKINGS, CANT_PRODUCTOS, CANT_USUARIOS, correoIng, idProdComprar);
							break;
						case 2:
							puts("Opción elegida: VENDER.\n");
							// MODIFICACION PUNTO 1
							rel_Producto_Usu_alta(arrayProductos,arrayUsuarios,
									CANT_PRODUCTOS, CANT_USUARIOS, correoIng);
							puts("Producto cargado");
							break;
						case 3:
							puts("Opción elegida: ESTADO DE COMPRAS\n");
							if(relTrackUsuProd_printMultTrackingsComp(arrayTrackings,
									arrayUsuarios, arrayProductos, CANT_TRACKINGS, CANT_USUARIOS, CANT_PRODUCTOS,
									correoIng)==1){
								if(!relTrackUsuProd_CancelaTrackingsComp(arrayTrackings,
										arrayUsuarios, arrayProductos, CANT_TRACKINGS, CANT_USUARIOS, CANT_PRODUCTOS,
										correoIng)){
									relTrackUsuProd_printMultTrackingsComp(arrayTrackings,
																		arrayUsuarios, arrayProductos, CANT_TRACKINGS, CANT_USUARIOS, CANT_PRODUCTOS,
																		correoIng);
								}
							}
							break;
						case 4:
							puts("Opción elegida: ESTADO DE VENTAS\n");
							opcionMenuEstadoVentas = printMenuGetOption(
									"********************************\n\n"
									"*****   ESTADO DE VENTAS   *****\n\n"
									"********************************\n\n",
									"1) LISTADO DE VENTAS FINALIZADAS\n"
									"\n"
									"2) VER PRODUCTOS\n"
									"\n"
									"********************************\n\n", "Error. Seleccione opción.\n", 3, 2);
							switch(opcionMenuEstadoVentas){
								case 1:
									relTrackUsuProd_printMultTrackingsVend(arrayTrackings,
											arrayUsuarios, arrayProductos, CANT_TRACKINGS, CANT_USUARIOS, CANT_PRODUCTOS,
											correoIng);
									break;
								case 2:
									indexSeller = eUsuario_findIndexByCorreo(arrayUsuarios, CANT_USUARIOS, correoIng);
									idSeller = arrayUsuarios[indexSeller].PK_idUsuario;
									eProducto_printMultBySellerWStock(arrayProductos, CANT_PRODUCTOS, ALTA, idSeller);
									break;
							}

							break;
						case 5:
							puts("Opción elegida: SALIR\n");
							break;
						default:
							break;
					}
				}while(opcionMenuUser!=5);
				break;

/*************** MENÚ ADMIN ***************************************/

			case ADMIN:
				do{

					opcionMenuAdmin = printMenuGetOption(
							"************************\n\n"
							"** MENU ADMINISTRADOR **\n\n"
							"************************\n\n",
							"1) LISTAR ESTADO DE TODOS LOS USUARIOS\n"
							"\n"
							"2) LISTAR TODOS LOS PRODUCTOS POR CATEGORIA\n"
							"\n"
							"3) BAJA DE UN PRODUCTO\n"
							"\n"
							"4) BAJA DE UN USUARIO\n"
							"\n"
							"5) VER TRACKING GLOBAL\n"
							"\n"
							"6) FILTRAR POR NOMBRE DE PRODUCTO\n"
							"\n"
							"7) SALIR\n", "Error. Seleccione opción de 1 a 7.\n", 3, 7);

					switch(opcionMenuAdmin){
						case 1:
							puts("Opción elegida: LISTAR ESTADO DE TODOS LOS USUARIOS\n");
							eUsuario_printMultNoLIBRE(arrayUsuarios, CANT_USUARIOS);
							break;
						case 2:
							puts("Opción elegida: LISTAR TODOS LOS PRODUCTOS POR CATEGORIA\n");
							eProducto_printMult(arrayProductos, CANT_PRODUCTOS, ALTA);
							break;
						case 3:
							puts("Opción elegida: BAJA DE UN PRODUCTO\n");
							eProducto_baja(arrayProductos, CANT_PRODUCTOS, -1, -1);
							break;
						case 4:
							puts("Opción elegida: BAJA DE UN USUARIO\n");
							eUsuario_baja(arrayUsuarios, CANT_USUARIOS, -1,&idUsuBaja);
							eProducto_baja(arrayProductos, CANT_PRODUCTOS, -1, idUsuBaja);
							break;
						case 5:
							puts("Opción elegida: VER TRACKING GLOBAL\n");
							relTrackUsuProd_printMultTrackingsADMIN(arrayTrackings,
									arrayUsuarios, arrayProductos, CANT_TRACKINGS,
									CANT_USUARIOS, CANT_PRODUCTOS);
							break;
						case 6:
							puts("Opción elegida: FILTRAR POR NOMBRE DE PRODUCTO\n");
							eProducto_printMult(arrayProductos, CANT_PRODUCTOS, ALTA);
							if(utn_getStringWNum("Ingrese nombre del producto para filtrar.\n", "Error. Reingrese.\n", 3, TAM_NOMPRODUCTO, nomProd)==0){
								eProducto_SortByStock(arrayProductos, CANT_PRODUCTOS, -1);
								eProducto_printMultByNombre(arrayProductos, CANT_PRODUCTOS, LIBRE, nomProd);
								break;
							}else{
								puts("Error.");
								break;
							}
						case 7:
							puts("Opción elegida: SALIR\n");
							break;
						default:
							break;
					} //de Switch opcionMenuAdmin

				}while(opcionMenuAdmin!=7);

				break;//del Case Admin

			default: //de switch User/Admin
				break;
		} //de Switch flagIngreso

	} while (retornoGral != -1);
	return 0;
}
