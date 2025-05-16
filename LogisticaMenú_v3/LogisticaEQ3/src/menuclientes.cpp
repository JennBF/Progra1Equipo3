#include "MenuClientes.h"
#include "Clientes.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits> // Para limpieza del buffer

using namespace std;

const int CODIGO_INICIAL = 3107;
const int CODIGO_FINAL = 3157;

void MenuClientes::mostrar(vector<Clientes>& listaClientes, usuarios& usuarioActual) {
    int opcion;
    string input;

    do {
        system("cls");
        cout << "\t\t=== MENÚ CLIENTES ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Agregar cliente\n"
             << "\t\t2. Mostrar clientes\n"
             << "\t\t3. Modificar cliente\n"
             << "\t\t4. Eliminar cliente\n"
             << "\t\t5. Volver al menú principal\n"
             << "\t\t=====================\n"
             << "\t\tSeleccione una opción: ";

        // Validación de entrada - CORRECCIÓN: Falta paréntesis de cierre en while
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Por favor ingrese un número: ";
        }
        cin.ignore(); // Limpiar el buffer

        switch(opcion) {
            case 1:
                Clientes::agregar(listaClientes, usuarioActual.getNombre());
                break;

            case 2:
                Clientes::mostrar(listaClientes);
                break;

            case 3: {
                Clientes::mostrar(listaClientes);
                if (!listaClientes.empty()) {
                    cout << "\n\t\tIngrese ID del cliente a modificar: ";
                    getline(cin, input);

                    if (Clientes::esIdValido(input)) {
                        Clientes::modificar(listaClientes, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tID no válido. Debe estar entre " << CODIGO_INICIAL
                             << " y " << CODIGO_FINAL << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 4: {
                Clientes::mostrar(listaClientes);
                if (!listaClientes.empty()) {
                    cout << "\n\t\tIngrese ID del cliente a eliminar: ";
                    getline(cin, input);

                    if (Clientes::esIdValido(input)) {
                        Clientes::eliminar(listaClientes, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tID no válido. Debe estar entre " << CODIGO_INICIAL
                             << " y " << CODIGO_FINAL << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 5:
                // Guardar cambios al salir
                Clientes::guardarEnArchivo(listaClientes);
                return;

            default:
                cout << "\t\tOpción no válida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true);
}
