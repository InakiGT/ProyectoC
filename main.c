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

void prueba() {
    for (int i = 0; i < BD.N; i++) {
        printf("%s\n", BD.productos[i].nombre);
    }
}

// Funciones auxiliares
void showData(int n, PRODUCTO producto) {
    printf("-----PRODUCTO-%i:\n", n);
    printf("%s\n", producto.nombre );
    printf("%s\n", producto.categoria);
    printf("%i\n", producto.codigo);
    printf("%i\n", producto.existencia);
    printf("%lf\n", producto.precio_compra);
    printf("%lf\n", producto.precio_venta);
    printf("---CADUCIDAD\n");
    printf("%i\n", producto.caducidad.dia);
    printf("%s\n", producto.caducidad.mes);
    printf("%i\n", producto.caducidad.anio);
}

void showAllData(int n, PRODUCTO data[]) {
    for(int i = 0; i < n; i++) {
        showData(i+1, data[i]);
    }
}

// Trabajando con archivos binarios
void readBinFile() {
	FILE *file;
	file = fopen("Data.bin", "r+b");

	fread(&BD.N, sizeof(int), 1, file);
	BD.productos = malloc(sizeof(PRODUCTO)*BD.N);
	fread(BD.productos, sizeof(PRODUCTO), BD.N, file);
	fclose(file);
}

void saveBinFile() {

}

// CRUD
void addProduct(PRODUCTO product) {
    PRODUCTO *tmp;
    BD.N++;
    tmp = realloc(BD.productos, sizeof(PRODUCTO)*BD.N);
    BD.productos = tmp;
    BD.productos[BD.N-1] = product;
}

// TODO: Mejorar
void deleteProduct(int id) {
    PRODUCTO *newData;
    newData = malloc(sizeof(PRODUCTO)*BD.N-1);
    int aux = 0;
    for(int i = 0; i < BD.N; i++) {
        if(id != BD.productos[i].codigo) {
            newData[aux] = BD.productos[i];
            aux++;
        }
    }
    BD.N--;
    BD.productos = realloc(BD.productos, BD.N * sizeof(PRODUCTO));
    BD.productos = newData;
}

void searchProductById(int id) {
    for(int i = 0; i < BD.N; i++) {
        if(id == BD.productos[i].codigo) {
            showData(i+1, BD.productos[i]);
            break;
        }
    }
}

void searchProductByName(char name[150]) {
    for(int i = 0; i < BD.N; i++) {
        if(strcmp(name, BD.productos[i].nombre) == 0) {
            showData(i+1, BD.productos[i]);
            break;
        }
    }
}

// TODO: 2 functions
int orderExpiration(const void *a, const void *b) {
    PRODUCTO *producto1 = (PRODUCTO*)a;
    PRODUCTO *producto2 = (PRODUCTO*)b;

    int date1 = (producto1->caducidad.anio * 365) + (producto1->caducidad.dia);
    int date2 = (producto1->caducidad.anio * 365) + (producto1->caducidad.dia);
    
    if(date1 < date2) {
        return 1;
    } else if(date1 > date2) {
        return -1;
    } else {
        return 0;
    }
}

int orderExistence(const void *a, const void *b) {
    PRODUCTO *producto1 = (PRODUCTO*)a;
    PRODUCTO *producto2 = (PRODUCTO*)b;

    if(producto1->existencia < producto2->existencia) {
        return 1;
    } else if(producto1->existencia > producto2->existencia) {
        return -1;
    } else {
        return 0;
    }
}

// TODO: Ordenamiento
void sortByExpiration() {
    qsort(BD.productos, BD.N, sizeof(PRODUCTO), *orderExpiration);
}

void sortByExistence() {
    qsort(BD.productos, BD.N, sizeof(PRODUCTO), *orderExistence);
    showAllData(BD.N, BD.productos);
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

int main() {
    readBinFile();
    FECHA fecha = createADate(20, "Agosto", 2020);
    PRODUCTO producto = createAProduct("Seven-up", "bebidas", 2139013, 10, 10.00, 12.00, fecha);
    addProduct(producto);
    sortByExistence();

    return 0;
}