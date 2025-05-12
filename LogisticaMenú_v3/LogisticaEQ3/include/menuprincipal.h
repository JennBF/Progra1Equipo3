#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#pragma once
#include <vector>
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
#include "Almacen.h"
#include "usuarios.h"

class MenuPrincipal {
public:
    static void mostrar(std::vector<Clientes>& clientes,
<<<<<<< HEAD
                        std::vector<Proveedor>& proveedores,
                        std::vector<Producto>& productos,
                        usuarios& usuarioActual
                        );
=======
                       std::vector<Proveedor>& proveedores,
                       std::vector<Producto>& productos,
                       std::vector<Almacen>& almacenes,
                       usuarios& usuarioActual);
>>>>>>> f25303509eeb8edd96c5008594897716d355c883
};

#endif // MENUPRINCIPAL_H
