#include "Producto.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include "bitacora.h"

using namespace std;

// Rango de códigos para productos (según tu documentación)
const int CODIGO_INICIAL = 3209;
const int CODIGO_FINAL = 3259;

string Producto::generarCodigoUnico(const vector<Producto>& lista) {
    // Buscar el primer código disponible en el rango
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string codigo = to_string(i);
        if (codigoDisponible(lista, codigo)) {
            return codigo;
        }
    }
    return ""; // Retorna cadena vacía si no hay códigos disponibles
}

bool Producto::codigoDisponible(const vector<Producto>& lista, const string& codigo) {
    return none_of(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });
}

bool Producto::esCodigoValido(const string& codigo) {
    try {
        int num = stoi(codigo);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

void Producto::agregar(vector<Producto>& lista, const string& usuarioActual) {
    Producto nuevo;

    // Asignar código automático
    nuevo.codigo = generarCodigoUnico(lista);
    if (nuevo.codigo.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles para nuevos productos (rango lleno)\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR PRODUCTO (Código Auto-Asignado: " << nuevo.codigo << ") ===\n";

    // Limpiar buffer antes de getline()
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tNombre del producto: ";
    getline(cin, nuevo.nombre);

    cout << "\t\tPrecio: ";
    while (!(cin >> nuevo.precio)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese un valor numérico para el precio: ";
    }

    cout << "\t\tStock inicial: ";
    while (!(cin >> nuevo.stock)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese un valor entero para el stock: ";
    }

    lista.push_back(nuevo);
    guardarEnArchivo(lista);

    bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto agregado - Código: " + nuevo.codigo);
    cout << "\n\t\tProducto registrado exitosamente con código: " << nuevo.codigo << "\n";
    system("pause");
}

void Producto::mostrar(const vector<Producto>& lista) {
    system("cls");
    cout << "\n\t\t=== INVENTARIO DE PRODUCTOS ===\n";
    cout << "\t\t" << left
         << setw(10) << "Código"
         << setw(30) << "Nombre"
         << setw(15) << "Precio"
         << setw(10) << "Stock" << "\n";
    cout << "\t\t" << string(65, '-') << "\n";

    for (const auto& producto : lista) {
        cout << "\t\t" << left
             << setw(10) << producto.codigo
             << setw(30) << producto.nombre
             << "$" << setw(14) << fixed << setprecision(2) << producto.precio
             << setw(10) << producto.stock << "\n";
    }
    system("pause");
}

void Producto::modificar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        cout << "\n\t\t=== MODIFICAR PRODUCTO (Código: " << codigo << ") ===\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

        cout << "\t\tNuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "\t\tNuevo precio (" << it->precio << "): ";
        while (!(cin >> it->precio)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un valor numérico para el precio: ";
        }

        cout << "\t\tNuevo stock (" << it->stock << "): ";
        while (!(cin >> it->stock)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un valor entero para el stock: ";
        }

        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto modificado - Código: " + codigo);
        cout << "\n\t\tProducto modificado exitosamente!\n";
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

void Producto::eliminar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto eliminado - Código: " + codigo);
        cout << "\n\t\tProducto eliminado exitosamente!\n";
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

void Producto::guardarEnArchivo(const vector<Producto>& lista) {
    // 1. Crear archivo temporal para escritura segura
    ofstream archivo("Productos.tmp", ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo crear archivo temporal!\n";
        return;
    }

    // 2. Escribir todos los productos con verificación
    bool errorEscritura = false;
    for (const auto& producto : lista) {
        if (!(archivo << producto.codigo << ","
                     << producto.nombre << ","
                     << producto.precio << ","
                     << producto.stock << "\n")) {
            cerr << "\n\t\tError al escribir producto Código: " << producto.codigo << "\n";
            errorEscritura = true;
        }
    }

    // 3. Forzar escritura y verificar
    archivo.flush();
    if (!archivo || errorEscritura) {
        cerr << "\n\t\tError: No se pudieron guardar todos los datos!\n";
        archivo.close();
        remove("Productos.tmp"); // Eliminar archivo temporal corrupto
        return;
    }
    archivo.close();

    // 4. Reemplazar archivo existente (operación atómica)
    if (remove("Productos.txt") != 0 && errno != ENOENT) {
        cerr << "\n\t\tAdvertencia: No se pudo eliminar archivo anterior\n";
    }
    if (rename("Productos.tmp", "Productos.txt") != 0) {
        cerr << "\n\t\tError crítico: Falló el guardado final!\n";
    }
}

void Producto::cargarDesdeArchivo(vector<Producto>& lista) {
    // 1. Limpiar lista existente
    lista.clear();

    // 2. Abrir archivo con verificación
    ifstream archivo("Productos.txt");
    if (!archivo) {
        // Crear archivo vacío si no existe
        ofstream nuevoArchivo("Productos.txt");
        if (!nuevoArchivo) {
            cerr << "\n\t\tError crítico: No se pudo crear archivo de productos!\n";
        }
        return;
    }

    // 3. Contadores para estadísticas
    int cargados = 0, omitidos = 0;
    string linea;

    // 4. Procesar cada línea
    while (getline(archivo, linea)) {
        // Eliminar espacios y saltos de línea
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        if (linea.empty()) continue;

        istringstream ss(linea);
        Producto temp;
        string campo;

        // 5. Parsear campos con verificación
        try {
            if (!getline(ss, temp.codigo, ',') ||
                !getline(ss, temp.nombre, ',') ||
                !(ss >> temp.precio) ||
                !(ss.ignore() && (ss >> temp.stock))) {
                throw runtime_error("Formato inválido");
            }

            // 6. Validar código
            if (!esCodigoValido(temp.codigo)) {
                throw runtime_error("Código fuera de rango");
            }

            if (!codigoDisponible(lista, temp.codigo)) {
                throw runtime_error("Código duplicado");
            }

            lista.push_back(temp);
            cargados++;
        } catch (const exception& e) {
            cerr << "\n\t\tAdvertencia: Producto omitido (" << e.what() << "): " << linea << "\n";
            omitidos++;
        }
    }

    // 7. Verificar estado final
    if (archivo.bad()) {
        cerr << "\n\t\tError: Fallo durante la lectura del archivo!\n";
    }

    // 8. Mostrar resumen (opcional)
    cout << "\n\t\tCarga completada. " << cargados << " productos cargados, "
         << omitidos << " omitidos.\n";
}

