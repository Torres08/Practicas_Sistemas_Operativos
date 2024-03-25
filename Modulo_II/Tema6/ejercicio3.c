/*

    Nombre: Ejercicio3.
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 3: Construye un programa que verifique que efectivamente, el kernel comprueba que puede darse una situacion de nterbloqueo en el bloqueo de archivos

    procesos A y B intentarán bloquear dos archivos diferentes, puede conducir a una situacion de interbloqueo si el proceso A 
    bloquea el archivo 1 y espera al proceso B para que se libere el archivo 2, mientras que el proceso B bloquea el
    archivo 2 y espera al proceso A para que se libere el archivo 1.
    Este programa no siempre genera una situacion de interbloqueo , no se que mas hacer

    Ejecucion del programa: ./ejercicio3    

*/

/*

    ./papelera/ejercicio3 
    Proceso A: bloqueando archivo 1
    Proceso A: bloqueando archivo 2
    Proceso A: terminado

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

// 5. defino el proceso A
void procesoA(int fd1, int fd2){

    // 6. defino cerrojo escritura
    struct flock cerrojo;

    cerrojo.l_type = F_WRLCK; // cerrojo de escritura
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0; // cerrojo todo el archivo

    printf("Proceso A: bloqueando archivo 1\n");
    fcntl(fd1, F_SETLK, &cerrojo); // pongo el cerrojo con F_SETLK

    // 7. doy una oportunidad a porceso B con sleep 2
    sleep(2);

    // 8. defino cerrojo para bloquear el otro archivo 
    // creo que no hace falta repetir esto otra vez, solo por si acaso 
    cerrojo.l_type = F_WRLCK; // cerrojo de escritura
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0; // cerrojo todo el archivo

    printf("Proceso A: bloqueando archivo 2\n");
    fcntl(fd2, F_SETLK, &cerrojo); // pongo el cerrojo con F_SETLK


    printf("Proceso A: terminado\n");   


    // 9. libero los cerrojos

    cerrojo.l_type = F_UNLCK; // cerrojo de escritura
    fcntl(fd1, F_SETLKW, &cerrojo);
    fcntl(fd2, F_SETLKW, &cerrojo);

}


// 10. proceso B exactamente igual al A
void procesoB(int fd1, int fd2) {
    struct flock cerrojo;

    // Bloquea el segundo archivo
    cerrojo.l_type = F_WRLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;

    printf("Proceso B intenta bloquear archivo 2\n");
    fcntl(fd2, F_SETLKW, &cerrojo);

    // Espera un momento para dar oportunidad al proceso A
    //sleep(2);

    // Intenta bloquear el primer archivo
    cerrojo.l_type = F_WRLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;

    printf("Proceso B intenta bloquear archivo 1\n");
    fcntl(fd1, F_SETLKW, &cerrojo);

    printf("Proceso B finalizado\n");

    // Libera los cerrojos
    cerrojo.l_type = F_UNLCK;
    fcntl(fd1, F_SETLKW, &cerrojo);
    fcntl(fd2, F_SETLKW, &cerrojo);
}


int main(){
    int fd1, fd2;

    // 1. si no existe lo creo y lo abro, si existe lo abro
    fd1 = open("./papelera/archivo1.txt", O_RDWR|O_CREAT|O_TRUNC, 0666);
    fd2 = open("./papelera/archivo2.txt", O_RDWR|O_CREAT|O_TRUNC, 0666);

    // 2. inicializar los archivos , les escribo algo
    write (fd1, "hola", 23);
    write (fd2, "adios", 23);

    // 3. creo proceso A y proceso B
    // proceso A lo hace el padre y B el hijo con PID_A y viceversa con PID_B
    pid_t PID_A, PID_B;

    if (PID_A == 0) {
        // Proceso hijo A
        procesoA(fd1, fd2);
    } else {
        // Proceso padre
        PID_B = fork();

        if (PID_B == 0) {
            // Proceso hijo B
            procesoB(fd1, fd2);
        } else {
            // Proceso padre espera a que los hijos terminen, a todos 
            wait(NULL);
            wait(NULL);
        }
    }

    // 4. cierro los archivos
    close(fd1);
    close(fd2);


}