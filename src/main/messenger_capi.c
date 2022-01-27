#include "messenger.h"

#include <string.h>

const char* error_messages[] =
{
  "Success"
};

const char* messenger_get_error_msg(int errno)
{
  if (errno >= sizeof(error_messages) / sizeof(error_messages[0]))
  {
    return "Unknown error";
  }

  return error_messages[errno];
}

messenger_error_t messenger_create_error(
  messenger_error_t* error,
  int status
)
{
  messenger_error_t err;
  if (!error)
    error = &err;

  error->status = status;
  error->message = messenger_get_error_msg(status);

  return *error;
}

void messenger_create_server(messenger_server_t* server)
{
}

void messenger_create_client(messenger_client_t* client)
{
}

void messenger_bind_server(messenger_server_t* server, uint16_t port)
{
}

void messenger_connect_client(messenger_client_t* client, const char* address, uint16_t port)
{
}
