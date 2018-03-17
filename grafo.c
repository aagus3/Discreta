#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Grafo ConstruccionDelGrafo() {
	struct GrafoSt *grafo = malloc(sizeof(struct GrafoSt));
	grafo->vertices = calloc(4, sizeof(u32));
	(*(grafo->vertices))[0] = 2;
	(*(grafo->vertices))[1] = 3;
	(*(grafo->vertices))[2] = 4;
	(*(grafo->vertices))[3] = 7;
        return grafo;
         
}

u32 NumeroDeVertices(Grafo G) {
	u32  f= (*(G->vertices))[0];
        return f;
}

int main() {
	Grafo g = ConstruccionDelGrafo();
	int f = (int) NumeroDeVertices(g);
	printf("%i", f);
        return 0;
}




