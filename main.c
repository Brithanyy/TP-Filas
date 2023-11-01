#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
///ESTRUCTURAS:
typedef struct NodoDoble{
    int dato;
    struct NodoDoble *Anterior;
    struct NodoDoble *Siguiente;
}NodoDoble;

typedef struct Filas{
    NodoDoble *Primero;
    NodoDoble *Ultimo;
}Filas;

///PROTOTIPADO FUNCIONES:

void inicFila(Filas *fila);
NodoDoble *crearNodo(int dato);
void agregarNodoEnFila(Filas *fila, int dato);
int devolverPrimerElementoFila(Filas fila);
void agregarNodoEnFila(Filas *fila, int dato);
void borrarElementoFila(Filas *fila);
void filaVacia(Filas fila);
void mostrarFila(Filas *fila);
NodoDoble *buscarNodoEnFila(Filas *fila, int datoBuscar);
void ingresarDatosAFilaUser(Filas **fila);
void crearArchivoTexto(char nombreArchi[], Filas *fila);
void cargaFilaTravesArchivo(char nombreArchi[], Filas *fila2);
void mostrarArchi(char nombreArchi[]);
void mostrarFilaRecursiva(Filas *fila);
int cantidadNumBuscadoRepetido(Filas *fila, int numBuscado);
void guardarEnArchiCantDeNumerosBuscadoRepetido(char nombreArchi[], Filas *fila, int numBuscado);
void mostrarArchiText(char nombreArchi[]);

int main(){
    Filas *fila;
    inicFila(&fila);
    ///Punto 1
//    ingresarDatosAFilaUser(&fila);

//    ///Punto 2
//    mostrarFila(&fila);

//    ///Punto 3
//    int nroBuscado;
//    printf("\nIngrese en numero a Buscar: ");
//    fflush(stdin);
//    scanf("%i", &nroBuscado);
//    NodoDoble *datoBuscado = buscarNodoEnFila(&fila, nroBuscado);
//    if(datoBuscado == NULL) printf("\nNo encontramos el dato ingresado.\n");
//    else printf("Encontramos es dato. Es --> %i\n", datoBuscado->dato);
    ///Punto 4

    char nombreArchi[] = {"numerosArchivos.bin"};
//    printf("Ingrese el nombre del archivo (que termine con .bin): ");
//    fflush(stdin);
//    gets(nombreArchi);
//    crearArchivoTexto(nombreArchi,&fila);
    printf("\nMostrando archivo: \n");
    mostrarArchi(nombreArchi);
    printf("\n\n");


    ///Punto 5
    Filas fila2;
    inicFila(&fila2);
    cargaFilaTravesArchivo(nombreArchi, &fila2);
    printf("\nMOSTRANDO FILA 2:");
    mostrarFila(&fila2);
    printf("\n\n");

    ///Punto 6
    printf("\nMostrando Fila recursiva\n");
    mostrarFilaRecursiva(&fila2);
    printf("\n\n");

    ///Punto 7
    char nombreArchi7[] = {"guardaArchiBuscados.txt"};
    int numBuscado = 20;
    //guardarEnArchiCantDeNumerosBuscadoRepetido(nombreArchi7,&fila,numBuscado);
    printf("\nMOSTRANDO EL ARCHIVO CON CANT DE NUM BUSCADO: \n");

    ///Punto 8
    mostrarArchiText(nombreArchi7);
    printf("\n\n");
}
///FUNCIONES:

NodoDoble *crearNodo(int dato){
    NodoDoble *aux = (NodoDoble*)malloc(sizeof(NodoDoble));
    aux->dato = dato;
    aux->Siguiente = NULL;
    aux->Anterior = NULL;
    return aux;
}

void inicFila(Filas *fila){
    (*fila).Primero = NULL;
    (*fila).Ultimo = NULL;
}

void agregarNodoEnFila(Filas *fila, int dato){
///Siempre insertamos los datos al final
    NodoDoble *nuevo = crearNodo(dato);
    if((*fila).Primero == NULL){///Si la fila esta vacia lo agrega al principio
            (*fila).Primero = nuevo;
            (*fila).Ultimo = nuevo;
    }else{
        (*fila).Ultimo->Siguiente = nuevo;
        nuevo->Anterior = (*fila).Ultimo;
        (*fila).Ultimo = nuevo;
    }
}

int devolverPrimerElementoFila(Filas fila){
    if (fila.Primero == NULL) {
        printf("\nLa fila esta vacía.\n");
    } else {
        return fila.Primero->dato;
    }
}

void borrarElementoFila(Filas *fila){
///Siempre sacamos eliminamos el primero
    int dato; ///Para devolver el dato eliminado.
    dato = (*fila).Primero->dato; ///Le almacenamos el dato

    NodoDoble *nodoBorrar = (*fila).Primero;///creamos nodo aux para luego eliminarlo

    (*fila).Primero = (*fila).Primero->Siguiente;
    (*fila).Primero->Anterior = NULL;

    free(nodoBorrar); ///Lo borramos
    nodoBorrar = NULL;

    ///Si el primer nodo quedo en nulo al ultimo tambien tiene que quedar en nulo.
    if((*fila).Primero == NULL) (*fila).Ultimo = NULL;

    return dato; ///Borramos el primer nodo y retornamos el dato que tenia.
}

void filaVacia(Filas fila){
    if(fila.Primero == NULL) return 1; ///Esta vacia
    else return 0; ///No esta vacia
}

void mostrarFila(Filas *fila){
    NodoDoble *aux = (*fila).Primero;
    if(aux == NULL) printf("\nLa fila esta vacia\n");
    else{
        printf("\nFila: \n");
        while(aux != NULL){
            printf("- %d -", aux->dato);
            aux = aux->Siguiente;
        }
        printf("\n");
    }
}

NodoDoble *buscarNodoEnFila(Filas *fila, int datoBuscar){
    NodoDoble *aux = (*fila).Primero;
    if(aux == NULL) printf("\nLa fila esta vacia.\n");
    else{
        while(aux != NULL && (aux->dato != datoBuscar)){
            aux = aux->Siguiente;
        }
        return aux;
    }
}

void ingresarDatosAFilaUser(Filas **fila){
    char eleccion = 's';
    int datoIngresar;
    while(eleccion == 's'){
        printf("Ingrese Numero: ");
        fflush(stdin);
        scanf("%i", &datoIngresar);

        agregarNodoEnFila(fila,datoIngresar);

        printf("Pulsa 's' si desea agregar otro dato: ");
        fflush(stdin);
        scanf("%c", &eleccion);
    }
}

void crearArchivoTexto(char nombreArchi[], Filas *fila){
    FILE *punteroArchi = fopen(nombreArchi, "ab");
    int datoFila;
    NodoDoble *aux = (*fila).Primero;
    if(punteroArchi != NULL){
        while(aux != NULL){
            datoFila = aux->dato;
            fwrite(&datoFila,sizeof(int),1,punteroArchi);
            aux = aux->Siguiente;
        }
        fclose(punteroArchi);
    }else printf("\nError al abrir el archivo.\n");
}

void cargaFilaTravesArchivo(char nombreArchi[], Filas *fila2){
    FILE *punteroArchi = fopen(nombreArchi, "rb");
    int datoInsertar;
    if(punteroArchi != NULL){
        while(!feof(punteroArchi)){
            fread(&datoInsertar,sizeof(int),1,punteroArchi);
            if(!feof(punteroArchi)){
            agregarNodoEnFila(fila2,datoInsertar);
            }
        }
        fclose(punteroArchi);
    }else printf("\nError al abrir el archivo CARGAR FILA 2\n");
}

void mostrarArchi(char nombreArchi[]){
    FILE *punteroArchi = fopen(nombreArchi, "rb");
    int dato;
    if(punteroArchi != NULL){
        while(!feof(punteroArchi)){
            fread(&dato,sizeof(int),1,punteroArchi);
            if(!feof(punteroArchi)){
                printf("- %i -", dato);
            }
        }
        fclose(punteroArchi);
    }else printf("\nError al MOSTRAR EL ARCHIVO\n");
}

void mostrarFilaRecursiva(Filas *fila){
    NodoDoble *aux = (*fila).Primero;
    if(aux == NULL) printf("\nLa lista llego a su fin\n");
    else{
        printf("-%i-",(aux->dato));
        mostrarFilaRecursiva (&(aux->Siguiente));
    }
}

int cantidadNumBuscadoRepetido(Filas *fila, int numBuscado){
    int contador = 0;
    NodoDoble *aux = (*fila).Primero;
    while(aux != NULL){
        if(aux->dato == numBuscado) contador = contador +1;
        aux = aux->Siguiente;
    }
    return contador;
}

void guardarEnArchiCantDeNumerosBuscadoRepetido(char nombreArchi[], Filas *fila, int numBuscado){
    int cantidadNumRepetidos = cantidadNumBuscadoRepetido(fila, numBuscado);
    if(cantidadNumRepetidos == 0) printf("\nEl numero no se encuentra no hay nada que guardar\n");
    else{
        FILE *punteroArchi = fopen(nombreArchi, "a");
        if(punteroArchi != NULL){
            fwrite(&cantidadNumRepetidos,sizeof(int),1,punteroArchi);
            fclose(punteroArchi);
        }else printf("\nError al abrir el archivo.\n");
    }
}

void mostrarArchiText(char nombreArchi[]){
    FILE *punteroArchi = fopen(nombreArchi, "r");
    int dato;
    if(punteroArchi != NULL){
        while(!feof(punteroArchi)){
            fread(&dato,sizeof(int),1,punteroArchi);
            if(!feof(punteroArchi)){
                printf("- %i -", dato);
            }
        }
        fclose(punteroArchi);
    }else printf("\nError al MOSTRAR EL ARCHIVO\n");
}
