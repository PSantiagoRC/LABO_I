#include "Tracking_Usuario_Producto.h"

//id autoincremental para trackings
static int idAutoTrack = 30000;
static int relTracking_getId(void);
static int relTracking_getId() {
	return idAutoTrack++;
}

/// @fn int relTrackUsuProd_alta(eTracking[], eProducto[], eUsuario[], int, int, int, char[], int)
/// @param arrayTrackings
/// @param arrayProductos
/// @param arrayUsuarios
/// @param tamTrackings
/// @param tamProductos
/// @param tamUsuarios
/// @param correoBuyer
/// @param idProdCompra
/// @return da de alta un tracking. Retorna 0 si éxito, negativo si fracaso. Recibe por parámetro los arrays, sus tamaños, el correo del comprador logueado, y el id del producto elegido.
int relTrackUsuProd_alta(eTracking arrayTrackings[], eProducto arrayProductos[], eUsuario arrayUsuarios[],
		int tamTrackings, int tamProductos, int tamUsuarios, char correoBuyer[], int idProdCompra) { //correoBuyer viene del login, idProdCompra de seleccion usuario.

	int retorno = 0;
	int emptyIndexTrackings;
	int sellerIndex;
	int sellerId;
	int stockDisp;
	int buyerIndex;
	int buyerId;
	int codPostComp;
	int distComp;
	int indexCompra;
	float totalCompra;
	float precioCompra;
	long int secondsFechaHoraLlegada;
	double plazoEntrega;
	eTracking trackingBuffer;

	emptyIndexTrackings = eTracking_findEmptyIndex(arrayTrackings,
			tamTrackings); //Ret index libre o -1 si no hay

	buyerIndex = eUsuario_findIndexByCorreo(arrayUsuarios, tamUsuarios, correoBuyer);
	buyerId = arrayUsuarios[buyerIndex].PK_idUsuario;
	codPostComp = arrayUsuarios[buyerIndex].codPostal;
	distComp = relTrackUsuProd_calculaDist(codPostComp);

	sellerIndex = eProducto_findIndexByIdALTA(arrayProductos, tamProductos, idProdCompra);
	sellerId = arrayProductos[sellerIndex].FK_idSeller;
	stockDisp = arrayProductos[sellerIndex].stock;

	if (arrayTrackings != NULL && arrayUsuarios != NULL && arrayProductos != NULL) {
		if (tamTrackings > 0 && tamUsuarios > 0 && tamProductos > 0) {
			if (emptyIndexTrackings >= 0 && sellerIndex >= 0 && sellerId >= 0 && buyerIndex >= 0 && buyerId >= 0) {
				if(distComp>0){

					trackingBuffer.PK_idTracking = relTracking_getId();
					trackingBuffer.FK_idVendedor = sellerId; //Id del vendedor que dio de alta el producto
					trackingBuffer.FK_idComprador = buyerId; //Id del vendedor que realiza la compra
					trackingBuffer.FK_idProducto = idProdCompra; //Id del producto elegido
					trackingBuffer.distanciaKM = distComp;

					if(trackingBuffer.FK_idComprador != trackingBuffer.FK_idVendedor){
						printf("\nCANTIDAD DISPONIBLE: %d\n", stockDisp);
						if(!utn_getInt("Ingrese la cantidad deseada.\n","Error. Reingrese.\n" , 1, stockDisp, 3, &trackingBuffer.cantidad)){

							indexCompra = eProducto_findIndexByIdNoLIBRE(arrayProductos, tamProductos, idProdCompra);
							precioCompra = arrayProductos[indexCompra].precio;
							totalCompra = trackingBuffer.cantidad*precioCompra;

							printf("El total de la compra es: %.2f\n", totalCompra);

							if (valid_siNo(
									"ESTÁ SEGURO DE QUE DESEA REALIZAR LA COMPRA? S/N\n",
									"Error. Ingrese S o N.\n", 3)) {

								//CARGA DE TRACKING

								plazoEntrega = TIEMPO*distComp;
								secondsFechaHoraLlegada = time_Add(plazoEntrega);

								arrayTrackings[emptyIndexTrackings].PK_idTracking = trackingBuffer.PK_idTracking;
								arrayTrackings[emptyIndexTrackings].FK_idComprador = trackingBuffer.FK_idComprador;
								arrayTrackings[emptyIndexTrackings].FK_idVendedor = trackingBuffer.FK_idVendedor;
								arrayTrackings[emptyIndexTrackings].FK_idProducto = trackingBuffer.FK_idProducto;
								arrayTrackings[emptyIndexTrackings].cantidad = trackingBuffer.cantidad;
								arrayTrackings[emptyIndexTrackings].distanciaKM = trackingBuffer.distanciaKM;
								arrayTrackings[emptyIndexTrackings].horaLlegada = secondsFechaHoraLlegada;
								arrayTrackings[emptyIndexTrackings].isEmpty = EN_VIAJE;

								arrayProductos[sellerIndex].stock -= arrayTrackings[emptyIndexTrackings].cantidad; //Resta
								if(arrayProductos[sellerIndex].stock == 0){
									arrayProductos[sellerIndex].isEmpty = BAJA;
								}

								char* horaLleg = ctime(&arrayTrackings[emptyIndexTrackings].horaLlegada);

								printf("Index: %d\n", emptyIndexTrackings);
								printf("Id tracking: %d\n", arrayTrackings[emptyIndexTrackings].PK_idTracking);
								printf("Id comprador: %d\n", arrayTrackings[emptyIndexTrackings].FK_idComprador);
								printf("Id vendedor: %d\n", arrayTrackings[emptyIndexTrackings].FK_idVendedor);
								printf("Cantidad: %d\n", arrayTrackings[emptyIndexTrackings].cantidad);
								printf("DistanciaKm: %d\n", arrayTrackings[emptyIndexTrackings].distanciaKM);
								printf("Fecha y hora de llegada: ");
								puts(horaLleg);
								printf("isEmpty: %d\n", arrayTrackings[emptyIndexTrackings].isEmpty);
								puts("Compra exitosa!");
							}else{
								retorno = -7;
								puts("Se decidió no dar el alta");
							}
						} else {
							puts("No se pudo realizar la compra");
							retorno = -6; //No quiso dar el alta
						}
					}else{
						puts("El vendedor y el comprador no deben coincidir.");
						retorno = -5; //Coinciden idComprador e idVendedor
					}
				} else {
					puts("Codigo Postal erroneo");
					retorno = -4; //Codigo postal erroneo
				}
			}else{
				retorno = -3;
				puts("Error en posición de base Trackings o en posición/IDs de comprador o vendedor");
			}
		}else {
			puts("Tamaño de bases insuficiente.");
			retorno = -2; // Len mal definido
		}
	} else {
		puts("Error en base provista.");
		retorno = -1; // Array Null
	}
	return retorno;
}

/// @fn int relTrackUsuProd_calculaDist(int)
/// @param codPostComp
/// @return calcula la distanciaKM del tracking. Retorna la distancia o -1 si fracasa.
int relTrackUsuProd_calculaDist(int codPostComp){
	int retorno = -1;
	if(codPostComp >0 && codPostComp <1001)
	{
		retorno = 20;
	}else{
		if(codPostComp >1000 && codPostComp <3001){
		retorno = 30;
		}else{
			if(codPostComp >3000 && codPostComp <5001){
			retorno = 50;
			}else{
				if(codPostComp >5000 && codPostComp <8001){
				retorno = 80;
				}else{
					if(codPostComp >8000 && codPostComp <10000){
					retorno = 150;
					}
				}
			}
		}
	}
	return retorno;
}

/// @fn void relTrackUsuProd_printOneTrackingComp(eTracking, eProducto[], int)
/// @param t
/// @param arrayProductos
/// @param tamProductos
/// imprime un registro del array de entidades eTracking, con datos de interés para el comprador.
void relTrackUsuProd_printOneTrackingComp(eTracking t, eProducto arrayProductos[], int tamProductos){
	int indexProd = eProducto_findIndexByIdNoLIBRE(arrayProductos, tamProductos, t.FK_idProducto);
	char nomProd[TAM_NOMPRODUCTO];
	strcpy(nomProd,arrayProductos[indexProd].nombreProducto);
	char *sHora = ctime(&t.horaLlegada);

	printf("|%15d|%-34s|%18d|", t.PK_idTracking, nomProd, t.FK_idVendedor); //con tam correo 25
	switch(t.isEmpty){
		case 0:
			printf("%-21s|","LIBRE");
			break;
		case 1:
			printf("%-21s|","EN VIAJE");
			break;
		case 2:
			printf("%-21s|","ENTREGADO");
			break;
		case 3:
			printf("%-21s|","CANCELADO");
			break;
	}
	printf("          %s",sHora); //Fecha ocupa 24chars
}

/// @fn int relTrackUsuProd_printMultTrackingsComp(eTracking[], eUsuario[], eProducto[], int, int, int, char[])
/// @param arrayTrackings
/// @param arrayUsuarios
/// @param arrayProductos
/// @param tamTrackings
/// @param tamUsuarios
/// @param tamProductos
/// @param correoBuyer
/// @return imprime múltiples registros de tracking con datos para el comprador.
int relTrackUsuProd_printMultTrackingsComp(eTracking arrayTrackings[],
		eUsuario arrayUsuarios[], eProducto arrayProductos[], int tamTrackings,
		int tamUsuarios, int tamProductos, char correoBuyer[]) {

	int retorno = 0;
	int flag = 0;
	int i;
	int indexBuyer;
	int idBuyer;

	if (arrayTrackings != NULL && arrayUsuarios != NULL
			&& arrayProductos != NULL) {
		if (tamTrackings > 0 && tamUsuarios > 0 && tamProductos > 0) {
			indexBuyer = eUsuario_findIndexByCorreo(arrayUsuarios, tamUsuarios,
					correoBuyer);
			if (indexBuyer >= 0) {
				idBuyer = arrayUsuarios[indexBuyer].PK_idUsuario;

				relTrackUsuProd_updateTrackingStatus(arrayTrackings,
						tamTrackings); //UPDATE!

				puts(
						"|---------------+----------------------------------+------------------+---------------------|-----------------------------------|");
				puts(
						"|  ID TRACKING  |         NOMBRE PRODUCTO          |    ID VENDEDOR   |   ESTADO TRACKING   |              ENGREGA              |");
				puts(
						"|---------------+----------------------------------+------------------+---------------------|-----------------------------------|");
				puts(
						"|---------------+----------------------------------+------------------+---------------------|-----------------------------------|");

				for (i = 0; i < tamTrackings; i++) {
					if (arrayTrackings[i].isEmpty != LIBRE
							&& arrayTrackings[i].FK_idComprador == idBuyer) {
						relTrackUsuProd_printOneTrackingComp(arrayTrackings[i],
								arrayProductos, CANT_PRODUCTOS);
						flag = 1;
						retorno = 1;
					}
				}
				puts(
						"|---------------+----------------------------------+------------------+---------------------|-----------------------------------|");
				if (flag == 0) {
					retorno = -1;
				}
			} else {
				retorno = -2; //tam <=0
			}
		} else {
			retorno = -3; //NULL array
		}
	}
	return retorno;
}

/// @fn void relTrackUsuProd_updateTrackingStatus(eTracking[], int)
/// @param arrayTrackings
/// @param tamTrackings
/// actualiza el estado de tracking
void relTrackUsuProd_updateTrackingStatus(eTracking arrayTrackings[], int tamTrackings){
	if(arrayTrackings != NULL && tamTrackings >0){
		for(int i=0 ; i<tamTrackings ; i++)
		{
			if(arrayTrackings[i].isEmpty == EN_VIAJE && time(NULL) > arrayTrackings[i].horaLlegada)
			{
				arrayTrackings[i].isEmpty = ENTREGADO;
			}
		}
	}
}

/// @fn int relTrackUsuProd_findIndexByIdENVIAJE(eTracking[], int, int)
/// @param arrayTrackings
/// @param tam
/// @param optId
/// @return devuelve posicion en array trackings que esté "EN VIAJE". 0 o negativo si fracasa.
int relTrackUsuProd_findIndexByIdENVIAJE(eTracking arrayTrackings[], int tam, int optId) {
	int retorno = 0;
	int flag = 0;
	int i;
	int IDtoFind = optId;
	if (arrayTrackings != NULL) {
		if (tam > 0) {
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
					puts("Error, ID no válido.");
				} else {
					for (i = 0; i < tam; i++) {
						if (arrayTrackings[i].isEmpty == EN_VIAJE) {
							if (arrayTrackings[i].PK_idTracking == IDtoFind) {
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
				puts("No se encontró el ID");
			}
		} else {
			retorno = -2; //Tamaño array <=0
		}
	} else {
		retorno = -1; //Array es NULL
	}
	return retorno;
}

/// @fn int relTrackUsuProd_CancelaTrackingsComp(eTracking[], eUsuario[], eProducto[], int, int, int, char[])
/// @param arrayTrackings
/// @param arrayUsuarios
/// @param arrayProductos
/// @param tamTrackings
/// @param tamUsuarios
/// @param tamProductos
/// @param correoBuyer
/// @return asigna "CANCELADO" a un tracking perteneciente al comprador logueado, cuyo eMail se pasa por parámetro.
int relTrackUsuProd_CancelaTrackingsComp(eTracking arrayTrackings[],
		eUsuario arrayUsuarios[], eProducto arrayProductos[], int tamTrackings, int tamUsuarios, int tamProductos,
		char correoBuyer[]){

	int retorno = -1;
	int indexBuyer;
	int idBuyer;
	int idTrackCancelar;
	int indexTrackCancelar;

	if (arrayTrackings != NULL && arrayUsuarios != NULL && arrayProductos != NULL) {
		if (tamTrackings > 0 && tamUsuarios > 0 && tamProductos > 0) {
			indexBuyer = eUsuario_findIndexByCorreo(arrayUsuarios, tamUsuarios,
					correoBuyer);
			if (indexBuyer >= 0) {
				idBuyer = arrayUsuarios[indexBuyer].PK_idUsuario;

				relTrackUsuProd_updateTrackingStatus(arrayTrackings, tamTrackings); //UPDATE!

				if(valid_siNo("Desea cancelar una compra? S/N\n", "Error. Ingrese S/N.\n", 3)==1){
					if(utn_getInt("Ingrese el ID de la compra.\n", "Error. Reingrese.\n", 30000, 30000+CANT_TRACKINGS, 3, &idTrackCancelar)==0){
						indexTrackCancelar = relTrackUsuProd_findIndexByIdENVIAJE(arrayTrackings, tamTrackings, idTrackCancelar);
						if(indexTrackCancelar>=0 && arrayTrackings[indexTrackCancelar].FK_idComprador == idBuyer){ //Solo puede cancelar sus operaciones
							arrayTrackings[indexTrackCancelar].isEmpty = CANCELADO;
							puts("COMPRA CANCELADA.\n");
							//NO SE DEVUELVE EL STOCK. SE ASUME QUE DEBE REVISARSE VOLVERSE A CARGAR MANUALMENTE.
							retorno = 0;
						}else{
							puts("No se encontró ID en viaje para cancelar.\n");
						}
					}else{
						puts("Error en ID ingresado para cancelar.\n");
					}
				}
			}
		}
	}
	return retorno;
}

/// @fn void relTrackUsuProd_printOneTrackingVend(eTracking, eProducto[], int)
/// @param t
/// @param arrayProductos
/// @param tamProductos
/// Imprime un registro de tracking con datos de interés para el vendedor
void relTrackUsuProd_printOneTrackingVend(eTracking t, eProducto arrayProductos[], int tamProductos){
	int indexProd = eProducto_findIndexByIdNoLIBRE(arrayProductos, tamProductos, t.FK_idProducto);
	char nomProd[TAM_NOMPRODUCTO];
	strcpy(nomProd,arrayProductos[indexProd].nombreProducto);
	char *sHora = ctime(&t.horaLlegada);

	printf("|%15d|%-34s|%18d|", t.PK_idTracking, nomProd, t.FK_idComprador); //con tam correo 25
	switch(t.isEmpty){
		case 0:
			printf("%-21s|","LIBRE");
			break;
		case 1:
			printf("%-21s|","EN VIAJE");
			break;
		case 2:
			printf("%-21s|","ENTREGADO");
			break;
		case 3:
			printf("%-21s|","CANCELADO");
			break;
	}
	printf("          %s",sHora); //Fecha ocupa 24chars
}

/// @fn int relTrackUsuProd_printMultTrackingsVend(eTracking[], eUsuario[], eProducto[], int, int, int, char[])
/// @param arrayTrackings
/// @param arrayUsuarios
/// @param arrayProductos
/// @param tamTrackings
/// @param tamUsuarios
/// @param tamProductos
/// @param correoSeller
/// @return
/// Imprime múltiples registros de tracking con datos de interés para el vendedor.
int relTrackUsuProd_printMultTrackingsVend(eTracking arrayTrackings[],
		eUsuario arrayUsuarios[], eProducto arrayProductos[], int tamTrackings,
		int tamUsuarios, int tamProductos, char correoSeller[]) {

	int retorno = 0;
	int flag = 0;
	int i;
	int indexSeller;
	int idSeller;

	if (arrayTrackings != NULL && arrayUsuarios != NULL
			&& arrayProductos != NULL) {
		if (tamTrackings > 0 && tamUsuarios > 0 && tamProductos > 0) {
			indexSeller = eUsuario_findIndexByCorreo(arrayUsuarios, tamUsuarios,
					correoSeller);
			if (indexSeller >= 0) {
				idSeller = arrayUsuarios[indexSeller].PK_idUsuario;

				relTrackUsuProd_updateTrackingStatus(arrayTrackings,
						tamTrackings); //UPDATE!

				puts(
						"|---------------+----------------------------------+------------------+---------------------|-----------------------------------|");
				puts(
						"|  ID TRACKING  |         NOMBRE PRODUCTO          |    ID COMPRADOR  |   ESTADO TRACKING   |              ENGREGA              |");
				puts(
						"|---------------+----------------------------------+------------------+---------------------|-----------------------------------|");
				puts(
						"|---------------+----------------------------------+------------------+---------------------|-----------------------------------|");

				for (i = 0; i < tamTrackings; i++) {
					if ((arrayTrackings[i].isEmpty == ENTREGADO
							|| arrayTrackings[i].isEmpty == CANCELADO)
							&& arrayTrackings[i].FK_idVendedor == idSeller) {
						relTrackUsuProd_printOneTrackingVend(arrayTrackings[i],
								arrayProductos, CANT_PRODUCTOS);
						flag = 1;
						retorno = 1;
					}
				}
				puts(
						"|---------------+----------------------------------+------------------+---------------------|-----------------------------------|");
				if (flag == 0) {
					retorno = -1;
				}
			} else {
				retorno = -2; //tam <=0
			}
		} else {
			retorno = -3; //NULL array
		}
	}
	return retorno;
}

/// @fn void relTrackUsuProd_printOneTrackingADMIN(eTracking, eProducto[], int)
/// @param t
/// @param arrayProductos
/// @param tamProductos
/// Imprime un tracking con datos de interes para el ADMINISTRADOR
void relTrackUsuProd_printOneTrackingADMIN(eTracking t, eProducto arrayProductos[], int tamProductos){

	printf("\n|%15d|%15d|%15d|", t.PK_idTracking, t.FK_idVendedor, t.FK_idComprador);
	switch(t.isEmpty){
		case 0:
			printf("%-21s|","LIBRE");
			break;
		case 1:
			printf("%-21s|","EN VIAJE");
			break;
		case 2:
			printf("%-21s|","ENTREGADO");
			break;
		case 3:
			printf("%-21s|","CANCELADO");
			break;
	}
	//puts("\n");
}

/// @fn void relTrackUsuProd_printMultTrackingsADMIN(eTracking[], eUsuario[], eProducto[], int, int, int)
/// @param arrayTrackings
/// @param arrayUsuarios
/// @param arrayProductos
/// @param tamTrackings
/// @param tamUsuarios
/// @param tamProductos
/// Imprime múltiples trackings con datos de interés para el ADMINISTRADOR
void relTrackUsuProd_printMultTrackingsADMIN(eTracking arrayTrackings[],
		eUsuario arrayUsuarios[], eProducto arrayProductos[], int tamTrackings,
		int tamUsuarios, int tamProductos) {

	if (arrayTrackings != NULL && arrayUsuarios != NULL
			&& arrayProductos != NULL) {
		if (tamTrackings > 0 && tamUsuarios > 0 && tamProductos > 0) {

				relTrackUsuProd_updateTrackingStatus(arrayTrackings,
						tamTrackings); //UPDATE!


				puts(
						"|---------------+---------------+---------------+---------------------|");
				puts(
						"|  ID TRACKING  |  ID VENDEDOR  |  ID COMPRADOR |   ESTADO TRACKING   |");
				puts(
						"|---------------+---------------+---------------+---------------------|");
				puts(
						"|---------------+---------------+---------------+---------------------|");

				for (int i = 0; i < tamTrackings; i++) {
					if(arrayTrackings[i].isEmpty != LIBRE)
					{
						relTrackUsuProd_printOneTrackingADMIN(arrayTrackings[i],
								arrayProductos, CANT_PRODUCTOS);
					}
				}
				puts(
						"\n|---------------+---------------+---------------+---------------------|");
		}
	}
}

long int time_Current(void){
	return time(NULL);
}

long int time_Add(double secondsAdd){
	return secondsAdd + time_Current();
}

/*
struct {
	int PK_idTracking;
	int FK_idProducto;
	short int isEmpty;
	int FK_idComprador;
	int FK_idVendedor;
	int cantidad;
	int distanciaKM;
	long int horaLlegada;
}typedef eTracking;
*/
void relTrackUsuProd_hardcode(eTracking arrayTrackings[],int tamTrackings){

	arrayTrackings[0].PK_idTracking = relTracking_getId();
	arrayTrackings[0].FK_idProducto = 20001;
	arrayTrackings[0].isEmpty = EN_VIAJE;
	arrayTrackings[0].FK_idComprador = 10003;
	arrayTrackings[0].FK_idVendedor = 10002;
	arrayTrackings[0].cantidad = 5;
	arrayTrackings[0].distanciaKM = 80;
	arrayTrackings[0].horaLlegada = time(NULL)+180;

	arrayTrackings[1].PK_idTracking = relTracking_getId();
	arrayTrackings[1].FK_idProducto = 20003;
	arrayTrackings[1].isEmpty = ENTREGADO;
	arrayTrackings[1].FK_idComprador = 10003;
	arrayTrackings[1].FK_idVendedor = 10002;
	arrayTrackings[1].cantidad = 5;
	arrayTrackings[1].distanciaKM = 80;
	arrayTrackings[1].horaLlegada = time(NULL)-60;

	arrayTrackings[2].PK_idTracking = relTracking_getId();
	arrayTrackings[2].FK_idProducto = 20004;
	arrayTrackings[2].isEmpty = CANCELADO;
	arrayTrackings[2].FK_idComprador = 10003;
	arrayTrackings[2].FK_idVendedor = 10002;
	arrayTrackings[2].cantidad = 5;
	arrayTrackings[2].distanciaKM = 80;
	arrayTrackings[2].horaLlegada = time(NULL)+180;

	arrayTrackings[3].PK_idTracking = relTracking_getId();
	arrayTrackings[3].FK_idProducto = 20004;
	arrayTrackings[3].isEmpty = EN_VIAJE;
	arrayTrackings[3].FK_idComprador = 10003;
	arrayTrackings[3].FK_idVendedor = 10002;
	arrayTrackings[3].cantidad = 5;
	arrayTrackings[3].distanciaKM = 20;
	arrayTrackings[3].horaLlegada = time(NULL)+360;

	arrayTrackings[4].PK_idTracking = relTracking_getId();
	arrayTrackings[4].FK_idProducto = 20002;
	arrayTrackings[4].isEmpty = EN_VIAJE;
	arrayTrackings[4].FK_idComprador = 10004;
	arrayTrackings[4].FK_idVendedor = 10002;
	arrayTrackings[4].cantidad = 5;
	arrayTrackings[4].distanciaKM = 40;
	arrayTrackings[4].horaLlegada = time(NULL)+360;
}
