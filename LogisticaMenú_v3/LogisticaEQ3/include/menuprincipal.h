#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#pragma once

#include <vector>
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
#include "usuarios.h"
#include "Transportistas.h"

class MenuPrincipal {
public:
    static void mostrar(std::vector<Clientes>& clientes,
                        std::vector<Proveedor>& proveedores,
                        std::vector<Producto>& productos,
                        usuarios& usuarioActual,
                        std::vector<Transportistas>& lista);
};

#endif // MENUPRINCIPAL_H
