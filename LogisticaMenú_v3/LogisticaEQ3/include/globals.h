#ifndef GLOBALS_H
#define GLOBALS_H
#pragma once

// Solo declaraciones forward (no incluir los headers completos)
class Pedidos;
class Inventario;
class Envios;
class Facturacion;
class Reportes;
class usuarios;
class bitacora;
class Transportistas;

// Declaraciones extern (sin inicialización)
extern Pedidos gestorPedidos;
extern Inventario gestorInventario;
extern Envios gestorEnvios;
extern Facturacion gestorFacturacion;
extern Reportes gestorReportes;
extern usuarios usuarioRegistrado;
extern bitacora auditoria;
extern std::vector<Transportistas> listaTransportistas;

#endif // GLOBALS_H
