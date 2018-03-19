
#define MAXSIZE 1024 

typedef unsigned long int u32;

struct lineaEntrada {
	int numCaracteres;
	char texto[80];
	struct lineaEntrada *next;
};

struct AristaSt {
  	u32 vert1;
  	u32 vert2;
};

struct GrafoSt {
	u32 numVertices;
	u32 numAristas;
	u32 numColores; 
	u32 (*vertices)[]; //ORDENADOS!!!! 
	struct AristaSt (*aristas)[];
	u32 (*colores)[];
};



typedef struct GrafoSt *Grafo;

