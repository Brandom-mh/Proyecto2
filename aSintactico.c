#include <stdio.h>
#include <string.h>
#include "cola.h"
Cola *cola; // Cola de prueba

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
