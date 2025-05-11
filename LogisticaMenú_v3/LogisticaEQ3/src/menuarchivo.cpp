#include "MenuArchivo.h"
#include "usuarios.h"
#include <iostream>  // Faltaba en varios archivos
using namespace std;

extern usuarios usuarioRegistrado;

void MenuArchivo::mostrar() {
    int opcion;
    do {
        system("cls");
        std::cout << "\t\t========================================\n"
                  << "\t\t|          MEN� ARCHIVO                |\n"
                  << "\t\t========================================\n"
                  << "\t\t| Usuario: " << usuarioRegistrado.getNombre() << "\n"  // Nombre aqu�
                  << "\t\t========================================\n"
                  << "\t\t 1. Cerrar sesi�n\n"
                  << "\t\t 2. Backup\n"
                  << "\t\t 3. Volver\n"
                  << "\t\t========================================\n"
                  << "\t\tIngresa tu opci�n: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: usuarioRegistrado.~usuarios(); return;  // Cierra sesi�n
            case 2: /* ... */ break;
            case 3: return;
            default: std::cout << "\n\t\tOpci�n inv�lida...";
        }
    } while(true);
}
