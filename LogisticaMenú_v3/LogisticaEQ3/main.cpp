#include <iostream>
#include <vector>
#include <string>
#include "usuarios.h"
#include "MenuPrincipal.h"
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
#include "Almacen.h"
#include "Administracion.h"
#include "transportistas.h"
#include "globals.h"

int main() {
    // Inicializar todas las estructuras de datos
    std::vector<Clientes> listaClientes;
    std::vector<Proveedor> listaProveedores;
    std::vector<Producto> listaProductos;
    std::vector<Almacen> listaAlmacenes;
    std::vector<Administracion> listaAdministradores;
    std::vector<Transportistas> listaTransportistas;

    // Cargar datos desde archivos
    Clientes::cargarDesdeArchivo(listaClientes);
    Almacen::cargarDesdeArchivo(listaAlmacenes);
    Administracion::cargarDesdeArchivo(listaAdministradores);
    Transportistas::cargarDesdeArchivo(listaTransportistas);

    // Sistema de login
    if (usuarioRegistrado.loginUsuarios()) {
        // Mostrar menú principal con todos los parámetros requeridos
        MenuPrincipal::mostrar(
            listaClientes,
            listaProveedores,
            listaProductos,
            listaAlmacenes,
            listaAdministradores,
            listaTransportistas,
            usuarioRegistrado
        );
    }

    // Mensaje de despedida
    std::cout << "\n\t\t** Sistema de Logística - Hasta pronto **\n";

    // Guardar datos antes de salir
    Clientes::guardarEnArchivo(listaClientes);
    Almacen::guardarEnArchivo(listaAlmacenes);
    Administracion::guardarEnArchivo(listaAdministradores);
    Transportistas::guardarEnArchivo(listaTransportistas);

    return 0;
}
