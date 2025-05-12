#include "administracion.h"
#include <iostream>

void Administracion::mostrarUsuarios() {
    std::cout << "--- LISTA DE USUARIOS ---\n";
    for (const auto& usuario : listaUsuarios) {
        std::cout << "Nombre: " << usuario.getNombre() << "\n";
    }
}

void Administracion::mostrarProveedores() {
    std::cout << "--- LISTA DE PROVEEDORES ---\n";
    for (const auto& proveedor : listaProveedores) {
        std::cout << "ID: " << proveedor.getId() << " | Nombre: " << proveedor.getNombre() << "\n";
    }
}

void Administracion::mostrarPedidos() {
    std::cout << "--- LISTA DE PEDIDOS ---\n";
    for (const auto& pedido : listaPedidos) {
        std::cout << "ID: " << pedido.getId() << " | Detalles: " << pedido.getDetalles() << "\n";
    }
}

void Administracion::agregarUsuario(const usuarios& nuevoUsuario) {
    listaUsuarios.push_back(nuevoUsuario);
}

void Administracion::agregarCliente(const Clientes& nuevoCliente) {
    listaClientes.push_back(nuevoCliente);
}

#include "Administracion.h"

void Administracion::mostrarClientes() {
    // Implementaci�n aqu�
}

void Administracion::agregarProveedor(const Proveedor& p) {
    // Implementaci�n aqu�
}



// Resto de m�todos manteniendo el mismo patr�n de acceso a trav�s de getters
