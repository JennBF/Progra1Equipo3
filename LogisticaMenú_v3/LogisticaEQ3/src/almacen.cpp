//9959 24 11603 GE
#include "Almacen.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "bitacora.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <limits> // Para numeric_limits

// Rango de c�digos de ID permitidos (compartido con Clientes)
const int CODIGO_INICIAL = 3260;
const int CODIGO_FINAL = 3310;

// Genera un ID �nico dentro del rango especificado, evitando colisiones con IDs existentes
std::string Almacen::generarID(const std::vector<Almacen>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        std::string id_candidato = std::to_string(i);
        bool existe = std::any_of(lista.begin(), lista.end(),
            [&id_candidato](const Almacen& a) { return a.id == id_candidato; });
        if (!existe) return id_candidato;
    }
    return "";
}

// Valida que el estado sea uno de los permitidos
bool Almacen::validarEstado(const std::string& estado) {
    return (estado == "operativo" || estado == "en mantenimiento");
}

// Agrega un nuevo almac�n a la lista y lo registra en la bit�cora
void Almacen::agregar(std::vector<Almacen>& lista, const std::string& usuario) {
    Almacen nuevo;
    nuevo.id = generarID(lista);
    if (nuevo.id.empty()) {
        std::cerr << "No hay IDs disponibles (rango 3260-3310 lleno)\n";
        return;
    }

    std::cout << "=== AGREGAR ALMAC�N (ID: " << nuevo.id << ") ===\n";

    // Recolecta los datos del nuevo almac�n desde consola
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Direcci�n: ";
    std::getline(std::cin, nuevo.direccion);

    // Solicita una capacidad v�lida (entero positivo)
    while (true) {
        std::cout << "Capacidad (m�): ";
        if (std::cin >> nuevo.capacidad && nuevo.capacidad > 0) break;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cerr << "Error: Ingrese un n�mero positivo\n";
    }

    std::cin.ignore();
    std::cout << "Responsable: ";
    std::getline(std::cin, nuevo.responsable);

    std::cout << "Contacto: ";
    std::getline(std::cin, nuevo.contacto);

    // Asegura que el estado ingresado sea v�lido
    do {
        std::cout << "Estado (operativo/en mantenimiento): ";
        std::getline(std::cin, nuevo.estado);
    } while (!validarEstado(nuevo.estado));

    // Guarda el nuevo almac�n en la lista y en archivo
    lista.push_back(nuevo);
    guardarEnArchivo(lista);

    // Registra la acci�n en la bit�cora
    bitacora::registrar(usuario, "ALMACEN", "Almac�n creado - ID: " + nuevo.id);
}

// Muestra la lista completa de almacenes
void Almacen::mostrar(const std::vector<Almacen>& lista) {
    std::cout << "\n=== LISTA DE ALMACENES ===\n";
    for (const auto& a : lista) {
        std::cout << "ID: " << a.id << "\n"
                  << "Direcci�n: " << a.direccion << "\n"
                  << "Capacidad: " << a.capacidad << " m�\n"
                  << "Responsable: " << a.responsable << "\n"
                  << "Contacto: " << a.contacto << "\n"
                  << "Estado: " << a.estado << "\n"
                  << "-----------------------\n";
    }
}

// Modifica los datos de un almac�n existente
void Almacen::modificar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id) {
    // Busca el almac�n por ID
    auto it = std::find_if(lista.begin(), lista.end(),
        [&id](const Almacen& a) { return a.id == id; });

    if (it != lista.end()) {
        // Actualiza los datos del almac�n
        std::cin.ignore();
        std::cout << "Nueva direcci�n: ";
        std::getline(std::cin, it->direccion);

        while (true) {
            std::cout << "Nueva capacidad: ";
            if (std::cin >> it->capacidad && it->capacidad > 0) break;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Error: Valor inv�lido\n";
        }

        std::cin.ignore();
        std::cout << "Nuevo responsable: ";
        std::getline(std::cin, it->responsable);

        std::cout << "Nuevo contacto: ";
        std::getline(std::cin, it->contacto);

        do {
            std::cout << "Nuevo estado: ";
            std::getline(std::cin, it->estado);
        } while (!validarEstado(it->estado));

        // Guarda cambios y registra en bit�cora
        guardarEnArchivo(lista);
        bitacora::registrar(usuario, "ALMACEN", "Almac�n modificado - ID: " + id);
    } else {
        std::cerr << "Almac�n no encontrado\n";
    }
}

// Elimina un almac�n seg�n su ID
void Almacen::eliminar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id) {
    auto it = std::find_if(lista.begin(), lista.end(),
        [&id](const Almacen& a) { return a.id == id; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivo(lista);
        bitacora::registrar(usuario, "ALMACEN", "Almac�n eliminado - ID: " + id);
    } else {
        std::cerr << "Almac�n no encontrado\n";
    }
}

// Guarda toda la lista de almacenes en un archivo de texto plano
void Almacen::guardarEnArchivo(const std::vector<Almacen>& lista) {
    std::ofstream archivo("almacenes.txt");
    for (const auto& a : lista) {
        archivo << a.id << "," << a.direccion << "," << a.capacidad << ","
                << a.responsable << "," << a.contacto << "," << a.estado << "\n";
    }
}

// Carga la lista de almacenes desde el archivo de texto
void Almacen::cargarDesdeArchivo(std::vector<Almacen>& lista) {
    std::ifstream archivo("almacenes.txt");
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        Almacen a;
        std::string campo;

        std::getline(ss, a.id, ',');
        std::getline(ss, a.direccion, ',');

        std::getline(ss, campo, ',');
        a.capacidad = std::stoi(campo);

        std::getline(ss, a.responsable, ',');
        std::getline(ss, a.contacto, ',');
        std::getline(ss, a.estado);

        lista.push_back(a);
    }
}
