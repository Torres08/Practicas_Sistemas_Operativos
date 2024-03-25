/*

    Nombre: Ejercicio5.c Maestro y esclavo
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    Ejercicio 5: Idea es usar vaios procesos para realizar partes de una computacion en paralelo

    maestro-esclavo , esclavos trabajan en paralelo y el maestro espera a que terminen todos los esclavos para terminar

    calculo de numeros primos que hay en un intervalo, creamos maestro.c y esclavo.c
    intervalo de nuemros es lo que pasamos por argumento al maestro, este luego crea 2 esclavos y divide el intervalo
    en dos intervalos entre 1000 y 2000 entonces esclavo calcla y devolver los primeros primos que hay en ese intervalo

    maestro crea dos cauces sin nombres y se encarga de su redireccion para comunicarse con los esclavos

    maestro ira recibiendo y mostrando en pantalla los numero primos calculados por los esclavos en
    orden creciente

    esclavo tiene como arrgumentos extremo inferior y superior del intervalo de numeros a comprobar
    usamos una funcion especifica apra ver si un numero es primo , el esclavo manda al maestro cada
    primo encontrado por cauce sin nombre

    Ejecucion del programa: $> ./maestro 5 10
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    // 1. compruebo argumentos, paso 2 int que van a ser los bordes del intervalo a buscar primos
    if (argc != 3)
    {
        perror("Error en el numero de argumentos");
        exit(EXIT_FAILURE);
    }

    // 2. declaro variables, basicamente intervalo min, max
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);

    // 3. argumentos que luego pasare a los esclavos
    char string_min[100], string_max[100];
    int bytesLeidos, val1, val2;

    // 4. modificacion salida estandar, desactivo el buffering, el maestro
    // garantiza qu las salidas en stdout se envien directamente aldispositivo de salida
    // sin ser almacenadas en un buffer , no hay retrasos

    setvbuf(stdout, NULL, _IONBF, 0);

    // 5. creo cauces sin nombre necesito 2, necesito 2 descriptores
    int fd1[2], fd2[2];
    pid_t PID_1, PID_2;

    // 6. Creo cauce sin nombre
    pipe(fd1);
    pipe(fd2);

    // 7. creo proceso hijo 1 y 2

    if ((PID_1 = fork()) < 0)
    {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }   

    // 8. tengo mis esclavos creado , le asigno trabajo, el padre los
    if (PID_1 == 0)
    {   
        // voy a escribir cierro lectura, flujo salida
        close(fd1[0]);
        dup2(fd1[1], STDOUT_FILENO); // 1 out

        // paso de int a string para pasar como argumento
        sprintf(string_min, "%i", min);
        sprintf(string_max, "%i", max/2);

        execl("./papelera/esclavo", "esclavo", string_min, string_max , NULL);
        perror("Error en execl");
        exit(EXIT_FAILURE);
    }
    else
    {
        // padre , leo cierro escritura
        close(fd1[1]);

        // leo el descriptor de lectura
        while ((bytesLeidos = read(fd1[0], &val1, sizeof(int))) > 0)
        {
            printf("%d ", val1);
        }

        // cierro 
        close(fd1[0]);
        printf("\nEsclavo 1 terminado\n");
        
    }


    // esclavo 2
    if ((PID_2 = fork()) < 0)
    {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }   

    // 8. tengo mis esclavos creado , le asigno trabajo, el padre los
    if (PID_2 == 0)
    {   
        // voy a escribir cierro lectura, flujo salida
        close(fd2[0]);
        dup2(fd2[1], STDOUT_FILENO); // 1 out

        // paso de int a string para pasar como argumento
        sprintf(string_min, "%i", max/2+1);
        sprintf(string_max, "%i", max);

        execl("./papelera/esclavo", "esclavo", string_min, string_max , NULL);
        perror("Error en execl");
        exit(EXIT_FAILURE);
    }
    else
    {
        // padre , leo cierro escritura
        close(fd2[1]);

        // leo el descriptor de lectura
        while ((bytesLeidos = read(fd2[0], &val2, sizeof(int))) > 0)
        {
            printf("%d ", val2);
        }

        // cierro 
        close(fd2[0]);
        printf("\nEsclavo 2 terminado\n");
        
    }

    

    return EXIT_SUCCESS;
}