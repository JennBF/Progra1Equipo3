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


// Constantes idénticas a Clientes
const int CODIGO_INICIAL = 3260;
const int CODIGO_FINAL = 3310;

// Genera ID único en rango 3260-3310 (igual que Clientes)
std::string Almacen::generarID(const std::vector<Almacen>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        std::string id_candidato = std::to_string(i);
        bool existe = std::any_of(lista.begin(), lista.end(),
            [&id_candidato](const Almacen& a) { return a.id == id_candidato; });
        if (!existe) return id_candidato;
    }
    return "";
}

bool Almacen::validarEstado(const std::string& estado) {
    return (estado == "operativo" || estado == "en mantenimiento");
}

// CREATE (idéntico a Clientes::agregar())
void Almacen::agregar(std::vector<Almacen>& lista, const std::string& usuario) {
    Almacen nuevo;
    nuevo.id = generarID(lista);
    if (nuevo.id.empty()) {
        std::cerr << "No hay IDs disponibles (rango 3260-3310 lleno)\n";
        return;
    }

    std::cout << "=== AGREGAR ALMACÉN (ID: " << nuevo.id << ") ===\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Dirección: ";
    std::getline(std::cin, nuevo.direccion);

    // Validación de capacidad (como en Clientes)
    while (true) {
        std::cout << "Capacidad (m²): ";
        if (std::cin >> nuevo.capacidad && nuevo.capacidad > 0) break;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cerr << "Error: Ingrese un número positivo\n";
    }

    std::cin.ignore();
    std::cout << "Responsable: ";
    std::getline(std::cin, nuevo.responsable);

    std::cout << "Contacto: ";
    std::getline(std::cin, nuevo.contacto);

    do {
        std::cout << "Estado (operativo/en mantenimiento): ";
        std::getline(std::cin, nuevo.estado);
    } while (!validarEstado(nuevo.estado));

    lista.push_back(nuevo);
    guardarEnArchivo(lista);
    bitacora::registrar(usuario, "ALMACEN", "Almacén creado - ID: " + nuevo.id);
}

// READ (igual que Clientes::mostrar())
void Almacen::mostrar(const std::vector<Almacen>& lista) {
    std::cout << "\n=== LISTA DE ALMACENES ===\n";
    for (const auto& a : lista) {
        std::cout << "ID: " << a.id << "\n"
                  << "Dirección: " << a.direccion << "\n"
                  << "Capacidad: " << a.capacidad << " m²\n"
                  << "Responsable: " << a.responsable << "\n"
                  << "Contacto: " << a.contacto << "\n"
                  << "Estado: " << a.estado << "\n"
                  << "-----------------------\n";
    }
}

// UPDATE (misma estructura que Clientes)
void Almacen::modificar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id) {
    auto it = std::find_if(lista.begin(), lista.end(),
        [&id](const Almacen& a) { return a.id == id; });

    if (it != lista.end()) {
        std::cin.ignore();
        std::cout << "Nueva dirección: ";
        std::getline(std::cin, it->direccion);

        // Validación idéntica a Clientes
        while (true) {
            std::cout << "Nueva capacidad: ";
            if (std::cin >> it->capacidad && it->capacidad > 0) break;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Error: Valor inválido\n";
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

        guardarEnArchivo(lista);
        bitacora::registrar(usuario, "ALMACEN", "Almacén modificado - ID: " + id);
    } else {
        std::cerr << "Almacén no encontrado\n";
    }
}

// DELETE (idéntico a Clientes)
void Almacen::eliminar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id) {
    auto it = std::find_if(lista.begin(), lista.end(),
        [&id](const Almacen& a) { return a.id == id; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivo(lista);
        bitacora::registrar(usuario, "ALMACEN", "Almacén eliminado - ID: " + id);
    } else {
        std::cerr << "Almacén no encontrado\n";
    }
}

// Persistencia (mismo enfoque que Clientes)
void Almacen::guardarEnArchivo(const std::vector<Almacen>& lista) {
    std::ofstream archivo("almacenes.txt");
    for (const auto& a : lista) {
        archivo << a.id << "," << a.direccion << "," << a.capacidad << ","
                << a.responsable << "," << a.contacto << "," << a.estado << "\n";
    }
}

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
