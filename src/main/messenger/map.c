#include "map.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

#define BLACK 0
#define RED 1

void messenger_map_node_init(struct messenger_map_node_t* node)
{
  if (!node) return;

  node->left = NULL;
  node->right = NULL;
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
  insert->color = RED;

  // add as root node
  if (map->root == NULL)
  {
    insert->color = BLACK;
  }

  int comparison;

  // find the correct location to place the new node at
  struct messenger_map_node_t* n = map->root;
  struct messenger_map_node_t* parent = NULL;

  while (n)
  {
    comparison = map->comparator(key, n->key);

    // element already exists
    if (comparison == 0)
    {
      messenger_map_node_destroy(insert);
      free(insert);
      return 1;
    }

    parent = n;
    if (comparison < 0)
    {
      n = n->left;
    }
    else
    {
      n = n->right;
    }
  }

  comparison = map->comparator(key, parent->key);
  if (comparison < 0)
    parent->left = insert;
  else
    parent->right = insert;

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

