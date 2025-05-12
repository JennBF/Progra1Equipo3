//9959 24 11603 GE
#include "MenuAlmacenes.h"
#include <iostream>
#include <limits>

// Funci�n para mostrar el men� de gesti�n de almacenes
void MenuAlmacenes::mostrar(std::vector<Almacen>& lista, usuarios& usuarioActual) {
    int opcion;             // Variable para almacenar la opci�n del men�
    std::string input;      // Entrada auxiliar para ID u otros textos

    do {
        // Limpia la pantalla (solo funciona en Windows)
        system("cls");

        // Muestra el men�
        std::cout << "=== MEN� ALMACENES ===\n"
                  << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
                  << "1. Agregar Almacen\n"
                  << "2. Mostrar Almacenes\n"
                  << "3. Modificar Almacen\n"
                  << "4. Eliminar Almacen\n"
                  << "5. Volver al men� principal\n"
                  << "\t\t=====================\n"
                  << "\t\tSeleccione una opci�n: ";

        // Validaci�n de entrada num�rica
        while (!(std::cin >> opcion)) {
            std::cin.clear(); // Limpia el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada inv�lida
            std::cout << "Entrada inv�lida. Ingrese un n�mero: ";
        }
        std::cin.ignore(); // Limpia el salto de l�nea del buffer

        // Ejecuta la opci�n seleccionada
        switch (opcion) {
            case 1:
                // Agrega un nuevo almac�n
                Almacen::agregar(lista, usuarioActual.getNombre());
                break;
            case 2:
                // Muestra la lista de almacenes
                Almacen::mostrar(lista);
                system("pause"); // Pausa hasta que el usuario presione una tecla
                break;
            case 3: {
                // Modifica un almac�n existente
                Almacen::mostrar(lista); // Muestra para que el usuario vea el ID
                std::cout << "ID a modificar: ";
                std::getline(std::cin, input);
                Almacen::modificar(lista, usuarioActual.getNombre(), input);
                break;
            }
            case 4: {
                // Elimina un almac�n
                Almacen::mostrar(lista); // Muestra para que el usuario vea el ID
                std::cout << "ID a eliminar: ";
                std::getline(std::cin, input);
                Almacen::eliminar(lista, usuarioActual.getNombre(), input);
                break;
            }
            case 5:
                // Vuelve al men� principal
                return;
            default:
                // Opci�n inv�lida
                std::cout << "Opci�n inv�lida\n";
                system("pause");
        }
    } while (true); // Repite hasta que se elija salir
}
