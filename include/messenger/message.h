#ifndef _MESSENGER_MESSAGE_H
#define _MESSENGER_MESSAGE_H

#include <stdint.h>
#include <stdlib.h>

#ifndef MESSENGER_DEFAULT_MESSAGE_ALLOC
#define MESSENGER_DEFAULT_MESSAGE_ALLOC 1024
#endif

typedef struct messenger_message_t
{
  size_t bufferred;
  size_t* buffer_lengths;
  char** buffer;

  struct messenger_session_t* session;
  struct messenger_client_t* client;
} messenger_message_t;

void messenger_message_init(struct messenger_message_t* message);
void messenger_message_destroy(struct messenger_message_t* message);

void messenger_message_property_set(struct messenger_message_t* message, uint16_t property, uint16_t value);
uint16_t messenger_message_property_get(struct messenger_message_t* message, uint16_t property);
void messenger_message_attach_client(struct messenger_message_t* message, struct messenger_client_t* client);
void messenger_message_attach_session(struct messenger_message_t* message, struct messenger_session_t* session);

void messenger_message_write(struct messenger_message_t* message, void* data, size_t len);
size_t messenger_message_read(struct messenger_message_t* message, char* buffer);
size_t messenger_message_size(struct messenger_message_t* message);
size_t messenger_message_transmitted(struct messenger_message_t* message);
size_t messenger_message_received(struct messenger_message_t* message);

size_t messenger_message_close(struct messenger_message_t* message);

#endif
