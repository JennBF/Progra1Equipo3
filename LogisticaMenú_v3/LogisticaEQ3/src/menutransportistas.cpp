#include "MenuTransportistas.h"
#include "Transportistas.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits> // Para limpieza del buffer

using namespace std;

const int CODIGO_INICIAL_TRANS = 4100;
const int CODIGO_FINAL_TRANS = 4199;

void MenuTransportistas::mostrar(vector<Transportistas>& listaTransportistas, usuarios& usuarioActual) {
    int opcion;
    string input;

    do {
        system("cls");
        cout << "\t\t=== MENÚ TRANSPORTISTAS ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Agregar transportista\n"
             << "\t\t2. Mostrar transportistas\n"
             << "\t\t3. Modificar transportista\n"
             << "\t\t4. Eliminar transportista\n"
             << "\t\t5. Volver al menú principal\n"
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
            case 1:
                Transportistas::agregar(listaTransportistas, usuarioActual.getNombre());
                break;

            case 2:
                Transportistas::mostrar(listaTransportistas);
                break;

            case 3: {
                Transportistas::mostrar(listaTransportistas);
                if (!listaTransportistas.empty()) {
                    cout << "\n\t\tIngrese ID del transportista a modificar: ";
                    getline(cin, input);

                    if (Transportistas::esIdValido(input)) {
                        Transportistas::modificar(listaTransportistas, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tID no válido. Debe estar entre " << CODIGO_INICIAL_TRANS
                             << " y " << CODIGO_FINAL_TRANS << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 4: {
                Transportistas::mostrar(listaTransportistas);
                if (!listaTransportistas.empty()) {
                    cout << "\n\t\tIngrese ID del transportista a eliminar: ";
                    getline(cin, input);

                    if (Transportistas::esIdValido(input)) {
                        Transportistas::eliminar(listaTransportistas, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tID no válido. Debe estar entre " << CODIGO_INICIAL_TRANS
                             << " y " << CODIGO_FINAL_TRANS << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 5:
                // Guardar cambios al salir
                Transportistas::guardarEnArchivo(listaTransportistas);
                return;

            default:
                cout << "\t\tOpción no válida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true);
}
