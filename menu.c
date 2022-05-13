#include <stdio.h>
#include "functions.h"

void selectOption(int option, int *repeat) {
    switch (option) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            *repeat = 1;
            break;
        default:
            printf("Opción no válida, favor de seleccionar una del menú de opciones\n");
            break;
    }
}

void showMenu(int *repeat) {

    int option;

    printf("--- Tienda de Abarrotes---\n");
    printf("1.- Listar todos los productos\n");
    printf("2.- Listar todos los productos según su caducidad (Mayor a menor)\n");
    printf("3.- Listar todos los productos según su existencia (Mayor a menor)\n");
    printf("4.- Listar todos los productos\n");
    printf("5.- Buscar un producto mediante código\n");
    printf("6.- Buscar un producto mediante nombre\n");
    printf("7.- Capital invertido\n");
    printf("8.- Ganancia total\n");
    printf("9.- Terminar de ejecutar el programa\n");
    printf("Elija una de las siguientes opciones ingresando su número:");

    scanf("%i", &option);
    selectOption(option, repeat);
}

void menu() {
    int repeat = 0;
    do {
        showMenu(&repeat);
    } while(repeat != 1);
}