#include "transportistas.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <vector>
#include "globals.h"

std::vector<Transportistas> listaTransportistas;  // DEFINICIÓN


using namespace std;

const int CODIGO_INICIAL = 3311;
const int CODIGO_FINAL = 3361;

std::string Transportistas::generarIdUnico(const std::vector<Transportistas>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        std::string id = to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

bool Transportistas::idDisponible(const std::vector<Transportistas>& lista, const std::string& id) {
    return none_of(lista.begin(), lista.end(),
        [&id](const Transportistas& t) { return t.id == id; });
}

bool Transportistas::esIdValido(const std::string& id) {
    try {
        int num = stoi(id);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

void Transportistas::agregar(std::vector<Transportistas>& lista, const std::string& usuarioActual) {
    Transportistas nuevo;
    nuevo.id = generarIdUnico(lista);

    if (nuevo.id.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles para nuevos transportistas\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR TRANSPORTISTA (ID: " << nuevo.id << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tNombre: ";
    getline(cin, nuevo.nombre);

    cout << "\t\tTeléfono: ";
    getline(cin, nuevo.telefono);

    cout << "\t\tVehículo: ";
    getline(cin, nuevo.vehiculo);

    cout << "\t\tDisponibilidad (Diurna/Nocturna/24-7): ";
    getline(cin, nuevo.disponibilidad);

    lista.push_back(nuevo);
    guardarEnArchivo(lista);
    cout << "\n\t\tTransportista registrado exitosamente!\n";
    system("pause");
}

void Transportistas::mostrar(const std::vector<Transportistas>& lista) {
    cout << "\n--- LISTA DE TRANSPORTISTAS ---\n";
    for (const auto& t : lista) {
        cout << "ID: " << t.id
             << " | Nombre: " << t.nombre
             << " | Tel: " << t.telefono
             << " | Vehículo: " << t.vehiculo
             << " | Disponibilidad: " << t.disponibilidad << "\n";
    }
    system("pause");
}

void Transportistas::modificar(std::vector<Transportistas>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Transportistas& t) { return t.id == id; });

    if (it != lista.end()) {
        cout << "\n--- MODIFICAR TRANSPORTISTA (ID: " << id << ") ---\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "Nuevo teléfono (" << it->telefono << "): ";
        getline(cin, it->telefono);

        cout << "Nuevo vehículo (" << it->vehiculo << "): ";
        getline(cin, it->vehiculo);

        cout << "Nueva disponibilidad (" << it->disponibilidad << "): ";
        getline(cin, it->disponibilidad);

        guardarEnArchivo(lista);
        cout << "Transportista modificado!\n";
    } else {
        cout << "Transportista no encontrado.\n";
    }
    system("pause");
}

void Transportistas::eliminar(std::vector<Transportistas>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Transportistas& t) { return t.id == id; });

    if (it != lista.end()) {
        char confirmar;
        cout << "¿Eliminar transportista " << it->nombre << "? (s/n): ";
        cin >> confirmar;

        if (tolower(confirmar) == 's') {
            lista.erase(it);
            guardarEnArchivo(lista);
            cout << "Transportista eliminado!\n";
        } else {
            cout << "Operación cancelada.\n";
        }
    } else {
        cout << "Transportista no encontrado.\n";
    }
    system("pause");
}

void Transportistas::guardarEnArchivo(const std::vector<Transportistas>& lista) {
    ofstream archivo("Transportistas.tmp");
    if (!archivo) {
        cerr << "\n\t\tError al crear archivo temporal!\n";
        return;
    }

    bool error = false;
    for (const auto& t : lista) {
        if (!(archivo << t.id << ","
                     << t.nombre << ","
                     << t.telefono << ","
                     << t.vehiculo << ","
                     << t.disponibilidad << "\n")) {
            cerr << "\n\t\tError al escribir transportista ID: " << t.id << "\n";
            error = true;
        }
    }

    archivo.close();
    if (error || !archivo) {
        remove("Transportistas.tmp");
        return;
    }

    if (remove("Transportistas.txt") != 0 && errno != ENOENT) {
        cerr << "\n\t\tAdvertencia: No se pudo eliminar archivo anterior\n";
    }
    if (rename("Transportistas.tmp", "Transportistas.txt") != 0) {
        cerr << "\n\t\tError crítico: Falló el guardado final!\n";
    }
}

void Transportistas::cargarDesdeArchivo(std::vector<Transportistas>& lista) {
    lista.clear();
    ifstream archivo("Transportistas.txt");

    if (!archivo) {
        ofstream nuevo("Transportistas.txt");
        return;
    }

    int cargados = 0, omitidos = 0;
    string linea;

    while (getline(archivo, linea)) {
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        if (linea.empty()) continue;

        istringstream ss(linea);
        Transportistas temp;
        string campo;

        try {
            if (!getline(ss, temp.id, ',') ||
                !getline(ss, temp.nombre, ',') ||
                !getline(ss, temp.telefono, ',') ||
                !getline(ss, temp.vehiculo, ',') ||
                !getline(ss, temp.disponibilidad)) {
                throw runtime_error("Formato inválido");
            }

            if (!esIdValido(temp.id)) throw runtime_error("ID inválido");
            if (!idDisponible(lista, temp.id)) throw runtime_error("ID duplicado");

            lista.push_back(temp);
            cargados++;
        } catch (const exception& e) {
            cerr << "\n\t\tAdvertencia: Transportista omitido (" << e.what() << "): " << linea << "\n";
            omitidos++;
        }
    }

    if (archivo.bad()) {
        cerr << "\n\t\tError durante la lectura del archivo!\n";
    }

    cout << "\n\t\tCargados: " << cargados << " | Omitidos: " << omitidos << "\n";
}
