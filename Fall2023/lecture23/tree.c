#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"


struct node_t* newnode(int data) 
{ 
    struct node_t* node;

    if ((node = (struct node_t*)malloc(sizeof(struct node_t))) != NULL)
    {
        node->data = data; 
        node->left = NULL; 
        node->right = NULL;
    }

    return node; 
} 


void inOrder(struct node_t *root)
{
  if (root != NULL)
  {
      inOrder(root->left);
      printf("%d ", root->data);
      inOrder(root->right);
  }
}

void freetree(struct node_t *root)
{
    if (root != NULL)
    {
        freetree(root->left);
        freetree(root->right);
        free(root);
    }
}

struct node_t* BSTInsert( struct node_t * root, int data) 
{
   // empty tree - return a new root node
   if (root == NULL) return newnode(data);

   // otherwise, find the “right” place
   if (data < root->data) 
     root->left = BSTInsert(root->left, data);
   else
     root->right = BSTInsert(root->right, data);

   return root; // return root node 
}

struct node_t* BSTSearch(struct node_t* root, int data) 
{
  if (root == NULL) return NULL;

  if (root->data == data) // we found it!
    return root;

  // otherwise, check which branch to take
  if (data < root->data)
    return BSTSearch(root->left, data);
  else
    return BSTSearch(root->right, data);
}



