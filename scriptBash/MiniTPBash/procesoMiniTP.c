#include <stdio.h>
int main()
{
    char nombre[10];
    
    int a = 20;
    int b = 5;
    int resultado;

    printf("Ingrese su nombre: ");
    scanf("%s", nombre);
    printf("Hola, %s\n", nombre);

    resultado = a + b;
    printf("Suma: %d\n", resultado);
    resultado = a - b;
    printf("Resta: %d\n", resultado);
    resultado = a * b;
    printf("Multiplicación: %d\n", resultado);

    return 0;
}
