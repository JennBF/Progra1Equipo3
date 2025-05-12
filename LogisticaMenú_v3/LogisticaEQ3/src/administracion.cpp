#include "administracion.h"

// Métodos para gestionar usuarios
void Administracion::agregarUsuario(const usuarios& nuevoUsuario) {
    listaUsuarios.push_back(nuevoUsuario);
    std::cout << "Usuario agregado exitosamente.\n";
}

void Administracion::mostrarUsuarios() {
    std::cout << "--- LISTA DE USUARIOS ---\n";
    for (const auto& usuario : listaUsuarios) {
        std::cout << "ID: " << usuario.getId() << " | Nombre: " << usuario.getNombre() << "\n";
    }
}

// Métodos para gestionar clientes
void Administracion::agregarCliente(const Clientes& nuevoCliente) {
    listaClientes.push_back(nuevoCliente);
    std::cout << "Cliente agregado exitosamente.\n";
}

void Administracion::mostrarClientes() {
    std::cout << "--- LISTA DE CLIENTES ---\n";
    for (const auto& cliente : listaClientes) {
        std::cout << "ID: " << cliente.id << " | Nombre: " << cliente.nombre << "\n";
    }
}

// Métodos para gestionar proveedores
void Administracion::agregarProveedor(const Proveedor& nuevoProveedor) {
    listaProveedores.push_back(nuevoProveedor);
    std::cout << "Proveedor agregado exitosamente.\n";
}

void Administracion::mostrarProveedores() {
    std::cout << "--- LISTA DE PROVEEDORES ---\n";
    for (const auto& proveedor : listaProveedores) {
        std::cout << "ID: " << proveedor.id << " | Nombre: " << proveedor.nombre << "\n";
    }
}

// Métodos para gestionar productos
void Administracion::agregarProducto(const Producto& nuevoProducto) {
    listaProductos.push_back(nuevoProducto);
    std::cout << "Producto agregado exitosamente.\n";
}

void Administracion::mostrarProductos() {
    std::cout << "--- LISTA DE PRODUCTOS ---\n";
    for (const auto& producto : listaProductos) {
        std::cout << "Código: " << producto.codigo << " | Nombre: " << producto.nombre << "\n";
    }
}

// Métodos para gestionar pedidos
void Administracion::agregarPedido(const Pedidos& nuevoPedido) {
    listaPedidos.push_back(nuevoPedido);
    std::cout << "Pedido agregado exitosamente.\n";
}

void Administracion::mostrarPedidos() {
    std::cout << "--- LISTA DE PEDIDOS ---\n";
    for (const auto& pedido : listaPedidos) {
        std::cout << "ID: " << pedido.id << " | Detalles: " << pedido.detalles << "\n";
    }
}

// Métodos para gestionar transportistas
void Administracion::agregarTransportista(const Transportistas& nuevoTransportista) {
    listaTransportistas.push_back(nuevoTransportista);
    std::cout << "Transportista agregado exitosamente.\n";
}

void Administracion::mostrarTransportistas() {
    std::cout << "--- LISTA DE TRANSPORTISTAS ---\n";
    for (const auto& transportista : listaTransportistas) {
        std::cout << "ID: " << transportista.id << " | Nombre: " << transportista.nombre << "\n";
    }
}
