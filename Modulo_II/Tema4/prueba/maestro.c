/*
 *      Ejercicio 4: Contar numero archivos regulares en un directorio dado y mostrar resultado
 *      Torres Ramos, Juan Luis
*
*       primero mirar ejercicio 1,2, 3 y 4 de la sesion 4 cauces
*
*       anotacion de los flags de execlp
*
*       modificacion del ejecricio 5
*       vamos a crear un esclavo.c que reciva un vector de argumentos y los suma
*       1 2 3 4 5 (lo que recibe)
*       como devovlemos por el esclavo.c
*       write (STDOUT_FILENO, &suma, sizeof(int))   //escribimos en el cauce
*
*       el maestro.c tiene que , reciba tambien l vector de argumentos, crea dos hijos,
        tiene que asegurarse de cerrar los descriptores, (2 descriptores, uno para cada hijo)
*
*       execv(exclavo, argumento)

*       priemr hijo uma hasta la mitad, segundo hijo suma desde la mitad hasta el final, en el padre
        recibimos, dividimos el trabajo dese el padre para cada hijo
*
        recibios el maestro y distribuimos el trabajo

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Validar argumentos
    if (argc < 2) {
        printf("Uso: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;

    // Creamos las tuberías
    int pipefd1[2]; // Para el primer esclavo
    int pipefd2[2]; // Para el segundo esclavo

    pipe(pipefd1);
    pipe(pipefd2);

    pid_t pid1, pid2;
    int mitad = n / 2;
    int bytesLeidos1, bytesLeidos2, val1, val2;

    // Esclavo 1
    char *params1[mitad + 2];
    params1[0] = "./esclavo";

    for (int i = 1; i <= mitad; i++) {
        params1[i] = argv[i];
    }

    params1[mitad + 1] = NULL;

    if ((pid1 = fork()) < 0) {
        perror("Error en el fork hijo 1");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        close(pipefd1[0]); // Cerrar descriptor de lectura

        // Redirigir la salida estándar
        dup2(pipefd1[1], STDOUT_FILENO);

        // Ejecutar el esclavo
        if (execv("./prueba/papelera/esclavo", params1) < 0) {
            perror("Error en el execv hijo 1");
            exit(EXIT_FAILURE);
        }
    } else {
        close(pipefd1[1]); // Cerrar descriptor de escritura
        while ((bytesLeidos1 = read(pipefd1[0], &val1, sizeof(int))) > 0) {
            printf("Suma hijo 1: %d ", val1);
        }
        close(pipefd1[0]); // Cerrar descriptor de lectura
        printf("\n");
        waitpid(pid1, NULL, 0); // Esperar al hijo 1
    }

    // Esclavo 2
    char *params2[n - mitad + 2];
    params2[0] = "./esclavo";

    for (int i = mitad + 1; i <= n; i++) {
        params2[i - mitad] = argv[i];
    }

    params2[n - mitad + 1] = NULL;

    if ((pid2 = fork()) < 0) {
        perror("Error en el fork hijo 2");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        close(pipefd2[0]); // Cerrar descriptor de lectura
        dup2(pipefd2[1], STDOUT_FILENO);

        // Ejecutar el esclavo
        if (execv("./prueba/papelera/esclavo", params2) < 0) {
            perror("Error en el execv hijo 2");
            exit(EXIT_FAILURE);
        }
    } else {
        close(pipefd2[1]); // Cerrar descriptor de escritura
        while ((bytesLeidos2 = read(pipefd2[0], &val2, sizeof(int))) > 0) {
            printf("Suma hijo 2: %d ", val2);
        }
        close(pipefd2[0]); // Cerrar descriptor de lectura
        printf("\n");
        waitpid(pid2, NULL, 0); // Esperar al hijo 2
    }

    return 0;
}
