//5hw3

#include <stdio.h>
#include <stdlib.h>
#define MAX 100  // Tamaño máximo del árbol
#define VACIO -1  // Constante para indicar un nodo vacío

int arbol[MAX];  // Array que representa el árbol
int hijoIzq(int n);
int hijoDer(int n);
void inicializar(void);
int insertar(int valor);
void muestra(void);
int buscar(int valor);
int maximo(int i);
int minimo(int i);
int eliminar(int valor, int i);
void cargarDesdeArchivo(const char *nombreArchivo); // Declaración de la nueva función

int main(int argc, const char *argv[]) {
    int opc, valor, r;
    inicializar();

    do {
        printf("\n1)Insertar\n2)Mostrar\n3)Buscar\n4)Maximo\n5)Minimo\n6)Eliminar\n7)Cargar desde archivo\n8)Salir\nOpcion:");
        scanf("%i", &opc);

        switch (opc) {
            case 1: 
                printf("\nValor a insertar:");
                scanf("%i", &valor);
                r = insertar(valor);
                if (r >= 0)
                    printf("\nSe insertó en la casilla %i", r);
                else
                    printf("\nNo se insertó");
                break;
            case 2: 
                muestra();
                break;
            case 3:
                printf("\nValor a buscar:");
                scanf("%i", &valor);
                r = buscar(valor);
                if (r < MAX)
                    printf("\nSe encontró en la casilla %i", r);
                else
                    printf("\nNo se encontró");
                break;
            case 4: 
                r = maximo(0);
                printf("\nEl máximo está en %i y es %i", r, arbol[r]);
                break;
            case 5: 
                r = minimo(0);
                printf("\nEl mínimo está en %i y es %i", r, arbol[r]);
                break;
            case 6:
                printf("\nValor a eliminar:");
                scanf("%i", &valor);
                r = eliminar(valor, 0);
                if (r == -1)
                    printf("\nEl valor no se encontró");
                else
                    printf("\nEl valor fue eliminado");
                break;
            case 7:
                cargarDesdeArchivo("datos100.txt");
                break;
        }
    } while (opc != 8);

    return 0;
}

int hijoIzq(int n) {
    return 2 * n + 1;
}

int hijoDer(int n) {
    return 2 * n + 2;
}

void inicializar(void) {
    int i;
    for (i = 0; i < MAX; i++)
        arbol[i] = VACIO;
}

int insertar(int valor) {
    int i = 0;
    while (i < MAX && arbol[i] != VACIO) {
        if (valor <= arbol[i])
            i = hijoIzq(i);
        else
            i = hijoDer(i);
    }
    if (i < MAX)
        arbol[i] = valor;
    else
        i = -1;
    return i;
}

void muestra(void) {
    int i;
    for (i = 0; i < MAX; i++)
        printf("\n%i-%i", i, arbol[i]);
}

int buscar(int valor) {
    int i = 0;
    while (i < MAX && arbol[i] != valor && arbol[i] != VACIO) {
        if (valor < arbol[i])
            i = hijoIzq(i);
        else
            i = hijoDer(i);
    }
    if (i >= MAX || arbol[i] == VACIO)
        i = MAX + 1;
    return i;
}

int maximo(int i) {
    int d = hijoDer(i);
    if (d < MAX && arbol[d] != VACIO)
        return maximo(d);
    else
        return i;
}

int minimo(int i) {
    int iz = hijoIzq(i);
    if (iz < MAX && arbol[iz] != VACIO)
        return minimo(iz);
    else
        return i;
}

int eliminar(int valor, int i) {
    if (i >= MAX || arbol[i] == VACIO) {
        return -1;
    }

    if (valor < arbol[i]) {
        return eliminar(valor, hijoIzq(i));
    } else if (valor > arbol[i]) {
        return eliminar(valor, hijoDer(i));
    } else {
        if ((hijoIzq(i) >= MAX || arbol[hijoIzq(i)] == VACIO) &&
            (hijoDer(i) >= MAX || arbol[hijoDer(i)] == VACIO)) {
            arbol[i] = VACIO;
        } else if (hijoIzq(i) >= MAX || arbol[hijoIzq(i)] == VACIO) {
            arbol[i] = arbol[hijoDer(i)];
            arbol[hijoDer(i)] = VACIO;
        } else if (hijoDer(i) >= MAX || arbol[hijoDer(i)] == VACIO) {
            arbol[i] = arbol[hijoIzq(i)];
            arbol[hijoIzq(i)] = VACIO;
        } else {
            int min = minimo(hijoDer(i));
            arbol[i] = arbol[min];
            return eliminar(arbol[min], min);
        }
        return 0;
    }
}

void cargarDesdeArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    int valor;
    while (fscanf(archivo, "%d", &valor) == 1) {
        int resultado = insertar(valor);
        if (resultado == -1) {
            printf("El árbol está lleno. No se puede insertar el valor %d\n", valor);
            break;
        }
    }

    fclose(archivo);
}
