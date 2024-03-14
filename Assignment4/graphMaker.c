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

int squareDistance(Vertex* v1, Vertex* v2) {
	return (v2->x - v1->x)*(v2->x - v1->x) + (v2->y - v1->y)*(v2->y - v1->y);
}

int isIntersect(Vertex *vertex1, Vertex *vertex2, Environment *env) {
	// go through each obstacle
    for (int i = 0; i < env->numObstacles; i++) {
        Obstacle obst = env->obstacles[i];
        // check if each edge of the obstacle has intersect with path
        if (linesIntersect(vertex1->x, vertex1->y, vertex2->x, vertex2->y, obst.x, obst.y, obst.x, obst.y - obst.h) ||
			linesIntersect(vertex1->x, vertex1->y, vertex2->x, vertex2->y, obst.x, obst.y, obst.x + obst.w, obst.y) ||
			linesIntersect(vertex1->x, vertex1->y, vertex2->x, vertex2->y, obst.x, obst.y - obst.h, obst.x + obst.w, obst.y - obst.h) ||
            linesIntersect(vertex1->x, vertex1->y, vertex2->x, vertex2->y, obst.x + obst.w, obst.y, obst.x + obst.w, obst.y - obst.h)) {
            return TRUE;
        }
    }
    return FALSE;
}

int pointInObstacle(Environment *env, short x, short y);
void findKNearNeighbor(Environment *env, Vertex* v);

// Create a graph using the numVertices and k parameters of the given environment.
void createGraph(Environment *env) {
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
			
			env->vertices[i]->x = rand() % (env->maximumX + 1);
			env->vertices[i]->y = rand() % (env->maximumY + 1);
			
			if (pointInObstacle(env, env->vertices[i]->x, env->vertices[i]->y)) 
				insideObstacle = TRUE;
			
		} while (insideObstacle);
	}
	
	for (int i = 0; i < env->numVertices; i++) {
		findKNearNeighbor(env, env->vertices[i]);
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

void findKNearNeighbor(Environment *env, Vertex* v) {
	v->neighbours = (Neighbour *)malloc(sizeof(Neighbour));
	if (v->neighbours == NULL) {
		printf("Error: malloc failed to allocate memory for neighbours\n");
		exit(-1);
	}
	
	// Array to hold k nearest neighbours
	Vertex** nearest = (Vertex **)malloc(env->k * sizeof(Vertex *));
	if (nearest == NULL) {
		printf("Error: malloc failed to allocate memory for nearest\n");
		exit(-1);
	}
	// make the first k vertices the nearest
	for (int i = 0; i < env->k; i++) {
		nearest[i] = env->vertices[i];
	}
	
	// go through each vertex except the vertex itself
	for (int i = 0; i < env->numVertices; i++) {
		if (v == env->vertices[i]) continue;
		
		Vertex* currentVertex = env->vertices[i];
		
		int distance = squareDistance(v, currentVertex);
		
		// go through the nearest array and check 
		// if the current vertex is closer to any vertex in the array
		for (int j = 0; j < env->k; j++) {
			if (distance < squareDistance(v, nearest[j])) {
				// if it's closer, replace the farthest vertex with the current vertex
				nearest[j] = currentVertex;
				break;
			}
		}
	}
	
	Neighbour* lastNbr = NULL;
	// add the nearest vertices to the neighbours linked list
	for (int i = 0; i < env->k; i++) {
		Vertex *nbr = nearest[i];
		
		if (isIntersect(v, nbr, env)) {
			continue;
		}
		
		Neighbour *newNeighbour = (Neighbour *)malloc(sizeof(Neighbour));
		if (newNeighbour == NULL) {
			printf("Error: malloc failed to allocate memory for newNeighbour\n");
			exit(-1);
		}
		
		newNeighbour->vertex = nbr;
		newNeighbour->next = NULL;
		
		// if it's the first un-intersect neighbour, add it to the vertex's neighbours
		if (lastNbr == NULL) {
			v->neighbours = newNeighbour;
		// if it's not the first neighbour, add it to the last neighbour's next
		} else {
			lastNbr->next = newNeighbour;
		}
		
		// update lastNbr
		lastNbr = newNeighbour;
	}
	
	free(nearest);
}

// This procedure cleans up everything by creeing all alocated memory
void cleanupEverything(Environment *env) {

	// ...
	// WRITE YOUR CODE HERE
	// ...
	
}
