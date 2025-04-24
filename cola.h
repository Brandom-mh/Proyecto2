#ifndef COLA_H
#define COLA_H

#include <stdbool.h>

// Estructura para los nodos de la cola
typedef struct Nodo {
    char dato;
    struct Nodo* siguiente;
} Nodo;

// Estructura para la cola
typedef struct Cola {
    Nodo* frente;
    Nodo* final;
    int tamano;
} Cola;

// Funciones para manejar la cola
Cola* crearCola();                // Crear una nueva cola
bool estaVacia(Cola* cola);       // Verificar si la cola está vacía
void encolar(Cola* cola, char dato); // Encolar un caracter
char desencolar(Cola* cola);      // Desencolar un caracter
char frente(Cola* cola);          // Ver el caracter al frente sin desencolar
int tamano(Cola* cola);           // Obtener el tamaño de la cola
void destruirCola(Cola* cola);    // Liberar la memoria de la cola
void mostrarCola(Cola* cola);     // Mostrar el contenido de la cola
void imprimirColaEnArchivo(Cola* cola, FILE* archivo); // Imprimir la cola en un archivo

#endif // COLA_H