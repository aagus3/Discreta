#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

void vaciarLinea(char (*linea)[], int size) {
	for (int i=0; i<size; i++) {
		(*linea)[i] = ' ';
	}
}

Grafo ConstruccionDelGrafo() {
	char (*str)[] = malloc(1024*sizeof(char));
   	scanf("%s", *str);
	while (((*str)[0]) == 'c') {
		vaciarLinea(str, 1024);
		scanf("%s", *str);
	}
	if (strncmp("p edge", *str, 5)) {
		printf("%s", *str);
	}
	free(str);
	struct GrafoSt *grafo = malloc(sizeof(struct GrafoSt));
	grafo->vertices = calloc(8, sizeof(u32));
	grafo->aristas = calloc(8, sizeof(struct AristaSt));
	grafo->numVertices = 8;
	(*(grafo->vertices))[0] = 1;
	(*(grafo->vertices))[1] = 2;
	(*(grafo->vertices))[2] = 3;
	(*(grafo->vertices))[3] = 4;
	(*(grafo->vertices))[4] = 5;
	(*(grafo->vertices))[5] = 6;
	(*(grafo->vertices))[6] = 7;
	(*(grafo->vertices))[7] = 8;
	((*(grafo->aristas))[0]).vert1 = 1;
	((*(grafo->aristas))[0]).vert2 = 4;
	((*(grafo->aristas))[1]).vert1 = 2;
	((*(grafo->aristas))[1]).vert2 = 6;
	((*(grafo->aristas))[2]).vert1 = 3;
	((*(grafo->aristas))[2]).vert2 = 6;
	((*(grafo->aristas))[3]).vert1 = 5;
	((*(grafo->aristas))[3]).vert2 = 4;
	((*(grafo->aristas))[4]).vert1 = 5;
	((*(grafo->aristas))[4]).vert2 = 6;
	((*(grafo->aristas))[5]).vert1 = 8;
	((*(grafo->aristas))[5]).vert2 = 6;
	((*(grafo->aristas))[6]).vert1 = 7;
	((*(grafo->aristas))[6]).vert2 = 6;
        return grafo;
         
}


void DestruccionDelGrafo(Grafo G) {
	free(G);
}

u32 NumeroDeVertices(Grafo G) {
        return G->numVertices;
}

u32 NumeroDeLados(Grafo G) {
        return G->numAristas;
}

u32 NumeroDeColores(Grafo G) {
        return G->numColores;
}

u32 NombreDelVertice(Grafo G, u32 i) {
	return (*(G->vertices))[i];
}

u32 ColorDelVertice(Grafo G, u32 i) {
	return (*(G->colores))[i];
}

/*u32 ColorJotaesimoVecino(Grafo G, u32 i, u32 j) {
	
}*/

u32 GradoDelVertice(Grafo G, u32 i) {
	u32 vertice = NombreDelVertice(G, i);
	u32 grado = 0;
	for (u32 j=0; j<(G->numVertices); j++) {
		if (((*(G->aristas))[j]).vert1 == vertice || ((*(G->aristas))[j]).vert2 == vertice) {
			grado++;
		}
	}
	return grado;
}

int main() {
	Grafo G = ConstruccionDelGrafo();
	//int f = (int) NombreDelVertice(G, 1);
	//printf("%i", f);
	//int f = (int) GradoDelVertice(G, 0);
	//printf("%i", f);
	DestruccionDelGrafo(G);
        return 0;
}




