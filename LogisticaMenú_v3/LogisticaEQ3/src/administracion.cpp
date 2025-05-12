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
    // Implementación aquí
}

void Administracion::agregarProveedor(const Proveedor& p) {
    // Implementación aquí
}



// Resto de métodos manteniendo el mismo patrón de acceso a través de getters
