#ifndef _TREE_H_
#define _TREE_H_

#include <stdint.h>

struct node_t
{
  // node’s data
  int data;
  // child nodes in the tree
  struct node_t *left;
  struct node_t *right;
};


struct node_t* newnode(int data);
void inOrder(struct node_t *root);

struct node_t* BSTInsert( struct node_t * root, int data);
struct node_t* BSTSearch(struct node_t* root, int data);

void freetree(struct node_t *root);

#endif
