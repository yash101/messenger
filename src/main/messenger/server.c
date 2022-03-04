#include "messenger/messenger_base.h"
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

struct messenger_error_t messenger_server_bind(struct messenger_server_t* server)
{
  int opt;
  int error;
  if (server->socket != messenger_DEFAULT_SOCKET) {
    return messenger_error(4);
  }

  server->addr = (struct sockaddr_in6*) calloc(1, sizeof(struct sockaddr_in6));
  if (!server->addr) {
    free(server->addr);
    return messenger_error(1);
  }

  // create socket
  server->socket = socket(AF_INET6, SOCK_DGRAM, 0);

  // Failed to create socket
  if (server->socket <= 0) {
    int err = errno;

    server->socket = messenger_DEFAULT_SOCKET;
    free(server->addr);
    server->addr = NULL;

    return messenger_error_errno(err);
  }

  // set reuseaddr and reuseport for the socket
  opt = 1;
  error = setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, (void*) &opt, sizeof(opt));
  if (error)
  {
    int err = errno;

    close(server->socket);
    server->socket = messenger_DEFAULT_SOCKET;
    free(server->addr);
    server->addr = NULL;

    return messenger_error_errno(err);
  }

  // allow ipv4 on ipv6 sockets
  opt = 0;
  error = setsockopt(server->socket, IPPROTO_IPV6, IPV6_V6ONLY, (void*) &opt, sizeof(opt));
  if (error)
  {
    int err = errno;

    close(server->socket);
    server->socket = messenger_DEFAULT_SOCKET;
    free(server->addr);
    server->addr = NULL;

    return messenger_error_errno(err);
  }

  // set the listen address

  server->addr->sin6_family = AF_INET6;
  server->addr->sin6_port = htons(server->port);
  server->addr->sin6_addr = in6addr_any;

  // bind to address
  error = bind(server->socket, (struct sockaddr*) server->addr, sizeof(struct sockaddr_in6));

  if (error) {
    close(server->socket);
    server->socket = messenger_DEFAULT_SOCKET;
    free(server->addr);
    server->addr = NULL;

    return messenger_error(5);
  }

  return messenger_error(0);
}

struct messenger_error_t messenger_server_recv_packet(struct messenger_server_t* server)
{
  if (!server || server->socket == messenger_DEFAULT_SOCKET)
    return messenger_error(6);

  // Receive a packet

}

#ifdef __cplusplus
}
#endif
