#ifndef MENUADMINISTRACION_H
#define MENUADMINISTRACION_H

#include <iostream>
#include <vector>
#include "administracion.h"
#include "usuarios.h"

class MenuAdministracion {
public:
    void mostrar(std::vector<usuarios>& listaUsuarios, Administracion& admin);
};

#endif // MENUADMINISTRACION_H
