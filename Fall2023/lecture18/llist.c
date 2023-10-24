#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "llist.h"


struct node_t* find(struct node_t *head, int val) 
{
    struct node_t *item = head;

    while (item != NULL && item->data != val) {
        item = item->next;
    }

    return item;
}

struct node_t* find_rec(struct node_t *head, int val) 
{
    if (head == NULL) return NULL;
    if (head->data == val) return head;
    return find_rec(head->next, val);
}


int insert_at_head(struct node_t **head, int val) 
{
    struct node_t *item;

    item = malloc(sizeof(struct node_t));
    if (item == NULL) return 0;

    item->data = val;
    item->next = *head;
    *head = item;

    return 1;
}



int insert_at_tail_rec(struct node_t **head, int val) 
{
    struct node_t *item;

    if (*head == NULL) {
        item = malloc(sizeof(struct node_t));
        if (item == NULL) return 0;
        item->data = val;
        item->next = NULL;
        *head = item;
        return 1;
    } else {
        return insert_at_tail_rec(&(*head)->next, val);
    }
}


int insert_rec(struct node_t **head, int val, int before) 
{
    if ((*head == NULL) || ((*head)->data == before)) {
        struct node_t *item;
        item = malloc(sizeof(struct node_t));
        if (item == NULL) return 0;
        item->data = val;
        item->next = *head;
        *head = item;
        return 1;
    } else {
        return insert_rec(&(*head)->next, val, before);
    }
}


int delete_head_node(struct node_t **head) 
{
    struct node_t *item = *head;
    if (*head == NULL) return 0;
    *head = (*head)->next;
    free(item);

    return 1;
}


int delete_tail_rec(struct node_t **head)
{
    struct node_t *item = *head;
    if (*head == NULL) return 0;
    if ((*head)->next == NULL) { 
        *head = NULL;
        free(item);
        return 1;
    } else {
        return delete_tail_rec(&(*head)->next);
    }
}


int delete_rec(struct node_t **head, int val)
{
    struct node_t *item = *head;
    if (*head == NULL) return 0;
    if ((*head)->data == val) { 
        *head = (*head)->next;
        free(item);
        return 1;
    } else {
        return delete_rec(&(*head)->next, val);
    }
}


void traversal(struct node_t *head) 
{
    struct node_t *item = head;

    while (item != NULL) {
        // do something with item’s data
        printf("%d ->", item->data);
        // move to next item
        item = item->next;
    }

    printf(" NULL\n");
}
