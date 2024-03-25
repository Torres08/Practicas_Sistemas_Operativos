# Modulo II Uso de los Servicios del SOP mediante la API

ejercicions modulo II SO ETSIIT UGR
todos sus ejercicios tienen su makefile correspondiente a ejecutar

## Tema 1 y 2: LLamadas al sistema para el SA
- `Ejercicio 0:` Contar numero archivos regulares en un directorio dado y mostrar resultado
- `Ejercicio 1:` ¿Qué hace el siguiente programa? Probad tras la ejecucion del programa las siguientes ordenes shell
- `Ejercicio 2:` implementa un programa que realice la siguiente funcionalidad. El programa acepta como argumento el nombre de un archivo (pathname),  lo abre y lo lee en bloques de tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la siguiente información:
- `Ejercicio 3:` ¿Qué hace el siguiente programa?
- `Ejercicio 4:` Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode) usando para ello los flags definidos en <sys/stat.h> para el campo st_mode de la struct stat y comprueba que funciona en un programa simple. COnsulta en un libro de C o en internet como se especifica una macro con argumentos en C
- `Ejercicio 5:` ¿Qué hace el siguiente programa?
- `Ejercicio 6:` Programa octal4dig
- `Ejercicio 7:` Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como argumento y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el grupo y para otros. Ademas del nombre de los archivos encontrados, deberá devolver sus números de inodo y la suma total de espacio ocupado por dicho archivo.
- `Ejercicio 8:` Prueba el programa que recorre un sub-arbol con la funcion nftw().Ademas imlpementa de nuevo el ejercicio7 pero usando nftw().
- `prueba1y2:` resumen ejercicios tema 1 y 2 lo más importante, Contar numero archivos regulares en un directorio dado , mostrar resultado y mas
- `prueba1y2_nftw:` version anterior pero usando nftw y recorriendo subdirectorios

## Tema 3: Llamadas al sistema para el Control de Procesos
- `Ejercicio 1:` Implementa un programa en C que tenga como argumento un número entero. Este programa debe crear un proceso hijo que se encargará de  comprobar si dicho número es un número par o impar e informará al usuario con un mensaje que se enviará a la salida estándar. A su vez el padre debe comprobar si dicho número es divisible por 4 e informará al usuario con un mensaje que se enviará a la salida estándar.
- `Ejercicio 2:` ¿Qué hace el siguiente programa?, pruebalo con y sin setvbuf Intenta entender lo que ocurre con las variables y sobre todo con los mensajes por pantalla cuando el núcleo tiene activado/desactivado el mecanismo de buffering.
- `Ejercicio 3:` ¿Qué hace el siguiente programa?, comprueba las dos jerarquias, genera 20 procesos en cada una, haz una jerarquia que sea secuancial padre, hijo
- `Ejercicio 4:` Implementa un programa que lance 5 procesos hijos. Cada uno de ellos se identificara en la salida estandar mostrando el mensaje <Soy el hijo PID>. El proceso padre simplemente tendrá que esperar a que todos sus hijos terminen. Cada vez que un hijo termina, el proceso padre mostrará el mensaje <Acaba de finalizar mi hijo con PID> <solo me quedan NUM_HIJOS vivos>
- `Ejercicio 5:` modificacion ejercicio 4, espera el padre primero a los impares 1,3,5 y luego a los pares 2,4
- `Ejercicio 6:` ¿Qué hace el siguiente programa?
- `Ejercicio 7:` Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene, y opcionalmente la cadena “bg”. Nuestro programa deberá ejecutar el programa pasado como primer argumento en foreground si no se especifica la cadena "bg" y en background en caso  contrario. Si el programa tiene argumentos hay que ejecutarlos con estos 
- `Ejercicio 30:` COntar pares e impares con 2 hijos
- `prueba30`: introduzca un vector, cree 2 hijos, uno se encarga de que cada numero del vector es par, se encarga de hacer sumas pares, y el 2 hijo se encarga de ver en el vector los numeros impares y los que haya hace una suma tambien al crear el hijo muestra informacion sobre los hijos como se muestra abajo

## Tema 4: Comunicación entre procesos utilizando cauces
- `Ejercicio 1:` Productor y consumidor comunicacion FIFO
- `Ejercicio 2:` Trabajo con llamadas al sistema del subsistema Procesos y cauces conforme POSIX 2.10
- `Ejercicio 3:` redirigiendo las entradas y salidas estandares de los procesos a los cauces podemos escribir un programa en lenguaje C que permita comunicar órdenes existentes sin necesidad de reprogramarlas, tal y como lo hace el shell. EN perticular, ejecute el siguiente programa que ilustra la comunicacion entre proceso padre e hijo a través de un cauce sin nombre redirigiendo la entrada estandar y la salida estandar del padre y el hijo respectivamente.
- `Ejercicio 4:` Programa del uso de pipes y la redireccion de entrada y salida estandar. "ls sort" utilizando la llamada dup2
- `Ejercicio 5:` Maestro y esclavo

## Tema 5: Llamadas al sistema para gestion y control de señales
- `Ejercicio 1:` Ejercicio envio y recivo Signal
- `Ejercicio 2:` Contador 
- `Ejercicio 3:` Ejemplo de manejador señal SIGINT tarea9.c
- `Ejercicio 4:` Ejemplo de manejador señal SIGINT
- `prueba ` Gestion de señales, utilizar metodos de la biblioteca signal : kill sigaction, sigpromask, 
- `tarea9` : ejemplo llamada al sistema sigaction para estrablecer un manejador para la señal SIGINT
- `tarea10` ejemplo llamada al sistema sigaction para estrablecer un manejador para la señal SIGINT, con un manejador propio
- `tarea 11 `  ejemplo uso signempryset, sigaddset sigsuspend

## Tema 6: Control de archivos y archivos proyectados a memoria
- `Ejercicio 1:` IMplementa un programa que admita t argumentos . El primer argumeto sera una orden de Linux, segundo < o > y el tercero el nombre de un archivo (puede existir o no) Programa ejecutara la orden que se especifica como un argumento primero, y luego redirigira la entrada o salida estandar segun el segundo argumento hacia el archivo indicado en el tercer argumento , < y > tienen que ir entre comillas
- `Ejercicio 2:` Reescribe el programa que implemente un encauzamiento de dos ordenes pero utilizando fcntl.Este programa admite 3 argumentos, el primero y el tercero serán dos ordenes de Linux El segundo argumento será el operador | (pipe) y el programa ejecutará las dos ordenes encauzadas
- `Ejercicio 3:` Construye un programa que verifique que efectivamente, el kernel comprueba que puede darse una situacion de nterbloqueo en el bloqueo de archivos
- `Ejercicio 4:` Construir un programa que se asegure que solo hay una instancia de el en ejecucion en un momento dado. EL programa, una vez establecido el mecanismo para asegurar que solo una instancia se ejecutara, entrara en un bucle infinito que nos permita comprobar que no podemos lanzar más ejecuciones del mismo.En la construccion del mismo, debemos asegurarnos de que el archivo a bloquear no contiene incialmente nada escrito en una ejecucion  anterior del programa
- `Ejercicio 5:` : escribe un programa , similar a la orden cp, que utilice para su implementacion la llamada al sistema mmap y una funcion de C que nos permite copiar memoria, como por ejemplo memcpy. Para conocer el tamaño del archivo de orgen podemos utilizar stat y para establecer el tamaño del archivo destino se puede usar ftruncate.
- `prueba` : fnctl + cerrojos
- `tarea13`: bloque de multiples archivos
- `tarea14 `: ejemplo de creacion de una proyeccion
- `tarea15` visualizaar un archivo con mmap()
- `tarea16` Comparticion de memoria entre procesos padre.hijo con mmap()
- `tarea17` proyeccion aninima con MAP_ANON
- `tarea18` proyeccion anonima con /dev/zero
- `tarea19` proyeccion que deja crecer un archivo

## Tema 7 Construcción de un spool de impresión
Esta sesion se basa unicamente en crear un spool concurrente de impresion en pantalla. Para mas informacion leer el guion. La carpeta old es una antigua version del spool.


