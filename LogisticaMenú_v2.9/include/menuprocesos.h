#ifndef MENUPROCESOS_H
#define MENUPROCESOS_H
//JENNIFER BARRIOS COORD EQ:3
#include <vector>

// Declaraciones adelantadas de clases.
// Estas se usan para decirle al compilador que existen estas clases,
// sin necesidad de incluir todos sus encabezados aquí.
class Clientes;
class Producto;
class Almacen;
class Proveedor; // Declaración anticipada de la clase Proveedor.
class usuarios;  // Declaración anticipada de la clase usuarios.

/*
 * Clase MenuProcesos
 * Esta clase contiene el menú principal de procesos que interactúa
 * con varias entidades del sistema como clientes, productos, almacenes y proveedores.
 */
class MenuProcesos
{
public:
    /*
     * Método público: mostrar
     * Muestra el menú de procesos y permite realizar operaciones sobre las entidades principales.
     *
     * Parámetros:
     * - clientes: vector que contiene los registros de los clientes.
     * - productos: vector que contiene los registros de los productos.
     * - almacenes: vector que contiene los registros de los almacenes.
     * - proveedores: vector que contiene los registros de los proveedores.
     *
     * Nota: El método está diseñado para trabajar directamente sobre los vectores
     *       recibidos por referencia, permitiendo modificar su contenido.
     */
    void mostrar(std::vector<Clientes>& clientes,
                 std::vector<Producto>& productos,
                 std::vector<Almacen>& almacenes,
                 std::vector<Proveedor>& proveedores);
};

#endif // MENUPROCESOS_H


