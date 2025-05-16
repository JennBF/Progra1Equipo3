#ifndef CLIENTES_H
#define CLIENTES_H

#include <vector>
#include <string>

/**
 * @class Clientes
 * @brief Clase que representa a un cliente y gestiona operaciones CRUD y de persistencia.
 */
class Clientes {
private:
    /// Identificador único del cliente (rango permitido: 3107–3157)
    std::string id;

    /// Nombre completo del cliente
    std::string nombre;

    /// Dirección del cliente
    std::string direccion;

    /// Número de teléfono del cliente
    std::string telefono;

    /// NIT (Número de Identificación Tributaria) del cliente
    std::string nit;

public:
    // ====================== MÉTODOS CRUD ======================

    static void agregar(std::vector<Clientes>& lista, const std::string& usuarioActual);
    static void mostrar(const std::vector<Clientes>& lista);
    static void modificar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& id);
    static void eliminar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& id);

    // ====================== MÉTODOS DE ARCHIVO ======================

    /**
     * @brief Guarda los clientes en archivo binario y tabular.
     *        - Binario: `clientes.dat`
     *        - Tabular: `Clientes.txt` (con seguridad por `Clientes.tmp`)
     * @param lista Lista de clientes a guardar.
     */
    static void guardarEnArchivos(const std::vector<Clientes>& lista);

    /**
     * @brief Guarda la lista de clientes en `Clientes.txt` en formato tabular.
     */
    static void guardarEnArchivo(const std::vector<Clientes>& lista);

    /**
     * @brief Carga los clientes desde `Clientes.txt` a la lista.
     */
    static void cargarDesdeArchivo(std::vector<Clientes>& lista);

    // ====================== MÉTODOS DE GESTIÓN DE ID ======================

    static std::string generarIdUnico(const std::vector<Clientes>& lista);
    static bool idDisponible(const std::vector<Clientes>& lista, const std::string& id);
    static bool esIdValido(const std::string& id);

    // ====================== GETTERS ======================

    std::string getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getDireccion() const { return direccion; }
    std::string getTelefono() const { return telefono; }
    std::string getNit() const { return nit; }
};

#endif // CLIENTES_H


