#include <iostream>
#include <string>
using namespace std;

// Declaración de funciones
void mostrarMenuPrincipal();
void gestionPedidos();
void facturacionYAnalisis(); // <-- Nueva función
void controlInventario(); // <-- Nueva función agregada

// Funciones de facturación y análisis
void generarFactura() {
    cout << "[Generando factura...]" << endl;
}

void consultarEstadoPago() {
    cout << "[Consultando estados de pago...]" << endl;
}

void registrarPago() {
    cout << "[Registrando un pago...]" << endl;
}

void verReportesFinancieros() {
    cout << "[Mostrando reportes financieros...]" << endl;
}

// Funciones de control de inventario
void stockDisponible() {
    cout << "[Revisando stock disponible...]" << endl;
}

void registroMercancia() {
    cout << "[Registrando mercancia nueva...]" << endl;
}

void ajusteInventario() {
    cout << "[Realizando ajustes en el inventario...]" << endl;
}

void verReportesExistencia() {
    cout << "[Mostrando reportes de existencias...]" << endl;
}

int main() {
    string nombre;

    // Solicitar nombre al usuario
    system("cls");
    cout << "========================\n";
    cout << "  SISTEMA  LOGISTICA\n";
    cout << "========================\n";
    cout << "Por favor ingrese su nombre: ";
    cin >> nombre;

    // Mostrar bienvenida
    cout << "\nBienvenido, " << nombre << "!\n";
    system("pause");

    // Menú principal
    int opcion;
    do {
        system("cls");
        mostrarMenuPrincipal();
        cout << "Seleccione una opcion (" << nombre << "): ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                gestionPedidos();
                break;
            case 2:
                controlInventario();
                break;
            case 3:
                cout << "\nEnvios y Transportes (pendiente)\n";
                system("pause");
                break;
            case 4:
                facturacionYAnalisis();
                break;
            case 5:
                cout << "\nReportes y Analisis (pendiente)\n";
                system("pause");
                break;
            case 0:
                cout << "\nHasta luego, " << nombre << "!\n";
                break;
            default:
                cout << "\nOpcion no valida!\n";
                system("pause");
        }
    } while(opcion != 0);

    return 0;
}

void mostrarMenuPrincipal() {
    cout << "\n========================\n";
    cout << "  MENU PRINCIPAL\n";
    cout << "========================\n";
    cout << "1. Gestion de Pedidos\n";
    cout << "2. Control de Inventario\n";
    cout << "3. Envios y Transportes\n";
    cout << "4. Facturacion y Administracion\n";
    cout << "5. Reportes y Analisis\n";
    cout << "0. Salir\n";
    cout << "========================\n";
}

void gestionPedidos() {
    int opcion;
    do {
        system("cls");
        cout << "\n========================\n";
        cout << "  GESTION DE PEDIDOS\n";
        cout << "========================\n";
        cout << "1. Crear nuevo pedido\n";
        cout << "2. Consultar pedidos en proceso\n";
        cout << "3. Modificar pedido\n";
        cout << "4. Cancelar pedido\n";
        cout << "5. Historial de pedidos\n";
        cout << "6. Volver al menu principal\n";
        cout << "========================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "\nCreando nuevo pedido...\n";
                system("pause");
                break;
            case 2:
                cout << "\nConsultando pedidos...\n";
                system("pause");
                break;
            case 3:
                cout << "\nModificando pedido...\n";
                system("pause");
                break;
            case 4:
                cout << "\nCancelando pedido...\n";
                system("pause");
                break;
            case 5:
                cout << "\nMostrando historial...\n";
                system("pause");
                break;
            case 6:
                break;
            default:
                cout << "\nSeleccione una opcion valida, por favor.\n";
                system("pause");
        }
    } while(opcion != 6);
}

// NUEVA FUNCION PARA FACTURACION Y ANALISIS
void facturacionYAnalisis() {
    int opcion;
    bool repetir = true;

    do {
        system("cls");
        cout << "\nFACTURACION Y ADMINISTRACION" << endl;
        cout << "-----------------------------------" << endl;
        cout << "1. Generar factura" << endl;
        cout << "2. Consultar estados de pago" << endl;
        cout << "3. Registro de pagos" << endl;
        cout << "4. Ver reportes financieros" << endl;
        cout << "5. Volver al menu principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                generarFactura();
                break;
            case 2:
                consultarEstadoPago();
                break;
            case 3:
                registrarPago();
                break;
            case 4:
                verReportesFinancieros();
                break;
            case 5:
                repetir = false;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }

        if (repetir) {
            cout << "\nPresione enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (repetir);
}

// NUEVA FUNCION PARA CONTROL DE INVENTARIO
void controlInventario() {
    int opcion;
    bool repetir = true;

    do {
        system("cls");
        cout << "CONTROL DE INVENTARIO" << endl;
        cout << "-----------------------------------" << endl;
        cout << "1. Consultar stock disponible" << endl;
        cout << "2. Registrar nueva mercancia" << endl;
        cout << "3. Ajustes de inventario" << endl;
        cout << "4. Ver reportes de existencias" << endl;
        cout << "5. Volver al menu principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                stockDisponible();
                break;
            case 2:
                registroMercancia();
                break;
            case 3:
                ajusteInventario();
                break;
            case 4:
                verReportesExistencia();
                break;
            case 5:
                repetir = false;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }

        if (repetir) {
            cout << "Presione enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (repetir);
}

