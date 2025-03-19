#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100

typedef struct {
    int codigo;
    char nombre[50];
    int cantidad;
    int precioUnitario;
} Producto;
Producto inventario[MAX_PRODUCTOS];
int numProductos = 0;

// Función para registrar un nuevo producto
void registrarProducto() {
    if (numProductos < MAX_PRODUCTOS) {
        Producto nuevoProducto;
        printf("Ingrese el código del producto: ");
        scanf("%d", &nuevoProducto.codigo);
        printf("Ingrese el nombre del producto: ");
        scanf(" %49[^\n]", nuevoProducto.nombre); // Lee hasta 49 caracteres o un salto de línea
        printf("Ingrese la cantidad inicial: ");
        scanf("%d", &nuevoProducto.cantidad);
        printf("Ingrese el precio por unidad: ");
        scanf("%d", &nuevoProducto.precioUnitario);

        inventario[numProductos++] = nuevoProducto;
        printf("Producto registrado con éxito.\n");
    } else {
        printf("Inventario lleno. No se pueden agregar más productos.\n");
    }
}

// Función para mostrar todos los productos en el inventario
void mostrarInventario() {
    if (numProductos > 0) {
        printf("\n--- Inventario ---\n");
        printf("%-10s %-30s %-10s %-15s %-15s\n", "Código", "Nombre", "Cantidad", "Precio/Unidad", "Costo Total");
        for (int i = 0; i < numProductos; i++) {
            int costoTotal = inventario[i].cantidad * inventario[i].precioUnitario;
            printf("%-10d %-30s %-10d %-15d %-15d\n", inventario[i].codigo, inventario[i].nombre, inventario[i].cantidad, inventario[i].precioUnitario, costoTotal);
        }
    } else {
        printf("El inventario está vacío.\n");
    }
}

// Función para actualizar la cantidad de un producto tras una compra
void actualizarCantidad() {
    int codigoCompra, cantidadCompra;
    printf("Ingrese el código del producto comprado: ");
    scanf("%d", &codigoCompra);
    printf("Ingrese la cantidad comprada: ");
    scanf("%d", &cantidadCompra);

    for (int i = 0; i < numProductos; i++) {
        if (inventario[i].codigo == codigoCompra) {
            if (inventario[i].cantidad >= cantidadCompra) {
                inventario[i].cantidad -= cantidadCompra;
                printf("Compra registrada. Cantidad actualizada.\n");
                return;
            } else {
                printf("No hay suficiente stock para la compra.\n");
                return;
            }
        }
    }
    printf("Producto no encontrado en el inventario.\n");
}

// Función para calcular el costo total del inventario
int calcularCostoTotalInventario() {
    int costoTotalInventario = 0;
    for (int i = 0; i < numProductos; i++) {
        costoTotalInventario += inventario[i].cantidad * inventario[i].precioUnitario;
    }
    return costoTotalInventario;
}

// Función para eliminar un producto del inventario
void eliminarProducto() {
    int codigoEliminar;
    printf("Ingrese el código del producto a eliminar: ");
    scanf("%d", &codigoEliminar);

    for (int i = 0; i < numProductos; i++) {
        if (inventario[i].codigo == codigoEliminar) {
            if (inventario[i].cantidad == 0) {
                // Mueve los productos restantes una posición hacia atrás
                for (int j = i; j < numProductos - 1; j++) {
                    inventario[j] = inventario[j + 1];
                }
                numProductos--;
                printf("Producto eliminado del inventario.\n");
                return;
            } else {
                printf("No se puede eliminar el producto. La cantidad debe ser cero.\n");
                return;
            }
        }
    }
    printf("Producto no encontrado en el inventario.\n");
}

int main() {
    int opcion;
    do {
        printf("\n--- Menú ---\n");
        printf("1. Registrar producto\n");
        printf("2. Mostrar inventario\n");
        printf("3. Actualizar cantidad (compra)\n");
        printf("4. Calcular costo total inventario\n");
        printf("5. Eliminar producto\n");
        printf("0. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarProducto();
                break;
            case 2:
                mostrarInventario();
                break;
            case 3:
                actualizarCantidad();
                break;
            case 4:
                printf("Costo total del inventario: %d\n", calcularCostoTotalInventario());
                break;
            case 5:
                eliminarProducto();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    return 0;
}