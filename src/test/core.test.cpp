#include <gtest/gtest.h>

#include "map.h"

#include <vector>

int default_keys[] = { 1, 2, 3, 4, 5, 6 };
int default_values[] = { 42, 69, 420, 42069, 80085, 25 };

int comparator(void* key1, void* key2) {
  return *((int*) key1) - *((int*) key2);
}

void traverse_inorder(struct messenger_map_node_t* n, std::vector<int>& vec)
{
  if (!n) return;
  
  traverse_inorder(n->left, vec);
  vec.push_back(*((int*) n->value));
  traverse_inorder(n->right, vec);
}

TEST(testMap, testMapTest)
{
  EXPECT_TRUE(sizeof(default_keys) == sizeof(default_values));
}

TEST(testMap, testMapCreate)
{
  struct messenger_map_t map;
  messenger_map_init(&map, comparator);

  EXPECT_TRUE(map.root == NULL);
  EXPECT_EQ(map.count, 0);
}

TEST(testMap, testMapInsert)
{
  struct messenger_map_t map;
  messenger_map_init(&map, comparator);

  for (size_t i = 0; i < sizeof(default_keys) / sizeof(default_keys[0]); i++)
  {
    messenger_map_insert(&map, &default_keys[i], &default_values[i]);
  }

  std::vector<int> items;
  traverse_inorder(map.root, items);

  EXPECT_EQ(items.size(), sizeof(default_keys) / sizeof(default_keys[0]));
  EXPECT_EQ(map.count, items.size());

  for (size_t i = 0; i < items.size(); i++)
    EXPECT_EQ(items[i], default_values[i]);
}
