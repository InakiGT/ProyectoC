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

struct {
    PRODUCTO *productos;
    int N;
}BD;


void CargarDatos() {
	FILE *file;
	int i;
	char basura[30];

	file = fopen("Data.txt", "r");
	fscanf(file, "%i", &BD.N); 
	BD.productos = malloc(sizeof(PRODUCTO)*BD.N);
	for(int i=0; i < BD.N; i++) {
		fscanf(file, "%s", basura);
		fscanf(file, "%s", BD.productos[i].nombre);
		fscanf(file, "%s", BD.productos[i].categoria);
		fscanf(file, "%i", &BD.productos[i].codigo);
		fscanf(file, "%i", &BD.productos[i].existencia);
		fscanf(file, "%lf", &BD.productos[i].precio_compra);
		fscanf(file, "%lf", &BD.productos[i].precio_venta);
		fscanf(file, "%s", basura);
		fscanf(file, "%i", &BD.productos[i].caducidad.dia);
		fscanf(file, "%s", BD.productos[i].caducidad.mes);
		fscanf(file, "%i", &BD.productos[i].caducidad.anio);
	}
	fclose(file);
}


void DescargarDatos() {
	free(BD.productos);
}

void GuardarEnBinario() {
	FILE *file;
	file = fopen("Data.bin", "w+b");

	fwrite(&BD.N, sizeof(int), 1, file);
	fwrite(BD.productos, sizeof(PRODUCTO), BD.N, file);
	fclose(file);
}

void MuestraRegistros() {
	printf("%d\n", BD.N);
	for(int i=0; i < BD.N; i++) {
		printf("-----PRODUCTO-%i:\n", i+1);
		printf("%s\n", BD.productos[i].nombre );
		printf("%s\n", BD.productos[i].categoria);
		printf("%i\n", BD.productos[i].codigo);
		printf("%i\n", BD.productos[i].existencia);
		printf("%lf\n", BD.productos[i].precio_compra);
		printf("%lf\n", BD.productos[i].precio_venta);
        printf("---CADUCIDAD\n");
		printf("%i\n", BD.productos[i].caducidad.dia);
		printf("%s\n", BD.productos[i].caducidad.mes);
		printf("%i\n", BD.productos[i].caducidad.anio);
    }
}


void CargarDatosBinario() {
	FILE *file;
	file = fopen("Data.bin", "r+b");

	fread(&BD.N, sizeof(int), 1, file); 
	BD.productos = malloc(sizeof(PRODUCTO)*BD.N);
	fread(BD.productos, sizeof(PRODUCTO), BD.N, file);
	fclose(file);
}

void DescargarDatosBinario() {
	free(BD.productos);
}

int main() {
	CargarDatos();
	GuardarEnBinario();
	DescargarDatos(); 
	
	CargarDatosBinario();
	MuestraRegistros();
	DescargarDatosBinario();
}