#include <stdio.h>
#include <stdlib.h>

struct treenode_t;

struct treenode_t {
  int value;
  struct treenode_t *right, *left;
};

typedef struct treenode_t treenode;

void tree_insert(treenode **root, int v) {
  if (!*root) {
    (*root) = malloc(sizeof(treenode));
    (*root)->left = (*root)->right = NULL;
    (*root)->value = v;
    return;
  }

  if ((*root)->value < v) {
    tree_insert(&((*root)->right), v);
  } else {
    tree_insert(&((*root)->left), v);
  }
}

void tree_insert_nr(treenode **root, int v) {
  while (*root) {
    if ((*root)->value < v) {
      root = &((*root)->right);
    } else {
      root = &((*root)->left);
    }
  }
  (*root) = malloc(sizeof(treenode));
  (*root)->left = (*root)->right = NULL;
  (*root)->value = v;
}

treenode *tree_find(treenode *root, int v) {
  if (!root) return NULL;
  if (root->value == v) return root;
  if (root->value < v)
    return tree_find(root->right, v);
  return tree_find(root->left, v);
}

void inorder_traverse(treenode *root) {
  if (!root) return;
  inorder_traverse(root->left);
  printf("%d\n", root->value);
  inorder_traverse(root->right);
}

void tree_delete(treenode **root, int v) {
  treenode *tmp, *tmp2;
  treenode **replacement;

  while (*root && ((*root)->value != v)) {
    if ((*root)->value < v)
      root = &((*root)->right);
    else
      root = &((*root)->left);
  }

  if (!*root)
    return;

  tmp = *root;

  if (tmp->left && tmp->right) {
    replacement = &(tmp->left);
    while ((*replacement)->right)
      replacement = &((*replacement)->right);
    tmp2 = *replacement;
    *replacement = tmp2->left;
    *root = tmp2;
    tmp2->left = tmp->left;
    tmp2->right = tmp->right;
  } else if (tmp->left) {
    *root = tmp->left;
  } else if (tmp->right) {
    *root = tmp->right;
  }

  free(tmp);
}

int main() {
  treenode *root = NULL;
  tree_insert(&root, 6);
  tree_insert(&root, 2);
  tree_insert(&root, 3);
  tree_insert(&root, 5);
  tree_insert(&root, 4);
  tree_insert(&root, 7);
  tree_delete(&root, 6);
  inorder_traverse(root);
}
