#ifndef MENUPRODUCTOS_H
#define MENUPRODUCTOS_H

#include <vector>
#include "Producto.h"
#include "usuarios.h"

class MenuProductos {
public:
    static void mostrar(std::vector<Producto>& listaProductos, usuarios& usuarioActual);
};

#endif // MENUPRODUCTOS_H
