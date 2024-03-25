/*

    Nombre: Ejercicio2.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 2: ¿Qué hace el siguiente programa?, pruebalo con y sin setvbuf
    Intenta entender lo que ocurre con las variables y sobre todo con los mensajes por pantalla cuando el núcleo tiene activado/desactivado el mecanismo de buffering.

    Ejecucion del programa: $> ./ejercicio3

    CASO SIN SETVBUF:
    ./papelera/ejercicio2 
    cualquier mensaje de salida

    Mensaje previo a la ejecución de fork
    pid= 1667531, global= 7, var= 89 // hijo
    Mensaje previo a la ejecución de fork
    pid= 1667530, global= 6, var= 88 // padre

    CASO CON SETVBUF:
    ./papelera/ejercicio2 
    cualquier mensaje de salida

    Mensaje previo a la ejecución de fork
    pid= 1670921, global= 7, var= 89 // hijo

    pid= 1670920, global= 6, var= 88 // padre


    diferencia: solo hace 2 print de mensaje previo
    
    STDOUT_FILENO: es un descriptor de fichero que hace referencia a la salida estandar
    setvbuf: cambia el comportamiento del búfer de salida estándar

    cuando hacemos write (STDOUT_FILENO, buf, tama), los datos se escriben directamente en la salioda estandar sin ser almacenados en un buffer temporal
    (no buffering salida), deshabilitarlo usamos servbuf 

    3 flujos de stream STDIN, STDOUT y STDERR, setvbuf trabaja sobre STREAMS , no sobre descriptores
    de archivos

    ___

    Este ejercicio quiere demostrar como cada proceso tiene sus propias variables de entorno, salvo compoartidas
    con global
*/

#include <sys/types.h> //Primitive system data types for abstraction of implementation-dependent data types.
                       //POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>    //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// 2. variables locales, buf es un mensaje
int global = 6;
char buf[] = "cualquier mensaje de salida\n";

int main(int argc, char *argv[])
{

    // 1. var y pid, declaro que var es 88
    int var;
    pid_t pid;
    var = 88;

    // 3. escribo el mensaje almacenado en buf en la salida estandar
    // si no se usa el setvbuf, el mensaje se almacena en un buffer temporal y se escribe cuando se llena
    if (write(STDOUT_FILENO, buf, sizeof(buf) + 1) != sizeof(buf) + 1)
    {
        perror("\nError en write");
        exit(EXIT_FAILURE);
    }

    // (1) El código comentado es una alternativa para cambiar 
    // el comportamiento del búfer de salida estándar
    // Al descomentarlo, se deshabilita el búfer de salida, 
    // evitando que el mensaje se almacene temporalmente

    if(setvbuf(stdout,NULL,_IONBF,0)) {
    	perror("\nError en setvbuf");
    }

    printf("\nMensaje previo a la ejecución de fork");

    // 4. creo el proceso hijo
    if ((pid = fork()) < 0)
    {
        perror("\nError en el fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // 5. proceso hijo ejecutando el programa, aumento var y global ++
        global+=2;
        var++;
    }
    else {
        // proceso padre ejecutando el programa, caso hago un sleep y ya
        
        //waitpid(pid, NULL, 0); // para que sea secuencial
        global+=3;
        var+=4;
        
        sleep(1);


    }
    
    
    
    
    // 6. print de la informacion de los procesos
    printf("\npid= %d, global= %d, var= %d\n", getpid(), global, var);
    exit(EXIT_SUCCESS);
}
