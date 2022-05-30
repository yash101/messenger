#ifndef _MESSENGER_BASE_H
#define _MESSENGER_BASE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <netinet/in.h>

#define TRUE 1
#define FALSE 0

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

/**
 * @brief Gets a string error from an error number
 * 
 * @param errno error number
 * @return const char* error message
 */
const char* messenger_error_msg(int errno);

/**
 * @brief Creates an error with all details
 * 
 * @param error Error to construct. May be NULL, and just the copy will be returned
 * @param code Error code 
 * @param file File the error is being thrown in
 * @param lineno Line number where the error is thrown
 * @return messenger_error_t A copy of the constructed error
 */
messenger_error_t messenger_error_create(messenger_error_t* error, int code, const char* file, const int lineno);

/**
 * @brief Create an error, pulling details from the error number
 * 
 * @param err Error to construct. May be NULL, and then just the copy will be returned
 * @param file File throwing the error
 * @param lineno Line number of the error
 * @return messenger_error_t Copy of the error
 */
messenger_error_t messenger_error_from_errno(int err, const char* file, const int lineno);

#define messenger_error(status) messenger_error_create(NULL, status, __FILE__, __LINE__)
#define messenger_error_errno(err) messenger_error_from_errno(err, __FILE__, __LINE__)

typedef int socket_handle_t; /// Type 
extern const socket_handle_t messenger_DEFAULT_SOCKET;

int isIPv6(struct sockaddr_in6* ipv6_addr);
void toIPv4(struct sockaddr_in6* ipv6_addr, struct sockaddr_in* ipv4_addr);
void toIPv6(struct sockaddr_in* ipv4_addr, struct sockaddr_in6* ipv6_addr);

typedef int messenger_connection_t;
extern const messenger_connection_t messenger_UDP;
extern const messenger_connection_t messenger_WS;

typedef struct messenger_buffer_t
{
  char* buffer;
  size_t length;
  size_t allocated;
} messenger_buffer_t;

void messenger_buffer_init(struct messenger_buffer_t* buffer);
void messenger_buffer_destroy(struct messenger_buffer_t* buffer);

size_t messenger_buffer_alloc(struct messenger_buffer_t* buffer, size_t len, int preserve);
size_t messenger_buffer_length(struct messenger_buffer_t* buffer);
size_t messenger_buffer_capacity(struct messenger_buffer_t* buffer);

size_t messenger_buffer_copy_from_buffer(struct messenger_buffer_t* buffer, const char* source, size_t len);
size_t messenger_buffer_copy_str(struct messenger_buffer_t* buffer, const char* str);
size_t messenger_buffer_copy_str_s(struct messenger_buffer_t* buffer, const char* str, size_t maxlen);

#ifdef __cplusplus
}
#endif

#endif
