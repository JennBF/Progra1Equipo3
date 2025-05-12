//9959 24 11603 GE
#ifndef ALMACEN_H
#define ALMACEN_H

#include <vector>
#include <string>
#include "bitacora.h"

// Clase que representa un almacén dentro del sistema
class Almacen {
public:
    // Atributos públicos del almacén
    std::string id;          // ID único autogenerado en el rango 3260-3310
    std::string direccion;   // Dirección física del almacén
    int capacidad;           // Capacidad en metros cuadrados (m²)
    std::string responsable; // Nombre del encargado del almacén
    std::string contacto;    // Información de contacto del responsable
    std::string estado;      // Estado operativo: "operativo" o "en mantenimiento"

    // Métodos públicos (CRUD)

    // Agrega un nuevo almacén a la lista y lo registra en la bitácora
    static void agregar(std::vector<Almacen>& lista, const std::string& usuario);

    // Muestra en consola la lista de almacenes
    static void mostrar(const std::vector<Almacen>& lista);

    // Modifica los datos de un almacén existente, identificado por ID
    static void modificar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id);

    // Elimina un almacén de la lista, identificado por ID
    static void eliminar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id);

    // Métodos de persistencia (archivo)

    // Guarda todos los almacenes en un archivo de texto
    static void guardarEnArchivo(const std::vector<Almacen>& lista);

    // Carga los almacenes desde un archivo de texto
    static void cargarDesdeArchivo(std::vector<Almacen>& lista);

private:
    // Métodos privados para validación interna

    // Genera un ID único dentro del rango permitido, asegurando que no se repita
    static std::string generarID(const std::vector<Almacen>& lista);

    // Verifica si el estado ingresado es válido ("operativo" o "en mantenimiento")
    static bool validarEstado(const std::string& estado);
};

#endif
