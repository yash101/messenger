#ifndef _MESSENGER_BASE_H
#define _MESSENGER_BASE_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef int socket_handle_t;
const socket_handle_t messenger_DEFAULT_SOCKET = 0;

/**
 * @brief Error object - contains a code and a status
 */
typedef struct messenger_error_t {
  int status;
  const char* message;
  const char* file;
  int lineno;
} messenger_error_t;

const char*
messenger_error_msg(
  int errno
);

messenger_error_t
messenger_error_create(
  messenger_error_t* error,
  int status,
  const char* file,
  const int lineno
);

#define messenger_error(status) messenger_error_create(NULL, status, __FILE__, __LINE__)

#ifdef __cplusplus
}
#endif

#endif
