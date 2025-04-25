#include <stdio.h>
#include <string.h>
#include "cola.h"
Cola *cola; // Cola de prueba

Cola *cola;
// --- Prototipos de funciones ---
void D(Cola *cola);
void Asig(Cola *cola);
void opAsig(Cola *cola);
void expresionArit(Cola *cola);

// --- Declaración ---
void D(Cola *cola) {
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
        opAsig(cola); // Verificar operador de asignación
        expresionArit(cola);
        if (frente(cola) == ';') {
            desencolar(cola);
            printf("Asignación válida.\n");
        } else {
            printf("Error: se esperaba ';' al final de la asignación.\n");
        }
    } else {
        printf("Error: se esperaba identificador en la asignación.\n");
    }
}

void opAsig(Cola *cola) {
    if (frente(cola) == '#' || frente(cola) == ':' || 
        frente(cola) == '$' || frente(cola) == ',' || 
        frente(cola) == '?' || frente(cola) == ':' || 
        frente(cola) == '^' || frente(cola) == '@' || 
        frente(cola) == '<' || frente(cola) == '>' ) {
        desencolar(cola);
    } else {
        printf("ERROR. No hay operador de asignacion\n");
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

// Proyección 23: <//Sent> ---> <Asig>
void Sent23() {
   // Asig();  // Procesar asignación
}

// Proyección 24: <//Sent> ---> <doW>
void doW(Cola *cola) {
    if (frente(cola) == 'd') {
        desencolar(cola);
        ////Sent(cola);
        if (frente(cola) == 'w') {
            desencolar(cola);
            if (frente(cola) == '(') {
                desencolar(cola);
                if (frente(cola) == ')') {
                    desencolar(cola);
                    if (frente(cola) == ';') {
                        desencolar(cola);
                    } else {
                        printf("Error: se esperaba ';' después de do-while\n");
                    }
                } else {
                    printf("Error: se esperaba ')' en condición de while\n");
                }
            } else {
                printf("Error: se esperaba '(' en condición de while\n");
            }
        } else {
            printf("Error: se esperaba 'while' después del cuerpo do\n");
        }
    } else {
        printf("Error: se esperaba 'do'\n");
    }
}

// Proyección 25: <//Sent> ---> <IF>
void IF(Cola *cola) {
    if (frente(cola) == 'i') {
        desencolar(cola);
        if (frente(cola) == '(') {
            desencolar(cola);
            if (frente(cola) == ')') {
                desencolar(cola);
                //Sent(cola);
                if (frente(cola) == 'e') {
                    desencolar(cola);
                    //Sent(cola);
                }
            } else {
                printf("Error: se esperaba ')' en la sentencia if\n");
            }
        } else {
            printf("Error: se esperaba '(' en la sentencia if\n");
        }
    } else {
        printf("Error: se esperaba 'if'\n");
    }
}

// Proyección 26: <//Sent> ---> <Switch>
void Switch(Cola *cola) {
    if (frente(cola) == 'k') {
        desencolar(cola);
        if (frente(cola) == '(') {
            desencolar(cola);
            if (frente(cola) == 'a' || frente(cola) == 'n') {
                desencolar(cola);
                if (frente(cola) == ')') {
                    desencolar(cola);
                    if (frente(cola) == '{') {
                        desencolar(cola);
                        while (frente(cola) == 'z') {
                            desencolar(cola);
                            if (frente(cola) == ':') {
                                desencolar(cola);
                                //Sent(cola);
                            } else {
                                printf("Error: se esperaba ':' en CASE\n");
                                break;
                            }
                        }
                        if (frente(cola) == '}') {
                            desencolar(cola);
                        } else {
                            printf("Error: se esperaba '}' para cerrar switch\n");
                        }
                    } else {
                        printf("Error: se esperaba '{' después del switch\n");
                    }
                } else {
                    printf("Error: se esperaba ')' en switch\n");
                }
            } else {
                printf("Error: se esperaba una expresión en switch()\n");
            }
        } else {
            printf("Error: se esperaba '(' en switch\n");
        }
    } else {
        printf("Error: se esperaba 'switch'\n");
    }
}

// Función principal para pruebas
int main() {
    cola = crearCola();

    // Prueba 1: IF () c. ELSE b.
    printf("\n--- Prueba IF ---\n");
    encolar(cola, 'i'); // if
    encolar(cola, '(');
    encolar(cola, ')');
    encolar(cola, 'c');
    encolar(cola, '.');
    encolar(cola, 'e'); // else
    encolar(cola, 'b');
    encolar(cola, '.');
    IF(cola);

    // Prueba 2: DO c. WHILE ();;
    printf("\n--- Prueba DO-WHILE ---\n");
    encolar(cola, 'd');
    encolar(cola, 'c');
    encolar(cola, '.');
    encolar(cola, 'w');
    encolar(cola, '(');
    encolar(cola, ')');
    encolar(cola, ';');
    doW(cola);

    // Prueba 3: SWITCH(a){ CASE : b. }
    printf("\n--- Prueba SWITCH ---\n");
    encolar(cola, 'k');
    encolar(cola, '(');
    encolar(cola, 'a');
    encolar(cola, ')');
    encolar(cola, '{');
    encolar(cola, 'z');
    encolar(cola, ':');
    encolar(cola, 'b');
    encolar(cola, '.');
    encolar(cola, '}');
    Switch(cola);

    destruirCola(cola);
    return 0;
}
