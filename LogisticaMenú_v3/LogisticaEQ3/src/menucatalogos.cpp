#include "MenuCatalogos.h"
#include "MenuClientes.h"
#include "MenuProveedores.h"
#include "MenuProductos.h"
#include <iostream>

using namespace std;

void MenuCatalogos::mostrar(vector<Clientes>& clientes,
                           vector<Proveedor>& proveedores,
                           vector<Producto>& productos,
                           usuarios& usuarioActual) {  // Par�metros completos
    int opcion;
    do {
        system("cls");
        cout << "\t\t=== MEN� CAT�LOGOS ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Clientes\n"
             << "\t\t2. Proveedores\n"
             << "\t\t3. Productos\n"
             << "\t\t4. Almacenes\n"
             << "\t\t5. Volver\n";
        cin >> opcion;

        switch(opcion) {
            case 1: MenuClientes::mostrar(clientes, usuarioActual); break;
            case 2: MenuProveedores::mostrar(proveedores, usuarioActual); break;
            case 3: MenuProductos::mostrar(productos, usuarioActual); break;
            case 5: return;
            default: cout << "Opci�n inv�lida\n";
        }
    } while(opcion != 5);
}
