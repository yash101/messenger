#include "connection.h"
#include "messenger_base.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

void
messenger_connection_init(
  messenger_connection_t* connection
)
{
  if (!connection)
    return;

  connection->local = NULL;
  connection->remote = NULL;
  connection->socket = messenger_DEFAULT_SOCKET;

  connection->server = NULL;
  connection->client = NULL;
}

#ifdef __cplusplus
}
#endif
