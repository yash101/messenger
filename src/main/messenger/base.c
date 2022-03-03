#ifdef __cplusplus
extern "C"
{
#endif

#include "messenger/messenger_base.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>

const char* error_messages[] =
{
  "Success",
  "Bad allocation",
  "Socket create failure",
  "Setsockopt failure",
  "Already initialized",
  "Bind failed",
  "Invalid argument",
  "Permission deined",
  "Address family not supported",
  "File descriptor limit reached",
  "Protocol not supported",
  "Unknown Failure",
  "Bad file descriptor",
  "Invalid address",
  "Not a socket",
  "Unknown option"
};

const char* messenger_error_msg(int err)
{
  if (errno >= sizeof(error_messages) / sizeof(error_messages[0]))
  {
    return "Unknown error";
  }

  return error_messages[errno];
}

messenger_error_t messenger_error_create(messenger_error_t* error, int status, const char* file, const int lineno)
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

messenger_error_t messenger_error_from_errno(int err, const char* file, const int lineno)
{
  messenger_error_t ret;
  ret.status = err + 64;
  ret.message = strerror(err);
  ret.file = file;
  ret.lineno = lineno;

  return ret;
}

const socket_handle_t messenger_DEFAULT_SOCKET = 0;

#ifdef __cplusplus
}
#endif
