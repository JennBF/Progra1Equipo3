// LUIS ANGEL MENDEZ FUENTES 9959-24-6845

#include "bitacora.h"         // Inclusión del archivo de cabecera de la clase bitacora
#include <iostream>           // Librería para entrada/salida estándar
#include <ctime>              // Librería para manejo de tiempo (formato de fecha y hora)
#include <sstream>            // Para trabajar con flujos de texto (formato de cadenas)
#include <iomanip>            // Para manipular la presentación (ej. setw)

// Inicialización del mapa estático con los códigos de cada módulo
std::unordered_map<std::string, int> CodigosBitacora::rangos = {
    {"AUTENTICACION", 3000}, {"USUARIOS", 3050}, {"PEDIDOS", 3100},
    {"CLIENTES", 3150}, {"PROVEEDORES", 3200}, {"PRODUCTOS", 3250},
    {"ALMACENES", 3300}, {"TRANSPORTISTAS", 3350}, {"FACTURACION", 3400},
    {"REPORTES", 3450}, {"INVENTARIO", 3500}, {"ENVIOS", 3550}
};

/**
 * Función que registra una acción en la bitácora.
 * @param usuario - Usuario que ejecuta la acción.
 * @param modulo - Nombre del módulo afectado.
 * @param descripcion - Descripción de la acción realizada.
 */
void bitacora::registrar(const std::string& usuario,
                         const std::string& modulo,
                         const std::string& descripcion) {
    std::ifstream check("bitacora.txt"); // Verifica si el archivo existe y si está vacío
    bool isEmpty = check.peek() == std::ifstream::traits_type::eof();
    check.close();

    std::ofstream file("bitacora.txt", std::ios::app); // Abre archivo en modo adjuntar
    int codigo = CodigosBitacora::getCodigo(modulo); // Obtiene el código del módulo

    std::time_t now = std::time(nullptr); // Obtiene el tiempo actual
    char fecha[100];
    std::strftime(fecha, sizeof(fecha), "%d/%m/%Y %H:%M:%S", std::localtime(&now)); // Formatea la fecha

    if (file.is_open()) {
        // Si el archivo está vacío, se escriben los encabezados
        if (isEmpty) {
            file << "-------------------------- BITÁCORA DEL SISTEMA --------------------------\n";
            file << std::left
                 << std::setw(12) << "ID_ACCION"
                 << std::setw(15) << "USUARIO"
                 << std::setw(20) << "MODULO"
                 << std::setw(35) << "DESCRIPCION"
                 << std::setw(20) << "FECHA_HORA" << "\n";
            file << "---------------------------------------------------------------------------\n";
        }

        // Se escribe la nueva línea en la bitácora
        file << std::left
             << std::setw(12) << codigo
             << std::setw(15) << usuario
             << std::setw(20) << modulo
             << std::setw(35) << descripcion
             << std::setw(20) << fecha << "\n";
    }
}

/**
 * Función que retorna la fecha actual en formato dd/mm/yyyy.
 * @return Fecha actual como cadena.
 */
std::string bitacora::obtenerFechaActual() {
    auto now = std::chrono::system_clock::now(); // Tiempo actual del sistema
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y"); // Formatea la fecha
    return oss.str();
}

/**
 * Muestra en pantalla el contenido de la bitácora.
 * Incluye encabezados, líneas registradas y maneja el caso en que el archivo no exista.
 */
void bitacora::mostrarBitacora() {
    system("cls"); // Limpia la pantalla (Windows)
    std::ifstream file("bitacora.txt"); // Abre el archivo de bitácora

    // Encabezado de la bitácora en consola
    std::cout << "\t\t========================================================\n";
    std::cout << "\t\t|                      BITÁCORA                        |\n";
    std::cout << "\t\t========================================================\n";
    std::cout << "\t\t" << std::left
              << std::setw(10) << "CÓDIGO"
              << std::setw(15) << "USUARIO"
              << std::setw(30) << "DESCRIPCIÓN"
              << std::setw(15) << "FECHA" << "\n";
    std::cout << "\t\t---------------------------------------------------------------\n";

    // Imprime línea por línea el contenido del archivo
    if (file.is_open()) {
        std::string linea;
        while (std::getline(file, linea)) {
            std::cout << "\t\t" << linea << "\n";
        }
        file.close();
    } else {
        std::cout << "\t\tNo hay registros en la bitácora.\n";
    }
    std::cout << "\t\t===============================================================\n";
    system("pause"); // Espera una tecla antes de continuar
}

/**
 * Genera un archivo de respaldo (backup) de la bitácora actual con nombre único por fecha y hora.
 */
void bitacora::generarBackup() {
    auto now = std::chrono::system_clock::now(); // Tiempo actual
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    // Nombre del archivo de respaldo con timestamp
    std::ostringstream oss;
    oss << "backup_bitacora_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".txt";

    std::ifstream src("bitacora.txt", std::ios::binary); // Archivo fuente
    std::ofstream dst(oss.str(), std::ios::binary);      // Archivo destino (backup)

    if (src && dst) {
        dst << src.rdbuf(); // Copia el contenido del archivo original al backup
        registrar("SISTEMA", "3106", "Backup de bitácora generado: " + oss.str()); // Registro del backup
        std::cout << "\n\t\tBackup generado exitosamente: " << oss.str() << "\n";
    } else {
        std::cerr << "\n\t\tError al generar backup!\n";
    }
}

/**
 * Elimina todo el contenido del archivo de bitácora.
 * Esto equivale a reiniciar la bitácora.
 */
void bitacora::reiniciarBitacora() {
    std::ofstream file("bitacora.txt", std::ios::trunc); // trunc = borra el contenido
    if (file.is_open()) {
        file.close();
        std::cout << "Bitácora reiniciada con éxito.\n";
    } else {
        std::cout << "Error al reiniciar la bitácora.\n";
    }
}

/**
 * Menú interactivo para gestionar la bitácora.
 * Permite al usuario ver registros, generar backup, buscar (por implementar), y reiniciar la bitácora.
 */
void bitacora::menuBitacora() {
    int opcion;
    do {
        system("cls"); // Limpia la pantalla
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\t|      ADMINISTRACIÓN DE BITÁCORA     |\n";
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\t 1. Ver registros completos\n";
        std::cout << "\t\t 2. Generar backup\n";
        std::cout << "\t\t 3. Buscar por código de usuario\n";
        std::cout << "\t\t 4. Buscar por fecha\n";
        std::cout << "\t\t 5. Reiniciar bitácora\n"; // Opción para limpiar los registros
        std::cout << "\t\t 6. Volver al menú principal\n";
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\tOpción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: mostrarBitacora(); break;
            case 2: generarBackup(); break;
            case 3:
                // Buscar por código de usuario (pendiente de implementación)
                break;
            case 4:
                // Buscar por fecha (pendiente de implementación)
                break;
            case 5: reiniciarBitacora(); break; // Reinicia la bitácora
            case 6: break; // Sale del menú
            default:
                std::cout << "\n\t\tOpción inválida!";
                std::cin.ignore();
                std::cin.get(); // Espera tecla para continuar
        }
    } while(opcion != 6); // Repite hasta que se elija salir
}
