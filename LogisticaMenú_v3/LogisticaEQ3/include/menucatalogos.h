#ifndef MENUCATALOGOS_H
#define MENUCATALOGOS_H
#pragma once
#include <vector>
#include "usuarios.h"
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
<<<<<<< HEAD
=======
#include "Almacen.h"

>>>>>>> f25303509eeb8edd96c5008594897716d355c883
class MenuCatalogos {
public:
    static void mostrar(std::vector<Clientes>& clientes,
                       std::vector<Proveedor>& proveedores,
                       std::vector<Producto>& productos,
                       std::vector<Almacen>& almacenes,
                       usuarios& usuarioActual);
};

#endif
