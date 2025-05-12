//Angoly Araujo Mayo 2025 9959-24-17623
#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <vector>
#include <string>

class Proveedor {
public:

    std::string getId() const;
    std::string getNombre() const;
    // Ajustar firmas de funciones según lo que requiere el menú
    static void agregar(std::vector<Proveedor>& lista, const std::string& usuarioActual);
    static void modificar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id);
    static void eliminar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id);
    static void mostrar(const std::vector<Proveedor>& lista);

    // Métodos para la bitácora (suponiendo que los necesitarás)
    static void guardarEnArchivo(const std::vector<Proveedor>& lista);
    static void cargarDesdeArchivo(std::vector<Proveedor>& lista);

    // Funciones adicionales de validación
    static std::string generarIdUnico(const std::vector<Proveedor>& lista);
    static bool idDisponible(const std::vector<Proveedor>& lista, const std::string& id);
    static bool esIdValido(const std::string& id);

private:
    std::string id;
    std::string nombre;
    std::string telefono;
    // Otros miembros de Proveedor
};

#endif // PROVEEDOR_H




