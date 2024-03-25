/*
    Nombre: prueba.c
    Autores: Torres Ramos, Juan Luis
    Sistemas Operativos

    prueba sesion 3:
    lee argumentos de un vector

    int n = argc - 1;
    int *num = (int*)malloc(n * sizeof(int));
    for (.....)
        num[i] = atoi(argv[i + 1])
    
    introduzca un vector, cree 2 hijos, uno se encarga de que cada numero del vector es par,
    se encarga de hacer sumas pares, y el 2 hijo se encarga de ver en el vector los numeros
    impares y los que haya hace una suma
    tambien al crear el hijo muestra informacion sobre los hijos como se muestra abajo

    referencia Ejercicio 2 y 6

    proc padre
        - proc hijo 1 -> suma n pares
         "Hijo 1 : (Mi PID es .... ) el de mi padre es ...."
        - proc hijo 2 -> suma n impares
    ...

        - suma total = suma pares + suma impares

        metodos: fork(), getpid(), getppid(), wait/waitpid() , pid_t pud_hijo1
    
    pasos:
        1. leer argumentos de un vector y expulsarlos con
        2. Crear los hijos y asignarle la tarea de decir PID y PPID
        3. hijo 1 cuente los nuemros pares
        4. hijo 2 cuente los numeros impares
        5. Expulsar la suma


    Ejecucion del programa: $> ./prueba 1 2 3 4 1

*/


#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <sys/wait.h> // waitpid

// contarPares e impares cuentan pares/impares dado un vector y su tamaño
// devolver la suma de los pares/impares el lo mismo que devolver el contador de Pares, no es lo importante del ejercicio
// lo importante es saber como crear varios hijos, darles un trabajo, que te devuelvan algo, esperar y recoger su resultado

int  contarPares(int *vector, int n){
	int contadorPares=0;
	for (int i = 0; i < n ; ++i){
		if (vector[i] % 2 == 0){
			contadorPares++;
		}
	}
 return contadorPares;
}

int  contarImpares (int *vector, int n){
	int contadorImpares=0;
	for (int i = 0; i < n; ++i){
		if (vector[i] % 2 != 0){
			contadorImpares++;
		}
	}
return contadorImpares;
}

int main (int argc, char *argv[]){

    // 1. compruebo argumentos
    if (argc < 2){
        perror("Error en el numero de argumentos: ./prueba <num1> <num2> .... <numN>\n");
        exit(EXIT_FAILURE);
    }


    // 2. leo argumentos de un vector y expulsarlos con, defino ademas el tamaño del vector
    int n = argc - 1; // numero de argumentos - 1

    // cre el vector del tamaño de los argumentos introducidos -1 (el 0 no lo cuento, referencia al mismo archivo)
    int *vector = (int*)malloc(n * sizeof(int)); 

    // uso atoi para convertir char a entero y los meto en el vector
    for (int i  = 0; i < n ; i++){
        vector[i] = atoi(argv[i+1]);
    }

    // 3. creo los hijos, cada uno tiene su propio PID, tambien podriamos hacerlo como 
    // el ejercicio 3 pero de cara al examen es mejor crear sin bucles, como mucho 2 o 3 hijos 
    // habra que crear pid para cada uno 
    pid_t pid_hijo1, pid_hijo2;
    int resultado1, resultado2;
    int estado;
    int suma1, suma2;


    // 4. creo el primer hijo

    if ((pid_hijo1 = fork()) < 0){
        perror("Error en el fork\n");
        exit(EXIT_FAILURE);
    } else if (pid_hijo1 == 0){
        // caso hijo 1 contar pares 
        // paso el vector y el tamaño del vector
        resultado1 = contarPares(vector, n); 
        printf("Hijo 1 con PID: %d. PPID: %d\n", getpid(), getppid());
        printf("El numero de pares es: %d\n", resultado1);

        // devuelve el resultado, lo cojo luego de estado que sera el valor que dara el hijo
        return resultado1;
    }

    // 5. creo el segundo hijo
    if ((pid_hijo2 = fork()) < 0){
        perror("Error en el fork\n");
        exit(EXIT_FAILURE);
    } else if (pid_hijo2 == 0){
        // caso hijo 1 contar pares 
        // paso el vector y el tamaño del vector
        resultado2 = contarImpares(vector, n); 
        printf("Hijo 2 con PID: %d. PPID: %d\n", getpid(), getppid());
        printf("El numero de impares es: %d\n", resultado2);

        return resultado2;
    }


    // 6. caso padre, espero a que terminen los hijos
    printf("Padre esperando a los hijos que terminen ... \n");
    waitpid(pid_hijo1, &estado, 0);
    suma1 = estado >> 8; // estado es un entero, lo desplazo 8 bits a la derecha para que me de el valor del hijo
    waitpid(pid_hijo2, &estado, 0);
    suma2 = estado >> 8;

    printf("Trabajo terminado tanto de los hijos como del padre\n");
	// al finalizar liberar memoria del vector dinamico
	
	printf ("Suma total= %d", suma1 + suma2);

    free(vector);

    return EXIT_SUCCESS;
}