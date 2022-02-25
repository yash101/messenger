#include "map.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

#define BLACK 'B'
#define RED 'R'

void messenger_map_node_init(struct messenger_map_node_t* node)
{
  if (!node) return;

  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  node->color = BLACK;

  node->key = NULL;
  node->value = NULL;
}

void messenger_map_node_destroy(struct messenger_map_node_t* node)
{
  if (!node) return;

  messenger_map_node_destroy(node->left);
  messenger_map_node_destroy(node->right);
  node->left = NULL;
  node->right = NULL;
}

void messenger_map_init(struct messenger_map_t* map, messenger_map_comparator_t comparator)
{
  if (!map) return;

  map->root = NULL;
  map->comparator = comparator;
  map->count = 0;
}

static void _messenger_map_left_rotate(struct messenger_map_t* map, struct messenger_map_node_t* x)
{
  if (!map || !x)
    return;

  struct messenger_map_node_t* y = x->right;
  x->right = y->left;         // Turn y's left subtree to x's right subtree
  if (y->left)
    y->left->parent = x;

  y->parent = x->parent;      // y's new parent was x's parent

  if (!x->parent)             // Check if x was the root node and update to the right subtree
  {
    map->root = y;
  }
  else
  {
    if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
  }

  x->left = x;
  x->parent = y;
}

static void _messenger_map_right_rotate(struct messenger_map_t* map, struct messenger_map_node_t* x)
{
  if (!map || !x)
    return;
  
  struct messenger_map_node_t* y = x->left;
  x->left = y->right;
  if (y->right)
    y->right->parent = x;
  
  y->parent = x->parent;
  
  if (!x->parent)
  {
    map->root = y;
  }
  else
  {
    if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
  }

  x->right = x;
  x->parent = y;
}

void* messenger_map_search(struct messenger_map_t* map, void* key)
{
  // invalid map / no elements
  if (!map || !map->root) return NULL;

  struct messenger_map_node_t* n = map->root;
  while (n != NULL)
  {
    int comp = map->comparator(key, n->key);
    if (comp == 0) {
      return n->value;
    } else if(comp < 0) {
      n = n->left;
    } else {
      n = n->right;
    }
  }
  
  return NULL;
}

int messenger_map_insert(struct messenger_map_t* map, void* key, void* value)
{
  if (!map) return -1;

  struct messenger_map_node_t* insert = calloc(1, sizeof(*insert));
  messenger_map_node_init(insert);
  insert->key = key;
  insert->value = value;

  map->count++;

  // add as root node
  if (map->root == NULL)
  {
    map->root = insert;
    return 0;
  }

  insert->color = RED;


  // BST search
  struct messenger_map_node_t* n = map->root;
  struct messenger_map_node_t* parent = NULL;
  int comparison;

  while (n)
  {
    comparison = map->comparator(key, n->key);

    // element already exists
    if (comparison == 0)
    {
      messenger_map_node_destroy(insert);
      free(insert);
      map->count--;
      return 1;
    }

    // Find the location in the tree to insert into
    parent = n;
    n = (comparison < 0) ? n->left : n->right;
  }

  // BST Insertion
  insert->parent = parent;
  comparison = map->comparator(key, parent->key);
  if (comparison < 0)
    parent->left = insert;
  else
    parent->right = insert;

  // R-B Balancing: Coloring

  // If x's parent is red
  if (insert->parent->color == RED)
  {
    insert->parent->color = BLACK;
    insert->parent->parent->color = RED;
  }

  return 0;
}

int messenger_map_comparator_int(void* key1, void* key2)
{
  if (!key1 || !key2) return 0;
  return *((int*) key1) - *((int*) key2);
}

#ifdef __cplusplus
}
#endif

