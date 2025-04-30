#include <stdio.h>
#include <string.h>
#include "cola.h"
Cola *cola;  // Cola global para almacenar los caracteres del archivo

// Declaraciones de funciones
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


// Función que carga caracteres desde archivo a la cola
void cargarColaCaracterPorCaracter() {
    
    // Crea una nueva cola vacía
    cola = crearCola();
    
    // Nombre del archivo de entrada que contiene los tokens
    char *nombreArchivo = "salida.txt"; 
    
    // Abre el archivo en modo lectura
    FILE *archivo = fopen(nombreArchivo, "r"); 
    
    // Verifica si el archivo se abrió correctamente
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        return;
    }

    char c; // Variable para almacenar cada carácter leído
    int dentroDeCorchetes = 0; // Bandera que indica si estamos dentro de corchetes

    // Lee el archivo carácter por carácter hasta el final del archivo (EOF)
    while ((c = fgetc(archivo)) != EOF) {
        // Si encontramos el carácter '[', activamos la bandera
        if (c == '[') {
            dentroDeCorchetes = 1; // Empezamos a leer contenido dentro de corchetes
        } 
        // Si encontramos el carácter ']', desactivamos la bandera y salimos del bucle
        else if (c == ']') {
            dentroDeCorchetes = 0; // Terminamos de leer contenido dentro de corchetes
            break; 
        } 
        // Si estamos dentro de corchetes, encolamos el carácter
        else if (dentroDeCorchetes) {
            encolar(cola, c); 
        }
    }

    // Cerrar el archivo después de leerlo
    fclose(archivo); 
    
    // Mostrar el contenido de la cola 
    mostrarCola(cola);
}

//Función principal que procesa las funciones del programa.
void Program() {

    // Carga los caracteres/tokens desde el archivo a la cola
    cargarColaCaracterPorCaracter();
    printf("entrada a program\n");
    
    // Procesa todas las funciones mientras haya elementos en la cola
    while(!estaVacia(cola)) {
        Func();      // Analiza una función
        otraFunc();  // Verifica si hay más funciones
    }

    printf("salida program\n");
}

//Función que verifica y procesa posibles funciones adicionales
void otraFunc() {
    // Verifica si la cola no está vacía y si el próximo token es el inicio de una declaración de función
    if( !estaVacia(cola) && (frente(cola) == 'o' || frente(cola) == 'q' || frente(cola) == 'g' || frente(cola) == 'u' ||
       frente(cola) == 'y' || frente(cola) == 't' || frente(cola) == 'h' || frente(cola) == 'f') ){
        // Procesar la función encontrada
        Func();
        // Llamada recursiva para verificar si hay más funciones
        otraFunc();
        return;
    }
    
    return;
}

// Analiza la estructura de una declaración de función completa
void Func() {
    // Verifica si hay tokens y si el primero es un tipo de función válido
    if(!estaVacia(cola) && (frente(cola) == 'o' || frente(cola) == 'q' || frente(cola) == 'g' || frente(cola) == 'u' ||
       frente(cola) == 'y' || frente(cola) == 't' || frente(cola) == 'h' || frente(cola) == 'f') ){
            TipoF(); //Procesar el tipo de retorno de la función
            if(frente(cola)== 'a'){ //Verifica el nombre de la función
                desencolar(cola);
                if(frente(cola) == '('){ //Verificar apertura de parámetros '('
                    desencolar(cola);
                    Arg(); //Procesar los argumentos de la función
                    if(frente(cola) == ')'){ //Verifica cierre de parámetros ')'
                        desencolar(cola);
                        if(frente(cola) == '{'){ //Verifica apertura de cuerpo '{'
                            desencolar(cola);
                            cuerpo(); //Procesa el cuerpo de la función
                            if(frente(cola) == '}'){ //Verifica cierre de cuerpo '}'
                                desencolar(cola);
                                return;
                            }else printf("Error: se esperaba }");
                        }else printf("Error: se esperaba {");
                    }else printf("Error: se esperaba )");
                }else printf("Error: se esperaba (");
            }else printf("Error: se esperaba a");
            printf("salida func\n");
            return;
       }
}



//Analiza el tipo de retorno de una función
void TipoF() {
    //Verificar si el tipo es void (representado por 'o')
    if (frente(cola) == 'o') {  
        desencolar(cola); // Consume el token 'o'
        return;
    } else Tipo(); // Procesa otros tipos (INT, FLOAT, etc.)
    return;
}

//Analiza los argumentos/parámetros de una función
void Arg() {
    // // Verificar si hay un tipo de parámetro
    if (frente(cola) == 'q' || frente(cola) == 'g' || frente(cola) == 'u' || 
        frente(cola) == 'y' || frente(cola) == 't'|| frente(cola) == 'h' || frente(cola) == 'f') {
        
        Tipo(); //Procesa el tipo del parámetro
        if (frente(cola) == 'a') { //Después del tipo debe venir un identificador
            desencolar(cola); 
            return;
        } else {
            printf("Error: Se esperaba identificador después del tipo en argumento\n");
        }
    }
    //Si encontramos '}', significa fin de parámetros
    if(frente(cola) == '}')
        return; // Si no hay tipo, es ε (no se hace nada)
}

//Analiza el cuerpo de una función
void cuerpo() {
    // Verifica si hay contenido en el cuerpo (declaraciones o sentencias)
    if (!estaVacia(cola) &&(frente(cola) == 'q' || frente(cola) == 'g' || frente(cola) == 'u' || 
        frente(cola) == 'y' || frente(cola) == 't'|| frente(cola) == 'h' || frente(cola) == 'f' ||
        frente(cola) == 'a' || frente(cola) == 'd' || frente(cola) == 'i' || frente(cola) == 'k'||
        frente(cola) == 'v' || frente(cola) == 'x' || frente(cola) == 'c' || frente(cola) == 'b')){
            listaDec(); //Procesa todas las declaraciones locales
            listaSent(); //Procesa todas las sentencias ejecutables
            return;
        }
    // Caso para cuerpo vacío (ε)
    return;
}

// Analiza una lista de declaraciones de variables locales en una función.
void listaDec() {
   // Verifica si el token actual es un tipo válido para declaraciones
   if(frente(cola) == 't'|| frente(cola) == 'h'|| frente(cola) == 'f'|| frente(cola) == 'g'|| frente(cola) == 'u'||frente(cola) == 'y'||
      frente(cola) == 'q'){
       // Procesa una declaración individual
        D();
        // Llamada recursiva para procesar más declaraciones
        listaDec();
        return;
      }
    // Casos donde termina la lista de declaraciones
    if(frente(cola) =='a' || frente(cola) =='d' || frente(cola) =='i' ||
       frente(cola) =='k' || frente(cola) =='f' || frente(cola) =='x' )
        return;
}

// Procesa una declaración de variable individual
void D() {
    // Verifica si el token actual es un tipo válido para declaración
    if(frente(cola) == 't'|| frente(cola) == 'h'|| frente(cola) == 'f'|| 
       frente(cola) == 'g'|| frente(cola) == 'u'||frente(cola) == 'y'|| frente(cola) == 'q'){
            Tipo(); //Procesa el tipo de la variable
            if (frente(cola) == 'a') { //Verifica identificador
                desencolar(cola);
                if (frente(cola) == ';') { //Verifica terminación con punto y coma
                    desencolar(cola);
                } else {
                    printf("Error: Falta ';' después de identificador\n");
                }
            } 
    }
}
//Clasifica y procesa los diferentes tipos de datos del lenguaje
void Tipo() {
    // Caso para tipos con modificador 'unsigned' ('q')
    if(frente(cola) =='q')
        unsig();
    // Caso para tipos con modificador de tamaño (short/long)    
    else if(frente(cola) =='g'|| frente(cola) =='u'|| frente(cola) =='y')    
        Size();
    // Caso para tipos decimales básicos    
    else if(frente(cola) =='t'|| frente(cola) =='h'|| frente(cola) =='f')    
        dec();
    return;
}
// Procesa el modificador 'unsigned' del lenguaje.
void unsig() {
    // Verifica si el token actual es 'q' (unsigned)
    if (frente(cola) == 'q') {
        desencolar(cola);
        return;
    }
    // Caso epsilon (no se consume nada)
    return;
}
// Procesa los modificadores de tamaño de tipos
void Size() {
    // Verifica si el token actual es un modificador de tamaño válido
    if (frente(cola) == 'g' || frente(cola) == 'u' || frente(cola) == 'y') {
        desencolar(cola);
        return;
    }
    // Caso epsilon (no se consume nada)
    return ;
}

//Procesa los tipos de datos fundamentales del lenguaje
void dec() {
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
// Procesa diferentes tipos de sentencias del lenguaje
void Sent(){
    
    switch (frente(cola)) {
        case 'a': // Asignación
            Asig(); // Procesa asignación completa
            break;
    
        case 'd': // do-while
            doW(); // Procesa bucle do-while
            break;
    
        case 'i': // if
            IF(); // Procesa condicional if
            break;
    
        case 'k': // switch
            Switch(); // Procesa estructura switch
            break;
    
        case 'v': // for
            For(); // Procesa bucle for
            break;
    
        case 'x': // return
            Ret(); // Procesa retorno de función
            break;
        case 'c': // Sentencia break
            desencolar(cola);
            if(frente(cola)== ';')
                desencolar(cola);
            break;
        case 'b': // Sentencia continue
            desencolar(cola);
            if(frente(cola)== ';')
                desencolar(cola);
            break;
        default: // Caso no reconocido
            printf("Error: Token inesperado '%c'\n", frente(cola));
            break;
    }
        
    }

//Procesa una secuencia de sentencias válidas hasta encontrar un delimitador de fin
void listaSent(){
    // Verifica si el token actual inicia una sentencia válida
    if(frente(cola) == 'a' || frente(cola) == 'd' || frente(cola) == 'i' ||
       frente(cola) == 'k' || frente(cola) == 'v' || frente(cola) == 'x'  ){
        Sent(); // Procesa la sentencia actual
        listaSent(); // Llamada para procesar posibles siguientes sentencias
        return;
    }
    // Casos de terminación
    if(frente(cola) == ']' || frente(cola) == '}' || frente(cola) == 'b'){
        return;
    }
}
//Analiza la estructura completa de un bucle do-while
void doW() {
    if (frente(cola) == 'd') { // Verifica token 'd'
        desencolar(cola);
        if (frente(cola) == '{') { // Verifica apertura de bloque '{'
            desencolar(cola);
            listaSent(cola); // Procesa todas las sentencias dentro del bloque
            if (frente(cola) == '}') { // Verifica cierre de bloque '}'
                desencolar(cola);
                if (frente(cola) == 'w') { // Verifica token 'w'
                    desencolar(cola);
                    if (frente(cola) == '(') { // Verifica apertura de condición '('
                        desencolar(cola);
                        exprLog(cola); // Procesa expresión lógica de la condición
                        if (frente(cola) == ')') { // Verifica cierre de condición ')'
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


// Analiza expresiones lógicas 
void exprLog() {
    // Primera producción: Negación !(E)
    if (frente(cola) == '!') { 
        desencolar(cola); 
        if (frente(cola) == '(') { // Verifica apertura de paréntesis
            desencolar(cola); 
            E();  // Procesar expresión interna
            if (frente(cola) == ')') { // Verifica cierre de paréntesis
                desencolar(cola); 
                return; // Producción procesada correctamente
            } else {
                printf("Error: se esperaba ')' después de E en !(E)\n");
                return;
            }
        } else {
            printf("Error: se esperaba '(' después de '!' en !(E)\n");
            return;
        }
    }
    // Segunda producción: Comparación (E)<opLog>(E)
    if (frente(cola) == '(') { // Verifica apertura de paréntesis
        desencolar(cola);
        E(); // Procesa primera expresión
        if (frente(cola) == ')') { // Verifica cierre de paréntesis
            desencolar(cola);
            opLog(); // Procesa operador lógico
            if (frente(cola) == '(') {  // Verifica apertura de paréntesis
                desencolar(cola); 
                E(); // Procesa segunda expresión
                if (frente(cola) == ')') {
                    desencolar(cola); 
                    return; 
                } else {
                    printf("Error: se esperaba ')' después de E en (E)<opLog>(E)\n");
                    return;
                }
            } else {
                printf("Error: se esperaba '(' después de <opLog> en (E)<opLog>(E)\n");
                return;
            }
        } else {
            printf("Error: se esperaba ')' después de E en (E)<opLog>(E)\n");
            return;
        }
    }

    printf("Error: expresión lógica no válida\n");
}

//Procesa operadores lógicos 
void opLog()
    // Operador AND lógico (&&)
    if(frente(cola) == '&'){
        desencolar(cola);
        return;
    }else printf("Error: se esperaba &\n");
    // Operador OR lógico (||)
    if(frente(cola) == '|'){
        desencolar(cola);
        return;
    }else printf("Error: se esperaba |\n");
}
//Analiza la estructura completa de un if
void IF(){
    if (frente (cola) == 'i'){ // Verifica token 'i' 
        desencolar(cola);
        if(frente (cola)=='('){ // Verifica apertura de condición '('
            desencolar(cola);
            exprLog(); // Procesa expresión lógica de condición
            if(frente(cola)== ')'){ // Verifica cierre de condición ')'
                desencolar(cola);
                if(frente(cola)=='{'){ // Verifica apertura de bloque '{'
                    desencolar(cola);
                    listaSent(); // Procesa todas las sentencias dentro del bloque if
                    if (frente(cola)=='}'){ // Verifica cierre de bloque '}'
                    desencolar(cola);
                    ELSE(); // Procesa else opcional (si existe)
                    return;
                    }else printf("Error: se esperaba }\n");   
                } else printf("Error: se esperaba {\n");  
            }else printf("Error: se esperaba )\n");  
        } else printf("Error: se esperaba (\n");  
    } else printf("Error: se esperaba i \n");  
}
//Procesa la parte else de una estructura condicional
void ELSE(){
    if(frente(cola)=='e'){ // Verifica token 'e' 
        desencolar(cola);
        if(frente (cola)=='{'){ // Verifica apertura de bloque '{'
            desencolar(cola);
            listaSent(); // Procesa todas las sentencias dentro del else
            if (frente (cola)=='}'){ // Verifica cierre de bloque '}'
                desencolar(cola);
            }else printf("Error: se esperaba } \n");  
        }else printf("Error: se esperaba {\n");  
    }  
    // Verificar si el siguiente token inicia una nueva sentencia
    if( frente (cola)== 'a' || frente (cola)== 'd'|| frente (cola)== 'i' || frente (cola)== 'k'|| frente (cola)== 'f' || frente (cola)== 'x' ){
        return;
    } 
}
// Analiza la estructura completa de un bucle for
void For() {

    if (frente(cola) != 'v') { // Verificar token 'v' 
        printf("Error: Se esperaba 'FOR' (átomo 'v')\n");
        return;
    }
    desencolar(cola);
    
    if (frente(cola) != '(') { // Verifica apertura de paréntesis '('
        printf("Error: Se esperaba '(' después de FOR\n");
        return;
    }
    desencolar(cola); 

    E(); // Procesa la expresión aritmética

    // Verifica paréntesis de cierre ')'
    if (frente(cola) != ')') {
        printf("Error: Se esperaba ')' después de la expresión en FOR\n");
        return;
    }
    desencolar(cola); 

    // Verifica llave de apertura '{'
    if (frente(cola) != '{') {
        printf("Error: Se esperaba '{' después de FOR(expresión)\n");
        return;
    }
    desencolar(cola); // Mover '{' a temp
    listaSent(); // Procesar las sentencias
    // Verifica llave de cierre '}'
    if (frente(cola) != '}') {
        printf("Error: Se esperaba '}' al final del bloque FOR\n");
        return;
    }
    desencolar(cola); 

    return;

}
//Analiza la estructura completa de una sentencia return
void Ret() {
    if (frente(cola) == 'x') {  // Verificar token 'x' 
        desencolar(cola); 
        
        if (frente(cola) == '(') { // Verifica apertura de paréntesis '('
            desencolar(cola); 
            valRet(); // Procesa valor de retorno 
            if (frente(cola) == ')') { // Verifica paréntesis de cierre ')'
                desencolar(cola);
                if(frente(cola) == ';'){ // Verifica terminación con ';'
                    desencolar(cola);
                    return;
                }else printf("Error: se esperaba ;");
            }else printf("Error: Se esperaba ')' al final de RETURN\n");
        } else printf("Error: Se esperaba '(' después de RETURN\n");
    } else printf("Error: Se esperaba 'RETURN' (átomo 'x')\n");
}

//Analiza el valor de retorno opcional en una sentencia return
void valRet(){
     // Verifica si hay una expresión de retorno
    if(frente(cola) == '('|| frente(cola) == 'a'|| frente(cola) == 'n'|| 
       frente(cola) == 'r'|| frente(cola) == 'l'|| frente(cola) == 'm'){
        E(); // Procesa expresión aritmética/lógica completa
        return;
       }

    if(frente(cola) == ')') // Caso para retorno sin valor (ε)
       return;
}
//Analiza la estructura completa de un switch
void Switch(){
    if(frente(cola)=='k'){ // Verifica token 'k' (switch)
        desencolar(cola);
        if(frente (cola)=='('){ //Verifica apertura de condición '('
            desencolar(cola);
            if (frente (cola)=='a'){ // Verifica variable de control 'a'
                desencolar(cola);
                if (frente(cola)==')'){ // Verifica cierre de condición ')'
                    desencolar(cola);
                    if(frente(cola)=='{'){ // Verifica apertura de bloque '{'
                        desencolar(cola);
                        listaCase(); // Procesa todos los casos (cases)
                        if(frente(cola)=='}'){ // Verifica cierre de bloque '}'
                            desencolar(cola);
                            return;
                        } else printf("Error: se esperaba } \n");  
                    }else printf("Error: se esperaba { \n");  
                } else printf("Error: se esperaba ) \n");  
            }else printf("Error: se esperaba a \n");  
        }else printf("Error: se esperaba (\n");  
    }else printf("Error: se esperaba k \n");  
}
// Procesa todos los casos (case/default) dentro de un bloque switch
void  listaCase(){
    if (frente(cola)=='z'){ // Verifica si hay un caso 
        Case();
        listaCase();  // Llamada para procesar más casos
    }
    if(frente(cola)== '}'){ //  Verifica fin de bloque switch
        return;
    }
}
//Analiza un caso individual dentro de una estructura switch
void Case(){
    if (frente(cola)=='z'){ // Verifica token 'z' (case)
        desencolar(cola);
        if(frente(cola)=='n'){ // Verifica valor del caso 'n' 
            desencolar(cola);
            if(frente(cola)==')'){ // Verifica separador ')'
                desencolar(cola);
                listaSent(); // Procesa sentencias del caso
                // Verifica break opcional ('b' ';')
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
//Analiza expresiones aritméticas mediante la gramática: E → T EP
void E(){
    // Verifica tokens válidos para iniciar expresión
    if(frente(cola)=='('|| frente(cola)=='a'||frente(cola)=='n'||frente(cola)=='r'){
        T(); // Procesa término principal
        EP(); // Procesa posibles operaciones adicionales
    }else printf("Error no se econtro E\n");

}
//Procesa operadores aditivos
void EP(){
    // Verifica si hay operador aditivo
    if(frente(cola) == '+'){
        desencolar(cola);
        T(); // Procesa siguiente término
        EP(); // Verifica más operaciones 
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
 
//Procesa terminos aritméticos
void T(){
    // Verifica tokens válidos para iniciar término
    if(frente(cola)=='('|| frente(cola)=='a'||frente(cola)=='n'||frente(cola)=='r'){
        F();  // Procesa factor principal
        TP(); // Procesa posibles operaciones adicionales
        return;
    }
}
//Procesa operadores multiplicativos y especiales
void TP() {
     // Operadores aritméticos estándar
    if (frente(cola) == '*') {
        desencolar(cola); 
        F(); // Procesa factor
        TP(); // Verificar más operaciones
        return;
    } else if (frente(cola) == '/') {
        desencolar(cola); // Consumir '/'
        F(); // Procesa factor
        TP(); // Verificar más operaciones
        return;
    } else if (frente(cola) == '%') {
        desencolar(cola); // Consumir '%'
        F(); // Procesa factor
        TP(); // Verificar más operaciones
        return;
    } else if (frente(cola) == 'p'){
        desencolar(cola); // Consumir '%'
        F(); // Procesa factor
        TP(); // Verificar más operaciones
        return;
    } else if (frente(cola) == 'l'){
        desencolar(cola); // Consumir '%'
        F(); // Procesa factor
        TP(); // Verificar más operaciones
        return;
    }else if (frente(cola) == 'm'){
        desencolar(cola); // Consumir '%'
        F(); // Procesa factor
        TP(); // Verificar más operaciones
        return;
    }
    // Caso epsilon: no se hace nada
    return;
}

//Procesa factores básicos en expresiones
void F(){
    if(frente(cola) == '('){ //Verifica paréntesis de apertura '('
        desencolar(cola);
        E(); // Procesa expresión interna
        if(frente(cola) == ')'){ // Verifica paréntesis de cierre ')'
            desencolar(cola);
            return;
        } else printf("Error se esperaba )\n");
    }

    if(frente(cola) == 'a'){ //Verifica identificador 
        desencolar(cola);
        G(); // Procesa operaciones sobre identificador
        return;
    }

    //Verifica que sea número entero
    if(frente(cola) == 'n'){
        desencolar(cola);
        return;
    }else printf("Error: se esperaba n\n");
    //Verifica que sea número real
    if(frente(cola) == 'r'){
        desencolar(cola);
        return;
    }else printf("Error: se esperaba r\n");
}

//65-67 G
void G(){
    if(frente(cola) == 'l'){ //Verifica token l
        desencolar(cola);
        return;
    }

    if(frente(cola) == 'm'){ //Verifica token l
        desencolar(cola);
        return;
    }
    // Caso ε - Cuando sigue un operador estándar (*, /, %)
    // No se consume ningún token, el análisis continúa
    if(frente(cola) == '*' || frente(cola) == '/' || frente(cola) == '%'){
        return;
    }
}
//Procesa una instrucción de asignación completa 
void Asig() {
    if (frente(cola) == 'a') { // Verifica identificador
        desencolar(cola); 
        opAsig(); // Procesa el operador de asignación 

        // Verificar si hay una expresión opcional <E>
        if (frente(cola) == '(' || frente(cola) == 'a' || frente(cola) == 'n' || frente(cola) == 'r') {
            E(); // Procesa la expresión aritmética/lógica
        }

        // Verifica si hay un 's' 
        if (frente(cola) == 's') {
            desencolar(cola);
        } else if (frente(cola) != ';') { // Si no hay 's', debe haber ';'
            printf("Error: Se esperaba 's' o ';' al final de la asignación\n");
            return;
        }

        // Verificar el ';' obligatorio
        if (frente(cola) == ';') {
            desencolar(cola); 
            return;
        } else {
            printf("Error: Falta ';' al final de la asignación\n");
            return;
        }
    } else {
        printf("Error: Se esperaba un identificador 'a' al inicio de la asignación\n");
        return;
    }
}

// Procesa los distintos operadores de asignación posibles
void opAsig(){
    switch(frente(cola)){
        case'=': desencolar(cola); // Consume (=)
                 break;
        case'#': desencolar(cola); // Consume (#)
                break;
        case';': desencolar(cola);// Consume (;)
                break;
        case'$': desencolar(cola); // Consume ($)
                break;
        case',': desencolar(cola); // Consume (,)
                break;
        case'?': desencolar(cola); // Consume (?)
                break;
        case':': desencolar(cola); // Consume (:)
                break;
        case'^': desencolar(cola); // Consume (^)
                break;
        case'@': desencolar(cola); // Consume (@)
                break;
        case'<': desencolar(cola); // Consume (<)
                break;
        case'>': desencolar(cola); // Consume (=)
                break; 
        default: printf("Error: operador no encontrado \n");
        break;
    }
}
