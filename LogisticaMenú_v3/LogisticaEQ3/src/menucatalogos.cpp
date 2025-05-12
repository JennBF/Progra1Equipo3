#include "MenuCatalogos.h"
#include "MenuClientes.h"
#include "MenuProveedores.h"
#include "MenuProductos.h"
#include "MenuAlmacenes.h"
#include <iostream>

using namespace std;

void MenuCatalogos::mostrar(vector<Clientes>& clientes,
                           vector<Proveedor>& proveedores,
                           vector<Producto>& productos,
                           vector<Almacen>& almacenes,
                           usuarios& usuarioActual) {  // Parámetros completos
    int opcion;
    do {
        system("cls");
        cout << "\t\t=== MENÚ CATÁLOGOS ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Clientes\n"
             << "\t\t2. Proveedores\n"
             << "\t\t3. Productos\n"
             << "\t\t4. Transportistas"
             << "\t\t5. Almacenes\n"
             << "\t\t6. Volver\n";
        cin >> opcion;

        switch(opcion) {
            case 1: MenuClientes::mostrar(clientes, usuarioActual); break;
            case 2: MenuProveedores::mostrar(proveedores, usuarioActual); break;
            case 3: MenuProductos::mostrar(productos, usuarioActual); break;
            case 4: MenuAlmacenes::mostrar(almacenes, usuarioActual); break;
            case 5: return;
            default: cout << "Opción inválida\n";
        }
    } while(opcion != 6);
}
