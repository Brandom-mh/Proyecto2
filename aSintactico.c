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
// Función para analizar <dec> → t | h | f
void dec(Cola* cola) {
    if (frente(cola) == 't' || frente(cola) == 'h' || frente(cola) == 'f') {
        desencolar(cola);
        return ;
    }
    printf("Error: Se esperaba 't', 'h' o 'f' en <dec>\n");
    return ;
}

// Función para analizar <size> → g | u | y | ξ
void size(Cola* cola) {
    if (frente(cola) == 'g' || frente(cola) == 'u' || frente(cola) == 'y') {
        desencolar(cola);
        return ;
    }
    // Caso epsilon (no se consume nada)
    return ;
}

// Función para analizar <unsig> → q | ξ
void unsig(Cola* cola) {
    if (frente(cola) == 'q') {
        desencolar(cola);
        return ;
    }
    // Caso epsilon (no se consume nada)
    return ;
}

void Tipo(Cola* cola) {
    return unsig(cola) && size(cola) && dec(cola);
}

// Función para analizar D → <Tipo>a.
void D(Cola* cola) {
    Tipo(cola); // Ahora es void, no se puede usar en if
    
    if (frente(cola) == 'a') {
        desencolar(cola);
        if (frente(cola) == ';') {
            desencolar(cola);
        } else {
            printf("Error: Falta ';' después de identificador\n");
        }
    } else {
        printf("Error: Se esperaba identificador después de tipo\n");
    }
}

// --- Función para asignaciones normales y compuestas ---
void Asig() {
    if (frente(cola) == 'a') { // identificador
        desencolar(cola);

        // Verificar el tipo de asignación
        if (frente(cola) == '=') {
            desencolar(cola);
            expresionArit();
        }
        else if (frente(cola) == '+') { // +=
            desencolar(cola);
            if (frente(cola) == '=') {
                desencolar(cola);
                expresionArit();
            } else {
                printf("Error: se esperaba '=' después de '+' en asignación compuesta\n");
            }
        }
        else if (frente(cola) == '-') { // -=
            desencolar(cola);
            if (frente(cola) == '=') {
                desencolar(cola);
                expresionArit();
            } else {
                printf("Error: se esperaba '=' después de '-' en asignación compuesta\n");
            }
        }
        else if (frente(cola) == '*') { // *=
            desencolar(cola);
            if (frente(cola) == '=') {
                desencolar(cola);
                expresionArit();
            } else {
                printf("Error: se esperaba '=' después de '*' en asignación compuesta\n");
            }
        }
        else {
            printf("Error: operador de asignación inválido\n");
        }

        // Termina con ;
        if (frente(cola) == ';') {
            desencolar(cola);
        } else {
            printf("Error: falta ';' al final de asignación\n");
        }
    } else {
        printf("Error: se esperaba identificador en asignación\n");
    }
}
// --- Función para analizar expresiones aritméticas ---
void expresionArit() {
    if (frente(cola) == 'n' || frente(cola) == 'a') {
        desencolar(cola);
    }
    else if (frente(cola) == '(') {
        desencolar(cola);
        expresionArit(); // recursión
        if (frente(cola) == ')') {
            desencolar(cola);
        } else {
            printf("Error: falta ')' en la expresión\n");
        }
    }
    else {
        printf("Error: expresión aritmética inválida\n");
        return;
    }

    // Verificar si siguen operadores
    while (frente(cola) == '+' || frente(cola) == '-' || frente(cola) == '*' ||
           frente(cola) == '/' || frente(cola) == '%') {
        desencolar(cola);
        if (frente(cola) == 'n' || frente(cola) == 'a') {
            desencolar(cola);
        }
        else if (frente(cola) == '(') {
            desencolar(cola);
            expresionArit();
            if (frente(cola) == ')') {
                desencolar(cola);
            } else {
                printf("Error: falta ')' en subexpresión\n");
            }
        }
        else {
            printf("Error: falta operando después del operador\n");
            break;
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


void Tipo() {
    // Procesar tipos básicos (INT, FLOAT, etc.)
    char actual = frente(cola);
    
    if (actual == 't' || actual == 'f' || actual == 'g' || actual == 'y') {
        desencolar(cola); // Consumir tipo
    } else {
        printf("Error: Se esperaba tipo de dato\n");
    }
}
void E(){
    T();
    EP(); 
}

void EP(){
    if(frente(cola) == '+'){
        desencolar(cola);
        T();
        EP();
    } else printf("Error: Se esperaba '+'\n");
    
    if(frente(cola) == '-'){
        desencolar(cola);
        T();
        EP();
    } else {
        printf("Error: Se esperaba '-'\n");
        return;
    }

    if (frente(cola) == ')')
    {
        return; // Fin de la expresión
    } else printf("Error: Se esperaba ')'\n");
    
}

void T(){
    F();
    TP(); 
}

void TP(){
    if(frente(cola) == '*'){
        desencolar(cola);
        F();
        TP();
    } else printf("Error: Se esperaba '*'\n");
    
    if(frente(cola) == '/'){
        desencolar(cola);
        F();
        TP();
    } else {
        printf("Error: Se esperaba '/'\n");
        return;
    }

    if (frente(cola) == '%')
    {
        F();
        TP();
    } else printf("Error: Se esperaba %% \n");

    if(frente(cola) == '*'){
        desencolar(cola);
        if (frente(cola) == '*') {
            desencolar(cola); 
        } else 
            printf("Error: Se esperaba '*' después de expresión\n");
        
    } else 
        printf("Error: Se esperaba '*'\n");

    if (frente(cola) == '+' || frente(cola) == '-'){
        return;
    } else printf("Error se esperaba + o -\n");
}

void F(){
    if(frente(cola) == '('){
        desencolar(cola);
        E();
        if(frente(cola) == ')'){
            desencolar(cola);
        } else printf("Error se esperaba )\n");
    } else printf("Error se esperaba (\n");

    if(frente(cola) == 'a'){
        desencolar(cola);
        G();
    } else printf("Error se esperaba a\n");

    if(frente(cola) == 'n'){
        desencolar(cola);
    }else printf("Error: se esperaba n\n");

    if(frente(cola) == 'r'){
        desencolar(cola);
    }else printf("Error: se esperaba r\n");
}

void G(){
    if(frente(cola) == 'l'){
        desencolar(cola);
    }else printf("Error: se esperaba l\n");

    if(frente(cola) == 'm'){
        desencolar(cola);
    }else printf("Error: se esperaba m\n");

    if(frente(cola) == '*' || frente(cola) == '/' || frente(cola) == '%'){
        return;
    }else printf("Error: se esperaba * / %%\n");
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


