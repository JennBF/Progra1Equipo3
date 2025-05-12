//Angoly Araujo Mayo 2025 9959-24-17623
// Progra
#include "proveedor.h"
#include "bitacora.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int CODIGO_INICIAL_PROV = 3158;
const int CODIGO_FINAL_PROV = 3208;

std::string Proveedor::generarIdUnico(const std::vector<Proveedor>& lista) {
    for (int i = CODIGO_INICIAL_PROV; i <= CODIGO_FINAL_PROV; ++i) {
        std::string id = std::to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

bool Proveedor::idDisponible(const std::vector<Proveedor>& lista, const std::string& id) {
    return std::none_of(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });
}

bool Proveedor::esIdValido(const std::string& id) {
    try {
        int num = std::stoi(id);
        return (num >= CODIGO_INICIAL_PROV && num <= CODIGO_FINAL_PROV);
    } catch (...) {
        return false;
    }
}

void Proveedor::agregar(std::vector<Proveedor>& lista, const std::string& usuarioActual) {
    Proveedor nuevo;
    nuevo.id = generarIdUnico(lista);

    if (nuevo.id.empty()) {
        std::cerr << "\n\t\tError: No hay códigos disponibles para nuevos proveedores.\n";
        system("pause");
        return;
    }

    std::cout << "\n\t\t=== AGREGAR PROVEEDOR (ID Auto-Asignado: " << nuevo.id << ") ===\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\t\tNombre completo: ";
    std::getline(std::cin, nuevo.nombre);

    std::cout << "\t\tTeléfono: ";
    std::getline(std::cin, nuevo.telefono);

    lista.push_back(nuevo);
    guardarEnArchivo(lista);

    bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor agregado - ID: " + nuevo.id);
    std::cout << "\n\t\tProveedor registrado exitosamente con ID: " << nuevo.id << "\n";
    system("pause");
}

void Proveedor::mostrar(const std::vector<Proveedor>& lista) {
    cout << "\n--- LISTA DE PROVEEDORES ---\n";
    for (const auto& p : lista) {
        cout << "ID: " << p.id
             << " | Nombre: " << p.nombre
             << " | Teléfono: " << p.telefono << "\n";
    }
    system("pause");
}

void Proveedor::modificar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });

    if (it != lista.end()) {
        cout << "\n--- MODIFICAR PROVEEDOR (ID: " << id << ") ---\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "Nuevo teléfono (" << it->telefono << "): ";
        getline(cin, it->telefono);

        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor modificado - ID: " + id);
        cout << "Proveedor modificado!\n";
    } else {
        cout << "Proveedor no encontrado.\n";
    }
    system("pause");
}

void Proveedor::eliminar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivo(lista);

        bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor eliminado - ID: " + id);
        cout << "Proveedor eliminado!\n";
    } else {
        cout << "Proveedor no encontrado.\n";
    }
    system("pause");
}

void Proveedor::guardarEnArchivo(const std::vector<Proveedor>& lista) {
    ofstream archivo("Proveedores.tmp", ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo crear archivo temporal!\n";
        return;
    }

    bool errorEscritura = false;
    for (const auto& p : lista) {
        if (!(archivo << p.id << "," << p.nombre << "," << p.telefono << "\n")) {
            cerr << "\n\t\tError al escribir proveedor ID: " << p.id << "\n";
            errorEscritura = true;
        }
    }

    archivo.flush();
    if (!archivo || errorEscritura) {
        cerr << "\n\t\tError: No se pudieron guardar todos los datos!\n";
        archivo.close();
        remove("Proveedores.tmp");
        return;
    }
    archivo.close();

    if (remove("Proveedores.txt") != 0 && errno != ENOENT) {
        cerr << "\n\t\tAdvertencia: No se pudo eliminar archivo anterior\n";
    }
    if (rename("Proveedores.tmp", "Proveedores.txt") != 0) {
        cerr << "\n\t\tError crítico: Falló el guardado final!\n";
    }
}

void Proveedor::cargarDesdeArchivo(std::vector<Proveedor>& lista) {
    lista.clear();

    ifstream archivo("Proveedores.txt");
    if (!archivo) {
        ofstream nuevoArchivo("Proveedores.txt");
        if (!nuevoArchivo) {
            cerr << "\n\t\tError crítico: No se pudo crear archivo de proveedores!\n";
        }
        return;
    }

    int cargados = 0, omitidos = 0;
    string linea;

    while (getline(archivo, linea)) {
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        if (linea.empty()) continue;

        istringstream ss(linea);
        Proveedor temp;
        string campo;

        try {
            if (!getline(ss, temp.id, ',') ||
                !getline(ss, temp.nombre, ',') ||
                !getline(ss, temp.telefono)) {
                throw runtime_error("Formato inválido");
            }

            if (!esIdValido(temp.id)) {
                throw runtime_error("ID fuera de rango");
            }

            if (!idDisponible(lista, temp.id)) {
                throw runtime_error("ID duplicado");
            }

            lista.push_back(temp);
            cargados++;
        } catch (const exception& e) {
            cerr << "\n\t\tAdvertencia: Proveedor omitido (" << e.what() << "): " << linea << "\n";
            omitidos++;
        }
    }

    if (archivo.bad()) {
        cerr << "\n\t\tError: Fallo durante la lectura del archivo!\n";
    }

    cout << "\n\t\tCarga completada. " << cargados << " proveedores cargados, "
         << omitidos << " omitidos.\n";
}


std::string Proveedor::getNombre() const {
    return nombre;
}

std::string Proveedor::getId() const {
    return nombre;
}
