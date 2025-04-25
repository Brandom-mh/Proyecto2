#include <stdio.h>
#include <string.h>
#include "cola.h"
// Proyección: D -> <tipo>a
void D() {
    // Procesar el tipo
    tipo();    
}

// --- Prototipos de funciones ---
void Declaracion(Cola *cola);
void Asig(Cola *cola);
void expresionArit(Cola *cola);

// --- Declaración ---
void Declaracion(Cola *cola) {
    if (frente(cola) == 't') { // 't' = INT (tipo de dato)
        desencolar(cola);
        if (frente(cola) == 'a') { // 'a' = identificador
            desencolar(cola);
            if (frente(cola) == ';') {
                desencolar(cola);
                printf("Declaración válida.\n");
            } else {
                printf("Error: se esperaba ';' al final de la declaración.\n");
            }
        } else {
            printf("Error: se esperaba identificador.\n");
        }
    } else {
        printf("Error: se esperaba tipo de dato.\n");
    }
}

// --- Asignación ---
void Asig(Cola *cola) {
    if (frente(cola) == 'a') { // identificador
        desencolar(cola);
        if (frente(cola) == '=') {
            desencolar(cola);
            expresionArit(cola);
            if (frente(cola) == ';') {
                desencolar(cola);
                printf("Asignación válida.\n");
            } else {
                printf("Error: se esperaba ';' al final de la asignación.\n");
            }
        } else {
            printf("Error: se esperaba '=' en la asignación.\n");
        }
    } else {
        printf("Error: se esperaba identificador en la asignación.\n");
    }
}

// --- Expresión Aritmética ---
void expresionArit(Cola *cola) {
    if (frente(cola) == 'n' || frente(cola) == 'a') {
        desencolar(cola); // número o identificador
        while (frente(cola) == '+' || frente(cola) == '-' || frente(cola) == '*' || frente(cola) == '/' || frente(cola) == '%') {
            desencolar(cola); // operador
            if (frente(cola) == 'n' || frente(cola) == 'a') {
                desencolar(cola); // operando
            } else {
                printf("Error: se esperaba un operando después del operador.\n");
                return;
            }
        }
    } else {
        printf("Error: expresión aritmética inválida.\n");
    }
}

// --- Main de prueba ---
int main() {
    cola = crearCola();

    // --- Declaración ---
    printf("\n--- Prueba Declaración ---\n");
    encolar(cola, 't'); // INT
    encolar(cola, 'a'); // identificador
    encolar(cola, ';');
    Declaracion(cola);

    // --- Asignación ---
    printf("\n--- Prueba Asignación ---\n");
    encolar(cola, 'a'); // identificador
    encolar(cola, '=');
    encolar(cola, 'n'); // número
    encolar(cola, '+');
    encolar(cola, 'n');
    encolar(cola, ';');
    Asig(cola);

    destruirCola(cola);
    return 0;
}