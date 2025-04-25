#include <stdio.h>
#include <string.h>
#include "cola.h"
// Proyección: D -> <tipo>a
void D() {
    // Procesar el tipo
    tipo();    
}

// Proyección: <tipo> -> <unsig><size><dec>
void tipo() {
    // Procesar parte unsigned (puede ser vacío)
    unsig();
    
    // Procesar tamaño
    size();
    
    // Procesar declaración
    dec();
}

// Proyección: <unsig> -> q
void unsig_q() {
    if (strcmp(yytext, "q") == 0) {
        desencolar(cola ); // Consumir 'q'
        // Marcar que el tipo es unsigned
        // tipoActual |= UNSIGNED_FLAG;
    } else {
        printf("Error: Se esperaba 'q' para unsigned\n");
    }
}

// Proyección: <unsig> -> ε 
void unsig_epsilon() {
    // No se consume ningún token, es producción vacía
    return;
}

// Función general para <unsig>
void unsig() {
    // Verificar si el siguiente token es 'q'
    if (strcmp(yytext, "q") == 0) {
        unsig_q();
    } else {
        // Si no, aplicar producción vacía
        unsig_epsilon();
    }
}

// Proyección: <size> -> g
void size_g() {
    if (strcmp(yytext, "g") == 0) {
        desencolar(cola ); // Consumir 'g'
        // Marcar tamaño correspondiente (ej. long)
        // tipoActual |= LONG_FLAG;
    } else {
        printf("Error: Se esperaba 'g' para tamaño\n");
    }
}

// Proyección: <size> -> u
void size_u() {
    if (strcmp(yytext, "u") == 0) {
        desencolar(cola ); // Consumir 'u'
        // Marcar tamaño correspondiente (ej. short)
        // tipoActual |= SHORT_FLAG;
    } else {
        printf("Error: Se esperaba 'u' para tamaño\n");
    }
}

// Proyección: <size> -> y
void size_y() {
    if (strcmp(yytext, "y") == 0) {
        desencolar(cola ); // Consumir 'y'
        // Marcar tamaño correspondiente (ej. long long)
        // tipoActual |= LONG_LONG_FLAG;
    } else {
        printf("Error: Se esperaba 'y' para tamaño\n");
    }
}

// Proyección: <size> -> ε 
void size_epsilon() {
    // No se consume ningún token, es producción vacía
    return;
}

// Función general para <size>
void size() {
    // Verificar las posibles opciones
    if (strcmp(yytext, "g") == 0) {
        size_g();
    } else if (strcmp(yytext, "u") == 0) {
        size_u();
    } else if (strcmp(yytext, "y") == 0) {
        size_y();
    } else {
        // Si no coincide con ninguna, aplicar producción vacía
        size_epsilon();
    }
}

// Proyección: <dec> -> t
void dec_t() {
    if (strcmp(yytext, "t") == 0) {
        desencolar(cola ); // Consumir 't'
        // Marcar tipo correspondiente (ej. int)
        // tipoActual |= INT_TYPE;
    } else {
        printf("Error: Se esperaba 't' para declaración\n");
    }
}

// Proyección: <dec> -> h
void dec_h() {
    if (strcmp(yytext, "h") == 0) {
        desencolar(cola ); // Consumir 'h'
        // Marcar tipo correspondiente (ej. char)
        // tipoActual |= CHAR_TYPE;
    } else {
        printf("Error: Se esperaba 'h' para declaración\n");
    }
}

// Proyección: <dec> -> f
void dec_f() {
    if (strcmp(yytext, "f") == 0) {
        desencolar(cola ); // Consumir 'f'
        // Marcar tipo correspondiente (ej. float)
        // tipoActual |= FLOAT_TYPE;
    } else {
        printf("Error: Se esperaba 'f' para declaración\n");
    }
}

// Función general para <dec>
void dec() {
    // Verificar las posibles opciones
    if (strcmp(yytext, "t") == 0) {
        dec_t();
    } else if (strcmp(yytext, "h") == 0) {
        dec_h();
    } else if (strcmp(yytext, "f") == 0) {
        dec_f();
    } else {
        printf("Error: Declaración de tipo no válida. Se esperaba 't', 'h' o 'f'\n");
    }
}
// Proyección: <Asig> -> a<opAsig>E;
void Asig() {
    // Verificar que el primer token es un identificador (a)
    if (token.clase == 8) { // 8 es la clase para identificadores
        desencolar(cola ); // Consumir el identificador
        
        // Procesar el operador de asignación
        opAsig();
        
        // Procesar la expresión (E)
        E();
        
        // Verificar que termina con ;
        if (strcmp(yytext, ";") == 0) {
            desencolar(cola ); // Consumir ;
        } else {
            printf("Error: Se esperaba ';' al final de la asignación\n");
        }
    } else {
        printf("Error: Se esperaba un identificador al inicio de la asignación\n");
    }
}

// Proyección: <opAsig> -> =
void opAsig_igual() {
    if (strcmp(yytext, "=") == 0) {
        desencolar(cola ); // Consumir '='
        // Operador de asignación simple reconocido
    } else {
        printf("Error: Se esperaba '=' como operador de asignación\n");
    }
}

// Proyección: <opAsig> -> +=
void opAsig_mas_igual() {
    if (strcmp(yytext, "+=") == 0) {
        desencolar(cola ); // Consumir '+='
        // Operador de asignación suma reconocido
    } else {
        printf("Error: Se esperaba '+=' como operador de asignación\n");
    }
}

// Proyección: <opAsig> -> -=
void opAsig_menos_igual() {
    if (strcmp(yytext, "-=") == 0) {
        desencolar(cola ); // Consumir '-='
        // Operador de asignación resta reconocido
    } else {
        printf("Error: Se esperaba '-=' como operador de asignación\n");
    }
}

// Función general para <opAsig>
void opAsig() {
    // Verificar todos los posibles operadores de asignación
    if (strcmp(yytext, "=") == 0) {
        opAsig_igual();
    } else if (strcmp(yytext, "+=") == 0) {
        opAsig_mas_igual();
    } else if (strcmp(yytext, "-=") == 0) {
        opAsig_menos_igual();
    } else if (strcmp(yytext, "*=") == 0) {
        // Similar para *=
        desencolar(cola );
    } else if (strcmp(yytext, "/=") == 0) {
        // Similar para /=
        desencolar(cola );
    } else if (strcmp(yytext, "%=") == 0) {
        // Similar para %=
        desencolar(cola );
    } else {
        printf("Error: Operador de asignación no válido\n");
    }
}
// Función simplificada para manejar expresiones (E)
void E() {
    // Esta es una implementación básica, deberías expandirla según tu gramática
    // Puede manejar expresiones simples como constantes, identificadores, etc.
    
    if (token.clase == 0 || token.clase == 1 || token.clase == 8) {
        // Constantes numéricas o identificadores
        desencolar(cola );
        
        // Opcional: manejar operaciones más complejas
        if (token.clase == 2) { // Operadores aritméticos
            desencolar(cola );
            E(); // Recursividad para manejar expresiones complejas
        }
    } else {
        printf("Error: Expresión no válida\n");
    }
}
// Función para E -> T E´
void E() {
    T();
    E_prima();
}

// Función para E´ -> + T E´
void E_prima_mas() {
    if (strcmp(yytext, "+") == 0) {
        desencolar(cola ); // Consumir '+'
        T();
        E_prima();
    } else {
        printf("Error: Se esperaba '+' en E'\n");
    }
}

// Función para E´ -> - T E´
void E_prima_menos() {
    if (strcmp(yytext, "-") == 0) {
        desencolar(cola ); // Consumir '-'
        T();
        E_prima();
    } else {
        printf("Error: Se esperaba '-' en E'\n");
    }
}

// Función para E´ -> ε
void E_prima_epsilon() {
    // Producción vacía, no hacer nada
}

// Función general para E´
void E_prima() {
    if (strcmp(yytext, "+") == 0) {
        E_prima_mas();
    } else if (strcmp(yytext, "-") == 0) {
        E_prima_menos();
    } else {
        // Verificar si el token actual está en FOLLOW(E´)
        // Si es así, aplicar producción vacía
        // Esto es simplificado, en una implementación real necesitarías FIRST y FOLLOW
        E_prima_epsilon();
    }
}

// Función para T -> F T´
void T() {
    F();
    T_prima();
}

// Función para T´ -> * F T´
void T_prima_mult() {
    if (strcmp(yytext, "*") == 0) {
        desencolar(cola ); // Consumir '*'
        F();
        T_prima();
    } else {
        printf("Error: Se esperaba '*' en T'\n");
    }
}

// Función para T´ -> / F T´
void T_prima_div() {
    if (strcmp(yytext, "/") == 0) {
        desencolar(cola ); // Consumir '/'
        F();
        T_prima();
    } else {
        printf("Error: Se esperaba '/' en T'\n");
    }
}

// Función para T´ -> % F T´
void T_prima_mod() {
    if (strcmp(yytext, "%") == 0) {
        desencolar(cola ); // Consumir '%'
        F();
        T_prima();
    } else {
        printf("Error: Se esperaba '%%' en T'\n");
    }
}

// Función para T´ -> ε
void T_prima_epsilon() {
    // Producción vacía, no hacer nada
}

// Función general para T´
void T_prima() {
    if (strcmp(yytext, "*") == 0) {
        T_prima_mult();
    } else if (strcmp(yytext, "/") == 0) {
        T_prima_div();
    } else if (strcmp(yytext, "%") == 0) {
        T_prima_mod();
    } else {
        // Verificar si el token actual está en FOLLOW(T´)
        T_prima_epsilon();
    }
}

// Función para F -> ( E )
void F_parentesis() {
    if (strcmp(yytext, "(") == 0) {
        desencolar(cola ); // Consumir '('
        E();
        if (strcmp(yytext, ")") == 0) {
            desencolar(cola ); // Consumir ')'
        } else {
            printf("Error: Se esperaba ')' después de expresión\n");
        }
    } else {
        printf("Error: Se esperaba '(' en F\n");
    }
}

// Función para F -> a G
void F_identificador() {
    if (token.clase == 8) { // 8 es la clase para identificadores (a)
        desencolar(cola ); // Consumir identificador
        G();
    } else {
        printf("Error: Se esperaba identificador en F\n");
    }
}

// Función para F -> n (constante entera)
void F_numero() {
    if (token.clase == 0) { // 0 es la clase para constantes enteras (n)
        desencolar(cola ); // Consumir número
    } else {
        printf("Error: Se esperaba constante numérica entera en F\n");
    }
}

// Función para F -> r (constante flotante)
void F_real() {
    if (token.clase == 1) { // 1 es la clase para constantes flotantes (r)
        desencolar(cola ); // Consumir número real
    } else {
        printf("Error: Se esperaba constante numérica flotante en F\n");
    }
}

// Función para F -> F´ a
void F_prima_identificador() {
    F_prima();
    if (token.clase == 8) { // 8 es la clase para identificadores (a)
        desencolar(cola ); // Consumir identificador
    } else {
        printf("Error: Se esperaba identificador después de F'\n");
    }
}

// Función general para F
void F() {
    if (strcmp(yytext, "(") == 0) {
        F_parentesis();
    } else if (token.clase == 8) { // Identificador
        F_identificador();
    } else if (token.clase == 0) { // Constante entera
        F_numero();
    } else if (token.clase == 1) { // Constante flotante
        F_real();
    } else if (strcmp(yytext, "l") == 0 || strcmp(yytext, "m") == 0) {
        // Posible F -> F´ a
        F_prima_identificador();
    } else {
        printf("Error: Factor no válido\n");
    }
}

// Función para F´ -> l
void F_prima_l() {
    if (strcmp(yytext, "l") == 0) {
        desencolar(cola ); // Consumir 'l'
    } else {
        printf("Error: Se esperaba 'l' en F'\n");
    }
}

// Función para F´ -> m
void F_prima_m() {
    if (strcmp(yytext, "m") == 0) {
        desencolar(cola ); // Consumir 'm'
    } else {
        printf("Error: Se esperaba 'm' en F'\n");
    }
}

// Función general para F´
void F_prima() {
    if (strcmp(yytext, "l") == 0) {
        F_prima_l();
    } else if (strcmp(yytext, "m") == 0) {
        F_prima_m();
    } else {
        printf("Error: Símbolo no válido en F'\n");
    }
}

// Función para G -> m
void G_m() {
    if (strcmp(yytext, "m") == 0) {
        desencolar(cola ); // Consumir 'm'
    } else {
        printf("Error: Se esperaba 'm' en G\n");
    }
}

// Función para G -> l
void G_l() {
    if (strcmp(yytext, "l") == 0) {
        desencolar(cola ); // Consumir 'l'
    } else {
        printf("Error: Se esperaba 'l' en G\n");
    }
}

// Función para G -> ε
void G_epsilon() {
    // Producción vacía, no hacer nada
}

// Función general para G
void G() {
    if (strcmp(yytext, "m") == 0) {
        G_m();
    } else if (strcmp(yytext, "l") == 0) {
        G_l();
    } else {
        // Verificar si el token actual está en FOLLOW(G)
        G_epsilon();
    }
}
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