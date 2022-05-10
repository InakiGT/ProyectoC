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

typedef struct {
    PRODUCTO *productos;
    int N;
}BD;


// Funciones auxiliares
BD BDConstructor() {
    BD bd;
    return bd;
}

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
void readBinFile(BD *bd) {
	FILE *file;
	file = fopen("Data.bin", "r+b");

	fread(&bd->N, sizeof(int), 1, file);
	bd->productos = malloc(sizeof(PRODUCTO) * bd->N);
	fread(bd->productos, sizeof(PRODUCTO), bd->N, file);
	fclose(file);
}

void saveBinFile(BD *bd) {
    FILE *file;
	file = fopen("Data.bin", "w+b");

	fwrite(&bd->N, sizeof(int), 1, file);
	fwrite(bd->productos, sizeof(PRODUCTO), bd->N, file);
	fclose(file);
}

// CRUD
void transderData(PRODUCTO *newData, PRODUCTO *oldData) {
    strcpy(newData->nombre, oldData->nombre);
    strcpy(newData->categoria, oldData->categoria);
    newData->codigo = oldData->codigo;
    newData->existencia = oldData->existencia;
    newData->precio_compra = oldData->precio_compra;
    newData->precio_venta = oldData->precio_venta;
    newData->caducidad.dia = oldData->caducidad.dia;
    strcpy(newData->caducidad.mes, oldData->caducidad.mes);
    newData->caducidad.anio = oldData->caducidad.anio;
}

void addProduct(BD *bd, PRODUCTO product) {
    PRODUCTO *tmp;
    bd->N++;
    tmp = realloc(bd->productos, sizeof(PRODUCTO)*bd->N);
    bd->productos = tmp;
    bd->productos[bd->N-1] = product;
}

void deleteProduct(BD *bd, int id) {
    PRODUCTO *newData;
    newData = malloc(sizeof(PRODUCTO)*(bd->N-1));
    int aux = 0;
    for(int i = 0; i < bd->N; i++) {
        if(id != bd->productos[i].codigo) {
            transderData(&newData[aux], &bd->productos[i]);
            // newData[aux] = bd->productos[i];
            aux++;
        }
    }
    bd->N--;
    bd->productos = realloc(bd->productos, bd->N * sizeof(PRODUCTO));
    bd->productos = newData;
}

void searchProductById(BD *bd, int id) {
    for(int i = 0; i < bd->N; i++) {
        if(id == bd->productos[i].codigo) {
            showData(i+1, bd->productos[i]);
            break;
        }
    }
}

void searchProductByName(BD *bd, char name[150]) {
    for(int i = 0; i < bd->N; i++) {
        if(strcmp(name, bd->productos[i].nombre) == 0) {
            showData(i+1, bd->productos[i]);
            break;
        }
    }
}

// Funciones de ordenamiento
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

// Ordenamiento
void sortByExpiration(BD *bd) {
    qsort(bd->productos, bd->N, sizeof(PRODUCTO), *orderExpiration);
    showAllData(bd->N, bd->productos);
}

void sortByExistence(BD *bd) {
    qsort(bd->productos, bd->N, sizeof(PRODUCTO), *orderExistence);
    showAllData(bd->N, bd->productos);
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
    BD bd = BDConstructor();
    readBinFile(&bd);
    FECHA fecha = createADate(20, "Agosto", 2020);
    PRODUCTO producto = createAProduct("Seven-up", "bebidas", 2139013, 10, 10.00, 12.00, fecha);
    addProduct(&bd, producto);
    deleteProduct(&bd, 2139013);
    sortByExistence(&bd);

    return 0;
}