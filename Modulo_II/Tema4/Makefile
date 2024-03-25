
ejercicio1: ./ejercicio1/consumidor.c ./ejercicio1/productor.c
	gcc ./ejercicio1/consumidor.c -o ./papelera/consumidor
	gcc ./ejercicio1/productor.c -o ./papelera/productor
	./papelera/consumidor &
	./papelera/productor "texto de preuba hola mundo fin"
	./papelera/productor hola
	./papelera/productor "otro texto mas"
	./papelera/productor fin
	./papelera/productor "texto que no se produce, antes va un fin"

ejercicio2: ./ejercicio2.c
	gcc ./ejercicio2.c -o ./papelera/ejercicio2
	./papelera/ejercicio2

ejercicio3: ./ejercicio3.c
	gcc ./ejercicio3.c -o ./papelera/ejercicio3
	./papelera/ejercicio3

ejercicio4: ./ejercicio4.c
	gcc ./ejercicio4.c -o ./papelera/ejercicio4
	./papelera/ejercicio4

ejercicio5: ./ejercicio5/maestro.c ./ejercicio5/esclavo.c
	gcc ./ejercicio5/maestro.c -o ./papelera/maestro
	gcc ./ejercicio5/esclavo.c -o ./papelera/esclavo
	./papelera/maestro 10 50

prueba2: ./prueba/maestro.c ./prueba/esclavo.c
	gcc ./prueba/maestro.c -o ./prueba/papelera/maestro
	gcc ./prueba/esclavo.c -o ./prueba/papelera/esclavo
	./prueba/papelera/maestro 1 2 3 4 5 20 21 22