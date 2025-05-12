//9959 24 11603 GE
#ifndef ALMACEN_H
#define ALMACEN_H

#include <vector>
#include <string>
#include "bitacora.h"

// Clase que representa un almac�n dentro del sistema
class Almacen {
public:
    // Atributos p�blicos del almac�n
    std::string id;          // ID �nico autogenerado en el rango 3260-3310
    std::string direccion;   // Direcci�n f�sica del almac�n
    int capacidad;           // Capacidad en metros cuadrados (m�)
    std::string responsable; // Nombre del encargado del almac�n
    std::string contacto;    // Informaci�n de contacto del responsable
    std::string estado;      // Estado operativo: "operativo" o "en mantenimiento"

    // M�todos p�blicos (CRUD)

    // Agrega un nuevo almac�n a la lista y lo registra en la bit�cora
    static void agregar(std::vector<Almacen>& lista, const std::string& usuario);

    // Muestra en consola la lista de almacenes
    static void mostrar(const std::vector<Almacen>& lista);

    // Modifica los datos de un almac�n existente, identificado por ID
    static void modificar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id);

    // Elimina un almac�n de la lista, identificado por ID
    static void eliminar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id);

    // M�todos de persistencia (archivo)

    // Guarda todos los almacenes en un archivo de texto
    static void guardarEnArchivo(const std::vector<Almacen>& lista);

    // Carga los almacenes desde un archivo de texto
    static void cargarDesdeArchivo(std::vector<Almacen>& lista);

private:
    // M�todos privados para validaci�n interna

    // Genera un ID �nico dentro del rango permitido, asegurando que no se repita
    static std::string generarID(const std::vector<Almacen>& lista);

    // Verifica si el estado ingresado es v�lido ("operativo" o "en mantenimiento")
    static bool validarEstado(const std::string& estado);
};

#endif
