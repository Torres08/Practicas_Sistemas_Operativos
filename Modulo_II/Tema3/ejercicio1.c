/*

	Nombre: Ejercicio1.c
	Autores: Torres Ramos, Juan Luis
	Sistemas Operativos

	Ejercicio 3: Implementa un programa en C que tenga como argumento un número entero. Este programa debe crear un proceso hijo que se encargará de 
    comprobar si dicho número es un número par o impar e informará al usuario con un mensaje que se enviará a la salida estándar. A su vez
    el padre debe comprobar si dicho número es divisible por 4 e informará al usuario con un mensaje que se enviará a la salida estándar.

	Ejecucion del programa: $> ./ejercicio3 <numero_entero>

*/

#include <stdlib.h> // exit
#include <stdio.h> // perror
#include <unistd.h> // fork
#include <sys/types.h> // pid_t

int main (int argc, char *argv[]){
    // 1. compruebo que envio un argumento
    if (argc != 2){
        perror("Error en el numero de argumentos: ./ejercicio3 <numero_entero>\n");
        exit(EXIT_FAILURE);
    }


    // 2. para usar for tengo que crear una variable PID
    // recupero tambien la variable pasada por argumento, convierto con atoi
    pid_t PID;
    int variable = atoi(argv[1]); // atoi convierte un string a un entero

    // 3. creo el proceso hijo
    if ((PID = fork()) < 0){
        perror("Error en el fork\n");
        exit(EXIT_FAILURE);
    }


    // 4. compruebo si es el padre o el hijo, es hijo cuando el PID es 0
    if (PID == 0){
        // 5. caso hijo
        // imprimo tambien el PID del proceso hijo
        printf("Soy el proceso hijo con PID: %d\n", getpid());
        printf("Mi padre es: %d\n", getppid()); 

        // 6. compruebo si es par o impar
        if (variable % 2 == 0){
            printf("El numero %d es par\n", variable);
        } else {
            printf("El numero %d es impar\n", variable);
        }

    } else {
        
        // 7. caso padre

        // caso en el que necesite que elpadre espere a su hijo/hijos , se ejecutara secuencialente, ponemos el waitpid al principio del codigo padre
        waitpid(PID, NULL, 0);
        
        // 8. print de su informacion 
        printf("Soy el proceso padre con PID: %d\n", getpid());
        printf("Mi hijo es: %d\n", PID);

        // 9. compruebo si es divisible por 4
        if (variable % 4 == 0){
            printf("El numero %d es divisible por 4\n", variable);
        } else {
            printf("El numero %d no es divisible por 4\n", variable);
        }
    
    }

    return EXIT_SUCCESS;
    
}