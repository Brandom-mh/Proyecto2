#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cola.h"

// Función que crea una nueva cola
Cola* crearCola() {
    // Asigna memoria para la estructura Cola
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    // Inicializa los punteros a NULL (cola vacía)
    cola->frente = NULL;
    cola->final = NULL;
    // Inicializa el tamaño a 0
    cola->tamano = 0;
    return cola;  // Retorna el puntero a la cola creada
}

// Función que verifica si la cola está vacía
bool estaVacia(Cola* cola) {
    // La cola está vacía si el frente es NULL
    return cola->frente == NULL;
}

// Función que agrega (encola) un elemento al final de la cola
void encolar(Cola* cola, char dato) {
    // Crea un nuevo nodo para almacenar el dato
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;      // Asigna el dato al nuevo nodo
    nuevoNodo->siguiente = NULL; // El siguiente siempre será NULL (será el último)
    
    // Si la cola está vacía, el nuevo nodo será el frente
    if (estaVacia(cola)) {
        cola->frente = nuevoNodo;
    } else {
        // Si no está vacía, enlaza el nuevo nodo al final
        cola->final->siguiente = nuevoNodo;
    }
    
    // Actualiza el final de la cola al nuevo nodo
    cola->final = nuevoNodo;
    cola->tamano++;  // Incrementa el tamaño de la cola
}

// Función que elimina (desencola) el elemento del frente de la cola
char desencolar(Cola* cola) {
    // Verifica si la cola está vacía
    if (estaVacia(cola)) {
        printf("Error: Cola vacía\n"); //Imprime mensaje de error
        return '\0'; // Retorna carácter nulo como indicador de error
    }
    
    // Guarda el nodo frontal en una variable temporal
    Nodo* temp = cola->frente;
    char dato = temp->dato;  // Extrae el dato del frente
    
    // Mueve el frente al siguiente nodo
    cola->frente = temp->siguiente;
    
    // Si después de desencolar la cola queda vacía
    if (cola->frente == NULL) {
        cola->final = NULL;  // Actualiza el final a NULL
    }
    
    free(temp);          // Libera la memoria del nodo eliminado
    cola->tamano--;      // Decrementa el tamaño de la cola
    mostrarCola(cola);   // Muestra el estado actual de la cola 
    return dato;         // Retorna el dato extraído
}

// Función que obtiene el dato en el frente sin desencolarlo
char frente(Cola* cola) {
    // Verifica si la cola está vacía
    if (estaVacia(cola)) {
        printf("Error: Cola vacía\n"); // Imprime mensaje de error
        return '\0'; // Retorna carácter nulo como indicador de error
    }
    return cola->frente->dato;  // Retorna el dato del frente
}

// Función que obtiene el tamaño actual de la cola
int tamano(Cola* cola) {
    return cola->tamano;  // Retorna el valor del tamaño
}

// Función que libera toda la memoria utilizada por la cola
void destruirCola(Cola* cola) {
    // Mientras la cola no este vacía desencola todos los elementos restantes
    while (!estaVacia(cola)) {
        desencolar(cola);
    }
    free(cola);  // Libera la estructura de la cola
}

// Función que muestra el contenido de la cola en la consola
void mostrarCola(Cola* cola) {
    // Verifica si la cola está vacía
    if (estaVacia(cola)) {
        printf("Cola vacía\n"); // Imprime mensaje de cola vacía
        return;
    }
    
    printf("Contenido de la cola (frente primero): ");
    Nodo* actual = cola->frente;
    // Recorre la cola desde el frente hasta el final
    while (actual != NULL) {
        printf("%c", actual->dato);  // Imprime cada carácter
        actual = actual->siguiente;   // Avanza al siguiente nodo
    }
    printf("\n");  // Imprime un salto de línea 
}

// Función que imprime el contenido de la cola en un archivo
void imprimirColaEnArchivo(Cola* cola, FILE* archivo) {
    // Verifica que la cola y el archivo no sean NULL
    if (cola == NULL || archivo == NULL) {
        fprintf(stderr, "Error: Cola o archivo no válidos\n"); //Si alguna de las variables es NULL imprime mensaje de error
        return;
    }

    Nodo* actual = cola->frente;
    fprintf(archivo, "Contenido de la cola: ["); // Abre el formato de impresión
    
    // Recorre la cola escribiendo cada dato en el archivo
    while (actual != NULL) {
        fprintf(archivo, "%c", actual->dato);
        actual = actual->siguiente;
    }
    
    fprintf(archivo, "]\n");  // Cierra el formato
