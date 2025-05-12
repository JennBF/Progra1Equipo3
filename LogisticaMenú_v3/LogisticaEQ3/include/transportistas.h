#ifndef TRANSPORTISTAS_H
#define TRANSPORTISTAS_H
#include <iostream>
#include <vector>
#include <string>

class Transportistas{

public:
    std::string id;
    std::string nombre;
    std::string telefono;
    std::string vehiculo;
    std::string disponibilidad;

    // Métodos estáticos
    static std::string generarIdUnico(const std::vector<Transportistas>& lista);
    static bool idDisponible(const std::vector<Transportistas>& lista, const std::string& id);
    static bool esIdValido(const std::string& id);

    // Métodos de instancia
    void agregar(std::vector<Transportistas>& lista, const std::string& usuarioActual);
    void mostrar(const std::vector<Transportistas>& lista);
    void modificar(std::vector<Transportistas>& lista, const std::string& usuarioActual, const std::string& id);
    void eliminar(std::vector<Transportistas>& lista, const std::string& usuarioActual, const std::string& id);
    void guardarEnArchivo(const std::vector<Transportistas>& lista);
    void cargarDesdeArchivo(std::vector<Transportistas>& lista);
};

#endif // TRANSPORTISTAS_H
