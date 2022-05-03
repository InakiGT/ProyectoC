#include <stdio.h>
#include <stdlib.h>

// Definición de tipos
typedef struct {
    int dia;
    char mes[50];
    int anio;
}FECHA;

typedef struct {
    char nombre[150];
    char categoria[150];
    int codigo;
    int existencia;
    double precio_compra;
    double precio_venta;
    FECHA caducidad;
}PRODUCTO;

typedef struct {
    PRODUCTO *productos;
    int N;
}BD;


int main(void) {



    return 0;
}