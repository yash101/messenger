#ifndef _MESSENGER_CONNECTION_H
#define _MESSENGER_CONNECTION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "messenger_base.h"

typedef struct messenger_connection_t
{
  struct sockaddr_in6* local;
  struct sockaddr_in6* remote;

  socket_handle_t socket;
  
  struct messenger_server_t* server;
  struct messenger_client_t* client;
} messenger_connection_t;

void
messenger_connection_init(
  struct messenger_connection_t* connection
);

#ifdef __cplusplus
}
#endif

#endif
