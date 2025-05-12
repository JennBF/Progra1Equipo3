#include "administracion.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "bitacora.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <limits> // Para numeric_limits

using namespace std;

// Rango de códigos para administradores
const int CODIGO_INICIAL_ADMIN = 3362;
const int CODIGO_FINAL_ADMIN = 3402;

std::string Administracion::generarIdUnico(const std::vector<Administracion>& lista) {
    for (int i = CODIGO_INICIAL_ADMIN; i <= CODIGO_FINAL_ADMIN; ++i) {
        std::string id = std::to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return ""; // Retorna cadena vacía si no hay códigos disponibles
}

bool Administracion::idDisponible(const std::vector<Administracion>& lista, const std::string& id) {
    return std::none_of(lista.begin(), lista.end(),
        [&id](const Administracion& a) { return a.id == id; });
}

bool Administracion::esIdValido(const std::string& id) {
    try {
        int num = std::stoi(id);
        return (num >= CODIGO_INICIAL_ADMIN && num <= CODIGO_FINAL_ADMIN);
    } catch (...) {
        return false;
    }
}

void Administracion::agregar(std::vector<Administracion>& lista, const std::string& usuarioActual) {
    Administracion nuevo;

    // Asignar ID automático
    nuevo.id = generarIdUnico(lista);
    if (nuevo.id.empty()) {
        std::cerr << "\n\t\tError: No hay códigos disponibles para nuevos administradores (rango lleno)\n";
        system("pause");
        return;
    }

    std::cout << "\n\t\t=== AGREGAR ADMINISTRADOR (ID Auto-Asignado: " << nuevo.id << ") ===\n";

    // Limpiar buffer antes de getline()
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\t\tNombre completo: ";
    std::getline(std::cin, nuevo.nombre);

    std::cout << "\t\tCargo: ";
    std::getline(std::cin, nuevo.cargo);

    std::cout << "\t\tDepartamento: ";
    std::getline(std::cin, nuevo.departamento);

    std::cout << "\t\tTeléfono: ";
    std::getline(std::cin, nuevo.telefono);

    std::cout << "\t\tCorreo electrónico: ";
    std::getline(std::cin, nuevo.email);

    std::cout << "\t\tNivel de acceso (1-5): ";
    while (!(std::cin >> nuevo.nivelAcceso) || nuevo.nivelAcceso < 1 || nuevo.nivelAcceso > 5) {
        std::cout << "\t\tPor favor ingrese un nivel válido (1-5): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    lista.push_back(nuevo);
    guardarEnArchivo(lista);

    bitacora::registrar(usuarioActual, "ADMINISTRACION", "Administrador agregado - ID: " + nuevo.id);
    std::cout << "\n\t\tAdministrador registrado exitosamente con ID: " << nuevo.id << "\n";
    system("pause");
}
