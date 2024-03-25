ejercicio0: ejercicio0.c
	gcc ejercicio0.c -o ./papelera/ejercicio0
	./papelera/ejercicio0 ./prueba 5

ejercicio1: ejercicio1.c
	gcc ejercicio1.c -o ./papelera/ejercicio1
	./papelera/ejercicio1
	cat archivo 
	od -c archivo

ejercicio2: ejercicio2.c
	gcc ejercicio2.c -o ./papelera/ejercicio2
	./papelera/ejercicio2 fichero.txt

ejercicio3: ejercicio3.c
	gcc ejercicio3.c -o ./papelera/ejercicio3
	./papelera/ejercicio3 fichero.txt salida.txt papelera

ejercicio4: ejercicio4.c
	gcc ejercicio4.c -o ./papelera/ejercicio4
	./papelera/ejercicio4 fichero.txt 

ejercicio5: ejercicio5.c
	rm -f ./recursos/*
	gcc ejercicio5.c -o ./papelera/ejercicio5
	./papelera/ejercicio5 

ejercicio6: ejercicio6.c
	gcc ejercicio6.c -o ./papelera/ejercicio6
	./papelera/ejercicio6 ./recursos 0667

ejercicio7: ejercicio7.c
	gcc ejercicio7.c -o ./papelera/ejercicio7
	./papelera/ejercicio7 ../Recursos

ejercicio8: ejercicio8.c
	gcc ejercicio8.c -o ./papelera/ejercicio8
	./papelera/ejercicio8 ../Recursos

prueba: prueba1y2.c
	gcc prueba.c -o ./papelera/prueba1y2
	./papelera/prueba1y2 ./prueba 13

prueba_nftw: prueba1y2_nftw.c
	gcc prueba1y2_nftw.c -o ./papelera/prueba1y2_nftw
	./papelera/prueba1y2_nftw ./prueba 20

clean:
	rm -f ./papelera/*
	rm -f ./recursos/*

