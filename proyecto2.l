%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"
#include "aSintactico.h"

int yylex(void);

Cola* colaDeAtomos;
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
char obtenerAtomo(Token token, const char* texto);
void Return();
void For();
void Funcion();
void ExprLogica();


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

char obtenerAtomo(Token token, const char* texto) {
    switch (token.clase) {
        case 0: return 'n';  // Constante entera
        case 1: return 'r';  // Constante flotante
        case 2: return texto[0];  // Operadores aritméticos (primer caracter)
        case 3: return texto[0];  // Símbolos especiales (primer caracter)
        case 4: return 's';  // Constante cadena
        case 5: {  // Palabras reservadas
            const char atomoReservadas[] = {
                'b','z','h','c','d','u','e','f','v','i',
                't','g','x','y','j','k','q','o','w'
            };
            return atomoReservadas[token.valor];
        }
        case 6: {  // Operadores de asignación
            const char atomoAsignacion[] = {
                '=', '#', ';', '$', ',', '?', ':', '^', '@', '<', '>'
            };
            return atomoAsignacion[token.valor];
        }
        case 7: {  // Operadores lógicos
            const char atomoLogico[] = {'|', '&', '!'};
            return atomoLogico[token.valor];
        }
        case 8: return 'a';  // Identificador
        default: return '?';
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
    char atomo = obtenerAtomo(token, texto);
    encolar(colaDeAtomos, atomo);  // Encolar el átomo
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
    colaDeAtomos=crearCola(); // Ejecutar el analizador léxico
    yylex(); 
    
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

    imprimirColaEnArchivo(colaDeAtomos, outputFile);  // Imprimir la cola de átomos en el archivo
    Program();
    destruirCola(colaDeAtomos);  // Destruir la cola de átomos

    fclose(outputFile);  // Cerrar archivo de salida
    fclose(yyin);  // Cerrar archivo de entrada

    return 0;
}