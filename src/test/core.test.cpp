#include <gtest/gtest.h>

#include "map.h"

#include <vector>
#include <iostream>

int default_keys[] = { 1, 2, 3, 4, 5, 6 };
int default_values[] = { 42, 69, 420, 42069, 80085, 25 };

void traverse_inorder(struct messenger_map_node_t* n, std::vector<int>& vec)
{
  if (!n) return;
  
  traverse_inorder(n->left, vec);
  vec.push_back(*((int*) n->value));
  traverse_inorder(n->right, vec);
}

TEST(messenger_map, init)
{
  EXPECT_TRUE(sizeof(default_keys) == sizeof(default_values));
}

TEST(messenger_map, create)
{
  struct messenger_map_t map;
  messenger_map_init(&map, messenger_map_comparator_int);

  EXPECT_TRUE(map.root == NULL);
  EXPECT_EQ(map.count, 0);
}

// needs to test the red-black structure
TEST(messenger_map, insert)
{
  struct messenger_map_t map;
  messenger_map_init(&map, messenger_map_comparator_int);

  for (size_t i = 0; i < sizeof(default_keys) / sizeof(default_keys[0]); i++)
  {
    EXPECT_EQ(0, messenger_map_insert(&map, &default_keys[i], &default_values[i]));
  }

  std::vector<int> items;
  traverse_inorder(map.root, items);

  EXPECT_EQ(items.size(), sizeof(default_keys) / sizeof(default_keys[0]));
  EXPECT_EQ(map.count, items.size());

  for (size_t i = 0; i < items.size(); i++)
    EXPECT_EQ(items[i], default_values[i]);

  EXPECT_EQ(1, messenger_map_insert(&map, &default_keys[2], &default_values[2]));
}

TEST(messenger_map, search)
{
  struct messenger_map_t map;
  messenger_map_init(&map, messenger_map_comparator_int);

  for (size_t i = 0; i < sizeof(default_keys) / sizeof(default_keys[0]); i++)
  {
    messenger_map_insert(&map, &default_keys[i], &default_values[i]);
  }

  for (size_t i = 0; i < sizeof(default_keys) / sizeof(default_keys[0]); i++)
  {
    EXPECT_EQ(default_values[i], *((int*) messenger_map_search(&map, &default_keys[i])->value));
  }
}

// needs to be finished
// test the red-black tree structure
TEST(messenger_map, deleteElement)
{
  struct messenger_map_t map;
  messenger_map_init(&map, messenger_map_comparator_int);

  for (size_t i = 0; i < sizeof(default_keys) / sizeof(default_keys[0]); i++)
  {
    messenger_map_insert(&map, &default_keys[i], &default_values[i]);
  }

  struct messenger_map_node_t n = messenger_map_remove(&map, &default_keys[4]);
  EXPECT_EQ(*((int*) n.value), default_values[4]);

  std::vector<int> items;
  traverse_inorder(map.root, items);

  EXPECT_EQ(items[4], default_values[5]);
}
