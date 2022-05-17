#ifndef PRODUCTO_H_
#define PRODUCTO_H_
#include <stdio.h>
#include <stdlib.h>
#include "UTN4.h"

#define TAM_NOMPRODUCTO 25
#define CANT_PRODUCTOS 1000 //CAMBIAR, COINCIDA CON MAIN

//Estados Producto/Usuario
#define LIBRE 0
#define ALTA 1
#define BAJA 2

//Categorias Producto
#define VEHICULO 0
#define INMUEBLE 1
#define TECNOLOGIA 2
#define HOGAR 3
#define CONSTRUCCION 4
#define DEPORTE 5
#define MODA 6
#define JUGUETES 7
#define FARMACIA 8



struct {
	int PK_idProducto;
	int FK_idSeller;
	short int isEmpty;
	char nombreProducto[TAM_NOMPRODUCTO];
	float precio;
	short int categoria;
	int stock;
}typedef eProducto;

/*****     ABM BÁSICO     *****/

int eProducto_init(eProducto arrayProductos[], int tam);
int eProducto_findEmptyIndex(eProducto arrayProductos[], int tam);
void eProducto_printOne(eProducto p);
int eProducto_printMult(eProducto arrayProductos[], int tam, int estado);
int eProducto_findIndexByIdALTA(eProducto arrayProductos[], int tam, int optId);
int eProducto_findIndexByIdNoLIBRE(eProducto arrayProductos[], int tam, int optId);
int eProducto_printMultBySellerWStock(eProducto arrayProductos[], int tam, int estado, int idSeller);
int eProducto_loadProducto(eProducto *p);
int addProducto(eProducto* arrayProductosItem, int tamProductos, char nombre[], float precio, short int categoria, int stock, int id);
int eProducto_getSellerIDbyProductId(eProducto arrayProductos[],int tamProductos,int productID);
int eProducto_printMultNoLIBRE(eProducto arrayProductos[], int tam);
int eProducto_baja(eProducto arrayProductos[], int tam, int optId, int optSellerId);
int eProducto_SortByCategoria(eProducto array[], int TAM, int criterio);
int eProducto_SortByName(eProducto array[], int TAM, int criterio);

#endif /* PRODUCTO_H_ */
