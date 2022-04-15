#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/generic_bst.h"

bst_node_t *insert_node(bst_node_t *root, void *payload,
                        bst_compare_t compare) {
  assert(payload != NULL);
  assert(compare != NULL);

  bst_node_t *new_node;

  if(root == NULL) {
   new_node = malloc(sizeof(bst_node_t));
   assert(new_node != NULL);

   new_node->left = NULL;
   new_node->right = NULL;
   new_node->payload = payload;

   return new_node;
  }

  if(compare(payload, root->payload) == 1) {
    if(root->left == NULL) {
      new_node = malloc(sizeof(bst_node_t));
      assert(new_node != NULL);

      new_node->left = NULL;
      new_node->right = NULL;
      new_node->payload = payload;

      root->left = new_node;

      return NULL;
    }

    insert_node(root->left, payload, compare);
  }

  if(compare(payload, root->payload) == 0) {
    if(root->right == NULL) {
      bst_node_t *new_node = malloc(sizeof(bst_node_t));
      assert(new_node != NULL);

      new_node->left = NULL;
      new_node->right = NULL;
      new_node->payload = payload;

      root->right = new_node;

      return NULL;
    }

    insert_node(root->right, payload, compare);
  }

  return NULL;
}


bst_node_t *build_bst(void *data, long type_size, int left, int right) {
  typedef char type_t[type_size];

  int middle = (left + right) / 2;

  type_t *data_ptr = data;
  bst_node_t *new_node;

  if(right < left) {
    return NULL;
  }

  if(right == left) {
    new_node = malloc(sizeof(bst_node_t));
    assert(new_node != NULL);

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->payload = data_ptr + left;

    return new_node;
  }

  bst_node_t *left_child = build_bst(data, type_size, left, middle - 1);
  bst_node_t *right_child = build_bst(data, type_size, middle + 1, right);

  new_node = malloc(sizeof(bst_node_t));
  assert(new_node != NULL);

  new_node->left = left_child;
  new_node->right = right_child;
  new_node->payload = data_ptr + middle;

  return new_node;
}

int binary_search(bst_node_t *root, void *needle, bst_compare_t compare) {
  if(needle == NULL) return 0;
  if(root == NULL) return 0;
  if(compare(needle, root->payload) == 0) return 1;

  if(compare(needle, root->payload) < 0) {
    return binary_search(root->left, needle, compare);
  }
  else if(compare(needle, root->payload) > 0) {
    return binary_search(root->right, needle, compare);
  }

  return 0;
}


void operation_inorder(bst_node_t *root, void (*operation)(void *)) {
  /*if(root->left == NULL && root->right == NULL) {
    operation(root->payload);
    return;
  }*/

  if(root->left != NULL) {
    operation_inorder(root->left, operation);
  }

  operation(root->payload);

  if(root->right != NULL) {
    operation_inorder(root->right, operation);
  }
 }
