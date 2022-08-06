#ifndef _MESSENGER_CLIENT_H
#define _MESSENGER_CLIENT_H

#include <netinet/in.h>

#include "base.h"
#include "session.h"

#ifdef __cplusplus

namespace messenger
{
  class Client
  {
  public:
    Client();
    ~Client();

    messenger_error_t dial(std::string address);
  };
}

#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct messenger_Client messenger_Client;

void messenger_Client_init(struct messenger_Client* client);
void messenger_Client_destroy(struct messenger_Client* client);
messenger_error_t messenger_Client_dial(struct messenger_Client* client, const char* address);
messenger_Session* messenger_Client_getSession(struct messenger_Client* client);

#ifdef __cplusplus
}
#endif

#endif
