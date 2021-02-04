//-----------------------------------------------------------------------------
// Dictionary.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
    KEY_TYPE key;
    VAL_TYPE val;
    struct NodeObj *parent;
    struct NodeObj *left;
    struct NodeObj *right;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct DictionaryObj
{
    Node root;
    Node cursor;
    Node NIL;
    int size;
    int unique;
} DictionaryObj;

// helper functions
Node newNode(KEY_TYPE key, VAL_TYPE data);
void Transplant(Dictionary D, Node u, Node v);
Node getNode(Dictionary D, KEY_TYPE k);
void PostOrderDeleteWalk(Dictionary D, Node x);

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(KEY_TYPE key, VAL_TYPE data)
{
    Node N = malloc(sizeof(NodeObj));

    N->key = key;
    N->val = data;
    N->parent = NULL;
    N->left = NULL;
    N->right = NULL;
    return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {

        free(*pN);
        *pN = NULL;
    }
}

// newDictionary()
// Returns reference to new empty Dictionary object.
Dictionary newDictionary(int unique)
{
    Dictionary D;
    D = malloc(sizeof(DictionaryObj));
    D->size = 0;
    D->unique = unique;
    D->NIL = newNode(KEY_UNDEF, VAL_UNDEF);
    D->root = D->NIL;
    D->cursor = D->NIL;
    return (D);
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary *pD)
{
    makeEmpty(*pD);
    freeNode(&(*pD)->NIL);
    if (pD != NULL && *pD != NULL)
    {

        free(*pD);
        *pD = NULL;
    }
}

// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D)
{
    return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D)
{
    return D->unique;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
    Node x = D->root;
    while (x != D->NIL && k != x->key)
    {
        if (KEY_CMP(k, x->key) < 0)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return x->val;
}

// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
    // STILL NEED TO DO NON UNIQUE
    if (getUnique(D))
    {
        if (lookup(D, k) != VAL_UNDEF)
        {
            fprintf(stderr, "Dict Error: inserting non-unique key\n");
            exit(EXIT_FAILURE);
        }
    }
    Node V = newNode(k, v);
    
    V->parent = D->NIL;
    
    V->left = D->NIL;
    V->right = D->NIL;
    D->size++;
    
    Node y = D->NIL;
    Node x = D->root;
    
    while (x != D->NIL)
    {
        y = x;
        if (KEY_CMP(k, x->key) < 0)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    V->parent = y;
    if (y == D->NIL)
    {
        D->root = V; // tree T was empty
        return;
    }
    else if (KEY_CMP(V->key, y->key) < 0)
    {
        y->left = V;
        return;
    }
    else
    {
        y->right = V;
        return;
    }
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete (Dictionary D, KEY_TYPE k)
{
    Node save = D->cursor;
    int flag = 1;
    KEY_TYPE curr_key = D->cursor->key;
    if (lookup(D, k) == VAL_UNDEF)
    {
        fprintf(stderr, "Dict Error: calling delete() on key not in dictionary\n");
        exit(EXIT_FAILURE);
    }
    if (D->size == 1)
    {
        Node z = getNode(D, k);
        D->root = D->NIL;
        D->cursor = D->NIL;
        D->size = 0;
        freeNode(&z);
        return;

    }
    Node z = getNode(D, k);
    if (z == save)
    {
        D->cursor = D->NIL;
        flag = 0;
    }
    if (z->left == D->NIL)
    {
        Transplant(D, z, z->right);
    }
    else if (z->right == D->NIL)
    {
        Transplant(D, z, z->left);
    }
    else
    {
        Node y = z->right;
        while (y->left != D->NIL)
        {
            y = y->left;
        }
        if (y->parent != z)
        {
            Transplant(D, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(D, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    if (flag)
    {
        D->cursor = save;
        D->cursor->key = curr_key;
    }
    D->size--;
    freeNode(&z);
    // Delete the node
}

// returns the node of the given key
Node getNode(Dictionary D, KEY_TYPE k)
{
    Node current = D->cursor;
    Node vertex;
    for (beginForward(D); currentVal(D) != VAL_UNDEF; next(D))
    {
        if (currentKey(D) == k)
        {
            vertex = D->cursor;
            D->cursor = current;
            freeNode(&current);
            return vertex;
        }
    }
    vertex = D->cursor;
    D->cursor = current;
    freeNode(&current);
    return D->NIL;
}

// Transplant ()
// Helper function for delete
void Transplant(Dictionary D, Node u, Node v)
{
    if (u->parent == D->NIL)
    {
        D->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v != D->NIL)
    {
        v->parent = u->parent;
    }
}
// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr, "Dict Error: calling make Empty on NULL Dictionary\n");
        exit(EXIT_FAILURE);
    }
    PostOrderDeleteWalk(D, D->root);
    D->cursor = D->NIL;
    D->root = D->NIL;
    D->size = 0;
}


// PostOrderDeleteWalk()
// Walks through the tree in post order, deleting as it goes
void PostOrderDeleteWalk(Dictionary D, Node x)
{
    if (x != D->NIL)
    {
        PostOrderDeleteWalk(D, x->left);
        PostOrderDeleteWalk(D, x->right);
        freeNode(&x);
    }
}


// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D)
{
    if (D->size == 0 || D->root == D->NIL)
    {
        return VAL_UNDEF;
    }
    Node V = D->root;
    while (V->left != D->NIL)
    {
        V = V->left;
    }
    D->cursor = V;
    return V->val;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D)
{
    if (D->size == 0)
    {
        return VAL_UNDEF;
    }
    Node V = D->root;
    while (V->right != D->NIL)
    {
        V = V->right;
    }
    D->cursor = V;
    return V->val;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D)
{
    if (D->cursor == NULL)
    {
        return KEY_UNDEF;
    }
    else
    {
        return D->cursor->key;
    }
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D)
{
    if (D->cursor == NULL)
    {
        return VAL_UNDEF;
    }
    else
    {
        return D->cursor->val;
    }
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D)
{
    if (D->cursor == D->NIL)
    {
        return VAL_UNDEF;
    }
    // If the current node has a right branch, return the min of that branch
    if (D->cursor->right != D->NIL)
    {
        D->cursor = D->cursor->right;
        while (D->cursor->left != D->NIL)
        {
            D->cursor = D->cursor->left;
        }
        return D->cursor->val;
    }

    Node p = D->cursor->parent;
    while (p != D->NIL && D->cursor == p->right)
    {
        D->cursor = p;
        p = p->parent;
    }
    D->cursor = p;
    return p->val;
}

// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D)
{
    if (D->cursor == D->NIL)
    {
        return VAL_UNDEF;
    }
    // If the current node has a right branch, return the min of that branch
    if (D->cursor->left != D->NIL)
    {
        D->cursor = D->cursor->left;
        while (D->cursor->right != D->NIL)
        {
            D->cursor = D->cursor->right;
        }
        return D->cursor->val;
    }

    Node p = D->cursor->parent;
    while (p != D->NIL && D->cursor == p->left)
    {
        D->cursor = p;
        p = p->parent;
    }
    D->cursor = p;
    return p->val;
}

// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE *out, Dictionary D)
{
    beginForward(D);
    fprintf(out, "%s:%d\n", currentKey(D), currentVal(D));
    while (next(D) != VAL_UNDEF)
    {
        fprintf(out, "%s:%d\n", currentKey(D), currentVal(D));
    }
}
