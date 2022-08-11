#include "messenger/session.h"

MessengerSession::MessengerSession()
{
}

MessengerSession::~MessengerSession()
{
}

struct sockaddr_in6 MessengerSession::getRemoteAddress()
{
  return sockaddr_in6{};
}

struct sockaddr_in6 MessengerSession::getLocalAddress()
{
  return sockaddr_in6{};
}
