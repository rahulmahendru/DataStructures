// ---------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
// ---------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE
#define _GRAPH_H_INCLUDE
 
#define UNVISITED -1
#define INPROGRESS 0
#define ALLDONE 1
#define FOUND 1
#define NOTFOUND 0

#include"List.h"

// Type Definition
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int numVertices);
// Returns a Graph that points to a newly created GraphObj representing a graph which has
// n vertices and no edges.

void freeGraph(Graph* pG);
// Frees all dynamic memory associated with its Graph* argument, and sets
// *pG to NULL.

/*** Access functions ***/

int getOrder(Graph G);
// Returns the order of G, the number of vertices in G.

int getSize(Graph G);
// Returns the size of G, the number of edges in G.

int getNeighborCount(Graph G, int v);
// Returns the number of neighbors that vertex v has in G. Returns -1 if v is not a legal vertex.

List getNeighbors(Graph G, int v);
// Returns a list that has all the vertices that are neighbors of u. There is no input operation
// that corresponds to getNeighbors.

/*** Manipulation procedures ***/

int addEdge(Graph G, int u, int v);
// Adds v to the adjacency list of u and u to the adjacency list of v, if that edge doesn’t
// already exist. If the edge does already exist, does nothing. Used when edges are entered.
// Returns 0 if u and v are legal vertices, otherwise returns -1.

void unvisitAll(Graph G);
// Marks all vertices of the graph as UNVISITED.

int getMark(Graph G, int u);
// Returns the mark for vertex u, which will be UNVISITED, INPROGRESS or ALLDONE.

void setMark(Graph G, int u, int theMark);
// Sets the mark for vertex u to be theMark.
// theMark must be UNVISITED, INPROGRESS or ALLDONE.

int PathExistsRecursive(Graph G, int w, int v);
// Described below; returns FOUND or NOTFOUND, which are (different) constants.

/*** Other operations ***/

void printGraph(FILE* out, Graph G);
// Prints the Graph G in the same format as an input line, so all that a client need to do is a single
// call to PrintGraph(). But it should not print out an edge twice. Achieve this by only printing
// the edge for {j, k} when j < k.

#endif
