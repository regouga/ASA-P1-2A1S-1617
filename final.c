/* ASA - Projeto 1
Grupo 29: Miguel Regouga, 83530 | Pedro Caldeira, 83539
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node * link;

struct node {
	int v;
	link next;
};

struct Graph {
	int size;
	link* array;
};

int* entradas; /* Vetor global que guarda o numero de entradas de cada vertice do grafo */

link createNewNode(int element, link next) {
	link newNode = malloc(sizeof(struct node));
	newNode->v = element;
	newNode->next = next;
	return newNode;
}

struct Graph* createNewGraph (int s) {
    int i;
	struct Graph* g = malloc(sizeof(struct Graph));
	entradas = malloc(s * sizeof(int));
	g->size = s;
	g->array = malloc(s*sizeof(link));
	for (i = 0; i < s; i++) {
		g->array[i] = NULL;
		entradas[i] = 0;
	}
	return g;
}

void addConnection (struct Graph* g, int old, int new) {
	g->array[old-1] = createNewNode (new, g->array[old-1]);
	entradas[new]++; /* Incremento do indice correspondente do vetor entradas */
}


void topologicalSort(struct Graph* graph) {
	int sizeG = graph->size;
	int i, k, u, listL[sizeG+1], listQ[sizeG+1];
	int countQ = 0, iterator = 0, popIterator = 0, countL = 0, flagInsuf = 0; 
	/* popIterator representa o proximo elemento a ser libertado */
	/* iterator representa o proximo indice a ser preenchido */
    
    for (i = 1; i <= sizeG; i++) {
		if (entradas[i] == 0) {         
			listQ[iterator] = i;
            iterator++;
            countQ++;
		}
	}
	
	while (countQ > 0) {
		if (countQ > 1) flagInsuf = 1; 
		/* Se isto se verificar, ha mais do que 1 vertice sem arcos de entrada, logo os dados sao insuficientes */
        
        u = listQ[popIterator++];
        countQ--;
        link h = graph->array[u-1];      
        while (h) {
        	graph->array[u-1] = h->next;
            entradas[h->v]--;
            if (entradas[h->v] == 0) {
                listQ[iterator++] = h->v;
                countQ++;
            }
            h = h->next;
        }
        listL[countL++] = u;
    } 

    if(countL < sizeG) { /* Caso seja incoerente, nao e necessario verificar se e insuficiente */
    	printf("Incoerente\n");	return;
    } else if(flagInsuf) {
    	printf("Insuficiente\n"); return;
    }   
    for (k = 0; k < countL; k++) {
        printf("%d", listL[k]);
        if(k != countL - 1) printf(" ");
    }
    printf("\n");
}

int main() {
	int nPhoto, nCond, i = 0, older, newer;
	scanf("%d %d", &nPhoto, &nCond);
	struct Graph* g = createNewGraph(nPhoto);
	while (i < nCond) {
		scanf("%d %d", &older, &newer);
		addConnection(g, older, newer);
		i++;
	}
	topologicalSort(g);
	return 0;
}