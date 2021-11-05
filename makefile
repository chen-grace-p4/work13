all: main.o work13.o
	gcc -o work13 main.o work13.o
main.o: main.c work13.h
	gcc -c main.c
work13.o: work13.c work13.h
	gcc -c work13.c
run:
	./work13
clean:
	rm *.o
	rm work13
