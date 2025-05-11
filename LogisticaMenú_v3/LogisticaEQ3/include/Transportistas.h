#ifndef MENU_TRANSPORTISTAS_H
#define MENU_TRANSPORTISTAS_H
#include <vector>
#include <string>
#include "Transportistas.h"
#include "usuarios.h"

class MenuTransportistas {
public:
    static void mostrar(std::vector<Transportistas>& listaTransportistas, usuarios& usuarioActual);
};

#endif
