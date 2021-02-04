

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char *argv[])
{
    printf("Starting Graph ADT Test Harness\n");
    printf("********************************\n\n\n");

    Graph A = newGraph(8);
    printf("TESTING ADDARC AND BFS\n\n");
    addArc(A, 1, 2);
    addArc(A, 2, 5);
    addArc(A, 2, 6);
    addArc(A, 6, 3);
    addArc(A, 6, 5);
    addArc(A, 5, 4);
    addArc(A, 4, 1);
    addArc(A, 5, 7);
    addArc(A, 8, 5);
    BFS(A, 6);

    return 0;
}
