#ifndef _MESSENGER_BASE_H
#define _MESSENGER_BASE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

/**
 * @brief Error object - contains a code and a status
 */
typedef struct messenger_error_t
{
  int status;
  const char* message;
  const char* file;
  int lineno;
} messenger_error_t;

const char* messenger_error_msg(int errno);
messenger_error_t messenger_error_create(messenger_error_t* error, int status, const char* file, const int lineno);
messenger_error_t messenger_error_from_errno(int err, const char* file, const int lineno);

#define messenger_error(status) messenger_error_create(NULL, status, __FILE__, __LINE__)
#define messenger_error_errno(err) messenger_error_from_errno(err, __FILE__, __LINE__)

typedef int socket_handle_t;
extern const socket_handle_t messenger_DEFAULT_SOCKET;

int isIPv6(struct sockaddr_in6* ipv6_addr);
void toIPv4(struct sockaddr_in6* ipv6_addr, struct sockaddr_in* ipv4_addr);
void toIPv6(struct sockaddr_in6* ipv6_addr, struct sockaddr_in* ipv4_addr);

typedef struct messenger_buffer_t
{
  char* buffer;
  size_t length;
  size_t allocated;
} messenger_buffer_t;

void messenger_buffer_init(struct messenger_buffer_t* buffer);
void messenger_buffer_destroy(struct messenger_buffer_t* buffer);

size_t messenger_buffer_alloc(struct messenger_buffer_t* buffer, size_t len);
size_t messenger_buffer_length(struct messenger_buffer_t* buffer);
size_t messenger_buffer_allocated(struct messenger_buffer_t* buffer);

size_t messenger_buffer_copy_from(struct messenger_buffer_t* buffer, const char* source, size_t len);
size_t messenger_buffer_copy_str(struct messenger_buffer_t* buffer, const char* str);
size_t messenger_buffer_copy_str_max(struct messenger_buffer_t* buffer, const char* str, size_t maxlen);

#ifdef __cplusplus
}
#endif

#endif
