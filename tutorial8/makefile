B = build/

make: $(B)coworkers.o $(B)person.o $(B)stats.o main

main:
	gcc -o $(B)coworkers $(B)coworkers.o $(B)person.o $(B)stats.o

$(B)coworkers.o: coworkers.c person.c person.h
	gcc -c coworkers.c -o $(B)coworkers.o

$(B)person.o: person.c person.h stats.c stats.h
	gcc -c person.c -o $(B)person.o

$(B)stats.o: stats.c
	gcc -c stats.c -o $(B)stats.o

clean:
	rm $(B)coworkers
	rm $(B)*.o

