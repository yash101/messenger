#include "messenger/private/map.h"

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

void messenger_map_init(struct messenger_map_t* map, messenger_map_comparator_t comparator)
{
  if (!map) return;

  map->root = NULL;
  map->comparator = comparator;
  map->count = 0;
}

static struct messenger_map_node_t* _grandparent(struct messenger_map_node_t* node)
{
  if (!node || !node->parent)
    return NULL;

  return node->parent->parent;
}

static struct messenger_map_node_t* _sibling(struct messenger_map_node_t* node)
{
  if (!node || !node->parent)
    return NULL;

  return (node->parent->left == node) ?
        node->parent->right :
        node->parent->left;
}

static struct messenger_map_node_t* _uncle(struct messenger_map_node_t* node)
{
  if (!node)
    return NULL;

  return _sibling(node->parent);
}

static struct messenger_map_node_t* _minValueNode(struct messenger_map_node_t* node)
{
  if (!node)
    return node;

  while (node->left)
    node = node->left;

  return node;
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

static void _messenger_map_rb_insert_fixup(struct messenger_map_t* map, struct messenger_map_node_t* node)
{
  while (node != map->root && node->parent->color == RED)
  {
    struct messenger_map_node_t* uncle = _uncle(node);

    if (uncle && uncle->color == RED)
    {
      node->parent->color = BLACK;
      uncle->color = BLACK;

      struct messenger_map_node_t* gp = _grandparent(node);
      while (gp)
      {
        gp->color = RED;
        gp = _grandparent(gp);
      }
    }
    else if(uncle && uncle->color == BLACK)
    {
      if (!_grandparent(node))
        return;

      // Case LL
      if (node->parent == _grandparent(node)->left && node == node->parent->left)
      {
        char color = node->parent->color;
        node->parent->color = _grandparent(node)->color;
        _grandparent(node)->color = color;
        _messenger_map_right_rotate(map, _grandparent(node));
      }

      // Case LR
      if (node->parent == _grandparent(node)->left && node == node->parent->right)
      {
        char color = node->parent->color;
        node->color = _grandparent(node)->color;
        _grandparent(node)->color = color;
        _messenger_map_left_rotate(map, node->parent);
        _messenger_map_right_rotate(map, _grandparent(node));
      }

      // Case RR
      if (node->parent == _grandparent(node)->right && node == node->parent->right)
      {
        char color = node->parent->color;
        node->parent->color = _grandparent(node)->color;
        _grandparent(node)->color = color;
        _messenger_map_left_rotate(map, _grandparent(node));
      }

      // Case RL
      if (node->parent == _grandparent(node)->right && node == node->parent->left)
      {
        char color = node->parent->color;
        node->color = _grandparent(node)->color;
        _grandparent(node)->color = color;
        _messenger_map_right_rotate(map, node->parent);
        _messenger_map_left_rotate(map, _grandparent(node));
      }
    }
  }

  map->root->color = BLACK;
}

struct messenger_map_node_t* messenger_map_search(struct messenger_map_t* map, void* key)
{
  // invalid map / no elements
  if (!map || !map->root) return NULL;

  struct messenger_map_node_t* n = map->root;
  while (n != NULL)
  {
    int comp = map->comparator(key, n->key);
    if (comp == 0) {
      return n;
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

//  // R-B Rebalance
//  _messenger_map_rb_insert_fixup(map, insert);

  return 0;
}

struct messenger_map_node_t messenger_map_remove(struct messenger_map_t* map, void* key)
{
  struct messenger_map_node_t ret;
  messenger_map_node_init(&ret);

  struct messenger_map_node_t* current = messenger_map_search(map, key);

  if (!current)
    return ret;

  ret.key = current->key;
  ret.value = current->value;
  map->count--;

  if (!current->left && !current->right)
  {
    if (current == map->root)
    {
      map->root = NULL;
      free(current);
      return ret;
    }
    else
    {
      if (current->parent->left == current)
        current->parent->left = NULL;
      else
        current->parent->right = NULL;
    }
    free(current);
    return ret;
  }
  else if(current->left && current->right)
  {
    struct messenger_map_node_t* successor = _minValueNode(current->right);
    // Swap the successor and current
    if (successor->parent->left == successor)
      successor->parent->left = NULL;
    else
      successor->parent->right = NULL;

    if (current == map->root)
      map->root = successor;
    else if (current->parent->left == current)
      current->parent->left = successor;
    else
      current->parent->right = successor;

    successor->parent = current->parent;
    successor->left = current->left;
    successor->right = current->right;

    free(current);
    return ret;
  }
  else
  {
    struct messenger_map_node_t* child = (current->left) ? current->left : current->right;
    if (current->parent == NULL)
      map->root = child;
    else if (current == current->parent->left)
      current->parent->left = child;
    else
      current->parent->right = child;

    free(current);
    return ret;
  }
}

int messenger_map_comparator_int(void* key1, void* key2)
{
  if (!key1 || !key2) return 0;
  return *((int*) key1) - *((int*) key2);
}

#ifdef __cplusplus
}
#endif

