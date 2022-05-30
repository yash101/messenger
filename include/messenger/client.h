#ifndef _MESSENGER_CLIENT_H
#define _MESSENGER_CLIENT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>

#include "base.h"
#include "session.h"

typedef struct messenger_client_t
{
  struct messenger_session_t* session;
} messenger_client_t;

void messenger_client_init(struct messenger_client_t* client);
void messenger_client_destroy(struct messenger_client_t* client);

messenger_error_t messenger_client_dial(struct messenger_client_t* client, const char* address);
struct messenger_session_t* messenger_client_get_session(struct messenger_client_t* client);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
