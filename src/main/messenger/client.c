#include <stdlib.h>

#include "messenger/client.h"

#ifdef __cplusplus
extern "C"
{
#endif

void messenger_client_init(struct messenger_client_t* client)
{
  client->session = (struct messenger_session_t*) malloc(sizeof(struct messenger_session_t));
  messenger_session_init(client->session);
}

void messenger_client_destroy(struct messenger_client_t* client)
{
  messenger_session_close(client->session);
  messenger_session_destroy(client->session);
  free(client->session);
}

#ifdef __cplusplus
}
#endif
