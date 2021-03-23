all: clean main.o Interface.o Commands.o ExtrasImplementation.o bloomfilterImplementation.o LinkedList.o SkiplistImplementation.o HashImplementation.o
	gcc main.o Interface.o Commands.o ExtrasImplementation.o bloomfilterImplementation.o LinkedList.o SkiplistImplementation.o HashImplementation.o -o vaccineMonitor

main.o: main.c
	gcc -g -c main.c

Interface.o: Interface.c
	gcc -g -c Interface.c

Commands.o: Commands.c
	gcc -g -c Commands.c

ExtrasImplementation.o: ExtrasImplementation.c
	gcc -g -c ExtrasImplementation.c

bloomfilterImplementation.o: bloomfilterImplementation.c
	gcc -g -c bloomfilterImplementation.c

LinkedList.o: LinkedList.c
	gcc -g -c LinkedList.c

SkiplistImplementation.o: SkiplistImplementation.c
	gcc -g -c SkiplistImplementation.c

HashImplementation.o: HashImplementation.c
	gcc -g -c HashImplementation.c

clean:
	rm -f main.o Interface.o Commands.o ExtrasImplementation.o bloomfilterImplementation.o LinkedList.o SkiplistImplementation.o HashImplementation.o vaccineMonitor