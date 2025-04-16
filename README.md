%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
int yywrap(void);
extern FILE *yyin;
extern char *yytext;

#define MAX_IDENTIFIERS 100  
#define MAX_LITERALS 100     

typedef struct {
    int clase;  
    int valor;  
} Token;

typedef struct {
    int posicion;  
    char nombre[50];  
    int tipo;  
} TablaSimbolos;

typedef struct {
    int posicion;  
    char dato[100];  
} TablaLiterales;

TablaSimbolos tablaSimbolos[MAX_IDENTIFIERS];  
int numSimbolos = 0;  

TablaLiterales tablaLiterales[MAX_LITERALS];  
int numLiterales = 0;  

FILE *outputFile;
char cadenaDeAtomos[10000] = "";

// Prototipos
const char* obtenerAtomo(Token token, const char* texto);
void imprimirToken(Token token, char *texto);
void Return();
void For();
void Funcion();
void IfElse();
void DoWhile();
void SwitchCase();
void Programa();

// Funciones de tabla
int buscarEnTablaSimbolos(char *nombre) {
    for (int i = 0; i < numSimbolos; i++) {
        if (strcmp(tablaSimbolos[i].nombre, nombre) == 0)
            return i;
    }
    return -1;
}

int agregarATablaSimbolos(char *nombre) {
    if (numSimbolos >= MAX_IDENTIFIERS) return -1;
    tablaSimbolos[numSimbolos].posicion = numSimbolos;
    strcpy(tablaSimbolos[numSimbolos].nombre, nombre);
    tablaSimbolos[numSimbolos].tipo = -1;
    return numSimbolos++;
}

int buscarEnTablaLiterales(char *dato) {
    for (int i = 0; i < numLiterales; i++) {
        if (strcmp(tablaLiterales[i].dato, dato) == 0)
            return i;
    }
    return -1;
}

int agregarATablaLiterales(char *dato) {
    if (numLiterales >= MAX_LITERALS) return -1;
    tablaLiterales[numLiterales].posicion = numLiterales;
    strcpy(tablaLiterales[numLiterales].dato, dato);
    return numLiterales++;
}

const char* obtenerAtomo(Token token, const char* texto) {
    static char atomo[10];
    switch (token.clase) {
        case 0: return "n";
        case 1: return "r";
        case 2: case 3: return texto;
        case 4: return "s";
        case 5: {
            const char* atomoReservadas[] = {
                "b","z","h","c","d","u","e","f","v","i",
                "t","g","x","y","j","k","q","o","w"
            };
            return atomoReservadas[token.valor];
        }
        case 6: {
            const char* atomoAsignacion[] = {
                "=", "#", ";", "$", ",", "?", ":", "^", "@", "<", ">"
            };
            return atomoAsignacion[token.valor];
        }
        case 7: {
            const char* atomoLogico[] = {"|", "&", "!"};
            return atomoLogico[token.valor];
        }
        case 8: return "a";
        default: return "?";
    }
}

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

    printf("TOKEN: Clase %d (%s), Valor: %d, Texto: %s\n",
           token.clase, descripcionesClases[token.clase], token.valor, texto);
    fprintf(outputFile, "TOKEN: Clase %d (%s), Valor: %d, Texto: %s\n",
            token.clase, descripcionesClases[token.clase], token.valor, texto);

    const char* atomo = obtenerAtomo(token, texto);
    strcat(cadenaDeAtomos, atomo);
    strcat(cadenaDeAtomos, " ");
}

// ----- Funciones Sintácticas -----

void Return() {
    if (strcmp(yytext, "RETURN") == 0) {
        yylex();
        if (strcmp(yytext, ";") == 0) {
            yylex();
        } else {
            printf("Error: se esperaba ';' después de return\n");
        }
    } else {
        printf("Error: se esperaba 'return'\n");
    }
}

void For() {
    if (strcmp(yytext, "FOR") == 0) {
        yylex();
        if (strcmp(yytext, "(") == 0) {
            yylex();
            if (strcmp(yytext, ";") == 0) {
                yylex();
                if (strcmp(yytext, ";") == 0) {
                    yylex();
                    if (strcmp(yytext, ")") == 0) {
                        yylex();
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

void Funcion() {
    Token token;
    if (strcmp(yytext, "INT") == 0 || strcmp(yytext, "VOID") == 0 || strcmp(yytext, "FLOAT") == 0) {
        yylex();
        if (token.clase == 8) {
            yylex();
            if (strcmp(yytext, "(") == 0) {
                yylex();
                if (strcmp(yytext, ")") == 0) {
                    yylex();
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

void IfElse() {
    if (strcmp(yytext, "IF") == 0) {
        yylex();
        if (strcmp(yytext, "(") == 0) {
            yylex();
            if (strcmp(yytext, ")") == 0) {
                yylex();
                if (strcmp(yytext, "ELSE") == 0) {
                    yylex();
                }
            } else {
                printf("Error: se esperaba ')'\n");
            }
        } else {
            printf("Error: se esperaba '('\n");
        }
    } else {
        printf("Error: se esperaba 'if'\n");
    }
}

void DoWhile() {
    if (strcmp(yytext, "DO") == 0) {
        yylex();
        if (strcmp(yytext, "WHILE") == 0) {
            yylex();
            if (strcmp(yytext, "(") == 0) {
                yylex();
                if (strcmp(yytext, ")") == 0) {
                    yylex();
                    if (strcmp(yytext, ";") == 0) {
                        yylex();
                    } else {
                        printf("Error: se esperaba ';'\n");
                    }
                } else {
                    printf("Error: se esperaba ')'\n");
                }
            } else {
                printf("Error: se esperaba '('\n");
            }
        } else {
            printf("Error: se esperaba 'while'\n");
        }
    } else {
        printf("Error: se esperaba 'do'\n");
    }
}

void SwitchCase() {
    if (strcmp(yytext, "SWITCH") == 0) {
        yylex();
        if (strcmp(yytext, "(") == 0) {
            yylex();
            if (strcmp(yytext, ")") == 0) {
                yylex();
                if (strcmp(yytext, "{") == 0) {
                    yylex();
                    while (strcmp(yytext, "CASE") == 0) {
                        yylex();
                        if (strcmp(yytext, ":") == 0) {
                            yylex();
                        } else {
                            printf("Error: se esperaba ':'\n");
                        }
                    }
                    if (strcmp(yytext, "}") == 0) {
                        yylex();
                    } else {
                        printf("Error: se esperaba '}'\n");
                    }
                } else {
                    printf("Error: se esperaba '{'\n");
                }
            } else {
                printf("Error: se esperaba ')'\n");
            }
        } else {
            printf("Error: se esperaba '('\n");
        }
    } else {
        printf("Error: se esperaba 'switch'\n");
    }
}

void Programa() {
    while (!feof(yyin)) {
        if (strcmp(yytext, "IF") == 0) IfElse();
        else if (strcmp(yytext, "DO") == 0) DoWhile();
        else if (strcmp(yytext, "SWITCH") == 0) SwitchCase();
        else if (strcmp(yytext, "FOR") == 0) For();
        else if (strcmp(yytext, "RETURN") == 0) Return();
        else if (strcmp(yytext, "INT") == 0 || strcmp(yytext, "VOID") == 0 || strcmp(yytext, "FLOAT") == 0) Funcion();
        else {
            printf("Aviso: token no reconocido: %s\n", yytext);
            yylex();
        }
    }
}
%}

constantesNumericas [0-9]+(u|l|ul)?  
constantesFlotantes [0-9]+\.[0-9]+(e[+-]?[0-9]+)?  
operadoresAritmeticos \+|\+\+|\-|\-\-|\*|\*\*|\/|\%
simbolosEspeciales \(|\)|\{|\}|\[|\]|\,|\:|\;|\. 
constantesCadena #([^#]{1,})# 
palabrasReservadas (WHILE|VOID|UNSIGNED|SWITCH|SIZEOF|SHORT|RETURN|LONG|INT|IF|FOR|FLOAT|ELSE|DOUBLE|DO|CONTINUE|CHAR|CASE|BREAK)  
opAsignacion =|\+=|\-=|\*=|\/=|%=|&=|\|=|\^=|<<=|>>=  
opLogicos !|&&|\|\|  
identificador [A-Za-z][A-Za-z0-9_]{0,14}
espacio [ \t\r\n]  
comentarioLinea ~~.* 
comentarioBloque ~\/([^~]|\~[^\/])*\~ 

%%

{constantesNumericas} { Token token; token.clase = 0; token.valor = atoi(yytext); imprimirToken(token, yytext); }
{constantesFlotantes} { Token token; token.clase = 1; int pos = buscarEnTablaLiterales(yytext); if (pos == -1) pos = agregarATablaLiterales(yytext); token.valor = pos; imprimirToken(token, yytext); }
{operadoresAritmeticos} {
    Token token; token.clase = 2;
    if (strcmp(yytext, "+") == 0) token.valor = 0;
    else if (strcmp(yytext, "-") == 0) token.valor = 1;
    else if (strcmp(yytext, "*") == 0) token.valor = 2;
    else if (strcmp(yytext, "/") == 0) token.valor = 3;
    else if (strcmp(yytext, "%") == 0) token.valor = 4;
    else if (strcmp(yytext, "++") == 0) token.valor = 5;
    else if (strcmp(yytext, "--") == 0) token.valor = 6;
    else if (strcmp(yytext, "**") == 0) token.valor = 7;
    imprimirToken(token, yytext);
}
{simbolosEspeciales} { Token token; token.clase = 3; token.valor = (int)yytext[0]; imprimirToken(token, yytext); }
{constantesCadena} { Token token; token.clase = 4; int pos = buscarEnTablaLiterales(yytext); if (pos == -1) pos = agregarATablaLiterales(yytext); token.valor = pos; imprimirToken(token, yytext); }
{palabrasReservadas} {
    Token token; token.clase = 5;
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
    Token token; token.clase = 6;
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
    Token token; token.clase = 7;
    if (strcmp(yytext, "&&") == 0) token.valor = 0;
    else if (strcmp(yytext, "||") == 0) token.valor = 1;
    else if (strcmp(yytext, "!") == 0) token.valor = 2;
    imprimirToken(token, yytext);
}
{identificador} {
    Token token; token.clase = 8;
    int pos = buscarEnTablaSimbolos(yytext);
    if (pos == -1) pos = agregarATablaSimbolos(yytext);
    token.valor = pos;
    imprimirToken(token, yytext);
}
{espacio} { }
{comentarioLinea} { printf("Comentario de línea: %s\n", yytext); fprintf(outputFile, "Comentario de línea: %s\n", yytext); }
{comentarioBloque} { printf("Comentario de bloque: %s\n", yytext); fprintf(outputFile, "Comentario de bloque: %s\n", yytext); }
. { printf("Error: '%s' no es válido\n", yytext); fprintf(outputFile, "Error: '%s' no es válido\n", yytext); }

%%

int yywrap() { return 1; }

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
    if (yyin == NULL || outputFile == NULL) {
        printf("Error al abrir archivos.\n");
        return 1;
    }

    yylex();
    Programa();

    printf("\nCadena de átomos:\n%s\n", cadenaDeAtomos);
    fprintf(outputFile, "\nCadena de átomos:\n%s\n", cadenaDeAtomos);

    printf("\nTabla de Símbolos:\n");
    fprintf(outputFile, "\nTabla de Símbolos:\n");
    for (int i = 0; i < numSimbolos; i++) {
        printf("Posición: %d, Nombre: %s, Tipo: %d\n", tablaSimbolos[i].posicion, tablaSimbolos[i].nombre, tablaSimbolos[i].tipo);
        fprintf(outputFile, "Posición: %d, Nombre: %s, Tipo: %d\n", tablaSimbolos[i].posicion, tablaSimbolos[i].nombre, tablaSimbolos[i].tipo);
    }

    printf("\nTabla de Literales:\n");
    fprintf(outputFile, "\nTabla de Literales:\n");
    for (int i = 0; i < numLiterales; i++) {
        printf("Posición: %d, Dato: %s\n", tablaLiterales[i].posicion, tablaLiterales[i].dato);
        fprintf(outputFile, "Posición: %d, Dato: %s\n", tablaLiterales[i].posicion, tablaLiterales[i].dato);
    }

    fclose(outputFile);
    fclose(yyin);
    return 0;
}
