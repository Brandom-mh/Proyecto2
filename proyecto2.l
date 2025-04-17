%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);

// Definición de constantes para los tamaños máximos de las tablas
#define MAX_IDENTIFIERS 100  
#define MAX_LITERALS 100     

// Definición de la estructura Token
typedef struct {
    int clase;  
    int valor;  
} Token;

// Definición de la estructura TablaSimbolos
typedef struct {
    int posicion;  
    char nombre[50];  
    int tipo;  
} TablaSimbolos;

// Definición de la estructura TablaLiterales
typedef struct {
    int posicion;  
    char dato[100];  
} TablaLiterales;

// Declaración de las tablas de símbolos y literales
TablaSimbolos tablaSimbolos[MAX_IDENTIFIERS];  
int numSimbolos = 0;  

TablaLiterales tablaLiterales[MAX_LITERALS];  
int numLiterales = 0;  

// Puntero al archivo de salida
FILE *outputFile;

// Cadena para acumular átomos
char cadenaDeAtomos[10000] = "";

// Prototipos de funciones
const char* obtenerAtomo(Token token, const char* texto);
void Return();
void For();
void Funcion();


// Función para buscar un identificador en la tabla de símbolos
int buscarEnTablaSimbolos(char *nombre) {
    for (int i = 0; i < numSimbolos; i++) {
        if (strcmp(tablaSimbolos[i].nombre, nombre) == 0) {
            return i;  // Retorna la posición si se encuentra
        }
    }
    return -1;  // Retorna -1 si no se encuentra
}

// Función para agregar un identificador a la tabla de símbolos
int agregarATablaSimbolos(char *nombre) {
    if (numSimbolos >= MAX_IDENTIFIERS) {
        return -1;  // Retorna -1 si la tabla está llena
    }
    tablaSimbolos[numSimbolos].posicion = numSimbolos;
    strcpy(tablaSimbolos[numSimbolos].nombre, nombre);
    tablaSimbolos[numSimbolos].tipo = -1;
    return numSimbolos++;  // Retorna la posición del nuevo identificador
}

// Función para buscar un literal en la tabla de literales
int buscarEnTablaLiterales(char *dato) {
    for (int i = 0; i < numLiterales; i++) {
        if (strcmp(tablaLiterales[i].dato, dato) == 0) {
            return i;  // Retorna la posición si se encuentra
        }
    }
    return -1;  // Retorna -1 si no se encuentra
}

// Función para agregar un literal a la tabla de literales
int agregarATablaLiterales(char *dato) {
    if (numLiterales >= MAX_LITERALS) {
        return -1;  // Retorna -1 si la tabla está llena
    }
    tablaLiterales[numLiterales].posicion = numLiterales;
    strcpy(tablaLiterales[numLiterales].dato, dato);
    return numLiterales++;  // Retorna la posición del nuevo literal
}

const char* obtenerAtomo(Token token, const char* texto) {
    static char atomo[10];
    
    switch (token.clase) {
        case 0: return "n";  // Constante entera
        case 1: return "r";  // Constante flotante
        case 2: return texto;  // Operadores aritméticos son sus propios átomos
        case 3: return texto;  // Símbolos especiales también
        case 4: return "s";  // Constante cadena
        case 5: {  // Palabras reservadas
            const char* atomoReservadas[] = {
                    "b","z","h","c","d","u","e","f","v","i",
                    "t","g","x","y","j","k","q","o","w"
            };
            return atomoReservadas[token.valor];
        }
        case 6: {  // Operadores de asignación
            const char* atomoAsignacion[] = {
                "=", "#", ";", "$", ",", "?", ":", "^", "@", "<", ">"
            };
            return atomoAsignacion[token.valor];
        }
        case 7: {  // Operadores lógicos
            const char* atomoLogico[] = {"|", "&", "!"};
            return atomoLogico[token.valor];
        }
        case 8: return "a";  // Identificador
        default: return "?";
    }
}

// Función para imprimir un token en la consola y en el archivo de salida
void imprimirToken(Token token, char *texto) {
    const char *descripcionesClases[] = {
        "Constante numérica entera",
        "Constante numérica flotante",
        "Operador aritmético",
        "Símbolo especial",
        "Constante cadena",
        "Palabra reservada",
        "Operador de asignación",
        "Operador lógico",
        "Identificador"
    };

    // Imprimir en consola
    printf("TOKEN: Clase %d (%s), Valor: %d, Texto: %s\n", token.clase, 
                                                           descripcionesClases[token.clase], 
                                                           token.valor, 
                                                           texto);
    // Imprimir en archivo
    fprintf(outputFile, "TOKEN: Clase %d (%s), Valor: %d, Texto: %s\n", token.clase, 
                                                           descripcionesClases[token.clase], 
                                                           token.valor, 
                                                           texto);
    // Agregar átomo a la cadena
    const char* atomo = obtenerAtomo(token, texto);
    strcat(cadenaDeAtomos, atomo);
    strcat(cadenaDeAtomos, " ");
}

// Proyección: D -> <tipo>a
void D() {
    // Procesar el tipo
    tipo();
    
    // Verificar que sigue un identificador (a)
    if (token.clase == 8) { // 8 es la clase para identificadores
        yylex(); // Consumir el identificador
        
        // Aquí podrías agregar el identificador a la tabla de símbolos con su tipo
        // Por ejemplo:
        // agregarATablaSimbolosConTipo(yytext, tipoActual);
    } else {
        printf("Error: Se esperaba un identificador después del tipo\n");
    }
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
        yylex(); // Consumir 'q'
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
        yylex(); // Consumir 'g'
        // Marcar tamaño correspondiente (ej. long)
        // tipoActual |= LONG_FLAG;
    } else {
        printf("Error: Se esperaba 'g' para tamaño\n");
    }
}

// Proyección: <size> -> u
void size_u() {
    if (strcmp(yytext, "u") == 0) {
        yylex(); // Consumir 'u'
        // Marcar tamaño correspondiente (ej. short)
        // tipoActual |= SHORT_FLAG;
    } else {
        printf("Error: Se esperaba 'u' para tamaño\n");
    }
}

// Proyección: <size> -> y
void size_y() {
    if (strcmp(yytext, "y") == 0) {
        yylex(); // Consumir 'y'
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
        yylex(); // Consumir 't'
        // Marcar tipo correspondiente (ej. int)
        // tipoActual |= INT_TYPE;
    } else {
        printf("Error: Se esperaba 't' para declaración\n");
    }
}

// Proyección: <dec> -> h
void dec_h() {
    if (strcmp(yytext, "h") == 0) {
        yylex(); // Consumir 'h'
        // Marcar tipo correspondiente (ej. char)
        // tipoActual |= CHAR_TYPE;
    } else {
        printf("Error: Se esperaba 'h' para declaración\n");
    }
}

// Proyección: <dec> -> f
void dec_f() {
    if (strcmp(yytext, "f") == 0) {
        yylex(); // Consumir 'f'
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
        yylex(); // Consumir el identificador
        
        // Procesar el operador de asignación
        opAsig();
        
        // Procesar la expresión (E)
        E();
        
        // Verificar que termina con ;
        if (strcmp(yytext, ";") == 0) {
            yylex(); // Consumir ;
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
        yylex(); // Consumir '='
        // Operador de asignación simple reconocido
    } else {
        printf("Error: Se esperaba '=' como operador de asignación\n");
    }
}

// Proyección: <opAsig> -> +=
void opAsig_mas_igual() {
    if (strcmp(yytext, "+=") == 0) {
        yylex(); // Consumir '+='
        // Operador de asignación suma reconocido
    } else {
        printf("Error: Se esperaba '+=' como operador de asignación\n");
    }
}

// Proyección: <opAsig> -> -=
void opAsig_menos_igual() {
    if (strcmp(yytext, "-=") == 0) {
        yylex(); // Consumir '-='
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
        yylex();
    } else if (strcmp(yytext, "/=") == 0) {
        // Similar para /=
        yylex();
    } else if (strcmp(yytext, "%=") == 0) {
        // Similar para %=
        yylex();
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
        yylex();
        
        // Opcional: manejar operaciones más complejas
        if (token.clase == 2) { // Operadores aritméticos
            yylex();
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
        yylex(); // Consumir '+'
        T();
        E_prima();
    } else {
        printf("Error: Se esperaba '+' en E'\n");
    }
}

// Función para E´ -> - T E´
void E_prima_menos() {
    if (strcmp(yytext, "-") == 0) {
        yylex(); // Consumir '-'
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
        yylex(); // Consumir '*'
        F();
        T_prima();
    } else {
        printf("Error: Se esperaba '*' en T'\n");
    }
}

// Función para T´ -> / F T´
void T_prima_div() {
    if (strcmp(yytext, "/") == 0) {
        yylex(); // Consumir '/'
        F();
        T_prima();
    } else {
        printf("Error: Se esperaba '/' en T'\n");
    }
}

// Función para T´ -> % F T´
void T_prima_mod() {
    if (strcmp(yytext, "%") == 0) {
        yylex(); // Consumir '%'
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
        yylex(); // Consumir '('
        E();
        if (strcmp(yytext, ")") == 0) {
            yylex(); // Consumir ')'
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
        yylex(); // Consumir identificador
        G();
    } else {
        printf("Error: Se esperaba identificador en F\n");
    }
}

// Función para F -> n (constante entera)
void F_numero() {
    if (token.clase == 0) { // 0 es la clase para constantes enteras (n)
        yylex(); // Consumir número
    } else {
        printf("Error: Se esperaba constante numérica entera en F\n");
    }
}

// Función para F -> r (constante flotante)
void F_real() {
    if (token.clase == 1) { // 1 es la clase para constantes flotantes (r)
        yylex(); // Consumir número real
    } else {
        printf("Error: Se esperaba constante numérica flotante en F\n");
    }
}

// Función para F -> F´ a
void F_prima_identificador() {
    F_prima();
    if (token.clase == 8) { // 8 es la clase para identificadores (a)
        yylex(); // Consumir identificador
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
        yylex(); // Consumir 'l'
    } else {
        printf("Error: Se esperaba 'l' en F'\n");
    }
}

// Función para F´ -> m
void F_prima_m() {
    if (strcmp(yytext, "m") == 0) {
        yylex(); // Consumir 'm'
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
        yylex(); // Consumir 'm'
    } else {
        printf("Error: Se esperaba 'm' en G\n");
    }
}

// Función para G -> l
void G_l() {
    if (strcmp(yytext, "l") == 0) {
        yylex(); // Consumir 'l'
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

// Implementación de Return()
void Return() {
    if (strcmp(yytext, "RETURN") == 0) {
        yylex(); // consumir 'return'
        // aquí podría venir una expresión opcional
        if (strcmp(yytext, ";") == 0) {
            yylex(); // consumir ';'
        } else {
            printf("Error: se esperaba ';' después de return\n");
        }
    } else {
        printf("Error: se esperaba 'return'\n");
    }
}

// Implementación de For()
void For() {
    if (strcmp(yytext, "FOR") == 0) {
        yylex(); // consumir 'for'
        if (strcmp(yytext, "(") == 0) {
            yylex(); // consumir '('
            // puedes agregar funciones: Declaracion(); o Expresion();
            if (strcmp(yytext, ";") == 0) {
                yylex(); // consumir ';'
                // otra expresión
                if (strcmp(yytext, ";") == 0) {
                    yylex(); // consumir ';'
                    // última expresión
                    if (strcmp(yytext, ")") == 0) {
                        yylex(); // consumir ')'
                        // luego el cuerpo
                        // puedes poner: Bloque(); o Instruccion();
                    } else {
                        printf("Error: se esperaba ')'\n");
                    }
                } else {
                    printf("Error: se esperaba segundo ';'\n");
                }
            } else {
                printf("Error: se esperaba primer ';'\n");
            }
        } else {
            printf("Error: se esperaba '('\n");
        }
    } else {
        printf("Error: se esperaba 'for'\n");
    }
}

// Implementación de Funcion()
void Funcion() {
    Token token;
    // Debe comenzar con tipo de retorno
    if (strcmp(yytext, "INT") == 0 || strcmp(yytext, "VOID") == 0 || strcmp(yytext, "FLOAT") == 0) {
        yylex(); // consumir tipo

        if (token.clase == 8) {  // identificador
            yylex(); // consumir nombre

            if (strcmp(yytext, "(") == 0) {
                yylex(); // consumir '('
                // Aquí puedes agregar una función Parametros();
                if (strcmp(yytext, ")") == 0) {
                    yylex(); // consumir ')'
                    // Aquí puedes poner Bloque(); para el cuerpo
                } else {
                    printf("Error: se esperaba ')'\n");
                }
            } else {
                printf("Error: se esperaba '('\n");
            }
        } else {
            printf("Error: se esperaba nombre de función\n");
        }
    } else {
        printf("Error: se esperaba tipo de retorno\n");
    }
}

%}

constantesNumericas [0-9]+(u|l|ul)?  
constantesFlotantes [0-9]+\.[0-9]+(e[+-]?[0-9]+)?  
operadoresAritmeticos \+|\+\+|\-|\-\-|\*|\*\*|\/|\%
simbolosEspeciales \(|\)|\{|\}|\[|\]|&|\,|\:|\;|\. 
constantesCadena #([A-Za-z0-9!\"$%&'()*+,\-./:;<=>?@\[\\\]^_{|}~ ]+)# 
palabrasReservadas (WHILE|VOID|UNSIGNED|SWITCH|SIZEOF|SHORT|RETURN|LONG|INT|IF|FOR|FLOAT|ELSE|DOUBLE|DO|CONTINUE|CHAR|CASE|BREAK)  
opAsignacion =|\+=|\-=|\*=|\/=|%=|&=|\\|=|\^=|<<=|>>=  
opLogicos !|&&|\|\|  
identificador [A-Za-z][A-Za-z0-9_]{0,14}
espacio [ \t\r\n]  
comentarioLinea ~~.* 
comentarioBloque "~/"([^~]|\~[^/])*"\~" 

%%
{constantesNumericas} {
    Token token;
    token.clase = 0;  
    token.valor = atoi(yytext);  
    imprimirToken(token, yytext); 
}

{constantesFlotantes} {
    Token token;
    token.clase = 1;  
    int pos = buscarEnTablaLiterales(yytext); 
    if (pos == -1) {
        pos = agregarATablaLiterales(yytext);  
    }
    token.valor = pos;  
    imprimirToken(token, yytext);  
}

{operadoresAritmeticos} {
    Token token;
    token.clase = 2;  // Clase: Operador aritmético
    if (strcmp(yytext, "+") == 0) token.valor = 0;
    else if (strcmp(yytext, "-") == 0) token.valor = 1;
    else if (strcmp(yytext, "*") == 0) token.valor = 2;
    else if (strcmp(yytext, "/") == 0) token.valor = 3;
    else if (strcmp(yytext, "%") == 0) token.valor = 4;
    else if (strcmp(yytext, "++") == 0) token.valor = 5;
    else if (strcmp(yytext, "--") == 0) token.valor = 6;
    else if (strcmp(yytext, "**") == 0) token.valor = 7;
    imprimirToken(token, yytext);  // Imprimir el token
}

{simbolosEspeciales} {
    Token token;
    token.clase = 3;  // Clase: Símbolo especial
    token.valor = (int)yytext[0];  // Asignar el valor ASCII del símbolo
    imprimirToken(token, yytext);  // Imprimir el token
}

{constantesCadena} {
    Token token;
    token.clase = 4;  // Clase: Constante cadena
    int pos = buscarEnTablaLiterales(yytext);  // Buscar en la tabla de literales
    if (pos == -1) {
        pos = agregarATablaLiterales(yytext);  // Agregar si no existe
    }
    token.valor = pos;  // Asignar la posición en la tabla
    imprimirToken(token, yytext);  // Imprimir el token
}

{palabrasReservadas} {
    Token token;
    token.clase = 5;  // Clase: Palabra reservada Esta madre esta al reves en el proyecto 1
    if (strcmp(yytext, "BREAK") == 0) token.valor = 0;
    else if (strcmp(yytext, "CASE") == 0) token.valor = 1;
    else if (strcmp(yytext, "CHAR") == 0) token.valor = 2;
    else if (strcmp(yytext, "CONTINUE") == 0) token.valor = 3;
    else if (strcmp(yytext, "DO") == 0) token.valor = 4;
    else if (strcmp(yytext, "DOUBLE") == 0) token.valor = 5;
    else if (strcmp(yytext, "ELSE") == 0) token.valor = 6;
    else if (strcmp(yytext, "FLOAT") == 0) token.valor = 7;
    else if (strcmp(yytext, "FOR") == 0) token.valor = 8;
    else if (strcmp(yytext, "IF") == 0) token.valor = 9;
    else if (strcmp(yytext, "INT") == 0) token.valor = 10;
    else if (strcmp(yytext, "LONG") == 0) token.valor = 11;
    else if (strcmp(yytext, "RETURN") == 0) token.valor = 12;
    else if (strcmp(yytext, "SHORT") == 0) token.valor = 13;
    else if (strcmp(yytext, "SIZEOF") == 0) token.valor = 14;
    else if (strcmp(yytext, "SWITCH") == 0) token.valor = 15;
    else if (strcmp(yytext, "UNSIGNED") == 0) token.valor = 16;
    else if (strcmp(yytext, "VOID") == 0) token.valor = 17;
    else if (strcmp(yytext, "WHILE") == 0) token.valor = 18;
    imprimirToken(token, yytext);  
}

{opAsignacion} {
    Token token;
    token.clase = 6;  // Clase: Operador de asignación
    if (strcmp(yytext, "=") == 0) token.valor = 0;
    else if (strcmp(yytext, "+=") == 0) token.valor = 1;
    else if (strcmp(yytext, "-=") == 0) token.valor = 2;
    else if (strcmp(yytext, "*=") == 0) token.valor = 3;
    else if (strcmp(yytext, "/=") == 0) token.valor = 4;
    else if (strcmp(yytext, "%=") == 0) token.valor = 5;
    else if (strcmp(yytext, "&=") == 0) token.valor = 6;
    else if (strcmp(yytext, "|=") == 0) token.valor = 7;
    else if (strcmp(yytext, "^=") == 0) token.valor = 8;
    else if (strcmp(yytext, "<<=") == 0) token.valor = 9;
    else if (strcmp(yytext, ">>=") == 0) token.valor = 10;
    imprimirToken(token, yytext);  
}

{opLogicos} {
    Token token;
    token.clase = 7;  // Clase: Operador lógico
    if (strcmp(yytext, "&&") == 0) token.valor = 0;
    else if (strcmp(yytext, "||") == 0) token.valor = 1;
    else if (strcmp(yytext, "!") == 0) token.valor = 2;
    imprimirToken(token, yytext);  
}

{identificador} {
    Token token;
    token.clase = 8;  // Clase: Identificador
    int pos = buscarEnTablaSimbolos(yytext);  // Buscar en la tabla de símbolos
    if (pos == -1) {
        pos = agregarATablaSimbolos(yytext);  // Agregar si no existe
    }
    token.valor = pos;  // Asignar la posición en la tabla
    imprimirToken(token, yytext);  
}

{espacio}           {}  // Ignorar espacios en blanco
{comentarioLinea}   { 
    printf("Comentario de línea, Texto: %s\n", yytext); 
    fprintf(outputFile, "Comentario de línea, Texto: %s\n", yytext); 
}
{comentarioBloque}  { 
    printf("Comentario de bloque, Texto: %s\n", yytext); 
    fprintf(outputFile, "Comentario de bloque, Texto: %s\n", yytext); 
}
.           { 
    printf("Error: '%s' no es un identificador\n", yytext); 
    fprintf(outputFile, "Error: '%s' no es un identificador\n", yytext); 
} 
%%

int yywrap() {
    return 1; 
}

// Función principal
int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");  // Abrir archivo de entrada
    outputFile = fopen(argv[2], "w");  // Abrir archivo de salida

    if (yyin == NULL || outputFile == NULL) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    yylex();  // Ejecutar el analizador léxico

    // Imprimir la cadena de átomos
    printf("\nCadena de átomos:\n%s\n", cadenaDeAtomos);
    fprintf(outputFile, "\nCadena de átomos:\n%s\n", cadenaDeAtomos);

    // Imprimir la tabla de símbolos
    printf("\nTabla de Símbolos:\n");
    fprintf(outputFile, "\nTabla de Símbolos:\n");
    for (int i = 0; i < numSimbolos; i++) {
        printf("Posición: %d, Nombre: %s, Tipo: %d\n", 
               tablaSimbolos[i].posicion, tablaSimbolos[i].nombre, tablaSimbolos[i].tipo);
        fprintf(outputFile, "Posición: %d, Nombre: %s, Tipo: %d\n", 
               tablaSimbolos[i].posicion, tablaSimbolos[i].nombre, tablaSimbolos[i].tipo);
    }

    // Imprimir la tabla de literales
    printf("\nTabla de Literales:\n");
    fprintf(outputFile, "\nTabla de Literales:\n");
    for (int i = 0; i < numLiterales; i++) {
        printf("Posición: %d, Dato: %s\n", 
               tablaLiterales[i].posicion, tablaLiterales[i].dato);
        fprintf(outputFile, "Posición: %d, Dato: %s\n", 
               tablaLiterales[i].posicion, tablaLiterales[i].dato);
    }

    fclose(outputFile);  // Cerrar archivo de salida
    fclose(yyin);  // Cerrar archivo de entrada

    return 0;
}
