#include "menuprincipal.h"
#include "menuarchivo.h"
#include "menucatalogos.h"
#include "menuprocesos.h"
#include "usuarios.h"
#include <vector>
#include <iostream>
using namespace std;

void MenuPrincipal::mostrar(std::vector<Clientes>& clientes,
                          std::vector<Proveedor>& proveedores,
                          std::vector<Producto>& productos,
                          std::vector<Almacen>& almacenes,  // A�adir este par�metro
                          usuarios& usuarioActual) {
    int choice;
    do {
        system("cls");
        cout << "\t\t========================================\n"
             << "\t\t|     SISTEMA DE GESTI�N LOG�STICA     |\n"
             << "\t\t========================================\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t================================================\n"
             << "\t\t 1. Archivo\n"
             << "\t\t 2. Cat�logos\n"
             << "\t\t 3. Procesos\n"
             << "\t\t 4. Informes\n"
             << "\t\t 5. Salir\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opci�n: ";
        cin >> choice;

        switch(choice) {
            case 1: MenuArchivo::mostrar(); break;
            case 2: MenuCatalogos::mostrar(clientes, proveedores, productos, almacenes, usuarioActual); break;
            case 3: MenuProcesos::mostrar(); break;
            case 4: /* INFORMES */ break;
            case 5: return;
            default: cout << "\n\t\tOpci�n inv�lida... Intenta de nuevo...";
        }
    } while(choice != 5);
}
