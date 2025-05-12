#include "menuadministracion.h"
#include <iostream>
#include <limits> // Para limpieza del buffer

using namespace std;

void MenuAdministracion::mostrar(std::vector<usuarios>& listaUsuarios, Administracion& admin) {
    int opcion;

    do {
        system("cls");
        cout << "\t\t=== MENÚ ADMINISTRACIÓN ===\n"
             << "\t\t1. Agregar usuario\n"
             << "\t\t2. Mostrar usuarios\n"
             << "\t\t3. Agregar cliente\n"
             << "\t\t4. Mostrar clientes\n"
             << "\t\t5. Agregar proveedor\n"
             << "\t\t6. Mostrar proveedores\n"
             << "\t\t7. Agregar producto\n"
             << "\t\t8. Mostrar productos\n"
             << "\t\t9. Agregar pedido\n"
             << "\t\t10. Mostrar pedidos\n"
             << "\t\t11. Agregar transportista\n"
             << "\t\t12. Mostrar transportistas\n"
             << "\t\t13. Volver al menú principal\n"
             << "\t\t===========================\n"
             << "\t\tSeleccione una opción: ";

        // Validación de entrada
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Por favor ingrese un número: ";
        }
        cin.ignore(); // Limpiar el buffer

        switch(opcion) {
            case 1: {
                usuarios nuevoUsuario;
                // Aquí se debe agregar la lógica para llenar los datos del nuevo usuario
                admin.agregarUsuario(nuevoUsuario);
                break;
            }
            case 2:
                admin.mostrarUsuarios();
                break;
            case 3: {
                Clientes nuevoCliente;
                // Aquí se debe agregar la lógica para llenar los datos del nuevo cliente
                admin.agregarCliente(nuevoCliente);
                break;
            }
            case 4:
                admin.mostrarClientes();
                break;
            case 5: {
                Proveedor nuevoProveedor;
                // Aquí se debe agregar la lógica para llenar los datos del nuevo proveedor
                admin.agregarProveedor(nuevoProveedor);
                break;
            }
            case 6:
                admin.mostrarProveedores();
                break;
            case 7: {
                Producto nuevoProducto;
                // Aquí se debe agregar la lógica para llenar los datos del nuevo producto
                admin.agregarProducto(nuevoProducto);
                break;
            }
            case 8:
                admin.mostrarProductos();
                break;
            case 9: {
                Pedidos nuevoPedido;
                // Aquí se debe agregar la lógica para llenar los datos del nuevo pedido
                admin.agregarPedido(nuevoPedido);
                break;
            }
            case 10:
                admin.mostrarPedidos();
                break;
            case 11: {
                Transportistas nuevoTransportista;
                // Aquí se debe agregar la lógica para llenar los datos del nuevo transportista
                admin.agregarTransportista(nuevoTransportista);
                break;
            }
            case 12:
                admin.mostrarTransportistas();
                break;
            case 13:
                return; // Volver al menú principal
            default:
                cout << "\t\tOpción no válida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true);
}
