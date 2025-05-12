//9959 24 11603 GE
#include "MenuAlmacenes.h"
#include <iostream>
#include <limits>

// Función para mostrar el menú de gestión de almacenes
void MenuAlmacenes::mostrar(std::vector<Almacen>& lista, usuarios& usuarioActual) {
    int opcion;             // Variable para almacenar la opción del menú
    std::string input;      // Entrada auxiliar para ID u otros textos

    do {
        // Limpia la pantalla (solo funciona en Windows)
        system("cls");

        // Muestra el menú
        std::cout << "=== MENÚ ALMACENES ===\n"
                  << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
                  << "1. Agregar Almacen\n"
                  << "2. Mostrar Almacenes\n"
                  << "3. Modificar Almacen\n"
                  << "4. Eliminar Almacen\n"
                  << "5. Volver al menú principal\n"
                  << "\t\t=====================\n"
                  << "\t\tSeleccione una opción: ";

        // Validación de entrada numérica
        while (!(std::cin >> opcion)) {
            std::cin.clear(); // Limpia el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada inválida
            std::cout << "Entrada inválida. Ingrese un número: ";
        }
        std::cin.ignore(); // Limpia el salto de línea del buffer

        // Ejecuta la opción seleccionada
        switch (opcion) {
            case 1:
                // Agrega un nuevo almacén
                Almacen::agregar(lista, usuarioActual.getNombre());
                break;
            case 2:
                // Muestra la lista de almacenes
                Almacen::mostrar(lista);
                system("pause"); // Pausa hasta que el usuario presione una tecla
                break;
            case 3: {
                // Modifica un almacén existente
                Almacen::mostrar(lista); // Muestra para que el usuario vea el ID
                std::cout << "ID a modificar: ";
                std::getline(std::cin, input);
                Almacen::modificar(lista, usuarioActual.getNombre(), input);
                break;
            }
            case 4: {
                // Elimina un almacén
                Almacen::mostrar(lista); // Muestra para que el usuario vea el ID
                std::cout << "ID a eliminar: ";
                std::getline(std::cin, input);
                Almacen::eliminar(lista, usuarioActual.getNombre(), input);
                break;
            }
            case 5:
                // Vuelve al menú principal
                return;
            default:
                // Opción inválida
                std::cout << "Opción inválida\n";
                system("pause");
        }
    } while (true); // Repite hasta que se elija salir
}
