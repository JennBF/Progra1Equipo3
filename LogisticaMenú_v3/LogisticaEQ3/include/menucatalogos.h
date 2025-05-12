#ifndef MENUCATALOGOS_H
#define MENUCATALOGOS_H
#pragma once
#include <vector>
#include "usuarios.h"
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
class MenuCatalogos {
public:
    static void mostrar(std::vector<Clientes>& clientes,
                       std::vector<Proveedor>& proveedores,
                       std::vector<Producto>& productos,
                       usuarios& usuarioActual);
};

#endif
