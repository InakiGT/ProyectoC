#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct {
    PRODUCTO *productos;
    int N;
}BD;

// Leer Datos de la DB
void readBinFile() {
	FILE *file;
	file = fopen("Data.bin", "r+b");

	fread(&BD.N, sizeof(int), 1, file); 
	BD.productos = malloc(sizeof(PRODUCTO)*BD.N);
	fread(BD.productos, sizeof(PRODUCTO), BD.N, file);
	fclose(file);
}

// CRUD
void addProduct(PRODUCTO product) {
    PRODUCTO *tmp;
    BD.N++;
    tmp = realloc(BD.productos, sizeof(PRODUCTO)*BD.N);
    BD.productos = tmp;
    BD.productos[BD.N-1] = product;
}

void deleteProduct(int id) {

}

// Crear una instancia de los structs
PRODUCTO createAProduct(char n[150], char cat[150], int cod, int e, double pc, double pv, FECHA date) {
    PRODUCTO product = { "", "", cod, e, pc, pv, date.dia, "", date.anio };
    strcpy(product.nombre, n);
    strcpy(product.categoria, cat);
    strcpy(product.caducidad.mes, date.mes);
    return product;
}

FECHA createADate(int day, char month[50], int year) {
    FECHA date = { day, "", year };
    strcpy(date.mes, month);
    return date;
}

int main(void) {

    // FECHA fecha = createADate(20, "Agosto", 2020);
    // PRODUCTO producto = createAProduct("Coca", "bebidas", 2139013, 10, 10.00, 12.00, fecha);
    // printf("%i %s %i", producto.existencia, producto.nombre, producto.codigo);


    return 0;
}