//-----------------------------------------------------------------------------
// DictionaryClient.c
// Test client for Dictionary ADT
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"

int main(int argc, char *argv[])
{

    int i, n = 26;
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);
    char *word[] = {"n", "z", "w", "k", "i", "c", "l", "d", "t", "a",
                    "e", "y", "b", "h", "v", "f", "s", "m", "x", "r",
                    "o", "u", "p", "g", "j", "q"};
    VAL_TYPE x;
    VAL_TYPE y;

    // add pairs to A --------------------------------------

    for (i = 0; i < n; i++)
    {
        insert(A, word[i], i);
    }

    // add pairs to B
    for (i = n - 1; i >= 0; i--)
    {
        insert(B, word[i], i);
    }

    // forward iteration over A ----------------------------
    printf("forward A:\n");
    for (x = beginForward(A); currentVal(A) != VAL_UNDEF; x = next(A))
    {
        printf("key: " KEY_FORMAT " value: " VAL_FORMAT "\n", currentKey(A), x);
    }
    printf("\n\n");

    // reverse iteratation over B
    printf("reverse B:\n");
    for (y = beginReverse(B); currentVal(B) != VAL_UNDEF; y = prev(B))
    {
        printf("key: " KEY_FORMAT " value: " VAL_FORMAT "\n", currentKey(B), y);
    }
    printf("\n\n");

    // print Dictionary A ----------------------------------
    printf("Dictionary A (%sunique keys):\n", (getUnique(A) ? "" : "non-"));
    printDictionary(stdout, A);
    printf("\n");

    // print Dictionary B
    printf("Dictionary B (%sunique keys):\n", (getUnique(B) ? "" : "non-"));
    printDictionary(stdout, B);
    printf("\n");

    // delete keys from A ----------------------------------
    for (i = 0; i < n; i += 2)
    {
        delete (A, word[i]);
    }

    // print Dictionary A after deletions
    printf("Dictionary A (%sunique keys):\n", (getUnique(A) ? "" : "non-"));
    printf("after deletions:\n");
    printDictionary(stdout, A);
    printf("\n");

    // delete keys from B ----------------------------------
    for (i = 1; i < n; i += 2)
    {
        delete (B, word[i]);
    }

    // print Dictionary B after deletions
    printf("Dictionary B (%sunique keys):\n", (getUnique(B) ? "" : "non-"));
    printf("after deletions:\n");
    printDictionary(stdout, B);
    printf("\n");

    // insert duplicates into A ----------------------------
    for (i = 1; i < n; i += 2)
    {
        insert(A, word[i], i);
    }

    // print Dictionary A after insertions
    printf("Dictionary A (%sunique keys):\n", (getUnique(A) ? "" : "non-"));
    printf("after insertions:\n");
    printDictionary(stdout, A);
    printf("\n");

    // uncomment line below to get error message
    // insert(B, word[10], 10);
    // Dictionary Error:
    // calling insert() on existing key: e

    freeDictionary(&A);
    freeDictionary(&B);
    Dictionary C = newDictionary(0);
    Dictionary D = newDictionary(1);
    char *words[] = {"nice", "zap", "wet", "kow", "ice", "cream", "lude", "dudette", "twins", "ass (like donkey)",
                     "each", "yogurt", "babette", "huge", "victory", "fake", "swimmer", "mas", "xtra", "raw",
                     "often", "under", "pew", "gogurt", "jumper", "quit"};

    // add pairs to A --------------------------------------
    for (i = 0; i < n; i++)
    {
        printf("inserting %s:%d\n", words[i], i);
        insert(C, words[i], i);
    }
    
    // add pairs to B
    for (i = n - 1; i >= 0; i--)
    {
        insert(D, words[i], i);
    }

    // forward iteration over A ----------------------------
    printf("forward C:\n");
    for (x = beginForward(C); currentVal(C) != VAL_UNDEF; x = next(C))
    {
        printf("key: " KEY_FORMAT " value: " VAL_FORMAT "\n", currentKey(C), x);
    }
    printf("\n\n");

    // reverse iteratation over B
    printf("reverse D:\n");
    for (y = beginReverse(D); currentVal(D) != VAL_UNDEF; y = prev(D))
    {
        printf("key: " KEY_FORMAT " value: " VAL_FORMAT "\n", currentKey(D), y);
    }
    printf("\n\n");

    // print Dictionary A ----------------------------------
    printf("Dictionary C (%sunique keys):\n", (getUnique(C) ? "" : "non-"));
    printDictionary(stdout, C);
    printf("\n");

    // print Dictionary B
    printf("Dictionary D (%sunique keys):\n", (getUnique(D) ? "" : "non-"));
    printDictionary(stdout, D);
    printf("\n");

    // delete keys from A ----------------------------------
    for (i = 0; i < n; i += 2)
    {
        delete (C, words[i]);
    }

    // print Dictionary A after deletions
    printf("Dictionary C (%sunique keys):\n", (getUnique(C) ? "" : "non-"));
    printf("after deletions:\n");
    printDictionary(stdout, C);
    printf("\n");

    // delete keys from B ----------------------------------
    for (i = 1; i < n; i += 2)
    {
        delete (D, words[i]);
    }

    // print Dictionary B after deletions
    printf("Dictionary D (%sunique keys):\n", (getUnique(D) ? "" : "non-"));
    printf("after deletions:\n");
    printDictionary(stdout, D);
    printf("\n");

    // insert duplicates into A ----------------------------
    for (i = 1; i < n; i += 2)
    {
        insert(C, words[i], i);
    }

    // print Dictionary A after insertions
    printf("Dictionary C (%sunique keys):\n", (getUnique(C) ? "" : "non-"));
    printf("after insertions:\n");
    printDictionary(stdout, C);
    printf("\n");

    // free heap memory ------------------------------------
    freeDictionary(&C);
    freeDictionary(&D);

    return (0);
}
