mymake2: myMake2.c graph.o graph.h
	gcc -Wall -g myMake2.c graph.o graph.h -o mymake2

graph.o: graph.c graph.h
	gcc -Wall -c graph.c -o graph.o

.PHONY: clean
clean:
	-rm *.o
	-rm mymake2