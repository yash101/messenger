#ifndef _MESSENGER_SERVER_H
#define _MESSENGER_SERVER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "messenger_base.h"
#include "connection.h"

typedef struct messenger_server_t
{
  struct sockaddr_in6* addr;
  socket_handle_t socket;

  unsigned short int port;
} messenger_server_t;

typedef (*messenger_server_accept_handler_t)(struct messenger_server_t* server, struct messenger_connection_t* connection);

void messenger_server_init(struct messenger_server_t* server, unsigned short int port);
void messenger_server_destroy(struct messenger_server_t* server);
struct messenger_error_t messenger_server_bind(struct messenger_server_t* server);
struct messenger_error_t messenger_server_recv_packet(struct messenger_server_t* server);

void messenger_server_accept_handler(struct messenger_server_t* server);

#ifdef __cplusplus
}
#endif

#endif
