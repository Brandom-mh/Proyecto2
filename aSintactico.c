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

//1 Program
void Program(){
    cargarColaCaracterPorCaracter();
    Func();
    otraFunc();
    return;
}

//2-3 otraFunc
void otraFunc(){
    Func();
    otraFunc();
    return;
}

//4 Func
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

//5-6 TipoF
void TipoF() {
    if (frente(cola) == 'o') {  // 'o' representa VOID
        desencolar(cola);
    } else {
        Tipo(cola); // Procesar otros tipos (INT, FLOAT, etc.)
    }
}

//7-8 Arg
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

//9 cuerpo
void cuerpo() {
    // Procesar declaraciones (puede ser ε)
    listaDec(cola);
    
    // Procesar sentencias (puede ser ε)
    listaSent(cola);
}

//10-11 listaDec
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

//12 D
void D() {
        Tipo();
        if (frente(cola) == 'a') {
            desencolar(cola);
            if (frente(cola) == '.') {
                desencolar(cola);
            } else {
                printf("Error: Falta '.' después de identificador\n");
            }
        } else {
            printf("Error: Se esperaba una a\n");
        }
}
//13 tipo
void Tipo() {
    unsig();
    Size();
    dec();
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
    if (frente(cola) == 't' || frente(cola) == 'h' || frente(cola) == 'f') {
        desencolar(cola);
        return ;
    }
    else printf("Error: Se esperaba 't', 'h' o 'f' en <dec>\n");
    return;
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
//31-32 listaSent
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
void ELSE(){
    if(frente(cola)=='e'){
        desencolar(cola);
        if(frente (cola)=='{'){
            desencolar(cola);
            listaSent();
            if (frente (cola)=='}'){
                desencolar(cola);
            }else printf("Error: se esperaba } \n");  
        }else printf("Error: se esperaba {\n");  
    }else printf("Error: se esperaba e \n");  

    if( frente (cola)== 'a' || frente (cola)== 'd'|| frente (cola)== 'i' || frente (cola)== 'k'|| frente (cola)== 'f' || frente (cola)== 'r' ){
        return;
    } 
}
//41 FOR
void For() {
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
//42 Ret
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
                    if(frente(cola)=='.'){
                        desencolar(cola);
                    } else printf("Error: se esperaba . \n"); 
                } else printf("Error: se esperaba b \n"); 
            } else printf("Error: se esperaba ) \n"); 
        }else printf("Error: se esperaba n \n"); 
    }else printf("Error: se esperaba z \n"); 
}
//49 E
void E(){
    T();
    EP(); 
}
//50-52 E'
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
//53 T
void T(){
    F();
    TP(); 
}
//54-57 T'
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

//58-62 F
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

//65-67 G
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
//68 Asig
void Asig() {
    if (frente(cola) == 'a') { // identificador
        desencolar(cola);
        opAsig();
        if(frente(cola)=='('||frente(cola)=='a'||frente(cola)=='n'||frente(cola)=='r'||frente(cola)=='l'||frente(cola)=='m')
        E();
    else if (frente(cola)=='#')
        Cadena();

    }
}
// 69 opAsig
void opAsig(){
    switch(frente(cola)){
        case'#': desencolar(cola);
                break;
        case';': desencolar(cola);
                break;
        case'$': desencolar(cola);
                break;
        case',': desencolar(cola);
                break;
        case'?': desencolar(cola);
                break;
        case':': desencolar(cola);
                break;
        case'^': desencolar(cola);
                break;
        case'@': desencolar(cola);
                break;
        case'<': desencolar(cola);
                break;
        case'>': desencolar(cola);
                break;
        default: printf("Error: operador no encontrado \n");
        break;
    }
}

//70 cadena 
void Cadena(){
    if(frente(cola)=='s'){
        desencolar(cola);
            if(frente(cola)==';'){
                desencolar(cola);
            }else ("Error: no se encontro ;\n");
    }else ("Error: no se encontro s\n");
}