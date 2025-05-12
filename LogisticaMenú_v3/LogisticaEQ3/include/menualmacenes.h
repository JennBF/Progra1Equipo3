//9959 24 11603 GE
#ifndef MENUALMACENES_H
#define MENUALMACENES_H

#include <vector>
#include "Almacen.h"
#include "usuarios.h"

// Clase que gestiona el menú interactivo para operaciones con almacenes
class MenuAlmacenes {
public:
    // Muestra el menú de opciones (agregar, mostrar, modificar, eliminar)
    // Recibe la lista de almacenes y el usuario actual para registrar en bitácora
    static void mostrar(std::vector<Almacen>& lista, usuarios& usuario);
};

#endif
