//-----------------------------------------------------------------------------
// Lex.c
// Implementation file for sort
//
//     compile:
//     gcc -std=c11 -Wall -o Lex Lex.c List.c
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 300
#define MAX_LINES 1000

int main(int argc, char *argv[])
{
    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];
    char *token;
    char strings[MAX_LINES][MAX_LEN];

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
    while (fgets(line, MAX_LEN, in) != NULL)
    {
        // get first token
        token = strtok(line, "\n");

        while (token != NULL)
        { // we have a token
            //copy into string array
            token[strcspn(token, "\r\n")] = 0;
            strcpy(strings[line_count], token);
            // get next token
            token = strtok(NULL, " \n");
            line_count++;
        }
    }

    // IT'S SORTING TIMEEE
    int i;
    List sort = newList();
    for (i = 0; i < line_count; i++)
    {

        moveFront(sort);
        while (1)
        {
            if (isEmpty(sort))
            {
                append(sort, i);
                break;
            }
            if (strcmp(strings[i], strings[get(sort)]) < 0)
            {
                insertBefore(sort, i);
                break;
            }
            else if (get(sort) == back(sort))
            {
                append(sort, i);
                break;
            }
            else
            {
                moveNext(sort);
            }
        }
    }
    moveFront(sort);
    while (index(sort) != UNDEFINED)
    {
        fprintf(out, "%s\n", strings[get(sort)]);
        moveNext(sort);
    }

    // Free list
    clear(sort);
    freeList(&sort);

    // close files
    fclose(in);
    fclose(out);

    return (0);
}
