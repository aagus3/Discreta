
#define MAXSIZE 1024 

typedef unsigned long int u32;

struct lineaEntrada {
	int numCaracteres;
	char texto[80];
	struct lineaEntrada *next;
};

struct VecinosSt {
  	struct VerticeSt *vecino;
  	struct VecinosSt *siguiente;
};

struct VerticeSt {
	u32 vertice;
	u32 color;
	struct VecinosSt *vecinos;
};

struct GrafoSt {
	u32 numVertices;
	u32 numAristas;
	u32 numColores; 
	struct VerticeSt (*vertices)[];
};



typedef struct GrafoSt *Grafo;


