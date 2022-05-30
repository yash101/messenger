#include "messenger/base.h"
#include "messenger/server.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void messenger_server_init(struct messenger_server_t* server, unsigned short int port)
{
  server->addr = NULL;
  server->port = port;
  server->socket = messenger_DEFAULT_SOCKET;
}

void messenger_server_destroy(struct messenger_server_t* server)
{
  if (server->socket != messenger_DEFAULT_SOCKET)
  {
    shutdown(server->socket, SHUT_RDWR);
    close(server->socket);
  }

  if (server->addr)
    free(server->addr);

  server->socket = messenger_DEFAULT_SOCKET;
  server->addr = NULL;
}

#ifdef __cplusplus
}
#endif
