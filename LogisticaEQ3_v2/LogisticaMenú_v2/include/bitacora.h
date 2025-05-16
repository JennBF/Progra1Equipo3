#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <unordered_map>

/**
 * @struct RegistroBitacora
 * @brief Representa un registro binario en la bit�cora.
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
 * @brief Asigna c�digos �nicos incrementales para cada m�dulo en la bit�cora.
 */
class CodigosBitacora {
private:
    static std::unordered_map<std::string, int> rangos;

public:
    /**
     * @brief Obtiene el c�digo incremental para un m�dulo espec�fico.
     * @param modulo Nombre del m�dulo.
     * @return C�digo �nico para el registro actual.
     */
    static int getCodigo(const std::string& modulo);
};

/**
 * @class bitacora
 * @brief Gestiona la bit�cora del sistema: registro, visualizaci�n, backup y reinicio.
 */
class bitacora {
public:
    /**
     * @brief Registra una acci�n en la bit�cora con usuario, m�dulo y descripci�n.
     * @param usuario Usuario que realiza la acci�n.
     * @param modulo M�dulo al que pertenece la acci�n.
     * @param descripcion Descripci�n del evento.
     */
    static void registrar(const std::string& usuario,
                          const std::string& modulo,
                          const std::string& descripcion);

    /**
     * @brief Genera un backup de la bit�cora con timestamp.
     */
    static void generarBackup();

    /**
     * @brief Muestra el contenido completo de la bit�cora en consola.
     */
    static void mostrarBitacora();

    /**
     * @brief Men� interactivo para administrar la bit�cora.
     */
    static void menuBitacora();

    /**
     * @brief Reinicia (vac�a) la bit�cora.
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
