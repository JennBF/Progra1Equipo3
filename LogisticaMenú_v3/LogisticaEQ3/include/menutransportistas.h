#ifndef MENU_TRANSPORTISTAS_H
#define MENU_TRANSPORTISTAS_H
#include <vector>
#include "Transportistas.h"
#include "usuarios.h"
#include "globals.h"

class MenuTransportistas {
public:
    static void mostrar(std::vector<Transportistas>& lista, usuarioActual);
    static void agregar(std::vector<Transportistas>& lista);
    static void modificar(std::vector<Transportistas>& lista);
    static void eliminar(std::vector<Transportistas>& lista);
};

#endif // MENUTRANSPORTISTAS_H
