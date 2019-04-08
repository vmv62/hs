all: main.o shm.o
	gcc main.o shm.o -o hs

main.o:
	gcc -c main.c

shm.o:
		gcc -c shm.c
clean:
		rm hs
