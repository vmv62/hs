all:
	gcc main.o shm.o -o hs

main.o:
	gcc main.c -c main.o

shm.o
	gcc shm.c -c shm.o

clean:
	rm hs
