#ifndef MENUADMINISTRACION_H
#define MENUADMINISTRACION_H

#include <vector>
#include "administracion.h"
#include "usuarios.h"

class MenuAdministracion {
public:
    static void mostrar(std::vector<Administracion>& listaAdministradores, usuarios& usuarioActual);
};

#endif // MENUADMINISTRACION_H
