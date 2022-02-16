#include "connection.h"
#include "messenger_base.h"

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
