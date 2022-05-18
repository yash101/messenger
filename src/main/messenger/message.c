#include "messenger/public/messenger_message.h"

void messenger_messaage_init(struct messenger_message_t* message)
{
  message->buffer_lengths = NULL;
  message->buffer = NULL;

  message->session = NULL;
  message->client = NULL;
}

void messenger_message_property_set(struct messenger_message_t* message, uint16_t property, uint16_t value)
{
}

uint16_t messenger_message_property_get(struct messenger_message_t* message, uint16_t proprety)
{
}

void messenger_message_attach_client(struct messenger_message_t* message, struct messenger_client_t* client)
{
  message->client = client;
}

void messenger_message_attach_session(struct messenger_message_t* message, struct messenger_session_t* session)
{
  message->session = session;
}
