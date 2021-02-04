//-----------------------------------------------------------------------------
// FindPath.c
// Client File for graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 20
#define MAX_LINES 1000

int main(int argc, char *argv[])
{

    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];
    char *token;

    // check command line for correct number of arguments
    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing
    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // read each line of input file, then count and print tokens
    line_count = 0;
    char *num_1;
    char *num_2;
    Graph G;
    List L;
    int flag;
    while (fgets(line, MAX_LEN, in) != NULL)
    {
        // get first token
        token = strtok(line, "\n");
        if (line_count == 0)
        {
            G = newGraph(atoi(token));
        }
        else
        {
            num_1 = strtok(token, " ");
            num_2 = strtok(NULL, " ");
            if (flag == 0 && (atoi(num_1) == 0 && atoi(num_2) == 0))
            {
                printGraph(out, G);
                flag = 1;
            }
            else if (flag == 1 && (atoi(num_1) == 0 && atoi(num_2) == 0))
            {
                break;
            }
            if (flag == 0)
            {
                addEdge(G, atoi(num_1), atoi(num_2));
            }
            else if (flag == 1 && (atoi(num_1) != 0 && atoi(num_2) != 0))
            {
                L = newList();
                BFS(G, atoi(num_1));
                getPath(L, G, atoi(num_2));
                fprintf(out, "\n\n");
                if (getDist(G, atoi(num_2)) != INF)
                {
                    fprintf(out, "The distance from %d to %d is %d\nA shortest %d-%d path is:",
                            atoi(num_1), atoi(num_2), getDist(G, atoi(num_2)), atoi(num_1), atoi(num_2));
                    printList(out, L);
                }
                else
                {
                    fprintf(out, "The distance from %d to %d is infinity\nNo %d-%d path exists",
                    atoi(num_1), atoi(num_2), atoi(num_1), atoi(num_2));
                }
            }
        }
        line_count++;
    }
    freeGraph(&G);
    freeList(&L);
    return 0;
}