#ifndef TRACKING_H_
#define TRACKING_H_
#include <stdio.h>
#include <stdlib.h>
#include "UTN4.h"

//Estados Tracking
#define LIBRE 0
#define EN_VIAJE 1
#define ENTREGADO 2
#define CANCELADO 3

#define TAM_CORREO 25
#define TAM_PASSWORD 10
#define TAM_DIRECCION 50

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

/*****     ABM BÁSICO     *****/

int eTracking_init(eTracking arrayTrackings[], int tam);
int eTracking_findEmptyIndex(eTracking arrayTrackings[], int tam);

#endif /* TRACKING_H_ */
