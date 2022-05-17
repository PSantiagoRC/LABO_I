#ifndef TRACKING_USUARIO_PRODUCTO_H_
#define TRACKING_USUARIO_PRODUCTO_H_

#define CANT_TRACKINGS 1000 //CAMBIAR

#include "Producto_Usuario.h"
#include "Tracking.h"
#include <time.h>

#define TIEMPO 1 // 10 segundos cada 10 km, o 1 segundo por cada km de distancia.

int relTrackUsuProd_alta(eTracking arrayTrackings[], eProducto arrayProductos[], eUsuario arrayUsuarios[],
		int tamTrackings, int tamProductos, int tamUsuarios, char correoBuyer[], int idProdCompra);

int relTrackUsuProd_calculaDist(int codPostComp);

int relTrackUsuProd_printMultTrackingsComp(eTracking arrayTrackings[],
		eUsuario arrayUsuarios[], eProducto arrayProductos[], int tamTrackings, int tamUsuarios, int tamProductos,
		char correoBuyer[]);

void relTrackUsuProd_updateTrackingStatus(eTracking arrayTrackings[], int tamTrackings);

int relTrackUsuProd_findIndexByIdENVIAJE(eTracking arrayTrackings[], int tam, int optId);

int relTrackUsuProd_CancelaTrackingsComp(eTracking arrayTrackings[],
		eUsuario arrayUsuarios[], eProducto arrayProductos[], int tamTrackings, int tamUsuarios, int tamProductos,
		char correoBuyer[]);

void relTrackUsuProd_printOneTrackingVend(eTracking t, eProducto arrayProductos[], int tamProductos);

int relTrackUsuProd_printMultTrackingsVend(eTracking arrayTrackings[],
		eUsuario arrayUsuarios[], eProducto arrayProductos[], int tamTrackings, int tamUsuarios, int tamProductos,
		char correoSeller[]);

void relTrackUsuProd_printOneTrackingADMIN(eTracking t, eProducto arrayProductos[], int tamProductos);

void relTrackUsuProd_printMultTrackingsADMIN(eTracking arrayTrackings[],
		eUsuario arrayUsuarios[], eProducto arrayProductos[], int tamTrackings,
		int tamUsuarios, int tamProductos);

long int time_Current(void);
long int time_Add(double secondsAdd);

#endif /* TRACKING_USUARIO_PRODUCTO_H_ */
