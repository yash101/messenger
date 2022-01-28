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

messenger_error_t messenger_server_create(messenger_server_t* server)
{
  server->socket = 0;
  server->addr_local = malloc(sizeof(struct sockaddr_in));
  server->addr_local6 = malloc(sizeof(struct sockaddr_in6));

  if (
    !server->addr_local ||
    !server->addr_local6
  )
  {
    return messenger_error_create(NULL, 1);
  }

  memset(server->addr_local, 0, sizeof(struct sockaddr_in));
  memset(server->addr_local6, 0, sizeof(struct sockaddr_in));

  server->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (server->socket < 0)
  {
    server->socket = 0;
    return messenger_error_create(NULL, 2);
  }

  server->socket6 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
  if (server->socket < 0)
  {
    close(server->socket);
    server->socket = 0;
    server->socket6 = 0;
    return messenger_error_create(NULL, 2);
  }

  return messenger_error_create(NULL, 0);
}

messenger_error_t messenger_client_create(messenger_client_t* client)
{
  client->addr_local = malloc(sizeof(struct sockaddr_in));
  client->addr_local6 = malloc(sizeof(struct sockaddr_in6));
  client->addr_remote = malloc(sizeof(struct sockaddr_in));
  client->addr_remote6 = malloc(sizeof(struct sockaddr_in6));

  if (
    !client->addr_local ||
    !client->addr_local6 ||
    !client->addr_remote ||
    !client->addr_remote6
  )
  {
    if (client->addr_local)
      free(client->addr_local);
    if (client->addr_local6)
      free(client->addr_local6);
    if (client->addr_remote)
      free(client->addr_remote);
    if (client->addr_remote6)
      free(client->addr_remote6);
    
    return messenger_error_create(NULL, 1);
  }

  memset(client->addr_local, 0, sizeof(struct sockaddr_in));
  memset(client->addr_local6, 0, sizeof(struct sockaddr_in));
  memset(client->addr_remote, 0, sizeof(struct sockaddr_in));
  memset(client->addr_remote6, 0, sizeof(struct sockaddr_in));

  return messenger_error_create(NULL, 0);
}

void messenger_server_destroy(messenger_server_t* server)
{
  if (server->addr_local)
    free(server->addr_local);
  if (server->addr_local6)
    free(server->addr_local6);
}

void messenger_client_destroy(messenger_client_t* client)
{
  if (client->addr_local)
    free(client->addr_local);
  if (client->addr_local6)
    free(client->addr_local6);
  if (client->addr_remote)
    free(client->addr_remote);
  if (client->addr_remote6)
    free(client->addr_remote6);
}

void messenger_server_bind(messenger_server_t* server, uint16_t port)
{
  server->addr_local->sin_family = AF_INET;
  server->addr_local->sin_port = htons(server->port);
  server->addr_local->sin_addr.s_addr = htonl(INADDR_ANY);

  server->addr_local6->sin6_family = AF_INET6;
  server->addr_local6->sin6_port = htons(server->port);
  server->addr_local6->sin6_addr = in6addr_any;

  if (bind(server->socket, (struct sockaddr*) server->addr_local, sizeof(struct sockaddr_in)) < 0)
  {
  }

  if (bind(server->socket6, (struct sockaddr*) server->addr_local6, sizeof(struct sockaddr_in6)) < 0)
  {
  }
}

void messenger_client_connect(messenger_client_t* client, const char* address, uint16_t port)
{
}
