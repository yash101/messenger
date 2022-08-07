#ifndef _MESSENGER_CLIENT_H
#define _MESSENGER_CLIENT_H

#include <netinet/in.h>

#include "base.h"
#include "session.h"

/**
 *  C++ only
 */
#ifdef __cplusplus

  class MessengerClient
  {
  public:
    MessengerClient();
    ~MessengerClient();

    void dial(std::string address);
  };

#endif

#ifdef __cplusplus
extern "C"
{
#endif

void messenger_Client_init(struct MessengerClient* client);
void messenger_Client_destroy(struct MessengerClient* client);

// messenger_error_t messenger_Client_dial(struct messenger_Client* client, const char* address);
// messenger_Session* messenger_Client_getSession(struct messenger_Client* client);

#ifdef __cplusplus
}
#endif

#endif
