#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <vector>
#include <string>
#include "bitacora.h"

class Producto {
public:
    std::string codigo;
    std::string nombre;
    double precio;
    int stock;

    // Métodos CRUD
    static void agregar(std::vector<Producto>& lista, const std::string& usuarioActual);
    static void mostrar(const std::vector<Producto>& lista);
    static void modificar(std::vector<Producto>& lista, const std::string& usuarioActual, const std::string& codigo);
    static void eliminar(std::vector<Producto>& lista, const std::string& usuarioActual, const std::string& codigo);

    // Manejo de archivos
    static void guardarEnArchivo(const std::vector<Producto>& lista);
    static void cargarDesdeArchivo(std::vector<Producto>& lista);

    // Validaciones
    static bool esCodigoValido(const std::string& codigo);
    static std::string generarCodigoUnico(const std::vector<Producto>& lista);
    static bool codigoDisponible(const std::vector<Producto>& lista, const std::string& codigo);
};

#endif // PRODUCTO_H
