// ---------------------------------------------------------------------
// Graph.c
// ADT file for Graph
// ---------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"


/*** Constructors-Destructors ***/
// GraphObj struct and type definition
typedef struct GraphObj{
    int numVertices;
    int numEdges;
    List* arr;
    int* visit;
}GraphObj;

// newGraph()
// Returns a Graph that points to a newly created GraphObj representing a graph which has
// n vertices and no edges.
Graph newGraph(int numVertices){
    Graph G = malloc(sizeof(GraphObj));
    G->numVertices = numVertices;
    G->numEdges = 0;
    G->arr=malloc((numVertices)*sizeof(List));
    for(int a=0;a<numVertices;a++){
        G->arr[a]=newList();
    }
    G->visit = malloc((numVertices)*sizeof(int));
    return(G);
}

// freeGraph()
// Frees all dynamic memory associated with its Graph* argument, and sets
// *pG to NULL.
void freeGraph(Graph* pG){
    if(pG==NULL && *pG==NULL){
        for(int i=0;i<(*pG)->numVertices;i++){
            freeList(&((*pG)->arr[i]));
        }
        free((*pG)->visit);
        (*pG)->visit = NULL;
        (*pG)->numEdges = 0;
        (*pG)->numVertices = 0;
        free(*pG);
        *pG=NULL;
    }
}

/*** Access functions ***/

// getOrder()
// Returns the order of G, the number of vertices in G.
int getOrder(Graph G){
    return (G->numVertices);
}

// getSize()
// Returns the size of G, the number of edges in G.
int getSize(Graph G){
    return (G->numEdges);
}

// getNeighbourCount()
// Returns the number of neighbors that vertex v has in G. Returns -1 if v is not a legal vertex.
int getNeighborCount(Graph G, int v){
    // check for legal vertices
    if (v<1 || v>G->numVertices)
        return(-1);
    return(G->arr[v-1]->length);
}

// getNeighbours()
// Returns a list that has all the vertices that are neighbors of u. There is no input operation
// that corresponds to getNeighbors.
List getNeighbors(Graph G, int v){
    return(G->arr[v-1]);
}

/*** Manipulation procedures ***/

// addEdge()
// Adds v to the adjacency list of u and u to the adjacency list of v, if that edge doesn’t
// already exist. If the edge does already exist, does nothing. Used when edges are entered.
// Returns 0 if u and v are legal vertices, otherwise returns -1.
int addEdge(Graph G, int u, int v){
    
    // check for legal vertices
    if (u<1 || u>G->numVertices || v<1 || v>G->numVertices){
        return(-1);
    }
    
    // check if v exits as a neighbour of u and if u is a neighbout of v
    // appends them both to eah others adjacency list if they do not exist
    Node M=G->arr[u-1]->front;
    int check = 0;
    while (M!=NULL){
        if(M->data==v)
            check++;
        M=M->next;
    }
    if(check==0){
        M=G->arr[v-1]->front;
        check = 0;
        while (M!=NULL){
            if(M->data==u)
                check++;
            M=M->next;
        }
        if(check==0){
            append(G->arr[v-1], u);
            append(G->arr[u-1], v);
            G->numEdges++;
        }
    }
    return(0);
}

// unvisitAll()
// Marks all vertices of the graph as UNVISITED.
void unvisitAll(Graph G){
    for(int i=0; i<G->numVertices;i++){
        G->visit[i]=UNVISITED;
    }
}

// getMark()
// Returns the mark for vertex u, which will be UNVISITED, INPROGRESS or ALLDONE.
int getMark(Graph G, int u){
    return(G->visit[u-1]);
}

// setMark()
// Sets the mark for vertex u to be theMark.
// theMark must be UNVISITED, INPROGRESS or ALLDONE.
void setMark(Graph G, int u, int theMark){
    // check if theMark is valid
    if (theMark==-1 || theMark==0 || theMark==1){
        G->visit[u-1]=theMark;
    }
}

// PathExistsRecursive()
// Described below; returns FOUND or NOTFOUND, which are (different) constants.
int PathExistsRecursive(Graph G, int w, int v){
    // Logic followed from an algorithm provided to check if Path exists using recursion
    if(w==v){
        return(FOUND);
    }
    int theFoundValue;
    setMark(G,w,INPROGRESS);
    Node M=getNeighbors(G,w)->front;
    while(M!=NULL){
        if(getMark(G,M->data)==UNVISITED)
            theFoundValue = PathExistsRecursive(G,M->data,v);
        if(theFoundValue==FOUND)
            return(FOUND);
        M=M->next;
    }
    setMark(G,w,ALLDONE);
    return(NOTFOUND);
}

/*** Other operations ***/

// printGraph()
// Prints the Graph G in the same format as an input line, so all that a client need to do is a single
// call to PrintGraph(). But it should not print out an edge twice. Achieve this by only printing
// the edge for {j, k} when j < k.
void printGraph(FILE* out, Graph G){
    fprintf(out,"%d", G->numVertices);
    for(int i=0;i<G->numVertices;i++){
        
        int u = i+1;
        Node M=G->arr[i]->front;
        while(M!=NULL){
            if(u<M->data){
                fprintf(out,", ");
                fprintf(out, "%d %d", u,M->data);
            }
            M=M->next;
        }
    }
}


