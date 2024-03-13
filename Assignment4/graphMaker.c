#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "obstacles.h"

#define TRUE 1
#define FALSE 0

// Return 1 if line segment (v1---v2) intersects line segment (v3---v4), otherwise return 0
unsigned char linesIntersect(short v1x, short v1y, short v2x, short v2y, short v3x, short v3y, short v4x, short v4y) {
	float uA = ((v4x-v3x)*(v1y-v3y) - (v4y-v3y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
	float uB = ((v2x-v1x)*(v1y-v3y) - (v2y-v1y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
	
	// If uA and uB are between 0-1, there is an intersection
	if (uA > 0 && uA < 1 && uB > 0 && uB < 1) 
		return 1;
	
	return 0;
}

int pointInObstacle(Environment *env, short x, short y);

// Create a graph using the numVertices and k parameters of the given environment.
void createGraph(Environment *env) {	

	// ...
	// WRITE YOUR CODE HERE
	// ...
	
	// Allocate memory for the vertices array
	env->vertices = (Vertex **)malloc(env->numVertices * sizeof(Vertex *));
	if (env->vertices == NULL) {
		printf("Error: malloc failed to allocate memory for vertices\n");
		exit(-1);
	}
	
	srand(time(NULL));
	
	for (int i = 0; i < env->numVertices; i++) {
		// Allocate memory for each vertex
		env->vertices[i] = (Vertex *)malloc(sizeof(Vertex));
		if (env->vertices[i] == NULL) {
			printf("Error: malloc failed to allocate memory for vertex %d\n", i+1);
			exit(-1);
		}
		
		int insideObstacle;
		
		do {
			insideObstacle = FALSE;
			
			env->vertices[i]->x = rand() % (env->maximumX);
			env->vertices[i]->y = rand() % (env->maximumY);
			
			if (pointInObstacle(env, env->vertices[i]->x, env->vertices[i]->y)) 
				insideObstacle = TRUE;
			
		} while (insideObstacle);
	}
}

int pointInObstacle(Environment *env, short x, short y) {
	for (int j = 0; j < env->numObstacles; j++) {
		if (x <= env->obstacles[j].x + env->obstacles[j].w &&
			x >= env->obstacles[j].x && 
			y <= env->obstacles[j].y && 
			y >= env->obstacles[j].y - env->obstacles[j].h) {
			return TRUE;
		}
	}
	return FALSE;
}

// This procedure cleans up everything by creeing all alocated memory
void cleanupEverything(Environment *env) {

	// ...
	// WRITE YOUR CODE HERE
	// ...
	
}


