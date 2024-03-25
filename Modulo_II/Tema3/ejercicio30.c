/*
 *      Ejercicio 3: Contar numero archivos regulares en un directorio dado y mostrar resultado
 *      Torres Ramos, Juan Luis
 *
 *      ./ejercicio3 1 2 3 4 1
 *	
 *	leer argumentos de un vector
 *
 *      int n = argc - 1
 *      int *num = (int*)malloc(n*sizeof(int)) 
 *      	for (.....)
 *      		num[i] = atoi(argv[i+1])
 *      
 *	introduzco un vector, creo 2 hijos, uno se encarga de que cada numero del vector es par,
 *	se encarga de hacer sumas pares, y el 2 hijo se encarga de ver en el vector los numeros 
 *	impares y los que haya hace una suma 
 *	tambien al crear el hijo muestra informacion sobre los hijos como se muestra abajo
 *
 * 	referencia Ejercicio 2 y 6
 *
 *	proc padre
 *		- proc hijo 1 -> suma n pares
 *		 "Hijo 1 : (Mi PID es .... ) el de mi padre es ...."
 *		- proc hijo 2 -> suma n impares
 *	...
 *
 *		- suma total = suma pares + suma impares
 *	
 * 	
 *      metodos: fork(), getpid(), getppid(), wait/waitpid() , pid_t pud_hijo1
 *
 * 	Pasos:
 * 		1. leer argumentos de un vector y expulsarlos con
 * 		2. Crear los hijos y asignarle la rarea de decir PID y PPID
* 		3. hijo 1 cuente los nuemros pares
* 		4. hijo 2 cuente los numeros impares
* 		5. Expulsar la suma
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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

	// minimo tengo que ingresar un numero, si no error
	if (argc < 2){
		printf("Uso: %s <num1> <num2> ... <numN>\n", argv[0]);
		return 1;
	}

	int n = argc - 1;

	// creo el vector del tamaño de los argumentos introducidos - 1 (el 0 hace referencia al mismo archivo)
	int *vector = (int*)malloc(n*sizeof(int));

	// COnvertir los argumentos a enteros y almacenarlos en el vector 
	for (int i = 0; i < n; ++i){
		vector[i] = atoi(argv[i+1]);
	}

	// Expulsarlo y comprobarlo
	//	for (int i = 0; i < n; ++i){
	//	printf("%d ", vector[i]);
	//}

	// pid_t para el hijo 1 y para el hijo 2
	pid_t pid1, pid2;
	int valor1, valor2;
	int status;
	int suma1, suma2;

	// voy a asignar tareas a los hijos
	
	// hijo 1
	if ((pid1=fork())<0){
		printf("Error en el fork hijo 1\n");
		exit(1);
	} else if (pid1==0){
		// aqui es donde asigno la tarea
		valor1= contarPares(vector, n);
		printf("Primer Hijo: ");
		printf("PID: %d. PPID: %d\n", getpid(), getppid());
		printf("valor1 = %d \n", valor1);	
	
		//return valor;
		exit(valor1);
			
	}


	// hijo 2
	if ((pid2=fork())<0){
                printf("Error en el fork hijo 2\n");
                exit(1);
        } else if (pid2==0){
                // aqui es donde asigno la tarea
                valor2=contarImpares(vector,n);
		printf("Segundo Hijo: ");
                printf("PID: %d. PPID: %d\n", getpid(), getppid());
                printf("valor2 = %d\n", valor2);
		exit(valor2);

        }

	// Padre esperando a los hijos
	
	printf("Padre esperando a los hijos que terminen ... \n");

	waitpid(pid1,&status,0);
	suma1 = status >> 8;
	waitpid(pid2,&status,0);
	suma2 = status >> 8;
	


	printf("Trabajo terminado tnato de los hijos como del padre\n");
	// al finalizar liberar memoria del vector dinamico
	
	printf ("Suma total= %d", suma1 + suma2);

	free(vector);
	return 0;




}
