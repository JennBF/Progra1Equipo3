#include "envios.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <stdexcept>

using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// Definici�n del vector de transportistas
const vector<string> Envios::transportistas = {
    "Transportes R�pidos S.A.",
    "Env�os Seguros Ltda.",
    "Log�stica Nacional",
    "Mensajer�a Express",
    "Carga Confiable"
};

// Constructor
Envios::Envios() {
    inicializarRandom();
}

// Destructor
Envios::~Envios() {
    // Limpieza si es necesaria
}

void Envios::inicializarRandom() {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned>(time(nullptr)));
        initialized = true;
    }
}

void Envios::gestionEnvios() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t\t========================================";
        cout << "\n\t\t|       GESTI�N DE ENV�OS             |";
        cout << "\n\t\t========================================";
        cout << "\n\t\t| 1. Generar gu�a de env�o            |";
        cout << "\n\t\t| 2. Asignar transportista            |";
        cout << "\n\t\t| 3. Rastrear env�o                   |";
        cout << "\n\t\t| 4. Confirmar entrega                |";
        cout << "\n\t\t| 5. Cancelar env�o                   |";
        cout << "\n\t\t| 6. Volver al men� principal         |";
        cout << "\n\t\t========================================";
        cout << "\n\t\tSeleccione una opci�n: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\t\tEntrada inv�lida! Por favor ingrese un n�mero.";
            continue;
        }
        cin.ignore();

        switch(opcion) {
            case 1: generarGuia(); break;
            case 2: asignarTransportista(); break;
            case 3: rastrearEnvio(); break;
            case 4: confirmarEntrega(); break;
            case 5: cancelarEnvio(); break;
            case 6: break;
            default:
                cout << "\n\t\tOpci�n inv�lida!";
                cin.get();
        }
    } while(opcion != 6);
}

void Envios::generarGuia() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       GENERAR GU�A DE ENV�O         |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tN�mero de pedido: ";
    getline(cin, numeroPedido);
    if (numeroPedido.empty()) {
        cout << "\n\t\tEl n�mero de pedido no puede estar vac�o!";
        system("pause");
        return;
    }

    cout << "\t\tNombre del destinatario: ";
    getline(cin, destinatario);
    if (destinatario.empty()) {
        cout << "\n\t\tEl nombre del destinatario no puede estar vac�o!";
        system("pause");
        return;
    }

    cout << "\t\tDirecci�n de entrega: ";
    getline(cin, direccion);
    if (direccion.empty()) {
        cout << "\n\t\tLa direcci�n no puede estar vac�a!";
        system("pause");
        return;
    }

    cout << "\t\tCiudad: ";
    getline(cin, ciudad);
    if (ciudad.empty()) {
        cout << "\n\t\tLa ciudad no puede estar vac�a!";
        system("pause");
        return;
    }

    cout << "\t\tTel�fono de contacto: ";
    getline(cin, telefono);
    if (telefono.empty()) {
        cout << "\n\t\tEl tel�fono no puede estar vac�o!";
        system("pause");
        return;
    }

    // Generar n�mero de gu�a autom�tico
    numeroGuia = "G" + to_string(rand() % 9000 + 1000);
    estado = "Pendiente";
    fechaGeneracion = obtenerFechaActual();
    transportista = "Por asignar";

    if (!guardarEnvio()) {
        cout << "\n\t\tError al guardar el env�o!";
        system("pause");
        return;
    }

    cout << "\n\t\t========================================";
    cout << "\n\t\t| �GU�A GENERADA CON �XITO!            |";
    cout << "\n\t\t========================================";
    cout << "\n\t\tN�mero de gu�a: " << numeroGuia;
    cout << "\n\t\tEstado: " << estado;
    cout << "\n\t\tFecha: " << fechaGeneracion;
    cout << "\n\t\t========================================";

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "GUIA-GENERADA-" + numeroGuia);
    system("pause");
}

void Envios::asignarTransportista() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|    ASIGNAR TRANSPORTISTA            |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tN�mero de gu�a: ";
    getline(cin, numeroGuia);
    if (numeroGuia.empty()) {
        cout << "\n\t\tEl n�mero de gu�a no puede estar vac�o!";
        system("pause");
        return;
    }

    if (!existeEnvio(numeroGuia)) {
        cout << "\n\t\t�Gu�a no encontrada!";
        system("pause");
        return;
    }

    // Selecci�n aleatoria de transportista
    transportista = transportistas[rand() % transportistas.size()];

    actualizarEnvio("transportista", transportista);
    actualizarEnvio("estado", "En camino");

    cout << "\n\t\tTransportista asignado: " << transportista;
    cout << "\n\t\tEstado actualizado: En camino";

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "TRANS-ASIGNADO-" + numeroGuia);
    system("pause");
}

void Envios::rastrearEnvio() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|      RASTREO DE ENV�O               |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tN�mero de gu�a: ";
    getline(cin, numeroGuia);
    if (numeroGuia.empty()) {
        cout << "\n\t\tEl n�mero de gu�a no puede estar vac�o!";
        system("pause");
        return;
    }

    ifstream archivo("envios.txt");
    if (!archivo.is_open()) {
        cout << "\n\t\tError al abrir el archivo de env�os!";
        system("pause");
        return;
    }

    bool encontrado = false;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = linea.find("|");
        if (pos == string::npos) continue;

        string guia = linea.substr(0, pos);
        if (guia == numeroGuia) {
            encontrado = true;
            vector<string> datos = split(linea, '|');

            // Verificar que tenemos suficientes datos
            if (datos.size() < 6) {
                cout << "\n\t\tError: Datos de env�o incompletos!";
                break;
            }

            cout << "\n\t\tINFORMACI�N DEL ENV�O";
            cout << "\n\t\t--------------------------------";
            cout << "\n\t\tGu�a: " << datos[0];
            cout << "\n\t\tPedido: " << datos[1];
            cout << "\n\t\tDestinatario: " << datos[2];
            cout << "\n\t\tTransportista: " << datos[3];
            cout << "\n\t\tEstado: " << datos[4];
            cout << "\n\t\tFecha: " << datos[5];
            cout << "\n\t\t--------------------------------";
            cout << "\n\t\tHISTORIAL DE MOVIMIENTOS:";
            cout << "\n\t\t1. " << datos[5] << " - Env�o registrado";

            if (datos[4] == "En camino") {
                cout << "\n\t\t2. " << datos[5] << " - En proceso de empaque";
                cout << "\n\t\t3. " << datos[5] << " - En ruta de entrega";
            }

            if (datos[4] == "Entregado") {
                cout << "\n\t\t4. " << datos[5] << " - Paquete entregado";
            }
            break;
        }
    }
    archivo.close();

    if (!encontrado) {
        cout << "\n\t\t�Gu�a no encontrada!";
    }

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "RASTREO-GUIA-" + numeroGuia);
    system("pause");
}

void Envios::confirmarEntrega() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|     CONFIRMACI�N DE ENTREGA         |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tN�mero de gu�a: ";
    getline(cin, numeroGuia);
    if (numeroGuia.empty()) {
        cout << "\n\t\tEl n�mero de gu�a no puede estar vac�o!";
        system("pause");
        return;
    }

    if (!existeEnvio(numeroGuia)) {
        cout << "\n\t\t�Gu�a no encontrada!";
        system("pause");
        return;
    }

    cout << "\t\tNombre de quien recibe: ";
    getline(cin, receptor);
    if (receptor.empty()) {
        cout << "\n\t\tEl nombre del receptor no puede estar vac�o!";
        system("pause");
        return;
    }

    cout << "\t\tDNI/C�dula de quien recibe: ";
    getline(cin, documentoReceptor);
    if (documentoReceptor.empty()) {
        cout << "\n\t\tEl documento no puede estar vac�o!";
        system("pause");
        return;
    }

    cout << "\t\tObservaciones: ";
    getline(cin, observaciones);

    actualizarEnvio("estado", "Entregado");
    actualizarEnvio("fechaEntrega", obtenerFechaActual());

    cout << "\n\t\t�Entrega confirmada con �xito!";

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "ENTREGA-CONFIRMADA-" + numeroGuia);
    system("pause");
}

void Envios::cancelarEnvio() {
    system("cls");
    cout << "\n\t\t========================================";
    cout << "\n\t\t|       CANCELACI�N DE ENV�O          |";
    cout << "\n\t\t========================================";

    cout << "\n\t\tN�mero de gu�a: ";
    getline(cin, numeroGuia);
    if (numeroGuia.empty()) {
        cout << "\n\t\tEl n�mero de gu�a no puede estar vac�o!";
        system("pause");
        return;
    }

    if (!existeEnvio(numeroGuia)) {
        cout << "\n\t\t�Gu�a no encontrada!";
        system("pause");
        return;
    }

    cout << "\t\tMotivo de cancelaci�n: ";
    string motivo;
    getline(cin, motivo);
    if (motivo.empty()) {
        cout << "\n\t\tDebe especificar un motivo!";
        system("pause");
        return;
    }

    // Eliminar el env�o del archivo
    ifstream archivo("envios.txt");
    if (!archivo.is_open()) {
        cout << "\n\t\tError al abrir el archivo de env�os!";
        system("pause");
        return;
    }

    ofstream temp("temp.txt");
    if (!temp.is_open()) {
        cout << "\n\t\tError al crear archivo temporal!";
        archivo.close();
        system("pause");
        return;
    }

    string linea;
    bool eliminado = false;
    while (getline(archivo, linea)) {
        if (linea.find(numeroGuia) == string::npos) {
            temp << linea << endl;
        } else {
            eliminado = true;
        }
    }

    archivo.close();
    temp.close();

    if (eliminado) {
        remove("envios.txt");
        if (rename("temp.txt", "envios.txt") != 0) {
            cout << "\n\t\tError al actualizar el archivo de env�os!";
            system("pause");
            return;
        }
        cout << "\n\t\t�Env�o cancelado con �xito!";
    } else {
        remove("temp.txt");
        cout << "\n\t\tNo se pudo encontrar el env�o para cancelar!";
    }

    auditoria.insertar(usuarioRegistrado.getNombre(), "300", "ENVIO-CANCELADO-" + numeroGuia + "-MOTIVO:" + motivo);
    system("pause");
}

// Funciones auxiliares
bool Envios::existeEnvio(const string& guia) {
    ifstream archivo("envios.txt");
    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find("|");
        if (pos != string::npos && linea.substr(0, pos) == guia) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void Envios::actualizarEnvio(const string& campo, const string& valor) {
    ifstream archivo("envios.txt");
    if (!archivo.is_open()) {
        cout << "\n\t\tError al abrir el archivo de env�os!";
        return;
    }

    ofstream temp("temp.txt");
    if (!temp.is_open()) {
        cout << "\n\t\tError al crear archivo temporal!";
        archivo.close();
        return;
    }

    string linea;
    bool actualizado = false;
    while (getline(archivo, linea)) {
        size_t pos = linea.find("|");
        if (pos != string::npos && linea.substr(0, pos) == numeroGuia) {
            vector<string> datos = split(linea, '|');

            if (campo == "transportista" && datos.size() > 3) datos[3] = valor;
            else if (campo == "estado" && datos.size() > 4) datos[4] = valor;
            else if (campo == "fechaEntrega" && datos.size() > 5) datos[5] = valor;

            // Reconstruir la l�nea
            string nuevaLinea = datos[0];
            for (size_t i = 1; i < datos.size(); i++) {
                nuevaLinea += "|" + datos[i];
            }
            temp << nuevaLinea << endl;
            actualizado = true;
        } else {
            temp << linea << endl;
        }
    }

    archivo.close();
    temp.close();

    if (actualizado) {
        remove("envios.txt");
        rename("temp.txt", "envios.txt");
    } else {
        remove("temp.txt");
    }
}

bool Envios::guardarEnvio() {
    ofstream archivo("envios.txt", ios::app);
    if (!archivo.is_open()) {
        return false;
    }

    archivo << numeroGuia << "|" << numeroPedido << "|" << destinatario << "|"
            << transportista << "|" << estado << "|" << fechaGeneracion << "|"
            << direccion << "|" << ciudad << "|" << telefono << endl;

    archivo.close();
    return true;
}

vector<string> Envios::split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string Envios::obtenerFechaActual() {
    time_t now = time(0);
    if (now == -1) {
        return "Fecha desconocida";
    }

    tm* ltm = localtime(&now);
    if (!ltm) {
        return "Fecha desconocida";
    }

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    return string(buffer);
}
