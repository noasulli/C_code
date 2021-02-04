//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

typedef struct GraphObj
{
    List *adj;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int source;
} GraphObj;

// Private helper function declarations

void insertSorted(List L, int i);

/*** Constructors-Destructors ***/

// Constructs and initializes a new graph.
// Sets number of vertices to n
Graph newGraph(int n)
{
    int i;
    Graph G;
    G = malloc(sizeof(GraphObj));
    G->adj = malloc(sizeof(List) * (n + 1));
    G->size = 0;
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->distance = calloc(n + 1, sizeof(int));
    G->source = NIL;
    for (i = 1; i < n + 1; i++)
    {
        G->adj[i] = newList();
    }
    G->order = n;
    return G;
}

// Frees Graph
// Sets pointer to NULL
void freeGraph(Graph *pG)
{
    int i;
    if (*pG == NULL)
    {
        fprintf(stderr, "Graph Error: calling freeGraph() on NULL graph pointer");
        exit(EXIT_FAILURE);
    }
    if (pG != NULL && *pG != NULL)
    {
        if ((*pG)->parent != NULL)
        {
            free((*pG)->parent);
            (*pG)->parent = NULL;
        }
        if ((*pG)->color != NULL)
        {
            free((*pG)->color);
            (*pG)->color = NULL;
        }
        if ((*pG)->distance != NULL)
        {
            free((*pG)->distance);
            (*pG)->distance = NULL;
        }
        for (i = 1; i <= getOrder(*pG); i++)
        {
            freeList(&((*pG)->adj)[i]);
        }
        free((*pG)->adj);
        (*pG)->adj = NULL;
        free(*pG);
        *pG = NULL;
    }
    return;
}

/*** Access functions ***/

// returns the order of the function
int getOrder(Graph G)
{
    return G->order;
}

// returns the size of the function
int getSize(Graph G)
{
    return G->size;
}

// return source most recently used in BFS
// return NIL if BFS has not been called
int getSource(Graph G)
{
    return G->source;
}

// returns the parent of vertex u
// in the BreadthFirst tree created by BFS()
// return NIL if BFS has not been called
int getParent(Graph G, int u)
{
    if (G->source == NIL)
    {
        return NIL;
    }
    return G->parent[u];
}

// returns the distance of vertex u
// to the most recent BFS source
// return inf if BFS() not called
int getDist(Graph G, int u)
{
    if (G->source == NIL)
    {
        return INF;
    }
    return G->distance[u];
}

// appends to the List L the vertices
// of a shortest path in G from source to u
// or appends to L the value NIL if no such path exists
// precondition getSource(G)!=NIL
void getPath(List L, Graph G, int u)
{
    int x;
    if (getSource(G) == NIL)
    {
        printf("Graph Error: calling getPath() on non-BFS graph\n");
        exit(EXIT_FAILURE);
    }
    if (u == getSource(G))
    {
        append(L, u);
        return;
    }
    if (G->parent[u] == NIL)
    {
        append(L, NIL);
        return;
    }
    append(L, u);
    moveBack(L);
    x = G->parent[u];
    while (1)
    {
        insertBefore(L, x);
        if (x == getSource(G))
        {
            return;
        }
        x = G->parent[x];
        movePrev(L);
    }
}

/*** Manipulation procedures ***/

// Inserts element into list based on magnitude
void insertSorted(List L, int i)
{
    if (isEmpty(L))
    {
        append(L, i);
        return;
    }
    moveFront(L);
    while (index(L) != UNDEFINED)
    {
        if (get(L) > i)
        {
            insertBefore(L, i);
            return;
        }
        moveNext(L);
    }
    append(L, i);
    return;
}

void makeNull(Graph G)
{
    int i;
    for (i = 1; i <= G->order; i++)
    {
        clear(G->adj[i]);
        G->color[i] = white;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->source = NIL;
    G->size = 0;
}

void addEdge(Graph G, int u, int v)
{
    insertSorted(G->adj[u], v);
    insertSorted(G->adj[v], u);
    G->size++;
}

void addArc(Graph G, int u, int v)
{
    insertSorted(G->adj[u], v);
    G->size++;
}

void BFS(Graph G, int s)
{

    int i;
    int x;
    int y;

    G->source = s;

    for (i = 1; i <= getOrder(G); i++)
    {
        if (i != s)
        {
            G->color[i] = white;
            G->distance[i] = INF;
            G->parent[i] = NIL;
        }
    }
    G->color[s] = gray;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    moveFront(Q);

    while (!isEmpty(Q))
    {
        x = front(Q);
        deleteFront(Q);
        moveFront(G->adj[x]);
        while (index(G->adj[x]) != UNDEFINED)
        {
            y = get(G->adj[x]);
            if (G->color[y] == white)
            {
                G->color[y] = gray;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                printf("Vertex: %d\n", y);
                append(Q, y);
            }
            moveNext(G->adj[x]);
        }
        G->color[x] = black;
    }
    freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE *out, Graph G)
{
    int i;

    for (i = 1; i <= getOrder(G); i++)
    {

        fprintf(out, "%d:", i);
        printList(out, G->adj[i]);
        if (i != getOrder(G))
        {
            fprintf(out, "\n");
        }
    }
}