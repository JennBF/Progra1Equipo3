#include "MenuCatalogos.h"
#include "MenuClientes.h"
#include "MenuProveedores.h"
#include "MenuProductos.h"
#include "MenuAlmacenes.h"
#include "MenuAdministracion.h"
#include "MenuTransportistas.h"
#include <iostream>
#include <limits>

using namespace std;

void MenuCatalogos::mostrar(std::vector<Clientes>& clientes,
                          std::vector<Proveedor>& proveedores,
                          std::vector<Producto>& productos,
                          std::vector<Almacen>& almacenes,
                          std::vector<Administracion>& administradores,
                          std::vector<Transportistas>& transportistas,
                          usuarios& usuarioActual) {
    int opcion;
    do {
        system("cls");
        cout << "\t\t====================================\n"
             << "\t\t|        MENÚ CATÁLOGOS           |\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t| Nivel: " << usuarioActual.getNivelAcceso() << "\n"
             << "\t\t====================================\n"
             << "\t\t1. Clientes\n"
             << "\t\t2. Proveedores\n"
             << "\t\t3. Productos\n"
             << "\t\t4. Almacenes\n"
             << "\t\t5. Transportistas\n";

        // Solo mostrar opción de Administración si tiene nivel de acceso suficiente
        if(usuarioActual.getNivelAcceso() >= 3) {
            cout << "\t\t6. Administración\n";
        }

        cout << "\t\t7. Volver al menú principal\n"
             << "\t\t====================================\n"
             << "\t\tSeleccione una opción: ";

        // Validación de entrada
        while(!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un número: ";
        }
        cin.ignore(); // Limpiar buffer

        switch(opcion) {
            case 1:
                MenuClientes::mostrar(clientes, usuarioActual);
                break;
            case 2:
                MenuProveedores::mostrar(proveedores, usuarioActual);
                break;
            case 3:
                MenuProductos::mostrar(productos, usuarioActual);
                break;
            case 4:
                MenuAlmacenes::mostrar(almacenes, usuarioActual);
                break;
            case 5:
                MenuTransportistas::mostrar(transportistas, usuarioActual);
                break;
            case 6:
                if(usuarioActual.getNivelAcceso() >= 3) {
                    MenuAdministracion::mostrar(administradores, usuarioActual);
                } else {
                    cout << "\n\t\tAcceso denegado. Nivel de acceso insuficiente.\n";
                    system("pause");
                }
                break;
            case 7:
                return;
            default:
                cout << "\n\t\tOpción inválida. Intente nuevamente.\n";
                system("pause");
        }
    } while(true);
}
