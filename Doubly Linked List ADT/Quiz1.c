#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int searchList(List L, int x)
{
    moveFront(L);
    while (index(L) != -1)
    {
        if (get(L) == x)
        {
            return index(L);
        }
        else
        {
            moveNext(L);
        }
    }
    return index(L);
}

int isPalindrome(List L)
{
    List copy = newList();
    moveBack(L);
    while (index(L) != -1)
    {
        append(copy, get(L));
        movePrev(L);
    }
    if (equals(L, copy))
    {
        freeList(&copy);
        return 1;
    }
    else
    {
        freeList(&copy);
        return 0;
    }
}

int main(int argc, char *argv[])
{
    List L = newList();
    List Q = newList();
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    append(L, a);
    append(L, b);
    append(L, c);
    append(L, d);
    append(Q, a);
    append(Q, b);
    append(Q, b);
    append(Q, a);
    printf("Index: %d\n", searchList(L, a)); //0
    printf("Index: %d\n", searchList(L, b)); //1
    printf("Index: %d\n", searchList(L, c)); //2
    printf("Index: %d\n", searchList(L, d)); //3
    printf("Index: %d\n", searchList(L, e)); //-1
    printf("Is palindrome?: %d\n", isPalindrome(L));
    printf("Is palindrome?: %d\n", isPalindrome(Q));
}