
typedef unsigned long int u32;

struct AristaSt {
  u32 vert1;
  u32 vert2;
};

struct GrafoSt {
  u32 (*vertices)[];
  struct AristaSt (*aristas)[];
  u32 (*colores)[];
  u32 (*orden[]); 
  
};



typedef struct GrafoSt *Grafo;

