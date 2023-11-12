#include <stdio.h>
#include "tree.h"

int main()
{
    struct node_t *root = NULL;

    root = BSTInsert(root, 0); 
    root = BSTInsert(root, 10); 
    root = BSTInsert(root, 20); 
    root = BSTInsert(root, -5);
    root = BSTInsert(root, -1); 
    
    inOrder(root);
    printf("\n");

    struct node_t *found = NULL;

    found = BSTSearch(root, -2);
    if (found != NULL)
        printf("found!\n");
    else
        printf("not found\n");


    freetree(root);

    return 0;
}
