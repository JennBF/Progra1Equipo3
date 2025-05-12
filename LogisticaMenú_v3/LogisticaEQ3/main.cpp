#include <iostream>
#include <vector>
#include <string>
#include "usuarios.h"
#include "MenuPrincipal.h"
#include "pedidos.h"
#include "inventario.h"
#include "envios.h"
#include "facturacion.h"
#include "reportes.h"
#include "MenuCatalogos.h"
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
#include "Almacen.h"
#include "bitacora.h"
#include "globals.h"  // Incluir el archivo de globales

int main() {
    // Inicializar estructuras de datos
    std::vector<Clientes> listaClientes;
    std::vector<Proveedor> listaProveedores;
    std::vector<Producto> listaProductos;
    std::vector<Almacen> listaAlmacenes;

    Clientes::cargarDesdeArchivo(listaClientes);  // <- Esta línea es crucial
    Almacen::cargarDesdeArchivo(listaAlmacenes);  // <- Esta línea es crucial


    // Sistema de login
    if (usuarioRegistrado.loginUsuarios()) {
        // Mostrar menú principal si el login es exitoso
        MenuPrincipal::mostrar(listaClientes, listaProveedores, listaProductos, listaAlmacenes, usuarioRegistrado);
    }

    // Mensaje de despedida
   std::cout << "\n\t\t** Sistema de Logística - Hasta pronto **\n";


    Clientes::guardarEnArchivo(listaClientes);
    Almacen::guardarEnArchivo(listaAlmacenes);
    return 0;
}
