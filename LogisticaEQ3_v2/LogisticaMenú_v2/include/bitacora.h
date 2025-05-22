#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <unordered_map>

/**
 * @struct RegistroBitacora
 * @brief Representa un registro binario en la bitácora.
 */
struct RegistroBitacora {
    int codigo;
    char usuario[50];
    char modulo[50];
    char descripcion[100];
    char fechaHora[50];
};
/**
 * @class CodigosBitacora
 * @brief Asigna códigos únicos incrementales para cada módulo en la bitácora.
 */
class CodigosBitacora {
private:
    static std::unordered_map<std::string, int> rangos;

public:
    /**
     * @brief Obtiene el código incremental para un módulo específico.
     * @param modulo Nombre del módulo.
     * @return Código único para el registro actual.
     */
    static int getCodigo(const std::string& modulo);
};

/**
 * @class bitacora
 * @brief Gestiona la bitácora del sistema: registro, visualización, backup y reinicio.
 */
class bitacora {
public:
    /**
     * @brief Registra una acción en la bitácora con usuario, módulo y descripción.
     * @param usuario Usuario que realiza la acción.
     * @param modulo Módulo al que pertenece la acción.
     * @param descripcion Descripción del evento.
     */
    static void registrar(const std::string& usuario,
                          const std::string& modulo,
                          const std::string& descripcion);

    /**
     * @brief Genera un backup de la bitácora con timestamp.
     */
    static void generarBackup();

    /**
     * @brief Muestra el contenido completo de la bitácora en consola.
     */
    static void mostrarBitacora();

    /**
     * @brief Menú interactivo para administrar la bitácora.
     */
    static void menuBitacora();

    /**
     * @brief Reinicia (vacía) la bitácora.
     */
    static void reiniciarBitacora();
        /**
     * @brief Muestra el contenido del archivo binario bitacora.dat en consola.
     */
    static void mostrarBitacoraBinaria();


private:
    /**
     * @brief Obtiene la fecha actual en formato "dd/mm/yyyy".
     * @return Fecha actual como string.
     */
    static std::string obtenerFechaActual();
};

#endif // BITACORA_H
