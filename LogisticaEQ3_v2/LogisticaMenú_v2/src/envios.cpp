#include "envios.h"
#include "pedidos.h"
#include "transportistas.h"
#include "almacen.h"
#include "clientes.h"
#include "bitacora.h"

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Variables externas (declaradas en otro lado)
extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// ----------- Funciones privadas est�ticas ------------

vector<Envio> Envios::cargarEnviosDesdeArchivo() {
    ifstream archivo("envios.dat", ios::binary);
    vector<Envio> lista;
    if (!archivo) return lista;

    while (!archivo.eof()) {
        Envio envio;
        size_t size;

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (archivo.eof()) break;
        envio.idPedido.resize(size);
        archivo.read(&envio.idPedido[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        envio.idTransportista.resize(size);
        archivo.read(&envio.idTransportista[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        envio.estado.resize(size);
        archivo.read(&envio.estado[0], size);

        lista.push_back(envio);
    }
    archivo.close();
    return lista;
}

void Envios::guardarEnviosEnArchivo(const vector<Envio>& envios) {
    ofstream archivo("envios.dat", ios::binary | ios::trunc);
    for (const auto& envio : envios) {
        size_t size;

        size = envio.idPedido.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(envio.idPedido.c_str(), size);

        size = envio.idTransportista.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(envio.idTransportista.c_str(), size);

        size = envio.estado.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(envio.estado.c_str(), size);
    }
    archivo.close();
}

// ----------- Funciones auxiliares fuera de la clase ------------

vector<Transportistas> cargarTransportistasDisponibles() {
    vector<Transportistas> todos;
    Transportistas::cargarDesdeArchivo(todos);
    vector<Transportistas> disponibles;
    for (const auto& t : todos) {
        if (t.getDisponibilidad() == "disponible") {
            disponibles.push_back(t);
        }
    }
    return disponibles;
}

vector<Pedidos> cargarPedidos() {
    vector<Pedidos> pedidos;
    Pedidos::cargarDesdeArchivo(pedidos);
    return pedidos;
}

void guardarPedidos(const vector<Pedidos>& pedidos) {
    Pedidos::guardarEnArchivo(pedidos);
}

// ----------- M�todos de la clase Envios ------------

void Envios::crearEnvioInteractivo() {
    system("cls");
    cout << "\n\t=== CREAR NUEVO ENV�O ===\n";

    vector<Transportistas> transportistas = cargarTransportistasDisponibles();
    vector<Pedidos> pedidos = cargarPedidos();

    if (transportistas.empty()) {
        cout << "\n\tNo hay transportistas disponibles.\n";
        return;
    }

    string idPedido;
    cout << "Ingrese ID del pedido para env�o: ";
    cin >> idPedido;

    auto itPedido = find_if(pedidos.begin(), pedidos.end(), [&](const Pedidos& p) {
        return p.getId() == idPedido;
    });

    if (itPedido == pedidos.end()) {
        cout << "\n\tPedido no encontrado.\n";
        return;
    }

    if (itPedido->getEstado() != "procesado") {
        cout << "\n\tEl pedido no est� en estado 'procesado'.\n";
        return;
    }

    Envio nuevo;
    nuevo.idPedido = idPedido;
    nuevo.idTransportista = transportistas.front().id;
    nuevo.estado = "en camino";

    vector<Envio> envios = cargarEnviosDesdeArchivo();
    envios.push_back(nuevo);
    guardarEnviosEnArchivo(envios);

    itPedido->setEstado("enviado");
    guardarPedidos(pedidos);

    auditoria.registrar(usuarioRegistrado.getNombre(), "ENVIOS", "Creado env�o para pedido " + idPedido);
    cout << "\n\tEnv�o creado exitosamente.\n";
}

void Envios::crearEnvio(const std::string& idPedido, const std::vector<Transportistas>& transportistasDisponibles) {
    if (transportistasDisponibles.empty()) {
        std::cout << "No hay transportistas disponibles." << std::endl;
        return;
    }

    Envio nuevo;
    nuevo.idPedido = idPedido;
    nuevo.idTransportista = transportistasDisponibles.front().id;
    nuevo.estado = "en camino";

    std::vector<Envio> envios = cargarEnviosDesdeArchivo();
    envios.push_back(nuevo);
    guardarEnviosEnArchivo(envios);

    std::cout << "Envio creado con �xito para pedido: " << idPedido << std::endl;
}


void Envios::mostrarEnvios() {
    vector<Envio> envios = cargarEnviosDesdeArchivo();
    if (envios.empty()) {
        cout << "\n\tNo hay env�os registrados.\n";
        return;
    }

    cout << "\n\t===== LISTA DE ENV�OS =====\n";
    for (const auto& envio : envios) {
        cout << "\nPedido ID: " << envio.idPedido
             << "\nTransportista ID: " << envio.idTransportista
             << "\nEstado: " << envio.estado << "\n--------------------------\n";
    }
}

void modificarEstadoEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();
    string id;
    cout << "Ingrese ID del pedido a modificar: ";
    cin >> id;

    auto it = find_if(envios.begin(), envios.end(), [&](const Envio& e) {
        return e.idPedido == id;
    });

    if (it == envios.end()) {
        cout << "\n\tEnv�o no encontrado.\n";
        return;
    }

    if (it->estado != "en camino") {
        cout << "\n\tSolo se puede modificar si est� 'en camino'.\n";
        return;
    }

    cout << "\nNuevo estado (entregado/demorado/devuelto): ";
    string nuevoEstado;
    cin >> nuevoEstado;

    if (nuevoEstado != "entregado" && nuevoEstado != "demorado" && nuevoEstado != "devuelto") {
        cout << "\n\tEstado inv�lido.\n";
        return;
    }

    it->estado = nuevoEstado;
    Envios::guardarEnviosEnArchivo(envios);
    cout << "\n\tEstado actualizado correctamente.\n";
}

void cancelarEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();
    string id;
    cout << "Ingrese ID del env�o a cancelar: ";
    cin >> id;

    auto it = find_if(envios.begin(), envios.end(), [&](const Envio& e) {
        return e.idPedido == id;
    });

    if (it == envios.end()) {
        cout << "\n\tEnv�o no encontrado.\n";
        return;
    }

    if (it->estado == "entregado") {
        cout << "\n\tNo se puede cancelar un env�o entregado.\n";
        return;
    }

    it->estado = "cancelado";
    Envios::guardarEnviosEnArchivo(envios);
    cout << "\n\tEnv�o cancelado correctamente.\n";
}

void eliminarEnvio() {
    vector<Envio> envios = Envios::cargarEnviosDesdeArchivo();
    string id;
    cout << "Ingrese ID del env�o a eliminar: ";
    cin >> id;

    auto it = find_if(envios.begin(), envios.end(), [&](const Envio& e) {
        return e.idPedido == id;
    });

    if (it == envios.end()) {
        cout << "\n\tEnv�o no encontrado.\n";
        return;
    }

    char confirm;
    cout << "�Confirmar eliminaci�n? (s/n): ";
    cin >> confirm;

    if (confirm == 's' || confirm == 'S') {
        envios.erase(it);
        Envios::guardarEnviosEnArchivo(envios);
        cout << "\n\tEnv�o eliminado exitosamente.\n";
    } else {
        cout << "\n\tOperaci�n cancelada.\n";
    }
}

void Envios::gestionEnvios() {
    int opcion = 0;
    do {
        system("cls");
        cout << "\t\t========================================\n";
        cout << "\t\t|     SISTEMA DE GESTI�N DE ENV�OS      |\n";
        cout << "\t\t========================================\n";
        cout << "\t\t 1. Crear nuevo env�o\n";
        cout << "\t\t 2. Consultar env�os\n";
        cout << "\t\t 3. Modificar estado de env�o\n";
        cout << "\t\t 4. Cancelar env�o\n";
        cout << "\t\t 5. Eliminar env�o\n";
        cout << "\t\t 6. Volver al men� principal\n";
        cout << "\t\t========================================\n";
        cout << "\t\t Opci�n a escoger: ";

        cin >> opcion;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: crearEnvioInteractivo(); break;
            case 2: mostrarEnvios(); break;
            case 3: modificarEstadoEnvio(); break;
            case 4: cancelarEnvio(); break;
            case 5: eliminarEnvio(); break;
            case 6:
                cout << "\n\tSaliendo...\n";
                break;
            default:
                cout << "\n\tOpci�n inv�lida.\n";
                system("pause");
                break;
        }

        if (opcion >= 1 && opcion <= 5) {
            system("pause");
        }

    } while (opcion != 6);
}




