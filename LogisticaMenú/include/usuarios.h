#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include "bitacora.h"

class usuarios {
private:
    std::string id;
    std::string nombre;
    std::string contrasena;
public:
    usuarios();
    ~usuarios();
    bool loginUsuarios();
    void registrarUsuario(); // Movido a p�blico para acceso desde login
    bool buscarUsuario(const std::string& user, const std::string& pass);
    std::string getNombre();
    void setNombre(const std::string& nombre);
    void menuUsuarios();
    void consultarUsuarios();
};

#endif // USUARIOS_H
