#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <fstream>
using namespace std;

class bitacora {
private:
    string nombreUsuario;
    string codigoAccion;
    string descripcion;
public:
    void insertar(string usuario, string codigo, string accion);
    void desplegar();
    void menuBitacora(); // Para acceso desde men� de administraci�n
};

#endif // BITACORA_H
