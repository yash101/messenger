#include "messenger/session.h"

void messenger_session_init(struct messenger_session_t* session)
{
  session->socket = messenger_DEFAULT_SOCKET;
}

void messenger_session_destroy(struct messenger_session_t* session)
{
}

struct messenger_error_t messenger_session_close(struct messenger_session_t* session)
{
  return messenger_error(0);
}

struct sockaddr_in6 messenger_session_get_remote_info(struct messenger_session_t* session)
{
  return session->remote_address;
}

struct sockaddr_in6 messenger_session_get_local_info(struct messenger_session_t* session)
{
  return session->local_address;
}

struct messenger_error_t messenger_session_next(struct messenger_session_t* session, struct messenger_message_t* message)
{
  return messenger_error(0);
}

struct messenger_error_t messenger_session_send(struct messenger_session_t* session, struct messenger_message_t* message)
{
  return messenger_error(0);
}
