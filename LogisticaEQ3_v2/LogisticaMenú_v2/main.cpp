// 9959 24 11603 GE
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
    // Inicializar todas las listas necesarias para almacenar datos del sistema
    std::vector<Clientes> listaClientes;
    std::vector<Proveedor> listaProveedores;
    std::vector<Producto> listaProductos;
    std::vector<Almacen> listaAlmacenes;
    std::vector<Administracion> listaAdministradores;
    std::vector<Transportistas> listaTransportistas;

    // Cargar los datos previamente guardados desde archivos a sus respectivas listas
    Clientes::cargarDesdeArchivo(listaClientes);
    Almacen::cargarDesdeArchivo(listaAlmacenes);
    Administracion::cargarDesdeArchivo(listaAdministradores);
    Transportistas::cargarDesdeArchivo(listaTransportistas);
    Producto::cargarDesdeArchivo(listaProductos); // A�ADIDO: carga de productos
    Proveedor::cargarDesdeArchivo(listaProveedores); // A�ADIDO: carga de proveedores

    // Iniciar sistema de login (verifica si el usuario puede ingresar)
    if (usuarioRegistrado.loginUsuarios()) {
        // Si el login es exitoso, se muestra el men� principal con todas las listas necesarias
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

    // Mensaje de salida cuando el programa termina
    std::cout << "\n\t\t** Sistema de Log�stica - Hasta pronto **\n";

    // Guardar todos los datos actualizados en sus respectivos archivos antes de finalizar
    Clientes::guardarEnArchivos(listaClientes);
    Almacen::guardarEnArchivo(listaAlmacenes);
    Administracion::guardarEnArchivo(listaAdministradores);
    Transportistas::guardarEnArchivo(listaTransportistas);
    Producto::guardarEnArchivo(listaProductos); // A�ADIDO: guardado de productos
    Proveedor::guardarEnArchivo(listaProveedores); // A�ADIDO: guardado de proveedores

    // Fin del programa
    return 0;
}
