#include "messenger.h"

#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>









// messenger_error_t
// messenger_connection_create(
//   messenger_connection_t* connection
// )
// {
//   connection->addr_local = NULL;
//   connection->addr_local6 = NULL;
//   connection->addr_remote = NULL;
//   connection->addr_remote6 = NULL;

//   connection->socket = messenger_DEFAULT_SOCKET;
//   connection->socket6 = messenger_DEFAULT_SOCKET;

//   connection->ipv6 = 1;
// }

// void
// messenger_connection_destroy(
//   messenger_connection_t* connection
// )
// {
//   if (connection->socket != messenger_DEFAULT_SOCKET)
//   {
//     close(connection->socket);
//   }

//   if (connection->socket6 != messenger_DEFAULT_SOCKET)
//   {
//     close(connection->socket);
//   }

//   if (connection->addr_local)
//     free(connection->addr_local);
  
//   if (connection->addr_local6)
//     free(connection->addr_local6);
  
//   if (connection->addr_remote)
//     free(connection->addr_remote);
  
//   if (connection->addr_remote6)
//     free(connection->addr_remote6);

//   connection->addr_local = NULL;
//   connection->addr_local6 = NULL;
//   connection->addr_remote = NULL;
//   connection->addr_remote6 = NULL;

//   connection->socket = messenger_DEFAULT_SOCKET;
//   connection->socket6 = messenger_DEFAULT_SOCKET;
// }

// void
// messenger_connection_ipv6(
//   messenger_connection_t* connection,
//   int enable
// )
// {
//   connection->ipv6 = (enable) ? 1 : 0;
// }







// messenger_error_t
// messenger_client_create(
//   messenger_client_t* client
// )
// {
//   messenger_connection_create(&client->connection);
// }

// void
// messenger_client_destroy(
//   messenger_client_t* client
// )
// {
//   messenger_connection_destroy(&client->connection);
// }

// void
// messenger_client_ipv6(
//   messenger_client_t* client,
//   int enable
// ) {
//   messenger_connection_ipv6(&client->connection, enable);
// }

// void
// messenger_client_connect(
//   messenger_client_t* client,
//   const char* address,
//   uint16_t port
// )
// {
// }







// messenger_error_t
// messenger_server_create(
//   messenger_server_t* server
// )
// {
//   server->addr_local = NULL;
//   server->addr_local6 = NULL;

//   server->socket = messenger_DEFAULT_SOCKET;
//   server->socket6 = messenger_DEFAULT_SOCKET;
// }

// void
// messenger_server_destroy(
//   messenger_server_t* server
// )
// {
// }

// void
// messenger_server_bind(
//   messenger_server_t* server,
//   uint16_t port
// )
// {
// }

