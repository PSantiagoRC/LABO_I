#include "Tracking.h"

/*****     ABM B�SICO     *****/

/// @fn int eTracking_init(eTracking[], int)
/// @param arrayTrackings
/// @param tam
/// @return inicializa array de entidades eTracking. 0 si �xito, negativo si fracaso.
int eTracking_init(eTracking arrayTrackings[], int tam) {
	int retorno = 0;
	int i;
	if (arrayTrackings != NULL) {
		if (tam > 0) {
			for (i = 0; i < tam; i++) {
				arrayTrackings[i].isEmpty = LIBRE;
			}
		} else {
			retorno = -2; //tam <=0
		}
	} else {
		retorno = -1;
	}
	return retorno;
}

/// @fn int eTracking_findEmptyIndex(eTracking[], int)
/// @param arrayTrackings
/// @param tam
/// @return encuentra posici�n LIBRE en array de entidades eTracking. Retorna posici�n, o 0 o negativo si fracaso.
int eTracking_findEmptyIndex(eTracking arrayTrackings[], int tam) {
	int retorno = 0;
	int flag = 0;
	int i;

	if (arrayTrackings != NULL) {
		if (tam > 0) {
			for (i = 0; i < tam; i++) {
				if (arrayTrackings[i].isEmpty == LIBRE) {
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

