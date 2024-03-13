OBJ = build/display.o build/graphMaker.o build/graphTester.o
EXE = build/graphTester

build:
	mkdir build/

all: build $(OBJ)
	gcc -o $(EXE) $(OBJ) -lX11

build/display.o: display.c display.h
	gcc -c display.c -o build/display.o

build/graphMaker.o: graphMaker.c
	gcc -c graphMaker.c -o build/graphMaker.o

build/graphTester.o: graphTester.c
	gcc -c graphTester.c -o build/graphTester.o

clean:
	rm -f $(OBJ) $(EXE)