#ifndef MENUTRANSPORTISTAS_H
#define MENUTRANSPORTISTAS_H
#include <iostream>
#include <vector>
#include "transportistas.h"
#include "usuarios.h"

class MenuTransportistas {
public:
    void mostrar(std::vector<Transportistas>& listaTransportistas, usuarios& usuarioActual);
};

#endif // MENUTRANSPORTISTAS_H
