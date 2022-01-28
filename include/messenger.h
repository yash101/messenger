#ifndef _MESSENGER_H
#define _MESSENGER_H

#include <stdint.h>

typedef int socket_handle_t;

typedef struct messenger_error_t {
  int status;
  const char* message;
} messenger_error_t;

typedef struct messenger_client_t {
  struct sockaddr_in* addr_local;
  struct sockaddr_in* addr_remote;

  struct sockaddr_in6* addr_local6;
  struct sockaddr_in6* addr_remote6;
  
  socket_handle_t socket;
} messenger_client_t;

typedef struct messenger_server_t {
  struct sockaddr_in* addr_local;
  struct sockaddr_in6* addr_local6;
  
  socket_handle_t socket;
  socket_handle_t socket6;
  uint16_t port;
} messenger_server_t;

/*
  Error management
*/
messenger_error_t messenger_error_create(messenger_error_t* error, int status);
const char* messenger_error_msg_get(int errno);

/*
  Server
*/
messenger_error_t messenger_server_create(messenger_server_t* server);
void messenger_server_destroy(messenger_server_t* server);

void messenger_server_bind(messenger_server_t* server, uint16_t port);

/*
  Client
*/
messenger_error_t messenger_client_create(messenger_client_t* client);
void messenger_client_destroy(messenger_client_t* client);

void messenger_client_connect(messenger_client_t* client, const char* address, uint16_t port);

#endif
