#ifndef _MESSENGER_MAP_H
#define _MESSENGER_MAP_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct messenger_map_node_t
{
  struct messenger_map_node_t* left;
  struct messenger_map_node_t* right;
  struct messenger_map_node_t* parent;

  void* key;
  void* value;

  char color;
} messenger_map_node_t;

typedef int (*messenger_map_comparator_t)(void* key1, void* key2);

typedef struct messenger_map_t
{
  struct messenger_map_node_t* root;
  messenger_map_comparator_t comparator;
  unsigned long int count;
} messenger_map_t;

void messenger_map_node_init(struct messenger_map_node_t* node);
void messenger_map_node_destroy(struct messenger_map_node_t* node);

void messenger_map_init(struct messenger_map_t* map, messenger_map_comparator_t comparator);
int messenger_map_insert(struct messenger_map_t* map, void* key, void* value);
struct messenger_map_node_t* messenger_map_search(struct messenger_map_t* map, void* key);
struct messenger_map_node_t messenger_map_remove(struct messenger_map_t* map, void* key);

int messenger_map_comparator_int(void* key1, void* key2);

#ifdef __cplusplus
}
#endif

#endif
