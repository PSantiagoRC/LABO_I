#include "Producto.h"


/*****     ABM BÁSICO     *****/

/// @fn int eProducto_init(eProducto[], int)
/// @param arrayProductos
/// @param tam
/// @return 0 si éxito, negativo si fracaso. Inicializa array de entidades eProducto.
int eProducto_init(eProducto arrayProductos[], int tam) {
	int retorno = 0;
	int i;
	if (arrayProductos != NULL) {
		if (tam > 0) {
			for (i = 0; i < tam; i++) {
				arrayProductos[i].isEmpty = LIBRE;
			}
		} else {
			retorno = -2; //tam <=0
		}
	} else {
		retorno = -1;
	}
	return retorno;
}

/// @fn int eProducto_findEmptyIndex(eProducto[], int)
/// @param arrayProductos
/// @param tam
/// @return
/// Devuelve posición "LIBRE" en array de entidades eProducto. Negativo si fracasa.
int eProducto_findEmptyIndex(eProducto arrayProductos[], int tam) {
	int retorno = 0;
	int flag = 0;
	int i;

	if (arrayProductos != NULL) {
		if (tam > 0) {
			for (i = 0; i < tam; i++) {
				if (arrayProductos[i].isEmpty == LIBRE) {
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

/// @fn void eProducto_printOne(eProducto)
/// @param p
/// imprime un Producto
void eProducto_printOne(eProducto p) {
	printf("|%6d|%-25s|", p.PK_idProducto, p.nombreProducto); //con tam categ y nombre 25
	switch(p.categoria){
		case 0:
			printf("%-25s|","CONSTRUCCION");
			break;
		case 1:
			printf("%-25s|","DEPORTES");
			break;
		case 2:
			printf("%-25s|","FARMACIA");
			break;
		case 3:
			printf("%-25s|","HOGAR");
			break;
		case 4:
			printf("%-25s|","INMUEBLE");
			break;
		case 5:
			printf("%-25s|","JUGUETES");
			break;
		case 6:
			printf("%-25s|","MODA");
			break;
		case 7:
			printf("%-25s|","TECNOLOGIA");
			break;
		case 8:
			printf("%-25s|","VEHICULO");
			break;
		default:
			break;
	}
	printf("%-20.2f|",p.precio);
	printf("%-20d|\n",p.stock);
}

/// @fn int eProducto_printMult(eProducto[], int, int)
/// @param arrayProductos
/// @param tam
/// @param estado
/// @return 1 si éxito, negativo si fracasa. Imprime múltiples productos condicional a isEmpty (estado).
int eProducto_printMult(eProducto arrayProductos[], int tam, int estado) {
	int retorno = 1;
	int i;

	if (arrayProductos != NULL) {
		if (tam > 0) { //OK

			eProducto_SortByName(arrayProductos, tam, 1);
			eProducto_SortByCategoria(arrayProductos, tam, -1);

			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|  ID  |     NOMBRE PRODUCTO     |       CATEGORIA         |       PRECIO       |       STOCK        |");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			for(i = 0; i < tam; i++) {
				if (arrayProductos[i].isEmpty == estado && arrayProductos[i].stock >=0) {
					eProducto_printOne(arrayProductos[i]);
					puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
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

/// @fn int eProducto_printMultNoLIBRE(eProducto[], int)
/// @param arrayProductos
/// @param tam
/// @return 1 si éxito, negativo si fracasa. Imprime múltiples productos siempre que su isEmpty no sea "LIBRE".
int eProducto_printMultNoLIBRE(eProducto arrayProductos[], int tam) {
	int retorno = 1;
	int i;

	if (arrayProductos != NULL) {
		if (tam > 0) { //OK
			eProducto_SortByName(arrayProductos, tam, 1);
			eProducto_SortByCategoria(arrayProductos, tam, -1);

			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|  ID  |     NOMBRE PRODUCTO     |       CATEGORIA         |       PRECIO       |       STOCK        |");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			for(i = 0; i < tam; i++) {
				if (arrayProductos[i].stock >=0 && arrayProductos[i].isEmpty != LIBRE) {
					eProducto_printOne(arrayProductos[i]);
					puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
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

/// @fn int eProducto_printMultBySellerWStock(eProducto[], int, int, int)
/// @param arrayProductos
/// @param tam
/// @param estado
/// @param idSeller
/// @return 1 si éxito, negativo si fracasa. Imprime múltiples productos correspondientes a un vendedor cuyo id se pasa por parámetro.
int eProducto_printMultBySellerWStock(eProducto arrayProductos[], int tam, int estado, int idSeller) {
	int retorno = 1;
	int i;

	if (arrayProductos != NULL) {
		if (tam > 0) { //OK
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|  ID  |     NOMBRE PRODUCTO     |       CATEGORIA         |       PRECIO       |       STOCK        |");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			for(i = 0; i < tam; i++) {
				if (arrayProductos[i].isEmpty == estado && arrayProductos[i].stock >=0 && arrayProductos[i].FK_idSeller == idSeller) {
					eProducto_printOne(arrayProductos[i]);
					puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
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

int eProducto_printMultBySellerAllStates(eProducto arrayProductos[], int tam, int estadoEvitar, int idSeller) {
	int retorno = 1;
	int i;

	if (arrayProductos != NULL) {
		if (tam > 0) { //OK
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|  ID  |     NOMBRE PRODUCTO     |       CATEGORIA         |       PRECIO       |       STOCK        |");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			for(i = 0; i < tam; i++) {
				if (arrayProductos[i].isEmpty != estadoEvitar && arrayProductos[i].stock >=0 && arrayProductos[i].FK_idSeller == idSeller) {
					eProducto_printOne(arrayProductos[i]);
					puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
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

int eProducto_printMultByNombre(eProducto arrayProductos[], int tam, int estadoEvitar, char nomProd[]){
	int retorno = 1;
	int i;

	if (arrayProductos != NULL) {
		if (tam > 0) {



			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|  ID  |     NOMBRE PRODUCTO     |       CATEGORIA         |       PRECIO       |       STOCK        |");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
			for(i = 0; i < tam; i++) {
				if (arrayProductos[i].isEmpty != estadoEvitar && arrayProductos[i].stock >=0 && (strcmp(arrayProductos[i].nombreProducto, nomProd)==0)) {
					eProducto_printOne(arrayProductos[i]);
					puts("|------+-------------------------+-------------------------|--------------------|--------------------|");
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

/// @fn int eProducto_findIndexByIdALTA(eProducto[], int, int)
/// @param arrayProductos
/// @param tam
/// @param optId
/// @return devuelve posición en un array de un determinado ID que debe estar dado de alta. Negativo o 0 si fracasa.
int eProducto_findIndexByIdALTA(eProducto arrayProductos[], int tam, int optId) {
	int retorno = 0;
	int flag = 0;
	int i;
	int IDtoFind = optId;
	if (arrayProductos != NULL) {
		if (tam > 0) {
			//eProducto_printMult(arrayProductos, tam, ALTA); //Lista selección para baja
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
						if (arrayProductos[i].isEmpty == ALTA) {
							if (arrayProductos[i].PK_idProducto == IDtoFind) {
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

/// @fn int eProducto_findIndexById(eProducto[], int, int)
/// @param arrayProductos
/// @param tam
/// @param optId
/// @return Index correspondiente al ID. 0 o negativo si fracasa.
int eProducto_findIndexByIdNoLIBRE(eProducto arrayProductos[], int tam, int optId) {
	int retorno = 0;
	int flag = 0;
	int i;
	int IDtoFind = optId;
	if (arrayProductos != NULL) {
		if (tam > 0) {
			//eProducto_printMult(arrayProductos, tam, ALTA); //Lista selección para baja
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
						if (arrayProductos[i].isEmpty != LIBRE) {
							if (arrayProductos[i].PK_idProducto == IDtoFind) {
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

/// @fn int eProducto_loadProducto(eProducto*)
/// @param p
/// @return
/// Pide por consola datos de un producto y los asigna a una dirección de memoria de una entidad eProducto. Retorna -1 si fracasa, 0 si éxito.
int eProducto_loadProducto(eProducto *p) {
	int ret = 1;
	do{
			if(ret == 1 && utn_getStringWNum("Ingrese nombre del producto a dar de alta.\n", "Error. Reingrese.\n", 3, TAM_NOMPRODUCTO, p->nombreProducto)==0){
				ret = 1;
			}else{
				ret = -1;
			}
			int opt = printMenuGetOption("Seleccione categoría de producto:\n",
					"1) CONSTRUCCION\n"
					"\n"
					"2) DEPORTES\n"
					"\n"
					"3) FARMACIA\n"
					"\n"
					"4) HOGAR\n"
					"\n"
					"5) INMUEBLES\n"
					"\n"
					"6) JUGUETES\n"
					"\n"
					"7) MODA\n"
					"\n"
					"8) TECNOLOGIA\n"
					"\n"
					"9) VEHICULOS\n", "Error. Seleccione una opción válida.", 3,9);
			if(opt > 0){
				p->categoria = opt-1;
				ret = 1;
			}else{
				ret = -1;
			}
			if(utn_getFloat(&p->precio,"Ingrese precio por unidad: \n", "Error. Reingrese.\n", 0, 9999999, 3)==0){
				ret = 1;
			}else{
				ret = -1;
			}
			if(utn_getInt("Ingrese stock: \n", "Error. Debe ingresar al menos una unidad.\n", 1, 99999, 3,
					&p->stock)==0){
				ret=0;
			}else{
				ret = -1;
			}
		}while(ret == 1);
		return ret;
}

/// @fn int addProducto(eProducto*, int, char[], float, short int, int, int)
/// @param arrayProductosItem
/// @param tamProductos
/// @param nombre
/// @param precio
/// @param categoria
/// @param stock
/// @param id
/// @return asigna a una dirección de memoria de una posición en el array de entidades eProducto todos sus datos pasados como parámetros. Devuelve -1 si no hay espacio en array.
int addProducto(eProducto* arrayProductosItem, int tamProductos, char nombre[], float precio, short int categoria, int stock, int id)
{
	int rtn = -1;
	if(arrayProductosItem->isEmpty == ALTA || tamProductos <= 0)
	{
		puts("No hay espacio en array.");
	}else{
		strncpy(arrayProductosItem->nombreProducto,nombre,TAM_NOMPRODUCTO);
		arrayProductosItem->precio = precio;
		arrayProductosItem->PK_idProducto = id;
		arrayProductosItem->categoria = categoria;
		arrayProductosItem->stock = stock;
		arrayProductosItem->isEmpty = ALTA;
		rtn = 0;
	}
	return rtn;

}


/// @fn int eProducto_baja(eProducto[], int, int)
/// @param arrayProductos
/// @param tam
/// @param optId
/// @return asigna "BAJA" al campo isEmpty del producto cuyo ID se pase por parámetro o consola. Retorno negativo si fracasa, 0 si éxito.
int eProducto_baja(eProducto arrayProductos[], int tam, int optId, int optSellerId) {
	int retorno = 0;
	int indexBaja = optId;

	if (arrayProductos != NULL) {
		if (tam > 0) {
			if(optSellerId<0){
				if(optId<=0)
				{
					eProducto_printMult(arrayProductos, CANT_PRODUCTOS, ALTA);
					indexBaja = eProducto_findIndexByIdALTA(arrayProductos, tam, optId); //-1 si no encuentra index a dar de baja, caso contrario index buscado.
				}
				if (indexBaja < 0) {
					retorno = -1;
				} else {
					printf("Index seleccionado: %d\n", indexBaja);
					if (valid_siNo(
							"ESTÁ SEGURO DE QUE DESEA DAR DE BAJA AL PRODUCTO? S/N\n",
							"Error. Ingrese S o N\n", 3)) {

						arrayProductos[indexBaja].isEmpty = BAJA;

						puts("\n\nSE DIO DE BAJA EL PRODUCTO.\n\n");
					} else {
						retorno = -4; // USUARIO NO ESTÁ SEGURO
					}
				}
			}else{
				//Si se le pasa un sellerId
				for(int i = 0; i<tam;i++){
					if(arrayProductos[i].FK_idSeller == optSellerId)
					{
						arrayProductos[i].isEmpty = BAJA;
					}
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

/// @fn int eProducto_SortByCategoria(eProducto[], int, int)
/// @param array
/// @param TAM
/// @param criterio
/// @return Ordena array de entidades eProducto por categoría.
int eProducto_SortByCategoria(eProducto array[], int TAM, int criterio) {
	int retorno = 0;
	int i;
	int j;
	eProducto aux;

	if (array != NULL && TAM > 0) { //Si existe array y límite es válido
		switch (criterio) {
		case -1:
			for (i = 0; i < TAM - 1; i++) {
				for (j = i + 1; j < TAM; j++) {
					if (array[i].isEmpty == ALTA //Verifico que ambos tengan estado "ocupado"
					&& array[j].isEmpty == ALTA) {
						if (array[i].categoria > array[j].categoria) { //Criterio de ordenamiento ASCENDENTE
							aux = array[i]; //Intercambio posiciones
							array[i] = array[j];
							array[j] = aux;
						}
					}
				}
			}
			retorno = 1;
			break;
		case 1:
			for (i = 0; i < TAM - 1; i++) {
				for (j = i + 1; j < TAM; j++) {
					if (array[i].isEmpty == ALTA //Verifico que ambos tengan estado "ocupado"
					&& array[j].isEmpty == ALTA) {
						if (array[i].categoria < array[j].categoria) { //Criterio de ordenamiento DESCENDENTE
							aux = array[i]; //Intercambio posiciones
							array[i] = array[j];
							array[j] = aux;
						}
					}
				}
			}
			retorno = 1;
			break;
		default:
			retorno = 0; //Error en criterio de ordenamiento
			break;
		}
	}
	return retorno;
}

/// @fn int eProducto_SortByCategoria(eProducto[], int, int)
/// @param array
/// @param TAM
/// @param criterio
/// @return Ordena array de entidades eProducto por stock.
int eProducto_SortByStock(eProducto array[], int TAM, int criterio) {
	int retorno = 0;
	int i;
	int j;
	eProducto aux;

	if (array != NULL && TAM > 0) { //Si existe array y límite es válido
		switch (criterio) {
		case -1:
			for (i = 0; i < TAM - 1; i++) {
				for (j = i + 1; j < TAM; j++) {
					if (array[i].isEmpty == ALTA //Verifico que ambos tengan estado "ocupado"
					&& array[j].isEmpty == ALTA) {
						if (array[i].stock > array[j].stock) { //Criterio de ordenamiento ASCENDENTE
							aux = array[i]; //Intercambio posiciones
							array[i] = array[j];
							array[j] = aux;
						}
					}
				}
			}
			retorno = 1;
			break;
		case 1:
			for (i = 0; i < TAM - 1; i++) {
				for (j = i + 1; j < TAM; j++) {
					if (array[i].isEmpty == ALTA //Verifico que ambos tengan estado "ocupado"
					&& array[j].isEmpty == ALTA) {
						if (array[i].stock < array[j].stock) { //Criterio de ordenamiento DESCENDENTE
							aux = array[i]; //Intercambio posiciones
							array[i] = array[j];
							array[j] = aux;
						}
					}
				}
			}
			retorno = 1;
			break;
		default:
			retorno = 0; //Error en criterio de ordenamiento
			break;
		}
	}
	return retorno;
}

/// @fn int eProducto_SortByName(eProducto[], int, int)
/// @param array
/// @param TAM
/// @param criterio
/// @return ordena array de entidades eProducto por nombre
int eProducto_SortByName(eProducto array[], int TAM, int criterio) {
	int retorno = 0;
	int i;
	int j;
	eProducto aux;

	//USAR 1 y -1 PARA ORDEN

	if (array != NULL && TAM > 0) { //Si existe array y límite es válido
		switch (criterio) {
		case -1:
			for (i = 0; i < TAM - 1; i++) {
				for (j = i + 1; j < TAM; j++) {
					if (array[i].isEmpty == ALTA //Verifico que ambos tengan estado "ocupado"
					&& array[j].isEmpty == ALTA) {
						if (strcmp(array[i].nombreProducto, array[j].nombreProducto) > 0) { //Criterio de ordenamiento ASCENDENTE
							aux = array[i]; //Intercambio posiciones
							array[i] = array[j];
							array[j] = aux;
						}
					}
				}
			}
			retorno = 1;
			break;
		case 1:
			for (i = 0; i < TAM - 1; i++) {
				for (j = i + 1; j < TAM; j++) {
					if (array[i].isEmpty == ALTA //Verifico que ambos tengan estado "ocupado"
					&& array[j].isEmpty == ALTA) {
						if (strcmp(array[i].nombreProducto, array[j].nombreProducto) > 0) { //Criterio de ordenamiento DESCENDENTE
							//Intercambio posiciones
							aux = array[i];
							array[i] = array[j];
							array[j] = aux;
						}
					}
				}
			}
			retorno = 1;
			break;
		default:
			retorno = 0; //Error en criterio de ordenamiento
			break;
		}
	}
	return retorno;
}

/// @fn int eProducto_getSellerIDbyProductId(eProducto[], int, int)
/// @param arrayProductos
/// @param tamProductos
/// @param productID
/// @return retorna id de producto correspondiente
int eProducto_getSellerIDbyProductId(eProducto arrayProductos[],int tamProductos,int productID){
	int retorno = 0;
	int flagEncontro=0;
	if(arrayProductos!= NULL && tamProductos > 0)
	{
		for(int i = 0;i<tamProductos;i++){
			if(arrayProductos[i].PK_idProducto==productID){
				flagEncontro=1;
				retorno = arrayProductos[i].FK_idSeller;
			}
		}
		if(flagEncontro==0)
		{
			retorno = -1;
			puts("No se encontro el vendedor correspondiente al ID de producto");
		}
	}else{
		retorno = -2; //array null o tam<=0
	}
	return retorno;
}

