//Angoly Araujo Mayo 2025 9959-24-17623


#include "MenuProveedores.h"
#include <iostream>
using namespace std;

void MenuProveedores::mostrar(vector<Proveedor>& lista, usuarios& usuarioActual) {
    int opcion;
    do {
        system("cls");
        cout << "\t\t=== MENÚ PROVEEDORES ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Agregar proveedor\n"
             << "\t\t2. Mostrar proveedores\n"
             << "\t\t3. Modificar proveedor\n"
             << "\t\t4. Eliminar proveedor\n"
             << "\t\t5. Volver\n"
             << "\t\t========================\n"
             << "\t\tIngrese opción: ";
        cin >> opcion;

        string id;
        switch(opcion) {
            case 1:
                Proveedor::agregar(lista, usuarioActual.getNombre());
                break;
            case 2:
                Proveedor::mostrar(lista);
                break;
            case 3:
                cout << "\t\tIngrese ID del proveedor a modificar: ";
                cin >> id;
                Proveedor::modificar(lista, usuarioActual.getNombre(), id);
                break;
            case 4:
                cout << "\t\tIngrese ID del proveedor a eliminar: ";
                cin >> id;
                Proveedor::eliminar(lista, usuarioActual.getNombre(), id);
                break;
            case 5:
                return;
            default:
                cout << "\t\tOpción inválida\n";
        }

        cout << "\n\t\tPresione Enter para continuar...";
        cin.ignore();
        cin.get();
    } while(opcion != 5);
}

