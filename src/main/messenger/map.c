#include "map.h"

#include <stdlib.h>

void messenger_map_node_init(struct messenger_map_node_t* node)
{
  if (!node) return;
  node->left = NULL;
  node->right = NULL;
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
    int comp = map->comparator(n->key, key);
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





int messenger_map_comparator_int(void* key1, void* key2)
{
  if (!key1 || !key2) return 0;
  return *((int*) key1) - *((int*) key2);
}

