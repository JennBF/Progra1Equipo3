#ifndef BACKUP_H
#define BACKUP_H

#include <string>
#include <vector>

//JENNIFER BARRIOS FLORES COORD EQ:3

// Clase Backup que permite realizar copias de seguridad y restaurarlas
class Backup {
public:
    // Muestra el menú principal de gestión de backups
    static void mostrarMenuBackup();

private:
    // Muestra el menú para seleccionar una clase específica
    static void menuPorClase();

    // Realiza un backup de todos los archivos del sistema
    static void crearBackupGlobal();

    // Restaura todos los archivos del sistema desde sus backups
    static void restaurarBackupGlobal();

    // Realiza un backup de un archivo específico
    static void crearBackupDe(const std::string& archivoOriginal);

    // Restaura un archivo específico desde su backup
    static void restaurarBackupDe(const std::string& archivoOriginal);

    // Copia un archivo origen a un destino (modo binario)
    static bool copiarArchivo(const std::string& origen, const std::string& destino);

    // Devuelve una lista con los nombres base de las clases maestras
    static std::vector<std::string> clasesMaestras();

    // Devuelve una lista con los nombres base de las clases transaccionales
    static std::vector<std::string> clasesTransaccionales();

    // Muestra cuáles backups binarios están disponibles
    static void mostrarBackupsDisponibles();
};

#endif
