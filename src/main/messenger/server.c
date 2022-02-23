#include "messenger_base.h"
#include "server.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void
messenger_server_init(
  struct messenger_server_t* server,
  unsigned short int port
)
{
  server->addr = NULL;
  server->port = port;
  server->socket = messenger_DEFAULT_SOCKET;
}

struct messenger_error_t
messenger_server_bind(
  struct messenger_server_t* server
)
{
  int opt;
  int error;
  if (server->socket != messenger_DEFAULT_SOCKET) {
    return messenger_error(4);
  }

  server->addr = (struct sockaddr_in6*) malloc(sizeof(struct sockaddr_in6));
  if (!server->addr) {
    free(server->addr);
    return messenger_error(1);
  }

  // create socket
  server->socket = socket(AF_INET6, SOCK_DGRAM, 0);
  if (server->socket <= 0) {
    server->socket = messenger_DEFAULT_SOCKET;
    free(server->addr);
    server->addr = NULL;
    return messenger_error(2);
  }

  // set reuseaddr and reuseport for the socket
  opt = 1;
  error = setsockopt(
    server->socket,
    SOL_SOCKET,
    SO_REUSEADDR | SO_REUSEPORT,
    (void*) &opt,
    sizeof(opt)
  );
  if (error)
  {
    close(server->socket);
    server->socket = messenger_DEFAULT_SOCKET;
    free(server->addr);
    server->addr = NULL;
    return messenger_error(3);
  }

  // allow ipv4 on ipv6 sockets
  opt = 0;
  error = setsockopt(
    server->socket,
    IPPROTO_IPV6,
    IPV6_V6ONLY,
    (void*) &opt,
    sizeof(opt)
  );
  if (error)
  {
    close(server->socket);
    server->socket = messenger_DEFAULT_SOCKET;
    free(server->addr);
    server->addr = NULL;

    return messenger_error(3);
  }

  // set the listen address
  memset((void*) server->addr, 0x0, sizeof(*server->addr));
  server->addr->sin6_family = AF_INET6;
  server->addr->sin6_port = htons(server->port);
  server->addr->sin6_addr = in6addr_any;

  // bind to address
  error = bind(
    server->socket,
    (struct sockaddr*) server->addr,
    sizeof(struct sockaddr_in6)
  );

  if (error) {
    close(server->socket);
    server->socket = messenger_DEFAULT_SOCKET;
    free(server->addr);
    server->addr = NULL;

    return messenger_error(5);
  }

  return messenger_error(0);
}

// accept works different since we are using UDP. shit!
struct messenger_error_t
messenger_server_accept(
  struct messenger_server_t* server,
  struct messenger_connection_t* connection
)
{
  if (!server || !connection)
    return messenger_error(1);

  messenger_connection_init(connection);
  connection->local = server->addr;
  int addrlen = sizeof(struct sockaddr_in6);

  getpeername(server->socket, (struct sockaddr*) connection->remote, (socklen_t*) &addrlen);

  return messenger_error(0);
}

void
messenger_server_destroy(
  struct messenger_server_t* server
)
{
  shutdown(server->socket, SHUT_RDWR);
  close(server->socket);
  free(server->addr);

  server->socket = messenger_DEFAULT_SOCKET;
  server->addr = NULL;
}
