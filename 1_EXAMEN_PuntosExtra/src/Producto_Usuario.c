#include "Producto_Usuario.h"

//id Autoincremental para productos
static int idAutoProd = 20000;
static int rel_Producto_getId(void);
static int rel_Producto_getId() {
	return idAutoProd++;
}

/// @fn int rel_Producto_Usu_alta(eProducto[], eUsuario[], int, int, char[])
/// @param arrayProductos
/// @param arrayUsuarios
/// @param tamProductos
/// @param tamUsuarios
/// @param correoSeller
/// @return da de alta producto en array de entidades eProducto
int rel_Producto_Usu_alta(eProducto arrayProductos[], eUsuario arrayUsuarios[],
		int tamProductos, int tamUsuarios, char correoSeller[]) {
	int retorno = 0;
	int emptyIndexProductos;
	int sellerIndex;
	int sellerId;
	int retLoad;
	eProducto productoBuffer;

	if (arrayProductos != NULL && arrayUsuarios != NULL) {
		if (tamProductos > 0 && tamUsuarios > 0) {

			if (valid_siNo("Desea reponer stock de algún producto? S/N\n",
					"Error,  ingrese S o N\n", 3)) {
				rel_Producto_Usu_reponer(arrayProductos, arrayUsuarios,
						tamUsuarios, tamProductos, correoSeller);
			}

			if (valid_siNo("Desea vender algún producto nuevo? S/N\n",
					"Error,  ingrese S o N\n", 3)) {
				emptyIndexProductos = eProducto_findEmptyIndex(arrayProductos,
						tamProductos); //Ret index libre o -1 si no hay
				sellerIndex = eUsuario_findIndexByCorreo(arrayUsuarios,
						tamUsuarios, correoSeller);
				sellerId = arrayUsuarios[sellerIndex].PK_idUsuario;

				if (emptyIndexProductos >= 0 && sellerIndex >= 0
						&& sellerId >= 0) {
					retLoad = eProducto_loadProducto(&productoBuffer); //Carga nomProd, categoria, price, precio, stock
					if (retLoad == 0) {

						productoBuffer.PK_idProducto = rel_Producto_getId();

						productoBuffer.isEmpty = ALTA; //Switch state a ALTA.
						productoBuffer.FK_idSeller = sellerId; //Id del vendedor que da de alta el producto

						if (valid_siNo(
								"ESTÁ SEGURO DE QUE DESEA REALIZAR EL ALTA? S/N\n",
								"Error. Ingrese S o N.\n", 3)) {
							if (addProducto(
									&arrayProductos[emptyIndexProductos],
									tamProductos, productoBuffer.nombreProducto,
									productoBuffer.precio,
									productoBuffer.categoria,
									productoBuffer.stock,
									productoBuffer.PK_idProducto) == 0) {
								arrayProductos[emptyIndexProductos].FK_idSeller =
										productoBuffer.FK_idSeller; //Se carga por fuera de addProducto
								puts("Carga de producto exitosa!");

								printf("Index: %d\n", emptyIndexProductos);
								printf("Nombre: %s\n",
										arrayProductos[emptyIndexProductos].nombreProducto);
								printf("Precio: %f\n",
										arrayProductos[emptyIndexProductos].precio);
								printf("Categoria: %d\n",
										arrayProductos[emptyIndexProductos].categoria);
								printf("Stock: %d\n",
										arrayProductos[emptyIndexProductos].stock);
								printf("IDproducto: %d\n",
										arrayProductos[emptyIndexProductos].PK_idProducto);
								printf("IDvendedor: %d\n",
										arrayProductos[emptyIndexProductos].FK_idSeller);

							} else {
								puts(
										"Error en la carga de proudcto a base de datos.");
								retorno = -6;
							}
						} else {
							puts("Se decidió no dar el alta");
							retorno = -5; //No quiso dar el alta
						}
					} else {
						puts("Falla en la carga de datos de producto");
						retorno = -4; //Falla en loadProducto
					}
				} else {
					puts(
							"Base de productos completa o no se encuentra al vendedor");
					retorno = -3; //Array lleno
				}
			}

		} else {
			puts("Tamaño de bases insuficiente.");
			retorno = -2; // Len mal definido
		}
	} else {
		puts("Error en base provista.");
		retorno = -1; // Array Null
	}
	return retorno;
}

int rel_Producto_Usu_reponer(eProducto arrayProductos[],eUsuario arrayUsuarios[], int tamUsuarios, int tamProductos, char correoSeller[]){
	int retorno = 0;
	int indexSeller;
	int idSeller;
	int idProdReponer;
	int indexProdReponer;
	int nuevoStock;

	if(arrayProductos!= NULL && arrayUsuarios!= NULL && tamProductos>0 && tamUsuarios>0){
		indexSeller = eUsuario_findIndexByCorreo(arrayUsuarios, tamUsuarios, correoSeller);
		idSeller = arrayUsuarios[indexSeller].PK_idUsuario;
		eProducto_printMultBySellerAllStates(arrayProductos, tamProductos, LIBRE, idSeller);

		if(!utn_getInt("Ingrese ID del producto a reponer.\n", "Error. Reintente.", 1, 99999, 3, &idProdReponer)){
			indexProdReponer = eProducto_findIndexByIdNoLIBRE(arrayProductos, tamProductos, idProdReponer);
			if(!utn_getInt("Ingrese cantidad de unidades a agregar.\n", "Error. Reintente.", 1, 999999, 3, &nuevoStock)){
				arrayProductos[indexProdReponer].stock += nuevoStock;
				arrayProductos[indexProdReponer].isEmpty = ALTA;
			}else{
				retorno = -1;
			}
		}else{
			retorno = -2;
		}
	}else{
		retorno = -3;
	}
	return retorno;
}


/// @fn void eProducto_hardcode(eProducto[], int)
/// @param arrayProductos
/// @param tamProductos
/// Usada para hardcodear productos en el array de productos.
void relProducto_Usu_hardcode(eProducto arrayProductos[],int tamProductos){

	int id_0 = rel_Producto_getId();
	arrayProductos[0].FK_idSeller = 10001;
	addProducto(&arrayProductos[0], tamProductos, "Termo Lumilagro", 500, 3, 5, id_0);

	int id_1 = rel_Producto_getId();
	arrayProductos[1].FK_idSeller = 10001;
	addProducto(&arrayProductos[1], tamProductos, "VW Gol", 5000000, 8, 1, id_1);

	int id_2 = rel_Producto_getId();
	arrayProductos[2].FK_idSeller = 10002;
	addProducto(&arrayProductos[2], tamProductos, "Remera Levis", 3000, 6, 30, id_2);

	int id_3 = rel_Producto_getId();
	arrayProductos[3].FK_idSeller = 10002;
	addProducto(&arrayProductos[3], tamProductos, "Notebook Dell", 200000, 7, 5, id_3);

	int id_4 = rel_Producto_getId();
	arrayProductos[4].FK_idSeller = 10003;
	addProducto(&arrayProductos[4], tamProductos, "Auriculares Sony", 4000, 7, 20, id_4);
}

/*Del main
//				  							idProd  idSeller isEmpty  nomProd	precio  categ  stock
eProducto arrayProductos[CANT_PRODUCTOS] = {{10000, 10001, ALTA, "Termo Peavody", 5000, 3, 10},
										   {10001, 10001, ALTA, "VW Gol", 5000000, 0, 1},
										   {10002, 10002, ALTA, "Remera Levis", 3000, 6, 30},
										   {10003, 10001, ALTA, "Notebook Dell", 200000, 2, 5},
										   {10004, 10001, BAJA, "Auriculares Sony", 4000, 2, 20}};
*/
