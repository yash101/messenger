#ifndef _MESSENGER_SESSION_H
#define _MESSENGER_SESSION_H

/**
 * @brief Session object for messenger. Maintains a connection between a Client and Server and faciliates message transmission between both.
 * 
 * The session is used to maintain a connection with a client. A session will transit and receive the stream of messages.
 */
typedef struct messenger_session_t
{
} messenger_session_t;

void messenger_session_init(struct messenger_session_t* session);
void messenger_session_destroy(struct messenger_session_t* session);

bool messenger_session_close(struct messenger_session_t* session);

struct sockaddr_in6* messenger_session_get_client_info(struct messenger_session_t* session);
struct messenger_message_t* messenger_session_next(struct messenger_session_t* session);
void messenger_session_send(struct messenger_hsession_t* session, struct messenger_message_t* message);

#endif
