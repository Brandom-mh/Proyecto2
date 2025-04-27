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
//2-3 otraFunc
//4 Func
//5-6 TipoF
//7-8 Arg
//9 cuerpo
//10-11 listaDec
//12 D
//13 tipo
//14-15 unsig
//16-19 size
//20-22 dec
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
//39-40 ELSE
//41 FOR
//42 Ret
//43-44 valRet
//45 Switch
//46-47 listaCase
//48 case
//49 E
//50-52 E'
//53 T
//54-57 T'
//58-62 F
//63-64 F'
//65-67 G
//68 Asig


