// Angoly Araujo Mayo 2025 9959-24-17623

#ifndef FACTURACION_H
#define FACTURACION_H

#include <string>
#include <vector>
#include "clientes.h"
#include "pedidos.h"

using namespace std;

// Estructura que representa una factura
struct Factura {
    int idFactura;        // Identificador único de la factura (numérico)
    string idCliente;     // Identificador del cliente asociado a la factura (string)
    string idPedido;      // Identificador del pedido asociado a la factura (string)
    double monto;         // Monto total de la factura
    bool pagada;          // Estado de pago de la factura (true = pagada, false = pendiente)
    char cliente[50];     // Nombre del cliente (máximo 50 caracteres)
};

// Clase que gestiona las operaciones relacionadas con la facturación
class Facturacion {
public:
    // Crea una nueva factura y la guarda en el archivo
    static void crearFactura();

    // Muestra todas las facturas almacenadas
    static void mostrarFacturas();

    // Permite modificar una factura existente
    static void modificarFactura();

    // Elimina una factura específica del archivo
    static void eliminarFactura();

    // Muestra el menú principal de opciones de facturación
    static void mostrarMenuFacturacion();

private:
    // Genera un ID único para una nueva factura
    static int generarIdFactura();

    // Guarda una factura en el archivo correspondiente
    static void guardarEnArchivo(const Factura& factura);

    // Carga una factura desde archivo binario
    static Factura cargarDesdeArchivo(ifstream& archivo);

    // Registra una acción en la bitácora
    static void registrarBitacora(const Factura& factura,
                                const string& accion,
                                const string& usuario);
};

#endif // FACTURACION_H
