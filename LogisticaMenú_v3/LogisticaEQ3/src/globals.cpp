#include "globals.h"
#include "pedidos.h"
#include "inventario.h"
#include "envios.h"
#include "facturacion.h"
#include "reportes.h"
#include "usuarios.h"
#include "bitacora.h"
#include "transportistas.h"

// Definiciones reales de las variables globales
Pedidos gestorPedidos;
Inventario gestorInventario;
Envios gestorEnvios;
Facturacion gestorFacturacion;
Reportes gestorReportes;
usuarios usuarioRegistrado;
bitacora auditoria;
std::vector<Transportistas> listaTransportistas;
