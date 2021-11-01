#ifndef _LLIST_H_
#define _LLIST_H_

#include <stdint.h>

struct node_t
{
  // node’s data
  int data;
  // next node in the list
  struct node_t *next;
};


struct node_t* find(struct node_t *head, int val);
struct node_t* find_rec(struct node_t *head, int val); 
int insert_at_head(struct node_t **head, int val); 
int insert_at_tail_rec(struct node_t **head, int val); 
int insert_rec(struct node_t **head, int val, int before);
int delete_head_node(struct node_t **head); 
int delete_tail_rec(struct node_t **head);
int delete_rec(struct node_t **head, int val);

void traversal(struct node_t *head);


#endif
