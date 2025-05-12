#ifndef MENUCATALOGOS_H
#define MENUCATALOGOS_H
#pragma once
#include <vector>
#include "usuarios.h"
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
#include "Almacen.h"

class MenuCatalogos {
public:
    static void mostrar(std::vector<Clientes>& clientes,
                       std::vector<Proveedor>& proveedores,
                       std::vector<Producto>& productos,
                       std::vector<Almacen>& almacenes,
                       usuarios& usuarioActual);
};

#endif
