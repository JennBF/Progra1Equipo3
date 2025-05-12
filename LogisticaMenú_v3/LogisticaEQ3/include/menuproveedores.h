//Angoly Araujo Mayo 2025 9959-24-17623

#ifndef MENUPROVEEDORES_H
#define MENUPROVEEDORES_H
#pragma once

#include <vector>
#include "proveedor.h"
#include "usuarios.h"

class MenuProveedores {
public:
    static void mostrar(std::vector<Proveedor>& lista, usuarios& usuarioActual);
};

#endif // MENUPROVEEDORES_H

