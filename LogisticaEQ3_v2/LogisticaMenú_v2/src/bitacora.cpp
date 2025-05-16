#include "bitacora.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstring>

// Inicializaci�n est�tica de los rangos de c�digos por m�dulo
std::unordered_map<std::string, int> CodigosBitacora::rangos = {
    {"AUTENTICACION", 3000}, {"USUARIOS", 3050}, {"PEDIDOS", 3100},
    {"CLIENTES", 3150}, {"PROVEEDORES", 3200}, {"PRODUCTOS", 3250},
    {"ALMACENES", 3300}, {"TRANSPORTISTAS", 3350}, {"FACTURACION", 3400},
    {"REPORTES", 3450}, {"INVENTARIO", 3500}, {"ENVIOS", 3550}
};

int CodigosBitacora::getCodigo(const std::string& modulo) {
    if (rangos.find(modulo) == rangos.end()) {
        // Si el m�dulo no existe, inicializa con 3000 (por defecto)
        rangos[modulo] = 3000;
    }
    return rangos[modulo]++;
}

void bitacora::registrar(const std::string& usuario,
                         const std::string& modulo,
                         const std::string& descripcion) {
    // --- C�digo para guardar en bitacora.txt ---
    std::ifstream check("bitacora.txt");
    bool isEmpty = check.peek() == std::ifstream::traits_type::eof();
    check.close();

    std::ofstream fileTxt("bitacora.txt", std::ios::app);
    int codigo = CodigosBitacora::getCodigo(modulo);

    std::time_t now = std::time(nullptr);
    char fecha[100];
    std::strftime(fecha, sizeof(fecha), "%d/%m/%Y %H:%M:%S", std::localtime(&now));

    if (fileTxt.is_open()) {
        if (isEmpty) {
            fileTxt << "-------------------------- BIT�CORA DEL SISTEMA --------------------------\n";
            fileTxt << std::left
                    << std::setw(12) << "ID_ACCION"
                    << std::setw(15) << "USUARIO"
                    << std::setw(20) << "MODULO"
                    << std::setw(35) << "DESCRIPCION"
                    << std::setw(20) << "FECHA_HORA" << "\n";
            fileTxt << "---------------------------------------------------------------------------\n";
        }

        fileTxt << std::left
                << std::setw(12) << codigo
                << std::setw(15) << usuario
                << std::setw(20) << modulo
                << std::setw(35) << descripcion
                << std::setw(20) << fecha << "\n";
    }
    fileTxt.close();

    // --- C�digo para guardar en bitacora.dat ---
    RegistroBitacora registro{};
    registro.codigo = codigo;
    strncpy(registro.usuario, usuario.c_str(), sizeof(registro.usuario) - 1);
    strncpy(registro.modulo, modulo.c_str(), sizeof(registro.modulo) - 1);
    strncpy(registro.descripcion, descripcion.c_str(), sizeof(registro.descripcion) - 1);
    strncpy(registro.fechaHora, fecha, sizeof(registro.fechaHora) - 1);

    std::ofstream fileDat("bitacora.dat", std::ios::binary | std::ios::app);
    if (fileDat.is_open()) {
        fileDat.write(reinterpret_cast<char*>(&registro), sizeof(RegistroBitacora));
        fileDat.close();
    }
}

std::string bitacora::obtenerFechaActual() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

void bitacora::mostrarBitacora() {
    system("cls");
    std::ifstream file("bitacora.txt");

    std::cout << "\t\t========================================================\n";
    std::cout << "\t\t|                      BIT�CORA                        |\n";
    std::cout << "\t\t========================================================\n";
    std::cout << "\t\t" << std::left
              << std::setw(10) << "C�DIGO"
              << std::setw(15) << "USUARIO"
              << std::setw(30) << "DESCRIPCI�N"
              << std::setw(15) << "FECHA" << "\n";
    std::cout << "\t\t---------------------------------------------------------------\n";

    if (file.is_open()) {
        std::string linea;
        while (std::getline(file, linea)) {
            std::cout << "\t\t" << linea << "\n";
        }
        file.close();
    } else {
        std::cout << "\t\tNo hay registros en la bit�cora.\n";
    }
    std::cout << "\t\t===============================================================\n";
    system("pause");
}

void bitacora::generarBackup() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << "backup_bitacora_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".txt";

    std::ifstream src("bitacora.txt", std::ios::binary);
    std::ofstream dst(oss.str(), std::ios::binary);

    if (src && dst) {
        dst << src.rdbuf();
        registrar("SISTEMA", "bitacora", "Backup de bit�cora generado: " + oss.str());
        std::cout << "\n\t\tBackup generado exitosamente: " << oss.str() << "\n";
    } else {
        std::cerr << "\n\t\tError al generar backup!\n";
    }
}

void bitacora::reiniciarBitacora() {
    std::ofstream file("bitacora.txt", std::ios::trunc);
    if (file.is_open()) {
        file.close();
        std::cout << "Bit�cora reiniciada con �xito.\n";
    } else {
        std::cout << "Error al reiniciar la bit�cora.\n";
    }
}

void bitacora::mostrarBitacoraBinaria() {
    std::ifstream file("bitacora.dat", std::ios::binary);
    if (!file) {
        std::cout << "No existe el archivo binario bitacora.dat\n";
        return;
    }

    std::cout << "\t\t============= BIT�CORA BINARIA =============\n";
    RegistroBitacora registro;
    while (file.read(reinterpret_cast<char*>(&registro), sizeof(RegistroBitacora))) {
        std::cout << "C�digo: " << registro.codigo
                  << ", Usuario: " << registro.usuario
                  << ", M�dulo: " << registro.modulo
                  << ", Descripci�n: " << registro.descripcion
                  << ", Fecha: " << registro.fechaHora << "\n";
    }
    file.close();
}

void bitacora::menuBitacora() {
    int opcion;
    do {
        system("cls");
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\t|      ADMINISTRACI�N DE BIT�CORA     |\n";
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\t 1. Ver registros completos\n";
        std::cout << "\t\t 2. Generar backup\n";
        std::cout << "\t\t 3. Buscar por c�digo de usuario (pendiente)\n";
        std::cout << "\t\t 4. Buscar por fecha (pendiente)\n";
        std::cout << "\t\t 5. Reiniciar bit�cora\n";
        std::cout << "\t\t 6. Volver al men� principal\n";
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\tOpci�n: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: mostrarBitacora(); break;
            case 2: generarBackup(); break;
            case 3:
                // TODO: Implementar b�squeda por c�digo
                std::cout << "\nFuncionalidad no implementada a�n.\n";
                system("pause");
                break;
            case 4:
                // TODO: Implementar b�squeda por fecha
                std::cout << "\nFuncionalidad no implementada a�n.\n";
                system("pause");
                break;
            case 5: reiniciarBitacora(); break;
            case 6: break;
            default:
                std::cout << "\n\t\tOpci�n inv�lida!";
                std::cin.clear();

            std::cin.ignore(10000, '\n');
            system("pause");
            break;
            }
            } while (opcion != 6);
            }
