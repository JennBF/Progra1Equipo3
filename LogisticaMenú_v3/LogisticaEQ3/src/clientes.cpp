#include "clientes.h"
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

// Rango de códigos para clientes
const int CODIGO_INICIAL = 3107;
const int CODIGO_FINAL = 3157;

/**
 * Genera un ID único dentro del rango permitido (3107–3157) para un nuevo cliente.
 * @param lista Lista actual de clientes.
 * @return ID disponible como string, o cadena vacía si el rango está lleno.
 */
std::string Clientes::generarIdUnico(const std::vector<Clientes>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        std::string id = std::to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return ""; // Retorna cadena vacía si no hay códigos disponibles
}

/**
 * Verifica si un ID está disponible (no repetido) en la lista de clientes.
 * @param lista Lista de clientes.
 * @param id ID a verificar.
 * @return true si el ID no está en uso, false si ya está ocupado.
 */
bool Clientes::idDisponible(const std::vector<Clientes>& lista, const std::string& id) {
    return std::none_of(lista.begin(), lista.end(),
        [&id](const Clientes& c) { return c.id == id; });
}

/**
 * Valida si un ID es un número dentro del rango permitido.
 * @param id ID a validar.
 * @return true si es válido, false si no.
 */
bool Clientes::esIdValido(const std::string& id) {
    try {
        int num = std::stoi(id);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

/**
 * Agrega un nuevo cliente a la lista, solicitando los datos desde la entrada estándar.
 * Asigna automáticamente un ID único, guarda en archivo y registra en bitácora.
 * @param lista Lista de clientes (modificable).
 * @param usuarioActual Nombre del usuario activo (para bitácora).
 */
void Clientes::agregar(std::vector<Clientes>& lista, const std::string& usuarioActual) {
    Clientes nuevo;

    // Asignar ID automático
    nuevo.id = generarIdUnico(lista);
    if (nuevo.id.empty()) {
        std::cerr << "\n\t\tError: No hay códigos disponibles para nuevos clientes (rango lleno)\n";
        system("pause");
        return;
    }

    std::cout << "\n\t\t=== AGREGAR CLIENTE (ID Auto-Asignado: " << nuevo.id << ") ===\n";

    // Limpiar buffer antes de getline()
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\t\tNombre completo: ";
    std::getline(std::cin, nuevo.nombre);

    std::cout << "\t\tDirección: ";
    std::getline(std::cin, nuevo.direccion);

    std::cout << "\t\tTeléfono: ";
    std::getline(std::cin, nuevo.telefono);

    std::cout << "\t\tNIT: ";
    std::getline(std::cin, nuevo.nit);

    lista.push_back(nuevo);
    guardarEnArchivo(lista);

    bitacora::registrar(usuarioActual, "CLIENTES", "Cliente agregado - ID: " + nuevo.id);
    std::cout << "\n\t\tCliente registrado exitosamente con ID: " << nuevo.id << "\n";
    system("pause");
}

/**
 * Muestra todos los clientes actualmente almacenados en la lista.
 * @param lista Lista de clientes a mostrar.
 */
void Clientes::mostrar(const std::vector<Clientes>& lista) {
    cout << "\n--- LISTA DE CLIENTES ---\n";
    for (const auto& cliente : lista) {
        cout << "ID: " << cliente.id
        << " | Nombre: " << cliente.nombre
        << " | Dirección: " << cliente.direccion
        << " | Teléfono: " << cliente.telefono
        << " | NIT: " << cliente.nit << "\n";
    }
    system("pause");
}

/**
 * Modifica los datos de un cliente existente según su ID.
 * Guarda los cambios en el archivo y registra en la bitácora.
 * @param lista Lista de clientes (modificable).
 * @param usuarioActual Usuario que realiza la modificación.
 * @param id ID del cliente a modificar.
 */
void Clientes::modificar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Clientes& c) { return c.id == id; });

    if (it != lista.end()) {
        cout << "\n--- MODIFICAR CLIENTE (ID: " << id << ") ---\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

        cout << "Nuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "Nueva dirección (" << it->direccion << "): ";
        getline(cin, it->direccion);

        cout << "Nuevo teléfono (" << it->telefono << "): ";
        getline(cin, it->telefono);

        cout << "Nuevo NIT (" << it->nit << "): ";
        getline(cin, it->nit);

        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "CLIENTES", "Cliente modificado - ID: " + id);
        cout << "Cliente modificado!\n";
    } else {
        cout << "Cliente no encontrado.\n";
    }
    system("pause");
}

/**
 * Elimina un cliente de la lista dado su ID.
 * Guarda los cambios y registra la acción en bitácora.
 * @param lista Lista de clientes (modificable).
 * @param usuarioActual Usuario que realiza la eliminación.
 * @param id ID del cliente a eliminar.
 */
void Clientes::eliminar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Clientes& c) { return c.id == id; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "CLIENTES", "Cliente eliminado - ID: " + id);
        cout << "Cliente eliminado!\n";
    } else {
        cout << "Cliente no encontrado.\n";
    }
    system("pause");
}

/**
 * Guarda la lista completa de clientes en formato tabular en el archivo `Clientes.txt`.
 * Se usa un archivo temporal (`Clientes.tmp`) para evitar errores de escritura parcial.
 * Si hay fallos, se cancela el guardado para proteger la integridad del archivo.
 * @param lista Lista actual de clientes.
 */
void Clientes::guardarEnArchivo(const std::vector<Clientes>& lista) {
    ofstream archivo("Clientes.tmp", ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo crear archivo temporal!\n";
        return;
    }

    archivo << "---------------------------------- Lista de Clientes ----------------------------------\n";
    archivo << std::left
            << std::setw(10) << "ID"
            << std::setw(25) << "Nombre"
            << std::setw(25) << "Dirección"
            << std::setw(15) << "Teléfono"
            << std::setw(15) << "NIT" << "\n";
    archivo << std::string(90, '-') << "\n";

    for (const auto& cliente : lista) {
        archivo << std::left
                << std::setw(10) << cliente.id
                << std::setw(25) << cliente.nombre
                << std::setw(25) << cliente.direccion
                << std::setw(15) << cliente.telefono
                << std::setw(15) << cliente.nit << "\n";
    }

    archivo << std::string(90, '-') << "\n";

    archivo.flush();
    if (!archivo) {
        cerr << "\n\t\tError: Fallo al guardar los datos en formato tabular!\n";
        archivo.close();
        remove("Clientes.tmp");
        return;
    }

    archivo.close();

    if (remove("Clientes.txt") != 0 && errno != ENOENT) {
        cerr << "\n\t\tAdvertencia: No se pudo eliminar el archivo anterior\n";
    }
    if (rename("Clientes.tmp", "Clientes.txt") != 0) {
        cerr << "\n\t\tError crítico: Falló el guardado final!\n";
    }
}

/**
 * Carga los datos de clientes desde el archivo `Clientes.txt`.
 * Realiza validación de formato, rango de ID y duplicados.
 * Si el archivo no existe, lo crea vacío. Los errores se muestran por consola.
 * @param lista Lista de clientes a llenar (se limpia antes).
 */
void Clientes::cargarDesdeArchivo(std::vector<Clientes>& lista) {
    lista.clear();

    ifstream archivo("Clientes.txt");
    if (!archivo) {
        ofstream nuevoArchivo("Clientes.txt");
        if (!nuevoArchivo) {
            cerr << "\n\t\tError crítico: No se pudo crear archivo de clientes!\n";
        }
        return;
    }

    int cargados = 0, omitidos = 0;
    string linea;

    while (getline(archivo, linea)) {
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        if (linea.empty()) continue;

        istringstream ss(linea);
        Clientes temp;
        string campo;

        try {
            if (!getline(ss, temp.id, ',') ||
                !getline(ss, temp.nombre, ',') ||
                !getline(ss, temp.direccion, ',') ||
                !getline(ss, temp.telefono, ',') ||
                !getline(ss, temp.nit)) {
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
            cerr << "\n\t\tAdvertencia: Cliente omitido (" << e.what() << "): " << linea << "\n";
            omitidos++;
        }
    }

    if (archivo.bad()) {
        cerr << "\n\t\tError: Fallo durante la lectura del archivo!\n";
    }

    cout << "\n\t\tCarga completada. " << cargados << " clientes cargados, "
         << omitidos << " omitidos.\n";
}
