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
void Program(){
    printf("entrada a program\n");
    Func();
    otraFunc();
    printf("salida program\n");
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
    printf("entrada a func\n");
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



//5-6 TipoF
void TipoF() {
    printf("entrada a tipoF\n");
    if (frente(cola) == 'o') {  // 'o' representa VOID
        desencolar(cola);
    } else Tipo();
     // Procesar otros tipos (INT, FLOAT, etc.)
    return;
}

//7-8 Arg
void Arg() {
    // Si hay un tipo, es un argumento, sino es ε
    if (frente(cola) == 't' || frente(cola) == 'f' || 
        frente(cola) == 'g' || frente(cola) == 'y') {
        
        Tipo(); // Procesar tipo
        if (frente(cola) == 'a') {
            desencolar(cola); // Consumir identificador de argumento
        } else {
            printf("Error: Se esperaba identificador después del tipo en argumento\n");
        }
    }
    return;
    // Si no hay tipo, es ε (no se hace nada)
}

//9 cuerpo
void cuerpo() {
    // Procesar declaraciones (puede ser ε)
    listaDec();
    
    // Procesar sentencias (puede ser ε)
    listaSent();

    return;
}

//10-11 listaDec
void listaDec() {
   if(frente(cola) == 't'|| frente(cola) == 'h'|| frente(cola) == 'f'|| frente(cola) == 'g'|| frente(cola) == 'u'||frente(cola) == 'y'||
      frente(cola) == 'q'){
        D();
        listaDec();
        return;
      }else printf("Error no hay tipo\n");
    return;
}

//12 D
void D() {
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
                if (frente(cola) == ';'){
                    desencolar(cola);
                }else printf("Error: se esperaba ;\n");       
            }else printf("Error: se esperaba c\n");        
    
            if (frente(cola) == 'b'){
                desencolar(cola);
                if(frente(cola) == ';'){
                    desencolar(cola);
                    return;
                } else printf("Error: se esperaba ;\n");
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
    if (frente(cola) == 'x') {  // 'x' representa RETURN
        desencolar(cola); // Consumir 'x'
        
        if (frente(cola) == '(') {
            desencolar(cola); // Consumir '('
            valRet();
            // Si lo siguiente no es ')', hay expresión
            if (frente(cola) == ')') {
                desencolar(cola);
                if(frente(cola) == ';'){
                    desencolar(cola);
                    return;
                }else printf("Error: se esperaba ;");
            }else printf("Error: Se esperaba ')' al final de RETURN\n");
        } else printf("Error: Se esperaba '(' después de RETURN\n");
    } else printf("Error: Se esperaba 'RETURN' (átomo 'x')\n");
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
    printf("entrado a OPASIG");
    switch(frente(cola)){
        case'=': desencolar(cola);
                 break;
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
            }else printf("Error: no se encontro ;\n");
    }else printf("Error: no se encontro s\n");
}

