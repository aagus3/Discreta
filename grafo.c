#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "grafo.h"
#include "ordenamiento.c"

void vaciarLinea(char (*linea)[], int size) {
	for (int i=0; i<size; i++) {
		(*linea)[i] = ' ';
	}
}

int comandoValido(char (*comando)[]) {
	if ((*comando)[0] == 'c') {
		return 0;
	}
	u32 a, b;
	int condicion1 = !strncmp("p edge ", *comando, 7);
	int condicion2 = isdigit((*comando)[7]);
	sscanf(*comando, "%*[^0123456789]%ld%*[^0123456789]%ld", &a, &b);
	int condicion3 = (a>0 && b>0);
	if (condicion1 && condicion2 && condicion3) {
		return 1;
	} else {
		printf("Comando no valido \n");
		return 0;
	}
}

int aristaValida(char (*comando)[]) {
	u32 a, b;
	int condicion1 = !strncmp("e ", *comando, 2);
	sscanf(*comando, "%*[^0123456789]%ld%*[^0123456789]%ld", &a, &b);
	int condicion2 = (a>0 && b>0);
	if (condicion1 && condicion2) {
		return 1;
	} else {
		printf("Comando no valido \n");
		return 0;
	}

}

u32 NombreDelVertice(Grafo G, u32 i) {
	return ((*(G->vertices))[i]).vertice;
}


void InsertarVertice(Grafo G, u32 indice, u32 vert, u32 color) {
	((*(G->vertices))[indice]).vertice = vert;
	((*(G->vertices))[indice]).color = color;
	((*(G->vertices))[indice]).vecinos = NULL;
} 

void InsertarVecino(Grafo G, u32 i, u32 j) {
	struct VecinosSt *nuevo = malloc(sizeof(struct VecinosSt));
	nuevo->vecino = &((*(G->vertices))[j]);
	nuevo->siguiente = NULL;
	if (((*(G->vertices))[i]).vecinos == NULL) {
		((*(G->vertices))[i]).vecinos = nuevo;
	} else {
		struct VecinosSt *actual = ((*(G->vertices))[i]).vecinos;
		if (nuevo->vecino == actual->vecino) {
				return;
		}
		while (actual->siguiente != NULL) {
			if (nuevo->vecino == actual->vecino) {
				return;
			} else {
				actual = actual->siguiente;
			}
		}
		actual->siguiente = nuevo;		
	}
}

void AgregarArista(Grafo G, u32 i, u32 j) {
	InsertarVecino(G, i, j);
	InsertarVecino(G, j, i);
}


void OrdenNatural(Grafo G) {
	quicksortColor(G, 1, (G->numVertices)-1);
}

void OrdenWelshPowell(Grafo G) {
	quicksortWP(G, 1, (G->numVertices)-1);
}


void dibujarVertices(Grafo G) {
	u32 k = G->numVertices;
	u32 j = 0;
	while (j<k) {
		printf("%ld -- %ld \n",((*(G->vertices))[j]).vertice, ((*(G->vertices))[j]).color);
		j++;
	}
}


void Decolorar(Grafo G) {
	G->numColores = 0;
	for (u32 i = 0; i<G->numVertices; i++) {
		((*(G->vertices))[i]).color = 0;
	}
}


int ComprobarVecinoColor (Grafo G, u32 i, u32 color) {
	struct VecinosSt *actual = ((*(G->vertices))[i]).vecinos;
	while (actual != NULL) {
		if (((*(actual->vecino))).color == color) {
			return 1;
		} else {
			actual = actual->siguiente;
		}
	}
	return 0;	
}

int ComprobarRangoVecinoColor (Grafo G, u32 i, u32 rango) {
	u32 indice = 1;
	while (indice <= rango) {
		if (!ComprobarVecinoColor(G, i, indice)) {
			return 0;
		}
		indice++;
	}
	return 1;
}


u32 ColorAlAzar(u32 colores[], u32 numColores, u32 semilla) {	
	return colores[0*numColores*semilla];
}

u32 NotSoGreedy(Grafo G, u32 semilla) {
	Decolorar(G);
	u32 nvertices = G->numVertices;
	u32 colores = 1+(0*semilla);
	((*(G->vertices))[0]).color = 1;
	u32 indice = 1;
	while (indice < nvertices) {
		//u32 gradoVertice = GradoDelVertice(G, indice);
		if (ComprobarRangoVecinoColor(G, indice, colores)) {
			((*(G->vertices))[indice]).color = colores+1;
				colores++;
		} else {
			u32 i = 1;
			u32 arregloc = 0;
			u32 k = colores;
			u32 coloresSU[k-1];
			while (i<=k) {
				if (!ComprobarVecinoColor(G, indice, i)) {
					coloresSU[arregloc] = i;
					arregloc++;
				}
				i++;
			}
			((*(G->vertices))[indice]).color = ColorAlAzar(coloresSU, arregloc, 5);
			
		}
		indice++;
	}
	G->numColores = colores;
	return semilla;

}

Grafo ConstruccionDelGrafo() {
	/*char (*str)[] = malloc(MAXSIZE*sizeof(char));
   	fgets(*str, MAXSIZE-1, stdin);
	while (!comandoValido(str)) {
		vaciarLinea(str, MAXSIZE);
		fgets(*str, MAXSIZE-1, stdin);
	}
	u32 cantVertices, cantAristas;
	sscanf(*str, "%*[^0123456789]%ld%*[^0123456789]%ld", &cantVertices, &cantAristas);
	struct GrafoSt *grafo = malloc(sizeof(struct GrafoSt));
	grafo->vertices = calloc(cantVertices, sizeof(u32));
	grafo->aristas = calloc(cantAristas, sizeof(struct AristaSt));
	grafo->numVertices = cantVertices;
	grafo->numAristas = cantAristas;
	u32 v1,v2;
	for (int i=0; i<cantAristas; i++) {
		printf("insertar arista: ");
		vaciarLinea(str, MAXSIZE);
		fgets(*str, MAXSIZE-1, stdin);
		while (!aristaValida(str)) {
			vaciarLinea(str, MAXSIZE);
			printf("insertar arista: ");
			fgets(*str, MAXSIZE-1, stdin);
		}
		sscanf(*str, "%*[^0123456789]%ld%ld", &v1, &v2);
		if (v1 == v2) {
			printf("No es arista\n");
			i--;
		} else {
			((*(grafo->aristas))[i]).vert1 = v1;
			((*(grafo->aristas))[i]).vert2 = v2;
		}
	}
	
	ordenSimpleVertices(grafo);
	printf("Cantidad de aristas: %lu  \n", cantAristas);
	printf("Cantidad de vertices: %lu  \n", cantVertices);
	free(str);*/
	//ordenSimpleVertices(grafo);
	struct GrafoSt *grafo = malloc(sizeof(struct GrafoSt));
	//((*(grafo->vertices))[0]).vertice = 1;
	grafo->numVertices = 10000;
	grafo->vertices = calloc(grafo->numVertices, sizeof(struct VerticeSt));
	for (int i=0; i<10000; i++) {
		InsertarVertice(grafo, i, rand(), i);
	}
	OrdenWelshPowell(grafo);
	NotSoGreedy(grafo, 4);
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


u32 ColorDelVertice(Grafo G, u32 i) {
	return ((*(G->vertices))[i]).color;
}

u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j) {
	struct VecinosSt *actual = ((*(G->vertices))[i]).vecinos;
	while (j>0) {
		actual = actual->siguiente;
		j--;
	}
	return (*(actual->vecino)).vertice;
}

u32 ColorJotaesimoVecino(Grafo G, u32 i, u32 j) {
	struct VecinosSt *actual = ((*(G->vertices))[i]).vecinos;
	while (j>0) {
		actual = actual->siguiente;
		j--;
	}
	return (*(actual->vecino)).color;
	
}



int main() {
	Grafo G = ConstruccionDelGrafo();
	//u32 b = ComprobarRangoVecinoColor(G, 6, 4);
	//u32 f = G->numColores + (0*b);
	//printf("%ld", b);
	dibujarVertices(G);
	DestruccionDelGrafo(G);
        return 0;
}

