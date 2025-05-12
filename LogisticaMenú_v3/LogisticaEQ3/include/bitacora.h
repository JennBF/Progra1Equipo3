// LUIS ANGEL MENDEZ FUENTES 9959-24-6845
#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <unordered_map>  // Necesario para utilizar mapas de claves únicas

// Clase encargada de gestionar los códigos únicos por módulo del sistema
class CodigosBitacora {
private:
    // Mapa que asocia cada módulo con su rango inicial de códigos
    static std::unordered_map<std::string, int> rangos;

public:
    // Método que devuelve el siguiente código disponible para un módulo específico
    // Si el módulo no existe en el mapa, se inicializa con el valor base 3000
    static int getCodigo(const std::string& modulo) {
        if (rangos.find(modulo) == rangos.end()) {
            rangos[modulo] = 3000; // Inicializa el código base del módulo
        }
        return rangos[modulo]++; // Retorna el código y lo incrementa para futuras llamadas
    }
};

// Clase encargada de todas las operaciones relacionadas con la bitácora
class bitacora {
public:
    // Registra una acción en el archivo de bitácora con información del usuario, módulo y descripción
    static void registrar(const std::string& usuario,
                          const std::string& modulo,
                          const std::string& descripcion);

    // Método alternativo a registrar (alias), útil para mantener compatibilidad con otros nombres
    static void insertar(const std::string& usuario,
                         const std::string& modulo,
                         const std::string& descripcion) {
        registrar(usuario, modulo, descripcion);
    }

    // Genera una copia de seguridad del archivo de bitácora con la fecha y hora actual en el nombre
    static void generarBackup();

    // Muestra en consola el contenido actual de la bitácora en un formato legible
    static void mostrarBitacora();

    // Muestra el menú interactivo para gestionar la bitácora (ver, buscar, reiniciar, etc.)
    static void menuBitacora();

    // Borra todo el contenido de la bitácora (reinicio total)
    static void reiniciarBitacora();

private:
    // Obtiene la fecha actual del sistema formateada como "dd/mm/yyyy"
    static std::string obtenerFechaActual();
};

#endif // BITACORA_H
