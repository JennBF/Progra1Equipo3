#ifndef ADMINISTRACION_H
#define ADMINISTRACION_H

#include <iostream>
#include <vector>
#include "usuarios.h"
#include "clientes.h"
#include "proveedor.h"
#include "producto.h"
#include "pedidos.h"
#include "transportistas.h"

class Administracion {
private:
    std::vector<usuarios> listaUsuarios;
    std::vector<Clientes> listaClientes;
    std::vector<Proveedor> listaProveedores;
    std::vector<Producto> listaProductos;
    std::vector<Pedidos> listaPedidos;
    std::vector<Transportistas> listaTransportistas;

public:
    // M�todos para gestionar usuarios
    void agregarUsuario(const usuarios& nuevoUsuario);
    void mostrarUsuarios();

    // M�todos para gestionar clientes
    void agregarCliente(const Clientes& nuevoCliente);
    void mostrarClientes();

    // M�todos para gestionar proveedores
    void agregarProveedor(const Proveedor& nuevoProveedor);
    void mostrarProveedores();

    // M�todos para gestionar productos
    void agregarProducto(const Producto& nuevoProducto);
    void mostrarProductos();

    // M�todos para gestionar pedidos
    void agregarPedido(const Pedidos& nuevoPedido);
    void mostrarPedidos();

    // M�todos para gestionar transportistas
    void agregarTransportista(const Transportistas& nuevoTransportista);
    void mostrarTransportistas();
};

#endif // ADMINISTRACION_H
