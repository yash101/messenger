#ifndef _MESSENGER_H
#define _MESSENGER_H

#include <stdint.h>

typedef struct messenger_error_t {
  int status;
  const char* message;
} messenger_error_t;

typedef struct messenger_client_t {
} messenger_client_t;

typedef struct messenger_server_t {
} messenger_server_t;

messenger_error_t messenger_create_error(messenger_error_t* error, int status);
const char* messenger_get_error_msg(int errno);

void messenger_create_server(messenger_server_t* server);
void messenger_create_client(messenger_client_t* server);
void messenger_bind_server(messenger_server_t* server, uint16_t port);
void messenger_connect_client(messenger_client_t* client, const char* address, uint16_t port);

#endif
