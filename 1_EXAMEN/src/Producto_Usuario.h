#ifndef PRODUCTO_USUARIO_H_
#define PRODUCTO_USUARIO_H_

#include "Usuario.h"
#include "Producto.h"

int rel_Producto_Usu_alta(eProducto arrayProductos[], eUsuario arrayUsuarios[],
		int tamProductos, int tamUsuarios, char correoSeller[]);

void relProducto_Usu_hardcode(eProducto arrayProductos[],int tamProductos);

#endif /* PRODUCTO_USUARIO_H_ */
