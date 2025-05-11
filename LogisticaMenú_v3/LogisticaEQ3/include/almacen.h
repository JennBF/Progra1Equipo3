#ifndef ALMACEN_H
#define ALMACEN_H

#include <vector>
#include <string>
#include "bitacora.h"

class Almacen {
public:
    std::string id;          // Autogenerado (3260-3310)
    std::string direccion;
    int capacidad;
    std::string responsable;
    std::string contacto;
    std::string estado;      // "operativo"/"en mantenimiento"

    // M�todos CRUD (id�nticos a Clientes)
    static void agregar(std::vector<Almacen>& lista, const std::string& usuario);
    static void mostrar(const std::vector<Almacen>& lista);
    static void modificar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id);
    static void eliminar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id);

    // M�todos de archivo
    static void guardarEnArchivo(const std::vector<Almacen>& lista);
    static void cargarDesdeArchivo(std::vector<Almacen>& lista);

private:
    // Validaciones espec�ficas
    static std::string generarID(const std::vector<Almacen>& lista);
    static bool validarEstado(const std::string& estado);
};

#endif
