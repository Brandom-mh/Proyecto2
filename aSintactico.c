#include <stdio.h>
#include <string.h>
#include "cola.h"

Cola *cola; // Cola global de átomos

// Funciones principales
void Sent(Cola *cola);
void listaSent(Cola *cola);
void exprLog(Cola *cola);

// --- IF-ELSE ---
void IF(Cola *cola) {
    if (frente(cola) == 'i') {
        desencolar(cola);
        if (frente(cola) == '(') {
            desencolar(cola);
            exprLog(cola);
            if (frente(cola) == ')') {
                desencolar(cola);
                if (frente(cola) == '{') {
                    desencolar(cola);
                    listaSent(cola);
                    if (frente(cola) == '}') {
                        desencolar(cola);
                        if (frente(cola) == 'e') { // ELSE opcional
                            desencolar(cola);
                            if (frente(cola) == '{') {
                                desencolar(cola);
                                listaSent(cola);
                                if (frente(cola) == '}') {
                                    desencolar(cola);
                                } else {
                                    printf("Error: falta '}' en else\n");
                                }
                            } else {
                                printf("Error: falta '{' después de else\n");
                            }
                        }
                    } else {
                        printf("Error: falta '}' en if\n");
                    }
                } else {
                    printf("Error: falta '{' después de )\n");
                }
            } else {
                printf("Error: falta ')' en if\n");
            }
        } else {
            printf("Error: falta '(' en if\n");
        }
    } else {
        printf("Error: se esperaba 'if'\n");
    }
}

// --- DO-WHILE ---
void doW(Cola *cola) {
    if (frente(cola) == 'd') {
        desencolar(cola);
        if (frente(cola) == '{') {
            desencolar(cola);
            listaSent(cola);
            if (frente(cola) == '}') {
                desencolar(cola);
                if (frente(cola) == 'w') {
                    desencolar(cola);
                    if (frente(cola) == '(') {
                        desencolar(cola);
                        exprLog(cola);
                        if (frente(cola) == ')') {
                            desencolar(cola);
                        } else {
                            printf("Error: falta ')' después de exprLog\n");
                        }
                    } else {
                        printf("Error: falta '(' después de while\n");
                    }
                } else {
                    printf("Error: falta 'while' después de bloque do\n");
                }
            } else {
                printf("Error: falta '}' en do\n");
            }
        } else {
            printf("Error: falta '{' después de do\n");
        }
    } else {
        printf("Error: se esperaba 'do'\n");
    }
}

// --- SWITCH-CASE ---
void Switch(Cola *cola) {
    if (frente(cola) == 'k') {
        desencolar(cola);
        if (frente(cola) == '(') {
            desencolar(cola);
            if (frente(cola) == 'a') {
                desencolar(cola);
                if (frente(cola) == ')') {
                    desencolar(cola);
                    if (frente(cola) == '{') {
                        desencolar(cola);
                        listaCase(cola);
                        if (frente(cola) == '}') {
                            desencolar(cola);
                        } else {
                            printf("Error: falta '}' al final del switch\n");
                        }
                    } else {
                        printf("Error: falta '{' después de switch\n");
                    }
                } else {
                    printf("Error: falta ')' después de identificador\n");
                }
            } else {
                printf("Error: falta identificador en switch\n");
            }
        } else {
            printf("Error: falta '(' después de switch\n");
        }
    } else {
        printf("Error: se esperaba 'switch'\n");
    }
}

// --- LISTA CASES ---
void listaCase(Cola *cola) {
    while (frente(cola) == 'z') { // mientras haya CASE
        caseSwitch(cola);
    }
}

// --- CASE individual ---
void caseSwitch(Cola *cola) {
    if (frente(cola) == 'z') {
        desencolar(cola);
        if (frente(cola) == 'n') { // número entero
            desencolar(cola);
            listaSent(cola);
            if (frente(cola) == 'b') { // BREAK
                desencolar(cola);
                if (frente(cola) == '.') {
                    desencolar(cola);
                } else {
                    printf("Error: falta '.' después de break\n");
                }
            } else {
                printf("Error: falta 'break' después de listaSent\n");
            }
        } else {
            printf("Error: falta número después de case\n");
        }
    } else {
        printf("Error: falta case\n");
    }
}

// --- LISTA DE SENTENCIAS ---
void listaSent(Cola *cola) {
    while (frente(cola) == 'a' || frente(cola) == 'i' || frente(cola) == 'd' || frente(cola) == 'k' || frente(cola) == 'c' || frente(cola) == 'b') {
        Sent(cola);
    }
    // ε (vacío)
}

// --- SENTENCIA individual ---
void Sent(Cola *cola) {
    char token = frente(cola);
    if (token == 'i') {
        IF(cola);
    } else if (token == 'd') {
        doW(cola);
    } else if (token == 'k') {
        Switch(cola);
    } else if (token == 'a') {
        desencolar(cola); // simulamos asignación
        if (frente(cola) == '=') {
            desencolar(cola);
            if (frente(cola) == 'n' || frente(cola) == 'a') {
                desencolar(cola);
                if (frente(cola) == ';') {
                    desencolar(cola);
                } else {
                    printf("Error: falta ';' después de asignación\n");
                }
            } else {
                printf("Error: falta valor en asignación\n");
            }
        } else {
            printf("Error: falta '=' en asignación\n");
        }
    } else if (token == 'c') { // sentencia c.
        desencolar(cola);
        if (frente(cola) == '.') {
            desencolar(cola);
        } else {
            printf("Error: falta '.' después de 'c'\n");
        }
    } else if (token == 'b') { // sentencia b.
        desencolar(cola);
        if (frente(cola) == '.') {
            desencolar(cola);
        } else {
            printf("Error: falta '.' después de 'b'\n");
        }
    } else {
        printf("Error: sentencia desconocida '%c'\n", token);
    }
}

// --- EXPRESIÓN LÓGICA SIMPLIFICADA ---
void exprLog(Cola *cola) {
    if (frente(cola) == 'n' || frente(cola) == 'a') {
        desencolar(cola); // aceptamos un número o un identificador
    } else {
        printf("Error: expresión lógica inválida\n");
    }
}

// --- MAIN para pruebas ---
int main() {
    cola = crearCola();

    printf("\n--- Prueba IF-ELSE ---\n");
    encolar(cola, 'i');
    encolar(cola, '(');
    encolar(cola, 'n');
    encolar(cola, ')');
    encolar(cola, '{');
    encolar(cola, 'c');
    encolar(cola, '.');
    encolar(cola, '}');
    encolar(cola, 'e'); // else
    encolar(cola, '{');
    encolar(cola, 'b');
    encolar(cola, '.');
    encolar(cola, '}');
    IF(cola);

    printf("\n--- Prueba DO-WHILE ---\n");
    encolar(cola, 'd');
    encolar(cola, '{');
    encolar(cola, 'c');
    encolar(cola, '.');
    encolar(cola, '}');
    encolar(cola, 'w');
    encolar(cola, '(');
    encolar(cola, 'n');
    encolar(cola, ')');
    doW(cola);

    printf("\n--- Prueba SWITCH-CASE ---\n");
    encolar(cola, 'k');
    encolar(cola, '(');
    encolar(cola, 'a');
    encolar(cola, ')');
    encolar(cola, '{');
    encolar(cola, 'z');
    encolar(cola, 'n');
    encolar(cola, 'c');
    encolar(cola, '.');
    encolar(cola, 'b');
    encolar(cola, '.');
    encolar(cola, 'z');
    encolar(cola, 'n');
    encolar(cola, 'b');
    encolar(cola, '.');
    encolar(cola, '}');
    Switch(cola);

    destruirCola(cola);
    return 0;
}
