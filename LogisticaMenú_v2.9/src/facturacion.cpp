// Angoly Araujo Mayo 2025 9959-24-17623

#include "facturacion.h"
#include "clientes.h"
#include "pedidos.h"
#include "bitacora.h"
#include "usuarios.h"
#include <fstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <regex>
#include <iostream>

using namespace std;

// Variables externas que se usan en este módulo
extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// Genera un nuevo ID de factura
int Facturacion::generarIdFactura() {
    ifstream archivo("facturas.bin", ios::binary);
    if (!archivo) return 3554;

    int ultimoId = 3554;
    Factura temp;

    while (true) {
        Factura factura = cargarDesdeArchivo(archivo);
        if (archivo.eof()) break;
        if (factura.idFactura > ultimoId) {
            ultimoId = factura.idFactura;
        }
    }

    archivo.close();
    return (ultimoId >= 3606) ? -1 : ultimoId + 1;
}

// Guarda una factura en el archivo binario
void Facturacion::guardarEnArchivo(const Factura& factura) {
    ofstream archivo("facturas.bin", ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&factura.idFactura), sizeof(factura.idFactura));
    archivo.write(reinterpret_cast<const char*>(&factura.monto), sizeof(factura.monto));
    archivo.write(reinterpret_cast<const char*>(&factura.pagada), sizeof(factura.pagada));

    size_t size;

    size = factura.idPedido.size();
    archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
    archivo.write(factura.idPedido.c_str(), size);

    size = factura.idCliente.size();
    archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
    archivo.write(factura.idCliente.c_str(), size);

    size = strlen(factura.cliente);
    archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
    archivo.write(factura.cliente, size);

    archivo.close();
}

Factura Facturacion::cargarDesdeArchivo(ifstream& archivo) {
    Factura factura;
    archivo.read(reinterpret_cast<char*>(&factura.idFactura), sizeof(factura.idFactura));
    archivo.read(reinterpret_cast<char*>(&factura.monto), sizeof(factura.monto));
    archivo.read(reinterpret_cast<char*>(&factura.pagada), sizeof(factura.pagada));

    size_t size;

    archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
    factura.idPedido.resize(size);
    archivo.read(&factura.idPedido[0], size);

    archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
    factura.idCliente.resize(size);
    archivo.read(&factura.idCliente[0], size);

    archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
    archivo.read(factura.cliente, size);
    factura.cliente[size] = '\0';

    return factura;
}

// Registra acción en bitácora
void Facturacion::registrarBitacora(const Factura& factura, const string& accion, const string& usuario) {
    ofstream bitacora("bitacora.bin", ios::app);
    bitacora << accion << " de factura ID: " << factura.idFactura
             << " por usuario: " << usuario << endl;
    bitacora.close();
}

// Menú principal de facturación
void Facturacion::mostrarMenuFacturacion() {
    int opcion;
    do {
        system("cls");
        cout << "===========================================\n";
        cout << "        SISTEMA DE FACTURACION\n";
        cout << "     Usuario: " << usuarioRegistrado.getNombre() << "\n";
        cout << "===========================================\n";
        cout << " [1] Crear Factura\n";
        cout << " [2] Mostrar Facturas\n";
        cout << " [3] Modificar Factura\n";
        cout << " [4] Eliminar Factura\n";
        cout << " [0] Salir\n";
        cout << "-------------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: crearFactura(); break;
            case 2: mostrarFacturas(); break;
            case 3: modificarFactura(); break;
            case 4: eliminarFactura(); break;
            case 0: cout << "\nSaliendo del modulo de facturacion...\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n"; break;
        }

        if (opcion != 0) {
            cout << "\nPresione ENTER para continuar...";
            cin.get();
        }

    } while (opcion != 0);
}

// Crear una nueva factura
void Facturacion::crearFactura() {
    system("cls");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "=====================================\n";
    cout << "        CREAR NUEVA FACTURA         \n";
    cout << "=====================================\n\n";
    cout << "Presione 0 en cualquier momento para cancelar\n\n";

    vector<Pedidos> listaPedidos;
    try {
        Pedidos::cargarDesdeArchivoBin(listaPedidos);
    } catch (...) {
        cout << "Error al cargar los pedidos.\n";
        system("pause");
        return;
    }

    if (listaPedidos.empty()) {
        cout << "No hay pedidos registrados.\n";
        system("pause");
        return;
    }

    cout << "--- Lista de todos los pedidos ---\n";
    for (const auto& pedido : listaPedidos) {
        cout << "ID: " << pedido.getId()
             << " | Cliente: " << pedido.getIdCliente()
             << " | Estado: " << pedido.getEstado()
             << " | Monto: $" << pedido.getMontoTotal() << "\n";
    }

    string idPedido;
    cout << "\nIngrese el ID del pedido a facturar (0 para cancelar): ";
    getline(cin, idPedido);
    if (idPedido == "0") return;

    auto it = find_if(listaPedidos.begin(), listaPedidos.end(),
        [&idPedido](const Pedidos& p) { return p.getId() == idPedido; });

    if (it == listaPedidos.end()) {
        cout << "Pedido no encontrado.\n";
        system("pause");
        return;
    }

    Factura nueva;
    nueva.idFactura = generarIdFactura();
    if (nueva.idFactura == -1) {
        cout << "No hay IDs disponibles para nuevas facturas.\n";
        system("pause");
        return;
    }

    nueva.idPedido = it->getId();
    nueva.idCliente = it->getIdCliente();
    nueva.monto = it->getMontoTotal();
    nueva.pagada = false;

    vector<Clientes> clientes;
    Clientes::cargarDesdeArchivo(clientes);

    auto clienteIt = find_if(clientes.begin(), clientes.end(),
        [&nueva](const Clientes& c) { return c.getId() == nueva.idCliente; });

    if (clienteIt != clientes.end()) {
        strncpy(nueva.cliente, clienteIt->getNombre().c_str(), sizeof(nueva.cliente) - 1);
        nueva.cliente[sizeof(nueva.cliente) - 1] = '\0';
    } else {
        strcpy(nueva.cliente, "Cliente Desconocido");
    }

    try {
        guardarEnArchivo(nueva);
        registrarBitacora(nueva, "Creacion", usuarioRegistrado.getNombre());

        cout << "\nFactura creada exitosamente!\n";
        cout << "ID Factura: " << nueva.idFactura << "\n";
        cout << "Cliente: " << nueva.cliente << "\n";
        cout << "Monto: $" << fixed << setprecision(2) << nueva.monto << "\n";
    } catch (...) {
        cout << "Error al guardar la factura.\n";
    }

    system("pause");
}

// Mostrar facturas
void Facturacion::mostrarFacturas() {
    system("cls");
    cout << "===========================================\n";
    cout << "          LISTADO DE FACTURAS           \n";
    cout << "===========================================\n";

    vector<Factura> facturas;
    ifstream archivo("facturas.bin", ios::binary);
    if (!archivo.is_open()) {
        cout << "\nNo hay facturas registradas.\n";
        system("pause");
        return;
    }

    try {
        while (archivo.peek() != EOF) {
            Factura fact = cargarDesdeArchivo(archivo);
            facturas.push_back(fact);
        }
    } catch (...) {
        cout << "\nError al leer el archivo de facturas.\n";
        archivo.close();
        system("pause");
        return;
    }
    archivo.close();

    vector<Clientes> clientes;
    Clientes::cargarDesdeArchivo(clientes);

    for (const auto& fact : facturas) {
        string nombreCliente = "No encontrado";
        for (const auto& cli : clientes) {
            if (cli.getId() == fact.idCliente) {
                nombreCliente = cli.getNombre();
                break;
            }
        }

        cout << "\nID Factura: " << fact.idFactura;
        cout << "\nID Pedido: " << fact.idPedido;
        cout << "\nCliente: " << nombreCliente;
        cout << "\nMonto: Q" << fixed << setprecision(2) << fact.monto;
        cout << "\nEstado: " << (fact.pagada ? "PAGADA" : "PENDIENTE");
        cout << "\n-------------------------------------------\n";
    }

    cout << "\nTotal de facturas: " << facturas.size() << "\n";
    system("pause");
}

// Modificar factura
void Facturacion::modificarFactura() {
    int volver;
    cout << "Desea regresar al menu principal? (1: Si / 0: No): ";
    cin >> volver;
    if (volver == 1) return;

    mostrarFacturas();

    int id;
    cout << "Ingrese el ID de la factura a modificar: ";
    cin >> id;

    vector<Factura> facturas;
    ifstream archivoEntrada("facturas.bin", ios::binary);
    if (!archivoEntrada.is_open()) {
        cout << "Error al abrir el archivo de facturas.\n";
        system("pause");
        return;
    }

    try {
        while (archivoEntrada.peek() != EOF) {
            Factura fact = cargarDesdeArchivo(archivoEntrada);
            facturas.push_back(fact);
        }
    } catch (...) {
        cout << "Error al leer las facturas.\n";
        archivoEntrada.close();
        system("pause");
        return;
    }
    archivoEntrada.close();

    bool encontrado = false;
    for (auto& fact : facturas) {
        if (fact.idFactura == id) {
            encontrado = true;
            cout << "Modificar estado de pago (1: Pagada / 0: No Pagada): ";
            cin >> fact.pagada;
            break;
        }
    }

    if (!encontrado) {
        cout << "Factura no encontrada.\n";
        system("pause");
        return;
    }

    ofstream archivoSalida("facturas.bin", ios::binary | ios::trunc);
    for (const auto& fact : facturas) {
        guardarEnArchivo(fact);
    }
    archivoSalida.close();

    cout << "Factura modificada correctamente.\n";
    system("pause");
}

// Eliminar factura
void Facturacion::eliminarFactura() {
    int volver;
    cout << "Desea regresar al menu principal? (1: Si / 0: No): ";
    cin >> volver;
    if (volver == 1) return;

    mostrarFacturas();

    int id;
    cout << "Ingrese el ID de la factura a eliminar: ";
    cin >> id;

    vector<Factura> facturas;
    ifstream archivo("facturas.bin", ios::binary);
    if (!archivo.is_open()) {
        cout << "Error al abrir facturas\n";
        system("pause");
        return;
    }

    try {
        while (archivo.peek() != EOF) {
            Factura fact = cargarDesdeArchivo(archivo);
            if (fact.idFactura != id) {
                facturas.push_back(fact);
            }
        }
    } catch (...) {
        cout << "Error al leer facturas\n";
        archivo.close();
        system("pause");
        return;
    }
    archivo.close();

    ofstream out("facturas.bin", ios::binary | ios::trunc);
    for (const auto& fact : facturas) {
        guardarEnArchivo(fact);
    }
    out.close();

    cout << "Factura eliminada correctamente\n";
    system("pause");
}
