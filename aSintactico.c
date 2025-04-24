#include <stdio.h>
#include <string.h>
#include "cola.h"

// Proyección 23: <Sent> ---> <Asig>
void Sent23() {
    Asig();  // Procesar asignación
}

// Proyección 24: <Sent> ---> <doW>
void Sent24() {
    doW();   // Procesar do-while
}

// Proyección 25: <Sent> ---> <IF>
void Sent25() {
    IF();    // Procesar if
}

// Proyección 26: <Sent> ---> <Switch>
void Sent26() {
    Switch(); // Procesar switch
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
        Sent23();
    }
    else if (strcmp(frente(cola), "do") == 0) {  // do-while
        Sent24();
    }
    else if (strcmp(frente(cola), "if") == 0) {  // if
        Sent25();
    }
    else if (strcmp(frente(cola), "switch") == 0) { // switch
        Sent26();
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