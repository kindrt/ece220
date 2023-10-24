#include <stdio.h>
#include "llist.h"

int main()
{
    struct node_t *list = NULL;
    struct node_t *node = NULL;

    printf("Adding to the head of the list...\n");
    insert_at_head(&list, 1);
    insert_at_head(&list, 2);
    insert_at_head(&list, 3);
    traversal(list);

    printf("Adding to the tail of the list...\n");
    insert_at_tail_rec(&list, -1);
    insert_at_tail_rec(&list, -2);
    insert_at_tail_rec(&list, -3);
    traversal(list);

    printf("Adding before an item in the list...\n");
    insert_rec(&list, 10, 1);
    insert_rec(&list, 11, -1);
    insert_rec(&list, 12, -3);
    insert_rec(&list, 15, 3);
    insert_rec(&list, 16, -5);

    traversal(list);

    printf("Finding an item in the list...\n");
    node = find(list, -1);
    printf("Found %d\n", node->data);

    printf("Finding an item in the list...\n");
    if ((node = find_rec(list, -5)) != NULL) 
      printf("Found %d\n", node->data);
    else
      printf("%d not found\n", -5);

    printf("Deleating head node...\n");
    delete_head_node(&list); 
    traversal(list);

    printf("Deleating tail node...\n");
    delete_tail_rec(&list);
    traversal(list);

    printf("Deleating a node...\n");
    delete_rec(&list, -1);
    traversal(list);

    return 0;
}
