#ifndef _MESSENGER_MESSENGER_H
#define _MESSENGER_MESSENGER_H

#include <stdint.h>

// typedef int socket_handle_t;
// const socket_handle_t messenger_DEFAULT_SOCKET = 0;

// /**
//  * @brief Error object - contains a code and a status
//  */
// typedef struct messenger_error_t {
//   int status;
//   const char* message;
// } messenger_error_t;

// /**
//  * @brief messenger protocol client structure
//  * 
//  * Manages and provides access to functions to connect to a messenger protocol server
//  */
// typedef struct messenger_client_t {
// } messenger_client_t;

// /**
//  * @brief messenger protocol server structure
//  * 
//  * Manages and provides access to functions to create a listening interface for messenger
//  *  protocol clients to join
//  */
// typedef struct messenger_server_t {
//   struct sockaddr_in* addr_local;     ///< Server ipv4 local address structure
//   struct sockaddr_in6* addr_local6;   ///< Server ipv6 local address structure
  
//   socket_handle_t socket;             ///< ipv4 socket handle
//   socket_handle_t socket6;            ///< ipv6 socket handle
//   uint16_t port;                      ///< Port to listen on

//   int ipv6;                           ///< enable / disable ipv6?
// } messenger_server_t;

// /**
//  * @brief Initializes a messenger_error_t structure with a status
//  * 
//  * Use error = NULL and the structure will be returned
//  * 
//  * @param error pointer to an error object to initialize
//  * @param status status code
//  * @return messenger_error_t A copy of the structure that was initialized
//  */
// messenger_error_t
// messenger_error_create(
//   messenger_error_t* error,
//   int status
// );

// /**
//  * @brief Get the string error description from an error code
//  * 
//  * @param errno 
//  * @return const char* Error string
//  */
// const char*
// messenger_error_msg_get(
//   int errno
// );


// /**
//  * @brief Initializes the messenger_connection_t object
//  * 
//  * @param connection pointer to connection object to be initialized
//  * @return messenger_error_t initialization error
//  */
// messenger_error_t
// messenger_connection_create(
//   messenger_connection_t* connection
// );

// /**
//  * @brief Destructor for messenger_connection_t object
//  * 
//  * @param connection Pointer to connection object to de-initialize and prepare to be freed
//  */
// void
// messenger_connection_destroy(
//   messenger_connection_t* connection
// );

// /**
//  * @brief Enables / disables ipv6 (default enabled)
//  * 
//  * @param connection Connection object
//  * @param enable 1 = on, 0 = off
//  */
// void
// messenger_connection_ipv6(
//   messenger_connection_t* connection,
//   int enable
// );


// /**
//  * @brief Initializes the messenger_server_t object
//  * 
//  * @param server pointer to the server object to be initialized
//  * @return messenger_error_t Initialization error
//  */
// messenger_error_t
// messenger_server_create(
//   messenger_server_t* server
// );

// /**
//  * @brief Destructor for messenger_server_t object
//  * 
//  * @param connection Pointer to connection object to de-initialize and prepare to be freed
//  */
// void
// messenger_server_destroy(
//   messenger_server_t* server
// );

// /**
//  * @brief Binds the server to a specific port - both on ipv4 and ipv6
//  * 
//  * @param server Pointer to server object
//  * @param port Port number to bind on
//  */
// void
// messenger_server_bind(
//   messenger_server_t* server,
//   uint16_t port
// );

// /**
//  * @brief Emables / disables ipv6
//  * 
//  * @param server Pointer to the server object
//  * @param enable 1 = on, 0 = off; default = 1
//  */
// void
// messenger_server_ipv6(
//   messenger_server_t* server,
//   int enable
// );


// /**
//  * @brief Initializes a messenger client
//  * 
//  * @param client Pointer to client to initialize
//  * @return messenger_error_t 
//  */
// messenger_error_t
// messenger_client_create(
//   messenger_client_t* client
// );

// /**
//  * @brief Destructor for the client object
//  * 
//  * @param client Pointer to client to deinitialize
//  */
// void
// messenger_client_destroy(
//   messenger_client_t* client
// );

// /**
//  * @brief Enables or disables ipv6
//  * 
//  * @param client Pointer to client
//  * @param enable 1 = on; 0 = off
//  */
// void
// messenger_client_ipv6(
//   messenger_client_t* client,
//   int enable
// );

// /**
//  * @brief Connects a client to a specific address and port
//  * 
//  * @param client Pointer to messenger_client_t client object
//  * @param address Address to connect to
//  * @param port Port to connect to
//  */
// void
// messenger_client_connect(
//   messenger_client_t* client,
//   const char* address,
//   uint16_t port
// );

#include "server.h"
#include "client.h"

#endif
