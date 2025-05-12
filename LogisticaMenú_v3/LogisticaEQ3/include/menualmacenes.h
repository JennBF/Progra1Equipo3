#ifndef MENUALMACENES_H
#define MENUALMACENES_H

#include <vector>
#include "Almacen.h"
#include "usuarios.h"

class MenuAlmacenes {
public:
    static void mostrar(std::vector<Almacen>& lista, usuarios& usuario);
};

#endif
