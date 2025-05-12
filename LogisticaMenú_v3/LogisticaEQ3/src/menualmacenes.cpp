#include "MenuAlmacenes.h"
#include <iostream>
#include <limits>



void MenuAlmacenes::mostrar(std::vector<Almacen>& lista, usuarios& usuarioActual) {
    int opcion;
    std::string input;

    do {


        system("cls");
        std::cout << "=== MENÚ ALMACENES ===\n"
                << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
                  << "1. Agregar Almacen\n"
                  << "2. Mostrar Almacenes\n"
                  << "3. Modificar Almacen\n"
                  << "4. Eliminar Almacen\n"
                  << "5. Volver al menú principal\n"
                << "\t\t=====================\n"
             << "\t\tSeleccione una opción: ";

        while (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Ingrese un número: ";
        }
        std::cin.ignore();

        switch (opcion) {
            case 1:
                Almacen::agregar(lista, usuarioActual.getNombre());
                break;
            case 2:
                Almacen::mostrar(lista);
                system("pause");
                break;
            case 3: {
                Almacen::mostrar(lista);
                std::cout << "ID a modificar: ";
                std::getline(std::cin, input);
                Almacen::modificar(lista, usuarioActual.getNombre(), input);
                break;
            }
            case 4: {
                Almacen::mostrar(lista);
                std::cout << "ID a eliminar: ";
                std::getline(std::cin, input);
                Almacen::eliminar(lista, usuarioActual.getNombre(), input);
                break;
            }
            case 5:
                return;
            default:
                std::cout << "Opción inválida\n";
                system("pause");
        }
    } while (true);
}
