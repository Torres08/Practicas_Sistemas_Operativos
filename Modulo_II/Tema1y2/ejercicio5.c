/*

    Nombre: Ejercicio5.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 5: ¿Qué hace el siguiente programa?

    Ejecucion del programa: $> ./ejercicio5

*/

/*
 Este programa fuente est� pensado para que se cree primero un programa con la parte
 de CREACION DE ARCHIVOS y se haga un ls -l para fijarnos en los permisos y entender
 la llamada umask.

 En segundo lugar (una vez creados los archivos) hay que crear un segundo programa
 con la parte de CAMBIO DE PERMISOS para comprender el cambio de permisos relativo
 a los permisos que actualmente tiene un archivo frente a un establecimiento de permisos
 absoluto.

*/

#include <sys/types.h> //Primitive system data types for abstraction of implementation-dependent data types.
                       //POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>    //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> //Needed for open
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // 1. creo dos file descriptors para crear 2 archivos y stat para ver sus atributos
    int fd1, fd2;
    struct stat atributos;

    // 9. ejecucion de 2 ls -l secuencialmente para ver los permisos de los archivos
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        
        // 9. codigo del proceso hijo, el hijo crea los archivos y hace el primer ls -l

        // 2. creo archivo1 , lectura, ejecucion grupo (S_IXGRP -> ejecucion de grupo)
        // printf("\nCreando archivo1\n");
        
        umask(0);
        if ((fd1 = open("./recursos/archivo1", O_CREAT | O_TRUNC | O_WRONLY, S_IRGRP | S_IWGRP | S_IXGRP)) < 0)
        {
            printf("\nError %d en open(archivo1,...)", errno);
            perror("\nError en open");
            exit(EXIT_FAILURE);
        }

        // 3. umask(0) -> mascara de permisos, no se aplica ninguna mascara
        umask(0);

        // 4. creo archivo2 , lectura, escritura grupo, ejecucion grupo (S_IXGRP -> ejecucion de grupo)
        // printf("Creando archivo2\n");
        if ((fd2 = open("./recursos/archivo2", O_CREAT | O_TRUNC | O_WRONLY, S_IRGRP | S_IWGRP | S_IXGRP)) < 0)
        {
            printf("\nError %d en open(archivo2,...)", errno);
            perror("\nError en open");
            exit(EXIT_FAILURE);
        }

        // 5. ejecuto ls -l para ver los permisos de los archivos
        printf("\nEjecutando ls -l 1º vez\n");
        chdir("./recursos");
        execl("/bin/ls", "ls", "-l", NULL);
    }
    else
    {
        // 9. Esperar a que el proceso hijo termine
        waitpid(pid, NULL, 0);

        // codigo del padre, veo los atributos y los cambios de permisos, 2º ls -l
        if (stat("./recursos/archivo1", &atributos) < 0)
        {
            printf("\nError al intentar acceder a los atributos de archivo1");
            perror("\nError en lstat");
            exit(EXIT_FAILURE);
        }

        // 6. llamo chmod para cambiar los atributos de arhivo 1
        // (atributos.st_mode & ~S_IXGRP) -> mascara de bits, quito el bit de ejecucion de grupo, ~ es quitar
        // luego agrego el bit de grupo con S_ISGID
        // quitando el bit de ejecución del grupo y estableciendo el bit de set-GID
        if (chmod("./recursos/archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        {
            perror("\nError en chmod para archivo1");
            exit(EXIT_FAILURE);
        }

        // 7. llamo chmod para cambiar los atributos de arhivo 2
        // en resumen todo esos flags: lectura, escritura y ejecución para el propietario, lectura para el grupo, y lectura para otros.
        if (chmod("./recursos/archivo2", S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0)
        {
            perror("\nError en chmod para archivo2");
            exit(EXIT_FAILURE);
        }

        // 8. ejecuto ls -l para ver los permisos de los archivos de nuevo
        printf("Ejecutando ls -l 2º vez\n");
        chdir("./recursos");
        execl("/bin/ls", "ls", "-l", NULL);
    }

    return EXIT_SUCCESS;
}
