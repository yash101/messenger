#include "messenger.h"

#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

const char* error_messages[] =
{
  "Success",
  "Bad allocation",
  "Socket create failure"
};

const char* messenger_error_msg_get(int errno)
{
  if (errno >= sizeof(error_messages) / sizeof(error_messages[0]))
  {
    return "Unknown error";
  }

  return error_messages[errno];
}

messenger_error_t messenger_error_create(
  messenger_error_t* error,
  int status
)
{
  messenger_error_t err;
  if (!error)
    error = &err;

  error->status = status;
  error->message = messenger_error_msg_get(status);

  return *error;
}








messenger_error_t messenger_connection_create(messenger_connection_t* connection)
{
  connection->addr_local = NULL;
  connection->addr_local6 = NULL;
  connection->addr_remote = NULL;
  connection->addr_remote6 = NULL;

  connection->socket = messenger_DEFAULT_SOCKET;
  connection->socket6 = messenger_DEFAULT_SOCKET;

  connection->ipv6 = 1;
}

void messenger_connection_destroy(messenger_connection_t* connection)
{
  if (connection->socket != messenger_DEFAULT_SOCKET)
  {
    close(connection->socket);
  }

  if (connection->socket6 != messenger_DEFAULT_SOCKET)
  {
    close(connection->socket);
  }

  if (connection->addr_local)
    free(connection->addr_local);
  
  if (connection->addr_local6)
    free(connection->addr_local6);
  
  if (connection->addr_remote)
    free(connection->addr_remote);
  
  if (connection->addr_remote6)
    free(connection->addr_remote6);

  connection->addr_local = NULL;
  connection->addr_local6 = NULL;
  connection->addr_remote = NULL;
  connection->addr_remote6 = NULL;

  connection->socket = messenger_DEFAULT_SOCKET;
  connection->socket6 = messenger_DEFAULT_SOCKET;
}








messenger_error_t messenger_server_create(messenger_server_t* server)
{
}

messenger_error_t messenger_client_create(messenger_client_t* client)
{
}

void messenger_client_connect(messenger_client_t* client, const char* address, uint16_t port)
{
}







void messenger_server_destroy(messenger_server_t* server)
{
}

void messenger_client_destroy(messenger_client_t* client)
{
}

void messenger_server_bind(messenger_server_t* server, uint16_t port)
{
}

