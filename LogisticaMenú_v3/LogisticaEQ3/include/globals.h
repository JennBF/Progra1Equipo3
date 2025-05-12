#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>

#include "usuarios.h"
#include "bitacora.h"
#include "reportes.h"
#include "envios.h"
#include "facturacion.h"
#include "transportistas.h"
#include "pedidos.h"
#include "inventario.h"

// Declaraciones extern (sin definición aquí)
extern Pedidos gestorPedidos;
extern Inventario gestorInventario;
extern Envios gestorEnvios;
extern Facturacion gestorFacturacion;
extern Reportes gestorReportes;
extern usuarios usuarioRegistrado;
extern bitacora auditoria;
extern std::vector<Transportistas> listaTransportistas;

#endif // GLOBALS_H
