//5hw3

#include <stdio.h>
#define MAX 10   // Tamaño máximo del árbol
#define VACIO -1  // Constante para indicar un nodo vacío

int arbol[MAX];  // Array que representa el árbol

int hijoIzq(int n);          // Calcula el índice del hijo izquierdo
int hijoDer(int n);          // Calcula el índice del hijo derecho
void inicializar(void);      // Inicializa el árbol
int insertar(int valor);     // Inserta un valor en el árbol
void muestra(void);          // Muestra el árbol
int buscar(int valor);       // Busca un valor en el árbol
int maximo(int i);           // Encuentra el valor máximo
int minimo(int i);           // Encuentra el valor mínimo
int eliminar(int valor, int i); // Elimina un valor del árbol

int main(int argc, const char *argv[]) {
    int opc, valor, r;
    inicializar();  // Inicializa el árbol

    do {
        // Menú de opciones
        printf("\n1)Insertar\n2)Mostrar\n3)Buscar\n4)Maximo\n5)Minimo\n6)Eliminar\n7)Salir\nOpcion:");
        scanf("%i", &opc);

        switch (opc) {
            case 1: 
                printf("\nValor a insertar:");
                scanf("%i", &valor);
                r = insertar(valor);  // Inserta el valor
                if (r >= 0)
                    printf("\nSe inserto en la casilla %i", r);
                else
                    printf("\nNo se inserto");
                break;
            case 2: 
                muestra();  // Muestra el árbol
                break;
            case 3:
                printf("\nValor a buscar:");
                scanf("%i", &valor);
                r = buscar(valor);  // Busca el valor
                if (r < MAX)
                    printf("\nSe encontró en la casilla %i", r);
                else
                    printf("\nNo se encontró");
                break;
            case 4: 
                r = maximo(0);  // Encuentra el valor máximo
                printf("\nEl maximo esta en %i y es %i", r, arbol[r]);
                break;
            case 5: 
                r = minimo(0);  // Encuentra el valor mínimo
                printf("\nEl minimo esta en %i y es %i", r, arbol[r]);
                break;
            case 6:
                printf("\nValor a eliminar:");
                scanf("%i", &valor);
                r = eliminar(valor, 0);  // Elimina el valor
                if (r == -1)
                    printf("\nEl valor no se encontró");
                else
                    printf("\nEl valor fue eliminado");
                break;
        }
    } while (opc != 7);  // Salir del menú

    return 0;
}

// Calcula el índice del hijo izquierdo
int hijoIzq(int n) {
    return 2 * n + 1;
}

// Calcula el índice del hijo derecho
int hijoDer(int n) {
    return 2 * n + 2;
}

// Inicializa el árbol a vacío
void inicializar(void) {
    int i;
    for (i = 0; i < MAX; i++)
        arbol[i] = VACIO;
}

// Inserta un valor en el árbol
int insertar(int valor) {
    int i = 0;
    // Encuentra la posición adecuada para insertar
    while (i < MAX && arbol[i] != VACIO) {
        if (valor <= arbol[i])
            i = hijoIzq(i);  // Mueve al subárbol izquierdo
        else
            i = hijoDer(i);  // Mueve al subárbol derecho
    }
    if (i < MAX)
        arbol[i] = valor;  // Inserta el valor
    else
        i = -1;  // Árbol lleno, no se pudo insertar
    return i;  // Retorna la posición o -1 si falla
}

// Muestra el árbol
void muestra(void) {
    int i;
    for (i = 0; i < MAX; i++)
        printf("\n%i-%i", i, arbol[i]);
}

// Busca un valor en el árbol
int buscar(int valor) {
    int i = 0;
    // Busca el valor en el árbol
    while (i < MAX && arbol[i] != valor && arbol[i] != VACIO) {
        if (valor < arbol[i])
            i = hijoIzq(i);  // Mueve al subárbol izquierdo
        else
            i = hijoDer(i);  // Mueve al subárbol derecho
    }
    if (i >= MAX || arbol[i] == VACIO)
        i = MAX + 1;  // Valor no encontrado
    return i;  // Retorna la posición o MAX + 1 si no se encontró
}

// Encuentra el valor máximo en el subárbol
int maximo(int i) {
    int d = hijoDer(i);
    if (d < MAX && arbol[d] != VACIO)
        return maximo(d);  // Recurre al hijo derecho
    else
        return i;  // Retorna el índice del máximo
}

// Encuentra el valor mínimo en el subárbol
int minimo(int i) {
    int iz = hijoIzq(i);
    if (iz < MAX && arbol[iz] != VACIO)
        return minimo(iz);  // Recurre al hijo izquierdo
    else
        return i;  // Retorna el índice del mínimo
}

// Elimina un valor del árbol
int eliminar(int valor, int i) {
    if (i >= MAX || arbol[i] == VACIO) {
        return -1;  // No se encuentra en el árbol
    }

    if (valor < arbol[i]) {
        // Recorrer al subárbol izquierdo
        return eliminar(valor, hijoIzq(i));
    } else if (valor > arbol[i]) {
        // Recorrer al subárbol derecho
        return eliminar(valor, hijoDer(i));
    } else {
        // Nodo a eliminar encontrado
        // Caso 1: Nodo hoja (sin hijos)
        if ((hijoIzq(i) >= MAX || arbol[hijoIzq(i)] == VACIO) &&
            (hijoDer(i) >= MAX || arbol[hijoDer(i)] == VACIO)) {
            arbol[i] = VACIO;  // Elimina el nodo
        }
        // Caso 2: Nodo con solo un hijo derecho
        else if (hijoIzq(i) >= MAX || arbol[hijoIzq(i)] == VACIO) {
            arbol[i] = arbol[hijoDer(i)];  // Reemplaza con el hijo derecho
            arbol[hijoDer(i)] = VACIO;  // Vacía el hijo derecho
        }
        // Caso 3: Nodo con solo un hijo izquierdo
        else if (hijoDer(i) >= MAX || arbol[hijoDer(i)] == VACIO) {
            arbol[i] = arbol[hijoIzq(i)];  // Reemplaza con el hijo izquierdo
            arbol[hijoIzq(i)] = VACIO;  // Vacía el hijo izquierdo
        }
        // Caso 4: Nodo con dos hijos
        else {
            // Encuentra el mínimo en el subárbol derecho
            int min = minimo(hijoDer(i));
            arbol[i] = arbol[min];  // Reemplaza valor
            return eliminar(arbol[min], min);  // Elimina nodo reemplazado
        }
        return 0;  // Eliminación exitosa
    }
}
