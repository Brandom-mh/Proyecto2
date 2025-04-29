#include <stdio.h>
#include <string.h>
#include "cola.h"

Cola *cola;

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
void dec();
void Sent();
void listaSent();
void doW();
void exprLog();
void opLog();
void IF(); 
void ELSE();
void For();
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
void G();
void Asig();
void opAsig();
void Cadena();
void Valor();

void cargarColaCaracterPorCaracter() {
    cola = crearCola();
    char *nombreArchivo = "salida.txt"; // Nombre del archivo a leer
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
    mostrarCola(cola);
}

//1 Program
void Program() {
    printf("entrada a program\n");
    
    // Procesar funciones mientras haya tokens
    while(!estaVacia(cola)) {
        Func();
        otraFunc();
    }
    
    printf("salida program\n");
}

//2-3 otraFunc
void otraFunc() {
    // Solo procesar si hay tokens y es una función
    if(!estaVacia(cola) && 
       (frente(cola) == 'o' || frente(cola) == 'q' || 
        frente(cola) == 'g' || frente(cola) == 'u' ||
        frente(cola) == 'y' || frente(cola) == 't' || 
        frente(cola) == 'h' || frente(cola) == 'f')) {
        Func();
        otraFunc();
        return;
    }
    // No es un error si no hay más funciones
}

//4 Func
void Func() {
    printf("entrada a func\n");
    if(frente(cola) == 'o' || frente(cola) == 'q' || frente(cola) == 'g' || frente(cola) == 'u' ||
       frente(cola) == 'y' || frente(cola) == 't' || frente(cola) == 'h' || frente(cola) == 'f' ){
            TipoF();
            if(frente(cola)== 'a'){
                desencolar(cola);
                if(frente(cola) == '('){
                    desencolar(cola);
                    Arg();
                    if(frente(cola) == ')'){
                        desencolar(cola);
                        if(frente(cola) == '{'){
                            desencolar(cola);
                            cuerpo();
                            if(frente(cola) == '}'){
                                desencolar(cola);
                                return;
                            }else printf("Error: se esperaba ]");
                        }else printf("Error: se esperaba [");
                    }else printf("Error: se esperaba }");
                }else printf("Error: se esperaba {");
            }else printf("Error: se esperaba a");
            printf("salida func\n");
            return;
       }
}



//5-6 TipoF
void TipoF() {
    if (frente(cola) == 'o') {  // 'o' representa VOID
        desencolar(cola);
        return;
    } else Tipo();
     // Procesar otros tipos (INT, FLOAT, etc.)
    return;
}

//7-8 Arg
void Arg() {
    // Si hay un tipo, es un argumento, sino es ε
    if (frente(cola) == 'q' || frente(cola) == 'g' || frente(cola) == 'u' || 
        frente(cola) == 'y' || frente(cola) == 't'|| frente(cola) == 'h' || frente(cola) == 'f') {
        
        Tipo(); // Procesar tipo
        if (frente(cola) == 'a') {
            desencolar(cola); // Consumir identificador de argumento
            return;
        } else {
            printf("Error: Se esperaba identificador después del tipo en argumento\n");
        }
    }
    if(frente(cola) == '}')
        return;
    // Si no hay tipo, es ε (no se hace nada)
}

//9 cuerpo
void cuerpo() {
    if (frente(cola) == 'q' || frente(cola) == 'g' || frente(cola) == 'u' || 
        frente(cola) == 'y' || frente(cola) == 't'|| frente(cola) == 'h' || frente(cola) == 'f'){
            listaDec();
            listaSent();
            return;
        }
    return;
}

//10-11 listaDec
void listaDec() {
    // Mientras encontremos tipos al frente, procesamos declaraciones
    while(frente(cola) == 't' || frente(cola) == 'h' || frente(cola) == 'f' || 
          frente(cola) == 'g' || frente(cola) == 'u' || frente(cola) == 'y' ||
          frente(cola) == 'q') {
        D();
    }
    
    // Sincronización: si encontramos el inicio de una sentencia o fin de bloque
    if(frente(cola) == 'a' || frente(cola) == 'd' || frente(cola) == 'i' ||
       frente(cola) == 'k' || frente(cola) == 'v' || frente(cola) == 'r' ||
       frente(cola) == '}' || frente(cola) == 'b') {
        return;  // Transición a listaSent o fin de bloque
    }
    
    // Manejo de error más robusto
    printf("Error: Token inesperado '%c' en listaDec\n", frente(cola));
    
    // Mecanismo de recuperación: avanzar hasta encontrar un token válido
    while(!estaVacia(cola) && 
          !(frente(cola) == 'a' || frente(cola) == 'd' || frente(cola) == 'i' ||
            frente(cola) == 'k' || frente(cola) == 'v' || frente(cola) == 'r' ||
            frente(cola) == '}' || frente(cola) == 'b')) {
        desencolar(cola);
    }
}

//12 D
void D() {
    if(frente(cola) == 't'|| frente(cola) == 'h'|| frente(cola) == 'f'|| 
       frente(cola) == 'g'|| frente(cola) == 'u'||frente(cola) == 'y'|| frente(cola) == 'q'){
            Tipo();
            if (frente(cola) == 'a') {
                desencolar(cola);
                if (frente(cola) == ';') {
                    desencolar(cola);
                } else {
                    printf("Error: Falta ';' después de identificador\n");
                }
            } else {
                printf("Error: Se esperaba una a\n");
            }
    }
}
//13 tipo checar otra vez
void Tipo() {
    if(frente(cola) =='q')
        unsig();
    else if(frente(cola) =='g'|| frente(cola) =='u'|| frente(cola) =='y')    
        Size();
    else if(frente(cola) =='t'|| frente(cola) =='h'|| frente(cola) =='f')    
        dec();
    return;
}
//14-15 unsig
void unsig() {
    if (frente(cola) == 'q') {
        desencolar(cola);
        return;
    }
    // Caso epsilon (no se consume nada)
    return;
}
//16-19 size
void Size() {
    if (frente(cola) == 'g' || frente(cola) == 'u' || frente(cola) == 'y') {
        desencolar(cola);
        return;
    }
    // Caso epsilon (no se consume nada)
    return ;
}
//20-22 dec
void dec() {
    mostrarCola(cola);
    switch (frente(cola)) {
        case 't': // Producción <dec> → t
            desencolar(cola);
            break;

        case 'h': // Producción <dec> → h
            desencolar(cola);
            break;

        case 'f': // Producción <dec> → f
            desencolar(cola);
            break;

        default: // Caso de error
            printf("Error: Se esperaba 't', 'h' o 'f' en <dec>\n");
            break;
    }
}
//23-30 Sent
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
    
        case 'v': // for
            For();
            break;
    
        case 'x': // return
            Ret();
            break;
        case 'c': // return
            desencolar(cola);
            if(frente(cola)== ';')
                desencolar(cola);
            break;
        case 'b':
            desencolar(cola);
            if(frente(cola)== ';')
                desencolar(cola);
            break;
        default: // Caso no reconocido
            printf("Error: Token inesperado '%c'\n", frente(cola));
            break;
    }
        
    }
//31-32 listaSent
void listaSent() {
    // Usamos while en lugar de recursión para evitar desbordamiento de pila
    while(frente(cola) == 'a' || frente(cola) == 'd' || frente(cola) == 'i' ||
          frente(cola) == 'k' || frente(cola) == 'v' || frente(cola) == 'x' ||
          frente(cola) == 'c' || frente(cola) == 'b') {
        Sent();
    }

    // Verificamos terminadores válidos
    if(frente(cola) == '}' || frente(cola) == ']' || frente(cola) == 'b' || 
       frente(cola) == 'e' || frente(cola) == 'z') {
        return;
    }

    // Manejo de errores mejorado
    if(!estaVacia(cola)) {
        printf("Error en listaSent: Token inesperado '%c'. Se esperaba sentencia o terminador\n", 
               frente(cola));
        
        // Mecanismo de recuperación: avanzar hasta encontrar un terminador
        while(!estaVacia(cola)) {
            if(frente(cola) == '}' || frente(cola) == ']' || frente(cola) == 'b' ||
               frente(cola) == 'e' || frente(cola) == 'z') {
                return;
            }
            desencolar(cola);
        }
    }
}
//33 doW
void doW() {
    if (frente(cola) == 'd') {
        desencolar(cola);
        if (frente(cola) == '{') {
            desencolar(cola);
            listaSent(cola);
            if (frente(cola) == '}') {
                desencolar(cola);
                if (frente(cola) == 'w') {
                    desencolar(cola);
                    if (frente(cola) == '(') {
                        desencolar(cola);
                        exprLog(cola);
                        if (frente(cola) == ')') {
                            desencolar(cola);
                        } else {
                            printf("Error: falta ')' después de exprLog\n");
                        }
                    } else {
                        printf("Error: falta '(' después de while\n");
                    }
                } else {
                    printf("Error: falta 'while' después de bloque do\n");
                }
            } else {
                printf("Error: falta '}' en do\n");
            }
        } else {
            printf("Error: falta '{' después de do\n");
        }
    } else {
        printf("Error: se esperaba 'do'\n");
    }
}


//34-35 exprLog
void exprLog() {
    // Caso 1: Negación (!)
    if(frente(cola) == '!') {
        desencolar(cola);
        if(frente(cola) != '(') {
            printf("Error: Se esperaba '(' después de '!'\n");
            return;
        }
        desencolar(cola);
        exprLog(); // Permitir expresión lógica dentro
        if(frente(cola) != ')') {
            printf("Error: Se esperaba ')' al final de expresión negada\n");
            return;
        }
        desencolar(cola);
        return;
    }

    // Caso 2: Expresión entre paréntesis
    if(frente(cola) == '(') {
        desencolar(cola);
        exprLog(); // Procesar expresión interior
        
        if(frente(cola) != ')') {
            printf("Error: Se esperaba ')'\n");
            return;
        }
        desencolar(cola);

        // Posible operador lógico
        if(frente(cola) == '&' || frente(cola) == '|') {
            opLog();
            exprLog(); // Procesar siguiente expresión
        }
        return;
    }

    // Caso 3: Identificador simple
    if(frente(cola) == 'a') {
        desencolar(cola);
        return;
    }

    // Caso 4: Valor numérico o constante
    if(frente(cola) == 'n' || frente(cola) == 'r') {
        desencolar(cola);
        return;
    }

    printf("Error: Expresión lógica mal formada. Token inesperado: '%c'\n", frente(cola));
}
//36-37 opLog
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
//38 IF
void IF(){
    if (frente (cola) == 'i'){
        desencolar(cola);
        if(frente (cola)=='('){
            desencolar(cola);
            exprLog();
            if(frente(cola)== ')'){
                desencolar(cola);
                if(frente(cola)=='{'){
                    desencolar(cola);
                    listaSent();
                    if (frente(cola)=='}'){
                    desencolar(cola);
                    ELSE();
                    return;
                    }else printf("Error: se esperaba }\n");   
                } else printf("Error: se esperaba {\n");  
            }else printf("Error: se esperaba )\n");  
        } else printf("Error: se esperaba (\n");  
    } else printf("Error: se esperaba i \n");  
}
//39-40 ELSE
void ELSE() {
    // El 'else' es opcional, solo procesar si existe
    if(!estaVacia(cola) && frente(cola) == 'e') {
        desencolar(cola);  // Consumir 'e' (else)
        
        if(estaVacia(cola)) {
            printf("Error: Inesperado fin de entrada después de 'else'\n");
            return;
        }
        
        // Procesar bloque else
        if(frente(cola) == '{') {
            desencolar(cola);  // Consumir '{'
            
            listaSent();  // Procesar sentencias dentro del else
            
            if(estaVacia(cola)) {
                printf("Error: Fin de entrada inesperado, se esperaba '}'\n");
                return;
            }
            
            if(frente(cola) == '}') {
                desencolar(cola);  // Consumir '}'
            } else {
                printf("Error: Se esperaba '}' para cerrar el bloque else\n");
                // Mecanismo de recuperación: buscar '}' o fin de bloque
                while(!estaVacia(cola) && frente(cola) != '}' && frente(cola) != ']' && frente(cola) != 'b') {
                    desencolar(cola);
                }
                if(!estaVacia(cola) && frente(cola) == '}') {
                    desencolar(cola);
                }
            }
        } else {
            printf("Error: Se esperaba '{' después de 'else'\n");
        }
    }
    // Si no hay 'e' (else), simplemente retornar sin error
}
//41 FOR
void For() {

    if (frente(cola) != 'v') {
        printf("Error: Se esperaba 'FOR' (átomo 'v')\n");
        return;
    }
    desencolar(cola);
    
    if (frente(cola) != '(') {
        printf("Error: Se esperaba '(' después de FOR\n");
        return;
    }
    desencolar(cola); // Mover '(' a temp

    // Procesar expresión aritmética
    E(); // Procesar la expresión aritmética

    // Verificar paréntesis de cierre ')'
    if (frente(cola) != ')') {
        printf("Error: Se esperaba ')' después de la expresión en FOR\n");
        return;
    }
    desencolar(cola); // Mover ')' a temp

    // Verificar llave de apertura '{'
    if (frente(cola) != '{') {
        printf("Error: Se esperaba '{' después de FOR(expresión)\n");
        return;
    }
    desencolar(cola); // Mover '{' a temp

    // Procesar lista de sentencias
    listaSent(); // Procesar las sentencias

    // Verificar llave de cierre '}'
    if (frente(cola) != '}') {
        printf("Error: Se esperaba '}' al final del bloque FOR\n");
        return;
    }
    desencolar(cola); // Mover '}' a temp

    printf("FOR analizado correctamente\n");
    return;

}
//42 Ret
void Ret() {
    // Verificar si hay suficiente tokens para procesar
    if(estaVacia(cola)) {
        printf("Error: Fin inesperado de entrada, se esperaba 'return'\n");
        return;
    }

    // Verificar token de return ('x')
    if(frente(cola) != 'x') {
        printf("Error: Se esperaba 'return' (token 'x')\n");
        return;
    }
    desencolar(cola); // Consumir 'x'

    // Manejar return sin valor
    if(frente(cola) == ';') {
        desencolar(cola);
        return;
    }

    // Manejar return con valor
    if(frente(cola) != '(') {
        printf("Error: Se esperaba '(' o ';' después de 'return'\n");
        return;
    }
    desencolar(cola); // Consumir '('

    valRet(); // Procesar valor de retorno

    if(estaVacia(cola)) {
        printf("Error: Fin inesperado de entrada, se esperaba ')'\n");
        return;
    }

    if(frente(cola) != ')') {
        printf("Error: Se esperaba ')' después de expresión de retorno\n");
        // Recuperación: buscar ')' o ';'
        while(!estaVacia(cola) && frente(cola) != ')' && frente(cola) != ';') {
            desencolar(cola);
        }
        if(!estaVacia(cola) && frente(cola) == ')') {
            desencolar(cola);
        }
    } else {
        desencolar(cola); // Consumir ')'
    }

    if(estaVacia(cola)) {
        printf("Error: Fin inesperado de entrada, se esperaba ';'\n");
        return;
    }

    if(frente(cola) != ';') {
        printf("Error: Se esperaba ';' al final de 'return'\n");
        return;
    }
    desencolar(cola); // Consumir ';'
}
//43-44 valRet
void valRet(){
    if(frente(cola) == '('|| frente(cola) == 'a'|| frente(cola) == 'n'|| 
       frente(cola) == 'r'|| frente(cola) == 'l'|| frente(cola) == 'm'){
        E();
        return;
       }

    if(frente(cola) == ')')
       return;
}
//45 Switch
void Switch(){
    if(frente(cola)=='k'){
        desencolar(cola);
        if(frente (cola)=='('){
            desencolar(cola);
            if (frente (cola)=='a'){
                desencolar(cola);
                if (frente(cola)==')'){
                    desencolar(cola);
                    if(frente(cola)=='{'){
                        desencolar(cola);
                        listaCase();
                        if(frente(cola)=='}'){
                            desencolar(cola);
                            return;
                        } else printf("Error: se esperaba } \n");  
                    }else printf("Error: se esperaba { \n");  
                } else printf("Error: se esperaba ) \n");  
            }else printf("Error: se esperaba a \n");  
        }else printf("Error: se esperaba (\n");  
    }else printf("Error: se esperaba k \n");  
}
//46-47 listaCase
void  listaCase(){
    if (frente(cola)=='z'){
        Case();
        listaCase();
    }
    if(frente(cola)== '}'){
        return;
    }
}
//48 case
void Case(){
    if (frente(cola)=='z'){
        desencolar(cola);
        if(frente(cola)=='n'){
            desencolar(cola);
            if(frente(cola)==')'){
                desencolar(cola);
                listaSent();
                if(frente(cola)=='b'){
                    desencolar(cola);
                    if(frente(cola)==';'){
                        desencolar(cola);
                    } else printf("Error: se esperaba ; \n"); 
                } else printf("Error: se esperaba b \n"); 
            } else printf("Error: se esperaba ) \n"); 
        }else printf("Error: se esperaba n \n"); 
    }else printf("Error: se esperaba z \n"); 
}
//49 E
void E(){
    if(frente(cola)=='('|| frente(cola)=='a'||frente(cola)=='n'||frente(cola)=='r'){
        T();
        EP(); 
    }else printf("Error no se econtro E\n");

}
//50-52 E'
void EP(){
    if(frente(cola) == '+'){
        desencolar(cola);
        T();
        EP();
    }
    else if(frente(cola) == '-'){
        desencolar(cola);
        T();
        EP();
    }
    return;
    // Caso epsilon
    // No es necesario imprimir error si no hay operador
}
 
//53 T
void T(){
    if(frente(cola)=='('|| frente(cola)=='a'||frente(cola)=='n'||frente(cola)=='r'){
        F();
        TP(); 
        return;
    }
}
//54-57 T'
void TP(){
    if(frente(cola) == '*'){
        desencolar(cola);
        F();
        TP();
        return;
    }
    else if(frente(cola) == '/'){
        desencolar(cola);
        F();
        TP();
        return;
    }
    else if(frente(cola) == '%'){
        desencolar(cola);
        F();
        TP();
        return;
    }
    // Caso epsilon
}

//58-62 F
void F() {
    if(estaVacia(cola)) {
        printf("Error (F): Cola vacía, se esperaba expresión\n");
        return;
    }

    char token = frente(cola);
    
    // Caso 1: Expresión entre paréntesis
    if(token == '(') {
        desencolar(cola);
        E(); // Procesar expresión interior
        
        if(estaVacia(cola)) {
            printf("Error (F): Fin inesperado, se esperaba ')'\n");
            return;
        }
        
        if(frente(cola) == ')') {
            desencolar(cola);
            return;
        } else {
            printf("Error (F): Se esperaba ')'\n");
            // Recuperación: buscar ')' o fin de expresión
            while(!estaVacia(cola) && frente(cola) != ')' && 
                  frente(cola) != '+' && frente(cola) != '-' &&
                  frente(cola) != '*' && frente(cola) != '/' &&
                  frente(cola) != ';') {
                desencolar(cola);
            }
            if(!estaVacia(cola) && frente(cola) == ')') {
                desencolar(cola);
            }
            return;
        }
    }
    // Caso 2: Identificador
    else if(token == 'a') {
        desencolar(cola);
        G();
        return;
    }
    // Caso 3: Número
    else if(token == 'n') {
        desencolar(cola);
        return;
    }
    // Caso 4: Valor real
    else if(token == 'r') {
        desencolar(cola);
        return;
    }

    printf("Error (F): Token inesperado '%c'. Se esperaba '(', 'a', 'n' o 'r'\n", token);
    
    // Mecanismo de recuperación
    while(!estaVacia(cola) && frente(cola) != '+' && frente(cola) != '-' &&
          frente(cola) != '*' && frente(cola) != '/' && frente(cola) != ')' &&
          frente(cola) != ';') {
        desencolar(cola);
    }
}

//65-67 G
void G(){
    if(frente(cola) == 'l'){
        desencolar(cola);
        return;
    }else printf("Error: se esperaba l\n");

    if(frente(cola) == 'm'){
        desencolar(cola);
        return;
    }else printf("Error: se esperaba m\n");

    if(frente(cola) == '*' || frente(cola) == '/' || frente(cola) == '%'){
        return;
    }else printf("Error: se esperaba * / %%\n");
}
//68 Asig
void Asig() {
    if(estaVacia(cola)) return;
    
    if(frente(cola) == 'a') {
        desencolar(cola); // Consume identificador
        
        // Verificación especial para casos como 'aax'
        if(!estaVacia(cola) && frente(cola) == 'a') {
            // Posible llamada a función (aa como identificador)
            desencolar(cola); // Consume segundo 'a'
            if(!estaVacia(cola) && frente(cola) == 'x') {
                // Manejar como posible return
                Ret();
                return;
            }
        }
        
        // Procesamiento normal de asignación
        opAsig();
        Valor();
        
        if(!estaVacia(cola) && frente(cola) == ';') {
            desencolar(cola);
        } else {
            printf("Error (Asig): Falta ';' al final\n");
        }
    }
}
// 69 opAsig
void opAsig() {
    // Verificar cola vacía
    if(estaVacia(cola)) {
        printf("Error (opAsig): Cola vacía, se esperaba operador\n");
        return;
    }

    printf("Entrada a OPASIG\n"); // Mensaje depuración mejorado

    // Operadores de asignación válidos (simplificado)
    char operador = frente(cola);
    switch(operador) {
        // Asignación básica y compuesta
        case '=': 
        case '+': case '-': case '*': case '/': case '%': 
        case '&': case '|': case '^': case '<': case '>':
        case '#': case '$':  // Mantengo algunos de tus operadores originales
            desencolar(cola);
            
            // Verificar si es operador compuesto (ej: '+=')
            if(!estaVacia(cola) && frente(cola) == '=') {
                desencolar(cola);
            }
            break;
            
        default:
            printf("Error (opAsig): Operador '%c' no válido\n", operador);
            // Mecanismo de recuperación: avanzar hasta próximo ';'
            while(!estaVacia(cola) && frente(cola) != ';') {
                desencolar(cola);
            }
            break;
    }
}

void Valor(){
    if(frente(cola) == 'n' || frente(cola) == 's'){
        desencolar(cola);
    }
    else printf("Error: falta para asignar");

}

//70 cadena 
void Cadena(){
    if(frente(cola)=='s'){
        desencolar(cola);
            if(frente(cola)==';'){
                desencolar(cola);
            }else printf("Error: no se encontro ;\n");
    }else printf("Error: no se encontro s\n");
}