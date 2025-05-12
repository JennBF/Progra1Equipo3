#include "menuadministracion.h"
#include "Administracion.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits> // Para limpieza del buffer

using namespace std;

// Definir las constantes aquí o incluirlas desde Administracion.h
const int CODIGO_INICIAL_ADMIN = 3362;
const int CODIGO_FINAL_ADMIN = 3402;

void MenuAdministracion::mostrar(vector<Administracion>& listaAdministradores, usuarios& usuarioActual) {
    int opcion;
    string input;

    do {
        system("cls");
        cout << "\t\t=== MENÚ ADMINISTRACIÓN ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t| Nivel de acceso: " << usuariosActual.getNivelAcceso() << "\n"
             << "\t\t1. Agregar administrador\n"
             << "\t\t2. Mostrar administradores\n"
             << "\t\t3. Modificar administrador\n"
             << "\t\t4. Eliminar administrador\n"
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
                // Verificar nivel de acceso para agregar administradores
                if (usuarioActual.getNivelAcceso() >= 4) {
                    Administracion::agregar(listaAdministradores, usuariosActual.getNombre());
                } else {
                    cout << "\n\t\tAcceso denegado. Se requiere nivel 4 o superior.\n";
                    system("pause");
                }
                break;

            case 2:
                Administracion::mostrar(listaAdministradores);
                break;

            case 3: {
                // Verificar nivel de acceso para modificar
                if (usuariosActual.getNivelAcceso() >= 3) {
                    Administracion::mostrar(listaAdministradores);
                    if (!listaAdministradores.empty()) {
                        cout << "\n\t\tIngrese ID del administrador a modificar: ";
                        getline(cin, input);

                        if (Administracion::esIdValido(input)) {
                            // No permitir modificar administradores con mayor nivel de acceso
                            auto it = find_if(listaAdministradores.begin(), listaAdministradores.end(),
                                [&input](const administracion& a) { return a.id == input; });

                            if (it != listaAdministradores.end() && it->nivelAcceso <= usuarioActual.getNivelAcceso()) {
                                Administracion::modificar(listaAdministradores, usuariosActual.getNombre(), input);
                            } else {
                                cout << "\t\tNo puedes modificar administradores con mayor nivel de acceso.\n";
                                system("pause");
                            }
                        } else {
                            cout << "\t\tID no válido. Debe estar entre " << CODIGO_INICIAL_ADMIN
                                 << " y " << CODIGO_FINAL_ADMIN << "\n";
                            system("pause");
                        }
                    }
                } else {
                    cout << "\n\t\tAcceso denegado. Se requiere nivel 3 o superior.\n";
                    system("pause");
                }
                break;
            }

            case 4: {
                // Verificar nivel de acceso para eliminar
                if (usuariosActual.getNivelAcceso() >= 5) {
                    Administracion::mostrar(listaAdministradores);
                    if (!listaAdministradores.empty()) {
                        cout << "\n\t\tIngrese ID del administrador a eliminar: ";
                        getline(cin, input);

                        if (Administracion::esIdValido(input)) {
                            // No permitir eliminarse a sí mismo o superiores
                            if (input != usuarioActual.getId()) {
                                auto it = find_if(listaAdministradores.begin(), listaAdministradores.end(),
                                    [&input](const Administracion& a) { return a.id == input; });

                                if (it != listaAdministradores.end() && it->nivelAcceso < usuariosActual.getNivelAcceso()) {
                                    Administracion::eliminar(listaAdministradores, usuarioActual.getNombre(), input);
                                } else {
                                    cout << "\t\tNo puedes eliminar este administrador.\n";
                                    system("pause");
                                }
                            } else {
                                cout << "\t\tNo puedes eliminarte a ti mismo.\n";
                                system("pause");
                            }
                        } else {
                            cout << "\t\tID no válido. Debe estar entre " << CODIGO_INICIAL_ADMIN
                                 << " y " << CODIGO_FINAL_ADMIN << "\n";
                            system("pause");
                        }
                    }
                } else {
                    cout << "\n\t\tAcceso denegado. Se requiere nivel 5 (Administrador Superior).\n";
                    system("pause");
                }
                break;
            }

            case 5:
                // Guardar cambios al salir
                Administracion::guardarEnArchivo(listaAdministradores);
                return;

            default:
                cout << "\t\tOpción no válida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true);
}
