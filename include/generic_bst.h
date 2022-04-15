

#ifndef GENERIC_BST_H
#define GENERIC_BST_H

//bst shorthand for "binary search tree"
typedef struct generic_bst_node {
  void *payload;
  struct generic_bst_node *left;
  struct generic_bst_node *right;
} bst_node_t;

typedef int (*bst_compare_t)(void *, void *);

bst_node_t *build_bst(void *data_ptr, long type_size, int left, int right);

int binary_search(bst_node_t *root, void *needle, bst_compare_t compare);

void operation_inorder(bst_node_t *root, void (*operation)(void *));

#endif
