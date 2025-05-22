#include "backup.h"     // Incluye la declaración de la clase Backup
#include <iostream>     // Para entrada y salida estándar
#include <fstream>      // Para manejo de archivos binarios

using namespace std;

// Función principal que muestra el menú del sistema de backups
void Backup::mostrarMenuBackup() {
    int opcion;
    do {
        system("cls");  // Limpia la pantalla para mejor visualización
        cout << "\t\t========================================\n";
        cout << "\t\t|            MENU BACKUP               |\n";
        cout << "\t\t========================================\n";
        cout << "\t\t 1. Backup total\n";                    // Crea backup de todos los archivos
        cout << "\t\t 2. Restaurar total\n";                 // Restaura todos los archivos
        cout << "\t\t 3. Backup por clase\n";                // Backup de solo una clase
        cout << "\t\t 4. Restaurar por clase\n";             // Restauración de una clase
        cout << "\t\t 5. Ver respaldos disponibles\n";       // Ver qué backups existen
        cout << "\t\t 6. Volver\n";
        cout << "\t\t========================================\n";
        cout << "\t\tIngrese su opcion: ";
        cin >> opcion;

        // Ejecuta según la opción seleccionada
        switch (opcion) {
            case 1: crearBackupGlobal(); break;
            case 2: restaurarBackupGlobal(); break;
            case 3: menuPorClase(); break;
            case 4: menuPorClase(); break;  // El tipo de acción se elige dentro del menú
            case 5: mostrarBackupsDisponibles(); break;
            case 6: return;                 // Salir del menú
            default:
                cout << "\t\tOpcion invalida.\n";
                system("pause");
        }
    } while (true);  // Ciclo hasta que el usuario elija salir
}

// Muestra el menú de clases disponibles y permite hacer backup/restaurar de una clase
void Backup::menuPorClase() {
    // Se combinan clases maestras y transaccionales
    vector<string> clases = clasesMaestras();
    vector<string> transacciones = clasesTransaccionales();
    clases.insert(clases.end(), transacciones.begin(), transacciones.end());

    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================\n";
        cout << "\t\t|     BACKUP / RESTAURAR POR CLASE     |\n";
        cout << "\t\t========================================\n";

        // Mostrar lista numerada de clases
        for (size_t i = 0; i < clases.size(); ++i) {
            cout << "\t\t " << (i + 1) << ". " << clases[i] << endl;
        }

        cout << "\t\t " << (clases.size() + 1) << ". Volver\n";
        cout << "\t\t========================================\n";
        cout << "\t\tIngrese su opcion: ";
        cin >> opcion;

        // Validación del número ingresado
        if (opcion < 1 || opcion > static_cast<int>(clases.size()) + 1) {
            cout << "\t\tOpcion invalida.\n";
            system("pause");
            continue;
        }

        // Salir si elige la última opción
        if (opcion == static_cast<int>(clases.size()) + 1) return;

        // Generar nombre de archivo original
        string archivo = clases[opcion - 1] + ".bin";

        // Preguntar si desea backup o restaurar
        int accion;
        cout << "\t\t1. Backup\n";
        cout << "\t\t2. Restaurar\n";
        cout << "\t\tElija acción: ";
        cin >> accion;

        if (accion == 1)
            crearBackupDe(archivo);     // Realiza backup de archivo seleccionado
        else if (accion == 2)
            restaurarBackupDe(archivo); // Restaura desde backup
        else
            cout << "\t\tAcción no válida.\n";

        system("pause");

    } while (true);
}

// Recorre todos los archivos del sistema y los respalda individualmente
void Backup::crearBackupGlobal() {
    vector<string> todos = clasesMaestras();
    vector<string> trans = clasesTransaccionales();
    todos.insert(todos.end(), trans.begin(), trans.end());

    for (const auto& clase : todos)
        crearBackupDe(clase + ".bin");  // Llama a la función específica por cada clase

    cout << "\n\tBackup global completado.\n";
    system("pause");
}

// Recorre todos los archivos y los restaura desde sus respectivos backups
void Backup::restaurarBackupGlobal() {
    vector<string> todos = clasesMaestras();
    vector<string> trans = clasesTransaccionales();
    todos.insert(todos.end(), trans.begin(), trans.end());

    for (const auto& clase : todos)
        restaurarBackupDe(clase + ".bin");

    cout << "\n\tRestauración global completada.\n";
    system("pause");
}

// Crea un archivo backup binario a partir de un archivo original
void Backup::crearBackupDe(const string& archivoOriginal) {
    // Genera nombre de respaldo (ej. clientes_backup.bin)
    string backup = archivoOriginal.substr(0, archivoOriginal.find(".bin")) + "_backup.bin";

    // Copia el contenido original al archivo backup
    if (copiarArchivo(archivoOriginal, backup))
        cout << "\tBackup creado para: " << archivoOriginal << " como " << backup << endl;
    else
        cout << "\tError al crear backup de: " << archivoOriginal << endl;
}

// Restaura el archivo original copiando desde el archivo de backup
void Backup::restaurarBackupDe(const string& archivoOriginal) {
    string backup = archivoOriginal.substr(0, archivoOriginal.find(".bin")) + "_backup.bin";

    // Verifica si el backup existe
    ifstream test(backup, ios::binary);
    if (!test.good()) {
        cout << "\tBackup no encontrado: " << backup << endl;
        return;
    }

    // Copia el backup al archivo original
    if (copiarArchivo(backup, archivoOriginal))
        cout << "\tRestaurado: " << archivoOriginal << " desde " << backup << endl;
    else
        cout << "\tError al restaurar: " << archivoOriginal << endl;
}

// Función que copia el contenido completo de un archivo binario a otro
bool Backup::copiarArchivo(const string& origen, const string& destino) {
    ifstream in(origen, ios::binary);   // Abrir archivo origen en modo binario
    ofstream out(destino, ios::binary); // Abrir archivo destino en modo binario
    if (!in || !out) return false;      // Si falla apertura, retorna false

    out << in.rdbuf();  // Copia todo el contenido del archivo
    return true;
}

// Devuelve una lista de nombres base de clases maestras
vector<string> Backup::clasesMaestras() {
    return {
        "usuarios",
        "productos",
        "transportistas",
        "bitacora",
        "Proveedores",     // Así está en tu sistema
        "clientes",
        "Almacenes",
        "administradores"
    };
}

// Devuelve una lista de nombres base de clases transaccionales
vector<string> Backup::clasesTransaccionales() {
    return {
        "pedidos",
        "envios",
        "facturacion",
        "inventarios"
    };
}

// Muestra una lista indicando qué archivos de backup existen
void Backup::mostrarBackupsDisponibles() {
    cout << "\n\t\t====== LISTA DE RESPALDOS BINARIOS DISPONIBLES ======\n";

    vector<string> clases = clasesMaestras();
    vector<string> transacciones = clasesTransaccionales();
    clases.insert(clases.end(), transacciones.begin(), transacciones.end());

    // Recorre todas las clases y verifica si el archivo *_backup.bin existe
    for (const auto& base : clases) {
        string backup = base + "_backup.bin";
        ifstream f(backup, ios::binary);
        if (f.good()) {
            cout << "\t\t✔ " << backup << " disponible\n";
        } else {
            cout << "\t\t✘ " << backup << " (no encontrado)\n";
        }
    }

    cout << "\t\t======================================================\n";
    system("pause");
}
