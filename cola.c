#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cola.h"
// Estructura para los nodos de la cola

// Función para crear una nueva cola
Cola* crearCola() {
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    cola->frente = NULL;
    cola->final = NULL;
    cola->tamano = 0;
    return cola;
}

// Función para verificar si la cola está vacía
bool estaVacia(Cola* cola) {
    return cola->frente == NULL;
}

// Función para encolar un caracter (enqueue)
void encolar(Cola* cola, char dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    
    if (estaVacia(cola)) {
        cola->frente = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
    }
    
    cola->final = nuevoNodo;
    cola->tamano++;
}

// Función para desencolar un caracter (dequeue)
char desencolar(Cola* cola) {
    if (estaVacia(cola)) {
        printf("Error: Cola vacía\n");
        return '\0'; // Caracter nulo como valor de error
    }
    
    Nodo* temp = cola->frente;
    char dato = temp->dato;
    cola->frente = temp->siguiente;
    
    if (cola->frente == NULL) {
        cola->final = NULL;
    }
    
    free(temp);
    cola->tamano--;
    return dato;
}

// Función para ver el caracter al frente sin desencolar
char frente(Cola* cola) {
    if (estaVacia(cola)) {
        printf("Error: Cola vacía\n");
        return '\0'; // Caracter nulo como valor de error
    }
    return cola->frente->dato;
}

// Función para obtener el tamaño de la cola
int tamano(Cola* cola) {
    return cola->tamano;
}

// Función para liberar la memoria de la cola
void destruirCola(Cola* cola) {
    while (!estaVacia(cola)) {
        desencolar(cola);
    }
    free(cola);
}

// Función para mostrar el contenido de la cola
void mostrarCola(Cola* cola) {
    if (estaVacia(cola)) {
        printf("Cola vacía\n");
        return;
    }
    
    printf("Contenido de la cola (frente primero): ");
    Nodo* actual = cola->frente;
    while (actual != NULL) {
        printf("%c", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}