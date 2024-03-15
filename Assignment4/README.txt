Name: Yuntian Ye
Student Number: 101322932

Source Files:
display.c 
display.h
graphMaker.c 
graphTester.c 
makefile 
obstacles.h

Compiling and Running Instructions:
1. Compile the code using the following command: 
	make or make all

2. Run the program:

	./build/graphTester <V> <K> <E>

<V> is a number from 20 to 2000 (inclusively) which represents the number of vertices to 
add to the graph. <K> is a number between 1 and 25 (inclusively) that indicates the number of 
nearest-neighbours that each vertex will attempt to be connected to in the graph. <E> is a number 
from 1 to 5 (inclusively) representing the environment number to use. 

3. To clean the files use command:
	make clean

