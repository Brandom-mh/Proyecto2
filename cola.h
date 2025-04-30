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
bool estaVacia(Cola* cola);       // Verifica si la cola está vacía
void encolar(Cola* cola, char dato); // Encola un carácter
char desencolar(Cola* cola);      // Desencola un carácter
char frente(Cola* cola);          // Ver el carácter al frente sin desencolar
int tamano(Cola* cola);           // Obtiene el tamaño de la cola
void destruirCola(Cola* cola);    // Libera la memoria de la cola
void mostrarCola(Cola* cola);     // Muestra el contenido de la cola
void imprimirColaEnArchivo(Cola* cola, FILE* archivo); // Imprime la cola en un archivo

#endif // COLA_H
