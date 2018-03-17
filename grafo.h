

struct GrafoSt {
  u32 vertices[];
  struct AristaSt aristas[];
  u32 colores[];
  u32 orden[]; 
  
};

struct AristaSt {
  u32 vert1;
  u32 vert2;
}; 

typedef struct GrafoSt *Grafo;
typedef unsigned long int u32;
