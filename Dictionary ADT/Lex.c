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
#include "Dictionary.h"

#define MAX_LEN 300

int main(int argc, char *argv[])
{
    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];
    char *token;
    char ch;
    //char strings;

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
    line_count = 1;
    while ((ch = fgetc(in)) != EOF)
    {
        if (ch == '\n')
        {
            line_count++;
        }
        
    }
    fseek(in, 0, SEEK_SET);
    char **strings = malloc(line_count * sizeof(char *));
    line_count = 0;
    while (fgets(line, MAX_LEN, in) != NULL)
    {
        // get first token
        token = strtok(line, "\n");

        while (token != NULL)
        { 
            // we have a token
            //copy into string array
            strings[line_count] = (char *)malloc(MAX_LEN+1);
            token[strcspn(token, "\r\n")] = 0;
            strcpy(strings[line_count], token);
            // get next token
            token = strtok(NULL, " \n");
            line_count++;
        }
    }

    // IT'S SORTING TIMEEE
    int i;
    Dictionary sort = newDictionary(0);
    for (i = 0; i < line_count; i++)
    {
        insert(sort, strings[i], i);
    }
    
    for (beginForward(sort); currentVal(sort) != VAL_UNDEF; next(sort))
    {
        fprintf(out, "%s\n", currentKey(sort));
    }
    for (i = 0; i < line_count; i++)
    {
        free(strings[i]);
    }
    free(strings);
    // Free list
    //makeEmpty(sort);
    freeDictionary(&sort);

    // close files
    fclose(in);
    fclose(out);

    return (0);
}
