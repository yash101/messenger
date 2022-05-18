#ifndef _MESSENGER_STRING_H
#define _MESSENGER_STRING_H

#include <stddef.h>

typedef struct messenger_buffer_t
{
  char* buffer;
  size_t length;
  size_t allocated;
} messenger_buffer_t;

void messenger_buffer_init(struct messenger_buffer_t* buffer);
void messenger_buffer_destroy(struct messenger_buffer_t* buffer);

size_t messenger_buffer_alloc(struct messenger_buffer_t* buffer, size_t len);
size_t messenger_buffer_length(struct messenger_buffer_t* buffer);
size_t messenger_buffer_allocated(struct messenger_buffer_t* buffer);

size_t messenger_buffer_copy_from(struct messenger_buffer_t* buffer, const char* source, size_t len);
size_t messenger_buffer_copy_str(struct messenger_buffer_t* buffer, const char* str);
size_t messenger_buffer_copy_str_max(struct messenger_buffer_t* buffer, const char* str, size_t maxlen);

#endif
