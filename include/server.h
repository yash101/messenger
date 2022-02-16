#ifndef _MESSENGER_SERVER_H
#define _MESSENGER_SERVER_H

#include "messenger_base.h"
#include "connection.h"

typedef struct messenger_server_t
{
  struct sockaddr_in6* addr;
  socket_handle_t socket;

  unsigned short int port;
} messenger_server_t;

void
messenger_server_init(
  struct messenger_server_t* server,
  unsigned short int port
);

struct messenger_error_t
messenger_server_bind(
  struct messenger_server_t* server
);

struct messenger_error_t
messenger_server_accept(
  struct messenger_server_t* server
);

void
messenger_server_destroy(
  struct messenger_server_t* server
);

#endif
