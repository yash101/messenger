#ifdef __cplusplus
extern "C"
{
#endif

#include "messenger_base.h"

const char* error_messages[] =
{
  "Success",
  "Bad allocation",
  "Socket create failure",
  "Setsockopt failure",
  "Already initialized",
  "Bind failed"
};

const char*
messenger_error_msg(
  int errno
)
{
  if (errno >= sizeof(error_messages) / sizeof(error_messages[0]))
  {
    return "Unknown error";
  }

  return error_messages[errno];
}

messenger_error_t
messenger_error_create(
  messenger_error_t* error,
  int status,
  const char* file,
  const int lineno
)
{
  messenger_error_t err;
  if (!error)
    error = &err;

  error->status = status;
  error->message = messenger_error_msg(status);
  error->file = file;
  error->lineno = lineno;

  return *error;
}

const socket_handle_t messenger_DEFAULT_SOCKET = 0;

#ifdef __cplusplus
}
#endif
