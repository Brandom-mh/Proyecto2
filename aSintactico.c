#include <stdio.h>
#include <string.h>
#include "cola.h"


void For(Cola* cola);
void Ret(Cola* cola);
void TipoF(Cola* cola);
void Arg(Cola* cola);
void cuerpo(Cola* cola);
void Func(Cola* cola);
void Tipo(Cola* cola);
void E(Cola* cola);
void listaSent(Cola* cola);
void listaDec(Cola* cola);
void sentencia(Cola* cola);

void For(Cola* cola) {
    Cola* temp = crearCola();
    Cola* copiaOriginal = clonarCola(cola); // Clonar la cola original
    
    char atomo;
    
    // Verificar si es un FOR (átomo 'v')
    if (frente(cola) != 'v') {
        printf("Error: Se esperaba 'FOR' (átomo 'v')\n");
        destruirCola(temp);
        destruirCola(copiaOriginal);
        return;
    }
    atomo = desencolar(cola);
    encolar(temp, atomo);
    
    // Verificar paréntesis de apertura '('
    if (frente(cola) != '(') {
        printf("Error: Se esperaba '(' después de FOR\n");
        destruirCola(temp);
        destruirCola(copiaOriginal);
        return;
    }
    encolar(temp, desencolar(cola)); // Mover '(' a temp

    // Procesar expresión aritmética
    E(cola); // Procesar la expresión aritmética

    // Verificar paréntesis de cierre ')'
    if (frente(cola) != ')') {
        printf("Error: Se esperaba ')' después de la expresión en FOR\n");
        destruirCola(temp);
        destruirCola(copiaOriginal);
        return;
    }
    encolar(temp, desencolar(cola)); // Mover ')' a temp

    // Verificar llave de apertura '{'
    if (frente(cola) != '{') {
        printf("Error: Se esperaba '{' después de FOR(expresión)\n");
        destruirCola(temp);
        destruirCola(copiaOriginal);
        return;
    }
    encolar(temp, desencolar(cola)); // Mover '{' a temp

    // Procesar lista de sentencias
    listaSent(cola); // Procesar las sentencias

    // Verificar llave de cierre '}'
    if (frente(cola) != '}') {
        printf("Error: Se esperaba '}' al final del bloque FOR\n");
        destruirCola(temp);
        destruirCola(copiaOriginal);
        return;
    }
    encolar(temp, desencolar(cola)); // Mover '}' a temp

    printf("FOR analizado correctamente\n");

    // Mostrar la cola original completa (incluyendo todos los átomos originales)
    mostrarCola(copiaOriginal);

    destruirCola(temp);
    destruirCola(copiaOriginal);
}



void Ret(Cola* cola) {
    if (frente(cola) == 'x') {  // 'x' representa RETURN
        desencolar(cola); // Consumir 'x'
        
        // Verificar paréntesis de apertura
        if (frente(cola) == '(') {
            desencolar(cola); // Consumir '('
            
            // Procesar valor de retorno (puede ser ε)
            if (frente(cola) != ')') {
                printf("Procesando expresión dentro del RETURN...\n");
                E(cola); // Procesar expresión si existe
            }
            
            // Verificar paréntesis de cierre
            if (frente(cola) == ')') {
                desencolar(cola); // Consumir ')'
                printf("RETURN procesado correctamente.\n");
            } else {
                printf("Error: Se esperaba ')' al final de RETURN\n");
            }
        } else {
            printf("Error: Se esperaba '(' después de RETURN\n");
        }
    } else {
        printf("Error: Se esperaba 'x' (RETURN)\n");
    }

// Verificar punto y coma después del return
    if (frente(cola) == ';') {
       desencolar(cola);
       printf("RETURN procesado correctamente.\n");
    } else {
       printf("Error: Se esperaba ';' después de RETURN\n");
    }
}


void Func(Cola* cola) {
    Cola* copiaOriginal = clonarCola(cola); // Clonamos la cola original
    Cola* temp = crearCola(); // Por si quieres ir guardando el bloque de la función (opcional)

    // Procesar tipo de retorno
    TipoF(cola);

    // Verificar identificador de función
    if (frente(cola) == 'a') {
        encolar(temp, desencolar(cola)); // Consumir identificador

        // Verificar paréntesis de apertura para argumentos
        if (frente(cola) == '(') {
            encolar(temp, desencolar(cola)); // Consumir '('

            // Procesar argumentos (puede ser ε)
            Arg(cola);

            // Verificar paréntesis de cierre
            if (frente(cola) == ')') {
                encolar(temp, desencolar(cola)); // Consumir ')'

                // Verificar llave de apertura del cuerpo
                if (frente(cola) == '{') {
                    encolar(temp, desencolar(cola)); // Consumir '{'

                    // Procesar cuerpo de la función
                    cuerpo(cola);

                    // Verificar llave de cierre
                    if (frente(cola) == '}') {
                        encolar(temp, desencolar(cola)); // Consumir '}'

                        printf("Función analizada correctamente\n");
                        mostrarCola(copiaOriginal);
                    } else {
                        printf("Error: Se esperaba '}' al final de la función\n");
                    }
                } else {
                    printf("Error: Se esperaba '{' después de los argumentos\n");
                }
            } else {
                printf("Error: Se esperaba ')' después de los argumentos\n");
            }
        } else {
            printf("Error: Se esperaba '(' después del nombre de función\n");
        }
    } else {
        printf("Error: Se esperaba identificador como nombre de función\n");
    }

    destruirCola(temp);
    destruirCola(copiaOriginal);
}

void TipoF(Cola* cola) {
    if (frente(cola) == 'o') {  // 'o' representa VOID
        desencolar(cola);
    } else {
        Tipo(cola); // Procesar otros tipos (INT, FLOAT, etc.)
    }
}

void Arg(Cola* cola) {
    // Si hay un tipo, es un argumento, sino es ε
    if (frente(cola) == 't' || frente(cola) == 'f' || 
        frente(cola) == 'g' || frente(cola) == 'y') {
        
        Tipo(cola); // Procesar tipo
        if (frente(cola) == 'a') {
            desencolar(cola); // Consumir identificador de argumento
        } else {
            printf("Error: Se esperaba identificador después del tipo en argumento\n");
        }
    }
    // Si no hay tipo, es ε (no se hace nada)
}

void cuerpo(Cola* cola) {
    // Procesar declaraciones (puede ser ε)
    listaDec(cola);
    
    // Procesar sentencias (puede ser ε)
    listaSent(cola);
}

void listaDec(Cola* cola) {
    while (frente(cola) == 't' || frente(cola) == 'f' || 
           frente(cola) == 'g' || frente(cola) == 'y') {
        
        Tipo(cola); // Procesar tipo
        
        if (frente(cola) == 'a') {
            desencolar(cola); // Consumir identificador
            
            // Manejar posible asignación O solo declaración
            if (frente(cola) == '=') {
                desencolar(cola); // Consumir '='
                E(cola); // Procesar expresión
            }
            
            // Verificar fin de declaración
            if (frente(cola) == ';') {
                desencolar(cola); // Consumir ';'
            } else {
                printf("Error: Se esperaba ';' después de declaración\n");
                break;
            }
        } else {
            printf("Error: Se esperaba identificador en declaración\n");
            break;
        }
    }
}

void listaSent(Cola* cola) {

    while (!estaVacia(cola)) {
        char actual = frente(cola);
        
        // Si encontramos una llave de cierre, salimos
        if (actual == '}') {
            break;
        }
        
        // Procesar sentencia individual
        sentencia(cola);
        
    }
}

void sentencia(Cola* cola) {
    char actual = frente(cola);
    
    if (actual == 'v') { // FOR
        For(cola);
    }
    else if (actual == 'x') { // RETURN
        Ret(cola);
    }
    else if (actual == 't' || actual == 'f' || actual == 'g' || actual == 'y') {
        // Es una declaración
        listaDec(cola);
    }
    else if (actual == 'a') { // Posible asignación
        desencolar(cola); // Consumir identificador
        if (frente(cola) == '=') {
            desencolar(cola); // Consumir '='
            E(cola); // Procesar expresión
        }
        // Verificar fin de sentencia
        if (frente(cola) == ';') {
            desencolar(cola);
        } else {
            printf("Error: Se esperaba ';' después de sentencia\n");
        }
    }
    else if (actual == '{') { // Bloque
        desencolar(cola);
        listaSent(cola);
        if (frente(cola) == '}') {
            desencolar(cola);
        } else {
            printf("Error: Se esperaba '}' al final del bloque\n");
        }
    }
    else {
        printf("Error: Sentencia no válida comenzando con '%c'\n", actual);
    }
}

void E(Cola* cola) {
    if (frente(cola) == 'a') { // Identificador
        desencolar(cola); // Consumir identificador
        
        // Verificar si es una asignación
        if (frente(cola) == '=') {
            desencolar(cola); // Consumir '='
            E(cola); // Procesar la expresión después del '='
        }
    }
    else if (frente(cola) == '(') { // Expresión entre paréntesis
        desencolar(cola); // Consumir '('
        E(cola); // Procesar expresión interna
        if (frente(cola) == ')') {
            desencolar(cola); // Consumir ')'
        } else {
            printf("Error: Se esperaba ')'\n");
        }
    }
    else if (frente(cola) == 'n' || frente(cola) == 'r') { // Número o literal
        desencolar(cola); // Consumir número o literal
    }
    else {
        printf("Error: Expresión inválida\n");
    }
    
    // Manejar operadores binarios
    if (frente(cola) == '+' || frente(cola) == '-' || 
        frente(cola) == '*' || frente(cola) == '/') {
        desencolar(cola); // Consumir operador
        E(cola); // Procesar siguiente expresión
    }
}


void Tipo(Cola* cola) {
    // Procesar tipos básicos (INT, FLOAT, etc.)
    char actual = frente(cola);
    
    if (actual == 't' || actual == 'f' || actual == 'g' || actual == 'y') {
        desencolar(cola); // Consumir tipo
    } else {
        printf("Error: Se esperaba tipo de dato\n");
    }
}
