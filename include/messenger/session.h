#ifndef _MESSENGER_SESSION_H
#define _MESSENGER_SESSION_H

#include <netinet/in.h>

#include "base.h"
#include "message.h"

/**
 * @brief Session object for messenger. Maintains a connection between a Client and Server and faciliates message transmission between both.
 * 
 * The session is used to maintain a connection with a client. A session will transit and receive the stream of messages.
 * 
 * Note: Session objects are generally created by a Client or a Server.
 */
typedef struct messenger_session_t
{
  socket_handle_t socket;
  struct sockaddr_in6 local_address;
  struct sockaddr_in6 remote_address;

  // need structures for the queueing
} messenger_session_t;

/**
 * @brief Constructor for messenger_session_t
 * 
 * @param session Session to initialize
 */
void messenger_session_init(struct messenger_session_t* session);
/**
 * @brief Destructor for messenger_session_t
 * 
 * @param session Session to destruct
 */
void messenger_session_destroy(struct messenger_session_t* session);

/**
 * @brief Close the remote connection
 * 
 * @param session Session to close
 * @return struct messenger_error_t Errors that happened (or success)
 */
struct messenger_error_t messenger_session_close(struct messenger_session_t* session);

/**
 * @brief Get the sockaddr_in6 for the remote peer
 * 
 * /todo Implement shutdown and close operations on the socket
 * /todo (future) Make cross-platform (support Windows)
 * 
 * @param session Session to pull the data from
 * @return struct sockaddr_in6 IPv6 POSIX sockaddr
 */
struct sockaddr_in6 messenger_session_get_remote_info(struct messenger_session_t* session);
/**
 * @brief Get the local address
 * 
 * @param session Session to pull the data from
 * @return struct sockaddr_in6 IPv6 POSIX sockaddr
 */
struct sockaddr_in6 messenger_session_get_local_info(struct messenger_session_t* session);

/**
 * @brief Wait for and receive the next message
 * 
 * /todo Implement the receive functionality
 * 
 * @param session Session to receive from
 * @param message Message object to put the message in
 * @return struct messenger_error_t Error
 */
struct messenger_error_t messenger_session_next(struct messenger_session_t* session, struct messenger_message_t* message);
/**
 * @brief Send a message to the remote peer
 * 
 * /todo Implement the send functionality
 * 
 * @param session Session with the connection to send to
 * @param message Message to send
 * @return struct messenger_error_t Error
 */
struct messenger_error_t messenger_session_send(struct messenger_session_t* session, struct messenger_message_t* message);

#endif
