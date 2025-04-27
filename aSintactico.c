#include <stdio.h>
#include <string.h>
#include "cola.h"
Cola *cola; // Cola de prueba

// --- Prototipos de funciones ---

void cargarColaCaracterPorCaracter();
void Program();
void otraFunc();
void Func();
void TipoF();
void Arg();
void cuerpo();
void listaDec();
void D();
void Tipo();
void unsig();
void Size();
void dec();//skock
void Sent();
void listaSent();
void doW();
void exprLog();
void IF(); //Corregir deivid
void ELSE();//hacer deivid
void For();
void Ret();
void valRet();//acabar memo
void Switch();// checar deivid
void listaCase();//chechar
void Case();//checar
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

void program(){
    Func(); // Llamar a la función Func()
    otraFunc(); // Llamar a otraFunc() 
}

void otraFunc(){
    Func(); // Llamar a la función Func()
    otraFunc(); // Llamar a otraFunc() recursivamente
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
        opAsig(); // Verificar operador de asignación
        E();
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

//Brandom

void Sent(){
    
switch (frente(cola)) {
    case 'a': // Asignación
        Asig();
        break;

    case 'd': // do-while
        doW();
        break;

    case 'i': // if
        IF();
        break;

    case 'k': // switch
        Switch();
        break;

    case 'f': // for
        For();
        break;

    case 'r': // return
        Ret();
        break;

    default: // Caso no reconocido
        printf("Error: Token inesperado '%c'\n", frente(cola));
        break;
}
        if (frente(cola) == 'c'){
            desencolar(cola);
            if (frente(cola) == '.'){
                desencolar(cola);
            }else printf("Error: se esperaba .\n");       
        }else printf("Error: se esperaba c\n");        

        if (frente(cola) == 'b'){
            desencolar(cola);
            if(frente(cola) == '.'){
                desencolar(cola);
                return;
            } else printf("Error: se esperaba .\n");
        } else printf("Error se esperaba b\n");
    
}

void listaSent(){
    if(frente(cola) == 'a' || frente(cola) == 'd' || frente(cola) == 'i' ||
       frente(cola) == 'k' || frente(cola) == 'f' || frente(cola) == 'r'  ){
        Sent();
        listaSent();
        return;
    }printf("Error token incorrecto\n");
    if(frente(cola) == ']' || frente(cola) == '}' || frente(cola) == 'b'){
        return;
    }else printf("Error: se esperaba ] } b\n");
}

void exprLog(){
    if(frente(cola) == '!'){
        desencolar(cola);
        if (frente(cola) == '('){
            desencolar(cola);
            E();
            if(frente(cola) == ')'){
                desencolar(cola);
                return;
            }else printf("Error: se esperaba )\n");
        }else printf("Error: se esperaba (\n");
    }else printf("Error: se esperaba !\n");

    if(frente(cola) == '('){
        desencolar(cola);
        E();
        if(frente(cola) == ')'){
            desencolar(cola);
            opLog();
            if(frente(cola) == '('){
                desencolar(cola);
                E();
                if(frente(cola) == ')'){
                    desencolar(cola);
                    return;
                }else printf("Error: se esperaba )\n");
            }else printf("Error: se esperaba (\n");
        }else printf("Error: se esperaba )\n");
    }   else printf("Error: se esperaba (\n");
}

void opLog(){
    if(frente(cola) == '&'){
        desencolar(cola);
        return;
    }else printf("Error: se esperaba &\n");

    if(frente(cola) == '|'){
        desencolar(cola);
        return;
    }else printf("Error: se esperaba |\n");
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
             // Procesar expresión lógica
            desencolar(cola);
            exprLog(cola);
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

//memo

void For() {
    Cola* temp = crearCola();
    Cola* copiaOriginal = clonarCola(cola); // Clonar la cola original
    
    char atomo;
    
    // Verificar si es un FOR (átomo 'v')
    if (frente(cola) == 'v') {
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



void Ret() {
    if (frente(cola) == 'x') {  // 'x' representa RETURN
        desencolar(cola); // Consumir 'x'
        
        if (frente(cola) == '(') {
            desencolar(cola); // Consumir '('
            
            // Si lo siguiente no es ')', hay expresión
            if (frente(cola) != ')') {
                printf("[DEBUG] Procesando expresión dentro del RETURN...\n");
                E(cola);
            }

            if (frente(cola) == ')') {
                desencolar(cola); // Consumir ')'
            } else {
                printf("Error: Se esperaba ')' al final de RETURN\n");
            }
        } else {
            printf("Error: Se esperaba '(' después de RETURN\n");
        }
    } else {
        printf("Error: Se esperaba 'RETURN' (átomo 'x')\n");
        return;
    }

    // Verificar punto y coma después del return
    if (frente(cola) == ';') {
        desencolar(cola);
        printf("RETURN procesado correctamente.\n");
    } else {
        printf("Error: Se esperaba ';' después de RETURN\n");
    }
}

void valRet(){
    E();
    if(frente(cola) == ')') {
        desencolar(cola); // Consumir ';'
        return;
    } else {
        printf("Error: Se esperaba ')' después de valor de retorno\n");
    }
}


void Func() {
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

void TipoF() {
    if (frente(cola) == 'o') {  // 'o' representa VOID
        desencolar(cola);
    } else {
        Tipo(cola); // Procesar otros tipos (INT, FLOAT, etc.)
    }
}

void Arg() {
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

void cuerpo() {
    // Procesar declaraciones (puede ser ε)
    listaDec(cola);
    
    // Procesar sentencias (puede ser ε)
    listaSent(cola);
}

void listaDec() {
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

void listaSent() {

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

void sentencia() {
    if (estaVacia(cola)) return;

    char actual = frente(cola);
    printf("[DEBUG] Analizando sentencia iniciando con '%c'\n", actual);
    
    if (actual == 'v') { // FOR
        For(cola);
    }
    else if (actual == 'x') { // RETURN
        Ret(cola);
    }
    else if (actual == 't' || actual == 'f' || actual == 'g' || actual == 'y') {
        listaDec(cola);
    }
    else if (actual == 'a') {
        desencolar(cola); // Consumir identificador
        if (frente(cola) == '=') {
            desencolar(cola); // Consumir '='
            E(cola); // Procesar expresión
        }
        if (frente(cola) == ';') {
            desencolar(cola);
        } else {
            printf("Error: Se esperaba ';' después de sentencia de asignación\n");
        }
    }
    else if (actual == '{') {
        desencolar(cola);
        listaSent(cola);
        if (frente(cola) == '}') {
            desencolar(cola);
        } else {
            printf("Error: Se esperaba '}' al final del bloque\n");
        }
    }
    else if (actual == ')') {
        printf("Advertencia: ')' inesperado. Saltando token para evitar ciclo.\n");
        desencolar(cola); // Evitar ciclo infinito
    }
    else {
        printf("Error: Sentencia no válida comenzando con '%c'\n", actual);
        desencolar(cola); // Consumir token para evitar loop infinito
    }
}


void E() {
    if (estaVacia(cola)) {
        printf("Error: Fin de entrada inesperado en expresión\n");
        return;
    }

    printf("[DEBUG] Analizando expresión comenzando con '%c'\n", frente(cola));

    char actual = frente(cola);

    if (actual == 'a') { // Identificador
        desencolar(cola); // Consumir identificador
        if (frente(cola) == '=') {
            desencolar(cola); // Consumir '='
            E(cola); // Procesar la expresión después del '='
        }
    }
    else if (actual == '(') {
        desencolar(cola); // Consumir '('
        E(cola);
        if (frente(cola) == ')') {
            desencolar(cola); // Consumir ')'
        } else {
            printf("Error: Se esperaba ')' al cerrar expresión entre paréntesis\n");
        }
    }
    else if (actual == 'n' || actual == 'r') { // Número o literal
        desencolar(cola); // Consumir número o literal
    }
    else {
        printf("Error: Expresión inválida comenzando con '%c'\n", actual);
        desencolar(cola); // Consumir token inválido para evitar bucle
        return;
    }

    // Operadores binarios
    char operador = frente(cola);
    if (operador == '+' || operador == '-' || operador == '*' || operador == '/') {
        desencolar(cola); // Consumir operador
        E(cola); // Evaluar siguiente parte de la expresión
    }
}



void Tipo() {
    // Procesar tipos básicos (INT, FLOAT, etc.)
    char actual = frente(cola);
    
    if (actual == 't' || actual == 'f' || actual == 'g' || actual == 'y') {
        desencolar(cola); // Consumir tipo
    } else {
        printf("Error: Se esperaba tipo de dato\n");
    }
}

// Función principal para pruebas
int main() {
    cola = crearCola();

    printf("\n\n--- Prueba de carga de cola desde archivo ---\n");
    cargarColaCaracterPorCaracter(); // Cargar la cola desde el archivo
    program(); // Iniciar el análisis sintáctico

    destruirCola(cola);
    return 0;
}
