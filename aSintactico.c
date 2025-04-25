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

// Proyección 23: <Sent> ---> <Asig>
void Sent23(Cola *cola) {
    Asig(cola);  // Procesar asignación
}

// Proyección 24: <Sent> ---> <doW>
void Sent24(Cola *cola) {
    doW(cola);   // Procesar do-while
}

// Proyección 25: <Sent> ---> <IF>
void Sent25(Cola *cola) {
    IF(cola);    // Procesar if
}

// Proyección 26: <Sent> ---> <Switch>
void Sent26(Cola *cola) {
    Switch(cola); // Procesar switch
}

// Proyección 27: <Sent> ---> <For>
void Sent27() {
    For();   // Procesar for
}

// Proyección 28: <Sent> ---> <Ret>
void Sent28() {
    Ret();   // Procesar return
}

// Proyección 29: <Sent> ---> c.
void Sent29(Cola *cola) {
    if (strcmp(frente(cola), "c") == 0) {
        desencolar(cola); // Consumir 'c'
        if (strcmp(frente(cola), ".") == 0) {
            desencolar(cola); // Consumir '.'
        } else {
            printf("Error: Se esperaba '.' después de 'c'\n");
        }
    } else {
        printf("Error: Se esperaba 'c' para sentencia\n");
    }
}

// Proyección 30: <Sent> ---> b.
void Sent30(Cola *cola) {
    if (strcmp(frente(cola), "b") == 0) {
        desencolar(cola); // Consumir 'b'
        if (strcmp(frente(cola), ".") == 0) {
            desencolar(cola); // Consumir '.'
        } else {
            printf("Error: Se esperaba '.' después de 'b'\n");
        }
    } else {
        printf("Error: Se esperaba 'b' para sentencia\n");
    }
}

// Función general para <Sent>
void Sent(Cola *cola) {
    // Verificar el token actual para decidir qué producción aplicar
    if (strcmp(frente(cola), "d") == 0) {        // Asumo que 'd' inicia <Asig>
        Sent23(cola);
    }
    else if (strcmp(frente(cola), "do") == 0) {  // do-while
        Sent24(cola);
    }
    else if (strcmp(frente(cola), "if") == 0) {  // if
        Sent25(cola);
    }
    else if (strcmp(frente(cola), "switch") == 0) { // switch
        Sent26(cola);
    }
    else if (strcmp(frente(cola), "for") == 0) { // for
        Sent27();
    }
    else if (strcmp(frente(cola), "return") == 0) { // return
        Sent28();
    }
    else if (strcmp(frente(cola), "c") == 0) {   // sentencia tipo 'c.'
        Sent29(cola);
    }
    else if (strcmp(frente(cola), "b") == 0) {   // sentencia tipo 'b.'
        Sent30(cola);
    }
    else {
        printf("Error: Token inesperado '%s' en <Sent>\n", frente(cola));
    }
}

// Proyección 31: <listaSent> ---> <Sent><listaSent>
// CS(31): FIRST(<Sent>) = {d, i, k, f, r}
void listaSent31(Cola *cola) {
    // Procesar una sentencia
    Sent(cola);
    
    // Procesar el resto de sentencias
    listaSent(cola);
}

// Proyección 32: <listaSent> ---> ε
// CS(32): { ], }, b }
void listaSent32() {
    // Producción vacía, no se hace nada
    return;
}

// Función general para <listaSent>
void listaSent(Cola *cola) {   
    // Verificar los tokens del FIRST(<Sent>) para la proyección 31
    if (strcmp(frente(cola), "d") == 0 ||   // declaración
        strcmp(frente(cola), "i") == 0 ||   // if
        strcmp(frente(cola), "k") == 0 ||   // for
        strcmp(frente(cola), "f") == 0 ||   // función
        strcmp(frente(cola), "r") == 0) {   // return
        listaSent31(cola);
    }
    // Verificar los tokens del CS(32) para la proyección vacía
    else if (strcmp(frente(cola), "]") == 0 ||
             strcmp(frente(cola), "}") == 0 ||
             strcmp(frente(cola), "b") == 0) {
        listaSent32();
    }
    else {
        printf("Error: Token inesperado '%s' en <listaSent>\n", frente(cola));
    }
}


// Proyección 34: <exprLog> ---> !(E)
void exprLog34(Cola *cola) {
    if (strcmp(frente(cola), "!") == 0) {
        desencolar(cola); // Consumir '!'
        if (strcmp(frente(cola), "(") == 0) {
            desencolar(cola); // Consumir '('
            E(cola);    // Procesar expresión E
            if (strcmp(frente(cola), ")") == 0) {
                desencolar(cola); // Consumir ')'
            } else {
                printf("Error: Se esperaba ')' después de expresión\n");
            }
        } else {
            printf("Error: Se esperaba '(' después de '!'\n");
        }
    } else {
        printf("Error: Se esperaba '!' para expresión lógica\n");
    }
}

// Proyección 35 modificada: <exprLog> ---> (E)<opLog>(E)
void exprLog35(Cola *cola) {
    if (strcmp(frente(cola), "(") == 0) {
        desencolar(cola); // Consumir '('
        E();     // Procesar primera expresión E
        
        if (strcmp(frente(cola), ")") == 0) {
            desencolar(cola); // Consumir ')'
            opLog(cola); // Procesar operador lógico (& o |)
            
            if (strcmp(frente(cola), "(") == 0) {
                desencolar(cola); // Consumir '('
                E();     // Procesar segunda expresión E
                
                if (strcmp(frente(cola), ")") == 0) {
                    desencolar(cola); // Consumir ')'
                    // Expresión lógica completa
                } else {
                    printf("Error: Se esperaba ')' después de la segunda expresión\n");
                }
            } else {
                printf("Error: Se esperaba '(' después del operador lógico\n");
            }
        } else {
            printf("Error: Se esperaba ')' después de la primera expresión\n");
        }
    } else {
        printf("Error: Se esperaba '(' para expresión lógica\n");
    }
}

// Proyección 36: <opLog> ---> &
void opLog36(Cola *cola) {
    if (strcmp(frente(cola), "&") == 0) {
        desencolar(cola); // Consumir '&'
        // € indica fin de la producción
    } else {
        printf("Error: Se esperaba operador '&'\n");
    }
}

// Proyección 37: <opLog> ---> |
void opLog37(Cola *cola) {
    if (strcmp(frente(cola), "|") == 0) {
        desencolar(cola); // Consumir '|'
        // € indica fin de la producción
    } else {
        printf("Error: Se esperaba operador '|'\n");
    }
}

// Función general para <opLog> que maneja ambas opciones (36 y 37)
void opLog(Cola *cola) {
    if (strcmp(frente(cola), "&") == 0) {
        opLog36(cola);
    } else if (strcmp(frente(cola), "|") == 0) {
        opLog37(cola);
    } else {
        printf("Error: Operador lógico desconocido. Se esperaba '&' o '|'\n");
    }
}

// Función general para <exprLog> que maneja ambas opciones (34 y 35)
void exprLog(Cola *cola) {
    // Verificar si empieza con '!' (proyección 34)
    if (strcmp(frente(cola), "!") == 0) {
        exprLog34(cola);
    } 
    // Verificar si empieza con '(' (proyección 35)
    else if (strcmp(frente(cola), "(") == 0) {
        exprLog35(cola);
    } else {
        printf("Error: Expresión lógica no válida. Debe comenzar con '!' o '('\n");
    }
}

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
