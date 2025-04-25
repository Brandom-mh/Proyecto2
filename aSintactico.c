#include <stdio.h>
#include <string.h>
#include "cola.h"
Cola *cola; // Cola de prueba

// --- Prototipos de funciones ---

void cargarColaCaracterPorCaracter();
void Program();
void OtraFunc();
void Func();
void TipoF();
void Arg();
void Cuerpo();
void listaDec();
void D();
void Tipo();
void unsig();
void Size();
void dec();
void Sent();
void listaSent();
void listaSent();
void doW();
void exprLog();
void IF();
void ELSE();
void FOR();
void Ret();
void valRet();
void Switch();
void listaCase();
void Case();
void E();
void EP();
void T();
void TP();
void F();
void FP();
void G();
void opLog();


void Asig();
void opAsig();



void cargarColaCaracterPorCaracter() {
    char *nombreArchivo = "salida2.txt"; // Nombre del archivo a leer
    FILE *archivo = fopen(nombreArchivo, "r"); // Abrir el archivo en modo lectura
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        return;
    }

    char c;
    int dentroDeCorchetes = 0;

    while ((c = fgetc(archivo)) != EOF) { // Leer carácter por carácter
        if (c == '[') {
            dentroDeCorchetes = 1; // Comenzar a leer dentro de los corchetes
        } else if (c == ']') {
            dentroDeCorchetes = 0; // Terminar de leer dentro de los corchetes
            break; // Salir del bucle después de cerrar los corchetes
        } else if (dentroDeCorchetes) {
            encolar(cola, c); // Encolar cada carácter dentro de los corchetes
        }
    }

    fclose(archivo); // Cerrar el archivo
}

// --- Declaración ---
void D() {
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
void Asig() {
    if (frente(cola) == 'a') { // identificador
        desencolar(cola);
        opAsig(cola); // Verificar operador de asignación
        E(cola);
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

void opAsig() {
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
void E() {
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
void Sent23() {
    Asig(cola);  // Procesar asignación
}

// Proyección 24: <Sent> ---> <doW>
void Sent24() {
    doW(cola);   // Procesar do-while
}

// Proyección 25: <Sent> ---> <IF>
void Sent25() {
    IF(cola);    // Procesar if
}

// Proyección 26: <Sent> ---> <Switch>
void Sent26() {
    Switch(cola); // Procesar switch
}

// Proyección 27: <Sent> ---> <For>
void Sent27() {
    //FOR(cola);   // Procesar for
}

// Proyección 28: <Sent> ---> <Ret>
void Sent28() {
    //Ret(cola);   // Procesar return
}

// Proyección 29: <Sent> ---> c.
void Sent29() {
    if (frente(cola) == 'c') {
        desencolar(cola); // Consumir 'c'
        if (frente(cola) == '.') {
            desencolar(cola); // Consumir '.'
        } else {
            printf("Error: Se esperaba '.' después de 'c'\n");
        }
    } else {
        printf("Error: Se esperaba 'c' para sentencia\n");
    }
}

// Proyección 30: <Sent> ---> b.
void Sent30() {
    if (frente(cola) == 'b') {
        desencolar(cola); // Consumir 'b'
        if (frente(cola) == '.') {
            desencolar(cola); // Consumir '.'
        } else {
            printf("Error: Se esperaba '.' después de 'b'\n");
        }
    } else {
        printf("Error: Se esperaba 'b' para sentencia\n");
    }
}

// Función general para <Sent>
void Sent() {
    if (frente(cola) == 'd') {        // Asumo que 'd' inicia <Asig>
        Sent23(cola);
    }
    else if (frente(cola) == 'i') {  // if
        Sent25(cola);
    }
    else if (frente(cola) == 'k') { // switch
        Sent26(cola);
    }
    else if (frente(cola) == 'f') { // for
        Sent27(cola);
    }
    else if (frente(cola) == 'r') { // return
        Sent28(cola);
    }
    else if (frente(cola) == 'c') {   // sentencia tipo 'c.'
        Sent29(cola);
    }
    else if (frente(cola) == 'b') {   // sentencia tipo 'b.'
        Sent30(cola);
    }
    else {
        printf("Error: Token inesperado '%c' en <Sent>\n", frente(cola));
    }
}

// Proyección 31: <listaSent> ---> <Sent><listaSent>
// CS(31): FIRST(<Sent>) = {d, i, k, f, r}
void listaSent31() {
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
void listaSent() {   
    if (frente(cola) == 'd' ||   // declaración
        frente(cola) == 'i' ||   // if
        frente(cola) == 'k' ||   // for
        frente(cola) == 'f' ||   // función
        frente(cola) == 'r') {   // return
        listaSent31(cola);
    }
    else if (frente(cola) == ']' ||
             frente(cola) == '}' ||
             frente(cola) == 'b') {
        listaSent32();
    }
    else {
        printf("Error: Token inesperado '%c' en <listaSent>\n", frente(cola));
    }
}

// Proyección 34: <exprLog> ---> !(E)
void exprLog34() {
    if (frente(cola) == '!') {
        desencolar(cola); // Consumir '!'
        if (frente(cola) == '(') {
            desencolar(cola); // Consumir '('
            E(cola);    // Procesar expresión E
            if (frente(cola) == ')') {
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
void exprLog35() {
    if (frente(cola) == '(') {
        desencolar(cola); // Consumir '('
        E(cola);     // Procesar primera expresión E
        
        if (frente(cola) == ')') {
            desencolar(cola); // Consumir ')'
            opLog(cola); // Procesar operador lógico (& o |)
            
            if (frente(cola) == '(') {
                desencolar(cola); // Consumir '('
                E(cola);     // Procesar segunda expresión E
                
                if (frente(cola) == ')') {
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
void opLog36() {
    if (frente(cola) == '&') {
        desencolar(cola); // Consumir '&'
    } else {
        printf("Error: Se esperaba operador '&'\n");
    }
}

// Proyección 37: <opLog> ---> |
void opLog37() {
    if (frente(cola) == '|') {
        desencolar(cola); // Consumir '|'
    } else {
        printf("Error: Se esperaba operador '|'\n");
    }
}

// Función general para <opLog> que maneja ambas opciones (36 y 37)
void opLog() {
    if (frente(cola) == '&') {
        opLog36(cola);
    } else if (frente(cola) == '|') {
        opLog37(cola);
    } else {
        printf("Error: Operador lógico desconocido. Se esperaba '&' o '|'\n");
    }
}

// Función general para <exprLog> que maneja ambas opciones (34 y 35)
void exprLog() {
    if (frente(cola) == '!') {
        exprLog34(cola);
    } 
    else if (frente(cola) == '(') {
        exprLog35(cola);
    } else {
        printf("Error: Expresión lógica no válida. Debe comenzar con '!' o '('\n");
    }
}

void doW() {
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
void IF() {
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
void Switch() {
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

    // // Prueba 1: IF () c. ELSE b.
    // printf("\n--- Prueba IF ---\n");
    // encolar(cola, 'i'); // if
    // encolar(cola, '(');
    // encolar(cola, ')');
    // encolar(cola, 'c');
    // encolar(cola, '.');
    // encolar(cola, 'e'); // else
    // encolar(cola, 'b');
    // encolar(cola, '.');
    // IF(cola);

    // // Prueba 2: DO c. WHILE ();;
    // printf("\n--- Prueba DO-WHILE ---\n");
    // encolar(cola, 'd');
    // encolar(cola, 'c');
    // encolar(cola, '.');
    // encolar(cola, 'w');
    // encolar(cola, '(');
    // encolar(cola, ')');
    // encolar(cola, ';');
    // doW(cola);

    // // Prueba 3: SWITCH(a){ CASE : b. }
    // printf("\n--- Prueba SWITCH ---\n");
    // encolar(cola, 'k');
    // encolar(cola, '(');
    // encolar(cola, 'a');
    // encolar(cola, ')');
    // encolar(cola, '{');
    // encolar(cola, 'z');
    // encolar(cola, ':');
    // encolar(cola, 'b');
    // encolar(cola, '.');
    // encolar(cola, '}');
    // Switch(cola);
    
    printf("\n\n--- Prueba de carga de cola desde archivo ---\n");
    cargarColaCaracterPorCaracter(); // Cargar la cola desde el archivo
    mostrarCola(cola); // Mostrar la cola después de las pruebas
    desencolar(cola); // Desencolar el primer elemento (opcional)
    mostrarCola(cola); // Mostrar la cola después de las pruebas
    desencolar(cola); // Desencolar el primer elemento (opcional)
    mostrarCola(cola); // Mostrar la cola después de las pruebas
    desencolar(cola); // Desencolar el primer elemento (opcional)
    mostrarCola(cola); // Mostrar la cola después de las pruebas
    desencolar(cola); // Desencolar el primer elemento (opcional)
    mostrarCola(cola); // Mostrar la cola después de las pruebas
    desencolar(cola); // Desencolar el primer elemento (opcional)
    mostrarCola(cola); // Mostrar la cola después de las pruebas
    desencolar(cola); // Desencolar el primer elemento (opcional)
    mostrarCola(cola); // Mostrar la cola después de las pruebas

    destruirCola(cola);
    return 0;
}
