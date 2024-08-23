//5hw3

#include <stdio.h>
#define MAX 10
#define VACIO -1


int arbol[MAX];

int hijoIzq(int n);
int hijoDer(int n);
void inicializar(void);
int insertar(int valor);
void muestra(void);
int buscar(int valor);
int maximo(int i);

int main(int argc, const char * argv[]) {
    int opc,valor,r;
    inicializar();
    do{
        printf("\n1)Insertar\n2)Mostrar\n3)Buscar\n4)Maximo\n6)Salir\nOpcion:");
        scanf("%i",&opc);
        switch(opc)
        {
            case 1: printf("\nValor a insertar:");
                scanf("%i", & valor);
                r = insertar(valor);
                if (r>=0)
                    printf("\nSe inserto en la casilla %i",r);
                else
                    printf("\nNo se inserto");
                break;
            case 2: muestra(); break;
            case 3:printf("\nValor a buscar:");
                scanf("%i", & valor);
                r = buscar(valor);
                if (r<MAX)
                    printf("\nSe encontró en la casilla %i",r);
                else
                    printf("\nNo se encontró");
                break;
            case 4: r = maximo(0);
                printf("\nEl maximo esta en %i y es %i",r,arbol[r]);
                break;
        }
    }while(opc!=6);
    
    
    return 0;
}
int hijoIzq(int n)
{
    return 2*n +1;
}
int hijoDer(int n)
{
    return 2*n +2;
}
void inicializar(void)
{
    int i;
    for(i=0;i<MAX;i++)
        arbol[i]=VACIO;
}
int insertar(int valor)
{
    int i=0;
    
    while(i<MAX && arbol[i]!=VACIO)
    {
        if(valor <= arbol[i])
            i = hijoIzq(i);
        else
            i = hijoDer(i);
    }
    if(i<MAX)
        arbol[i]=valor;
    else
        i = -1;
    return i;
   
}
void muestra(void)
{
    int i;
    for(i=0;i<MAX;i++)
        printf("\n%i-%i",i,arbol[i]);
}
int buscar(int valor)
{
    int i=0;
    while(i<MAX && arbol[i]!=valor && arbol[i]!=VACIO)
    {
        if(valor < arbol[i])
            i = hijoIzq(i);
        else
            i = hijoDer(i);
    }
    if(arbol[i]==VACIO)
        i =MAX+1;
    return i;
}

int maximo(int i)
{
    int d,r;
    d = hijoDer(i);
    if(d<MAX && arbol[d]!=VACIO)
        r=maximo(d);
    else
        r = i;
    return r;
        
}
