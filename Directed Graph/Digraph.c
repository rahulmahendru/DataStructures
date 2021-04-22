#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Digraph.h"

/*** Constructors-Destructors ***/

// DigraphObj struct
typedef struct DigraphObj{
    int numVertices;
    int numEdges;
    List* arr;
    int* visit;
    int* color;
    int* d;
    int* inD;
    List topo;
}DigraphObj;

// newDigraph()
// Returns a Digraph that points to a newly created DigraphObj representing a digraph which has
// n vertices and no edges.
Digraph newDigraph(int numVertices){
    Digraph G = malloc(sizeof(DigraphObj));
    G->numVertices = numVertices;
    G->numEdges = 0;
    G->arr = malloc((numVertices)*sizeof(List));
    for(int a=0;a<numVertices;a++){
        G->arr[a]=newList();
    }
    G->visit = malloc((numVertices+1)*sizeof(int));
    G->color = malloc((numVertices+1)*sizeof(int));
    G->d = malloc((numVertices+1)*sizeof(int));
    G->inD = malloc((numVertices)*sizeof(int));
    G->topo = newList();
    return(G);
}

// freeDigraph()
// Frees all dynamic memory associated with its Digraph* argument, and sets
// *pG to NULL.
void freeDigraph(Digraph* pG){
    if(pG==NULL && *pG==NULL){
        for(int i=0;i<(*pG)->numVertices;i++){
            freeList(&((*pG)->arr[i]));
        }
        free((*pG)->visit);
        (*pG)->visit = NULL;
        (*pG)->color = NULL;
        (*pG)->d = NULL;
        (*pG)->inD = NULL;
        (*pG)->topo = NULL;
        (*pG)->numEdges = 0;
        (*pG)->numVertices = 0;
        free(*pG);
        *pG=NULL;
    }
}

/*** Access functions ***/

// getOrder()
// Returns the order of G, the number of vertices in G.
int getOrder(Digraph G){
    return (G->numVertices);
}

// getSize()
// Returns the size of G, the number of edges in G.
int getSize(Digraph G){
    return (G->numEdges);
}

// getOutDegree()
// Returns the number of outgoing neighbors that vertex u has in G, the number of vertices v such
// that (u, v) is an edge in G. Returns -1 if v is not a legal vertex.
int getOutDegree(Digraph G, int u){
    if (u<1 || u>G->numVertices)
        return(-1);
    return(G->arr[u-1]->length);
}

// getNeighbors
// Returns a list that has all the vertices that are outgoing neighbors of vertex u, i.e.,
// a list that has all the vertices v such that (u, v) is an edge in G.
// There is no input operation that corresponds to getNeighbors.
List getNeighbors(Digraph G, int u){
    return (G->arr[u-1]);
}

/*** Manipulation procedures ***/

// addEdge()
// Adds v to the adjacency list of u, if that edge doesn’t already exist.
// If the edge does already exist, does nothing. Used when edges are entered or added.
// Returns 0 if (u, v) is a legal edge, and the edge didn’t already exist.
// Returns 1 if (u, v) is a legal edge and the edge did already exist.
// Returns -1 if (u, v) is not a legal edge.
int addEdge(Digraph G, int u, int v){
    if (u<1 || u>G->numVertices || v<1 || v>G->numVertices){
        return(-1);
    }
    Node M=G->arr[u-1]->front;
    int check = 0;
    while (M!=NULL){
        if(M->data==v)
            check++;
        M=M->next;
    }
    if(check!=0){
        return(1);
    }
    else{
        if (G->arr[u-1]->length==0){
            append(G->arr[u-1], v);
        }
        else if(G->arr[u-1]->back->data < v){
            append(G->arr[u-1], v);
        }
        else{
            M = G->arr[u-1]->front;
            while(M!=NULL && M->data < v){
                M = M->next;
            }
            insertBefore(G->arr[u-1], M, v);
        }
        G->numEdges++;
        return(0);
    }
}

// deleteEdge()
// Deletes v from the adjacency list of u, if that edge exists.
// If the edge doesn’t exist, does nothing. Used when edges are deleted.
// Returns 0 if (u, v) is a legal edge, and the edge did already exist.
// Returns 1 if (u, v) is a legal edge and the edge didn’t already exist.
// Returns -1 if (u, v) is not a legal edge.
int deleteEdge(Digraph G, int u, int v){
    if (u<1 || u>G->numVertices || v<1 || v>G->numVertices){
        return(-1);
    }
    Node M = G->arr[u-1]->front;
    int check = 0;
    while (M!=NULL){
        
        if(M->data==v){
            
            check++;
        
        }
        M=M->next;
    }
    
    if(check!=0){
        Node N = newNode(v);
        deleteNode(G->arr[u-1],N);
        G->numEdges--;
        return(0);
    }
    return(1);
}

/*** Other operations ***/

// printDigraph()

// Outputs the digraph G in the same format as an input line, including the number of vertices
// and the edges. The edges should be in sorted order, as described above.
void printDigraph(FILE* out, Digraph G){
    fprintf(out,"%d", G->numVertices);
    for(int i=0;i<G->numVertices;i++){
        Node M=G->arr[i]->front;
        while(M!=NULL){
            fprintf(out,", ");
            fprintf(out, "%d %d", i+1,M->data);
            M=M->next;
        }
    }
}

// distance()
// Outputs the distance between vertices u and v if there is a directed path between them in the
// digraph. Otherwise, outputs INF
void distance(FILE* out, Digraph G, int u, int v){
    DistanceBFS(G,u);
    if(G->d[v-1]!=0){
    fprintf(out, "%d\n", G->d[v-1]);
    }
    else{
        fprintf(out,"INF\n");
    }
}

// acyclic()
// Outputs YES if the digraph is acyclic. Otherwise, outputs NO.
void acyclic(FILE* out, Digraph G){
    int check = DFS(G,G->numVertices);
    if(check==POSSIBLE)
        fprintf(out,"YES");
    else
        fprintf(out,"NO");
}

// topoSort()
// Outputs a topological sort of the digraph. If the digraph is not acyclic, outputs IMPOSSIBLE.
void topoSort(FILE* out, Digraph G){
    clear(G->topo);
    int check = DFS(G, 1);
    if (check==POSSIBLE){
        int start=1;
        while(start<=G->numVertices){
            if(InDegreeExists(G,start)==FOUND){
                DFS(G, start);
                Node N = G->topo->front;
                while(N!=NULL){
                    fprintf(out, "%d ", N->data);
                    N=N->next;
                }
                return;
            }
            start++;
        }
        return;
    }
        fprintf(out, "IMPOSSIBLE");
}

// Helper Methods

/*** For distance() ***/

// setInitial()
// to set all the arrays for distance to NULL and 0
void setInitial(Digraph G){
    for (int i=1; i<=G->numVertices;i++){
        G->color[i]=WHITE;
        G->d[i]=0;
    }
}

// setDistanceBFS()
// to set the distance to each vertex from the source using BFS
// the BFS algorithm has been adapted from the CLRS textbook
void DistanceBFS(Digraph G, int u){
    setInitial(G);
    G->color[u]=GRAY;
    G->d[u]=0;
    List L = newList();
    append(L, u);
    while(L->length>0){
        int temp = L->front->data;
        deleteFront(L);
        List neighbors = getNeighbors(G, temp);
        Node N = neighbors->front;
        while(N!=NULL){
            if(G->color[N->data]==WHITE){
                G->color[N->data]=GRAY;
                G->d[(N->data)]=G->d[temp]+1;
                append(L,N->data);
            }
            N=N->next;
        }
        G->color[temp]=BLACK;
    }
}


/*** Topographical Sort and Acyclic Functions ***/

// unvisitAll()
// Marks all vertices of the graph as UNVISITED.
void unvisitAll(Digraph G){
    for(int i=1; i<=G->numVertices;i++){
        G->visit[i]=UNVISITED;
    }
}

int DFS(Digraph G, int u){
    unvisitAll(G);
    List L = newList();
    append(L, u);
    while(L->length>0){
        int v = L->back->data;
        deleteBack(L);
        if(G->visit[v] != VISITED){
            G->visit[v]=VISITED;
        }
        else {
            return IMPOSSIBLE;
        }
        append(G->topo , v);
        Node N=G->arr[v-1]->front;
        while(N!= NULL){
            if(G->visit[N->data] == UNVISITED){
                append(L, N->data);
            }
            N=N->next;
            
        }
    }
    return POSSIBLE;
}


int InDegreeExists(Digraph G, int u){
    for(int i=0;i<G->numVertices;i++){
        Node N=G->arr[i]->front;
        while(N!=NULL){
            if(N->data==u){
                return FOUND;
            }
            N=N->next;
        }
    }
    return NOTFOUND;
}
