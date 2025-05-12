// LUIS ANGEL MENDEZ FUENTES 9959-24-6845
#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <unordered_map>  // Necesario para utilizar mapas de claves �nicas

// Clase encargada de gestionar los c�digos �nicos por m�dulo del sistema
class CodigosBitacora {
private:
    // Mapa que asocia cada m�dulo con su rango inicial de c�digos
    static std::unordered_map<std::string, int> rangos;

public:
    // M�todo que devuelve el siguiente c�digo disponible para un m�dulo espec�fico
    // Si el m�dulo no existe en el mapa, se inicializa con el valor base 3000
    static int getCodigo(const std::string& modulo) {
        if (rangos.find(modulo) == rangos.end()) {
            rangos[modulo] = 3000; // Inicializa el c�digo base del m�dulo
        }
        return rangos[modulo]++; // Retorna el c�digo y lo incrementa para futuras llamadas
    }
};

// Clase encargada de todas las operaciones relacionadas con la bit�cora
class bitacora {
public:
    // Registra una acci�n en el archivo de bit�cora con informaci�n del usuario, m�dulo y descripci�n
    static void registrar(const std::string& usuario,
                          const std::string& modulo,
                          const std::string& descripcion);

    // M�todo alternativo a registrar (alias), �til para mantener compatibilidad con otros nombres
    static void insertar(const std::string& usuario,
                         const std::string& modulo,
                         const std::string& descripcion) {
        registrar(usuario, modulo, descripcion);
    }

    // Genera una copia de seguridad del archivo de bit�cora con la fecha y hora actual en el nombre
    static void generarBackup();

    // Muestra en consola el contenido actual de la bit�cora en un formato legible
    static void mostrarBitacora();

    // Muestra el men� interactivo para gestionar la bit�cora (ver, buscar, reiniciar, etc.)
    static void menuBitacora();

    // Borra todo el contenido de la bit�cora (reinicio total)
    static void reiniciarBitacora();

private:
    // Obtiene la fecha actual del sistema formateada como "dd/mm/yyyy"
    static std::string obtenerFechaActual();
};

#endif // BITACORA_H
