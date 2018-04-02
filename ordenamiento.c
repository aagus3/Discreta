u32 GradoDelVertice(Grafo G, u32 i) {
	u32 grado = 0;
	struct VecinosSt *actual = ((*(G->vertices))[i]).vecinos;
	while (actual != NULL) {
		actual = actual->siguiente;
		grado++;
	}
	return grado;
}


u32 partitionColor (Grafo G, u32 low, u32 high)
{
    // pivot (Element to be placed at right position)
    u32 pivot = ((*(G->vertices))[high]).vertice;  
 
    u32 i = (low - 1);  // Index of smaller element

    for (u32 j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (((*(G->vertices))[j]).vertice <= pivot)
        {
        	i++;    // increment index of smaller element
        	struct VerticeSt tmp = ((*(G->vertices))[j]);
		((*(G->vertices))[j]) = ((*(G->vertices))[i]);
		((*(G->vertices))[i]) = tmp;
        }
    }
    struct VerticeSt tmp2 = ((*(G->vertices))[i+1]);
    ((*(G->vertices))[i+1]) = ((*(G->vertices))[high]);
    ((*(G->vertices))[high]) = tmp2;
    return (i + 1);
}

u32 partitionWP (Grafo G, u32 low, u32 high)
{
    // pivot (Element to be placed at right position)
    u32 pivot = GradoDelVertice(G, high);  
 
    u32 i = (low - 1);  // Index of smaller element

    for (u32 j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (GradoDelVertice(G, j) > pivot)
        {
        	i++;    // increment index of smaller element
        	struct VerticeSt tmp = ((*(G->vertices))[j]);
		((*(G->vertices))[j]) = ((*(G->vertices))[i]);
		((*(G->vertices))[i]) = tmp;
        }
    }
    struct VerticeSt tmp2 = ((*(G->vertices))[i+1]);
    ((*(G->vertices))[i+1]) = ((*(G->vertices))[high]);
    ((*(G->vertices))[high]) = tmp2;
    return (i + 1);
}

void quicksortWP(Grafo G, u32 low, u32 high)
{	
	
	if (low < high)
	{
        /* pi is partitioning index, arr[p] is now
           at right place */
        u32 pi = partitionWP(G, low, high);

        quicksortWP(G, low, pi - 1);  // Before pi
        quicksortWP(G, pi + 1, high); // After pi
    }
}

void quicksortColor(Grafo G, u32 low, u32 high)
{	
	
	if (low < high)
	{
        /* pi is partitioning index, arr[p] is now
           at right place */
        u32 pi = partitionColor(G, low, high);

        quicksortColor(G, low, pi - 1);  // Before pi
        quicksortColor(G, pi + 1, high); // After pi
    }
}

