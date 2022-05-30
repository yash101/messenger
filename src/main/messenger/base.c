#ifdef __cplusplus
extern "C"
{
#endif

#include "messenger/base.h"

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

static const uint8_t mask_6to4[12] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff };

int isIPv6(struct sockaddr_in6* ipv6_addr)
{
  for (size_t i = 0; i < 12; i++)
    if (ipv6_addr->sin6_addr.s6_addr[i] != mask_6to4[i])
      return FALSE;

  return TRUE;
}

void toIPv4(struct sockaddr_in6* v6, struct sockaddr_in* v4)
{
  v4->sin_addr.s_addr = htonl(
    (v6->sin6_addr.s6_addr[12] << 24) |
    (v6->sin6_addr.s6_addr[13] << 16) |
    (v6->sin6_addr.s6_addr[14] << 8) |
    v6->sin6_addr.s6_addr[15]
  );

  v4->sin_family = v6->sin6_family;
  v4->sin_port = v6->sin6_port;
  memset(v4->sin_zero, 0x0, sizeof(v4->sin_zero));
}

void toIPv6(struct sockaddr_in* v4, struct sockaddr_in6* v6)
{
  for (int i = 0; i < 12; i++)
    v6->sin6_addr.s6_addr[i] = mask_6to4[i];
  
  v6->sin6_addr.s6_addr[12] = (v4->sin_addr.s_addr >> 24) & 0xff;
  v6->sin6_addr.s6_addr[13] = (v4->sin_addr.s_addr >> 16) & 0xff;
  v6->sin6_addr.s6_addr[14] = (v4->sin_addr.s_addr >> 8) & 0xff;
  v6->sin6_addr.s6_addr[15] = (v4->sin_addr.s_addr >> 0) & 0xff;

  v6->sin6_family = v4->sin_family;
  v6->sin6_port = v4->sin_port;
}

void messenger_buffer_init(struct messenger_buffer_t* buffer)
{
  if (!buffer)
    return;

  buffer->buffer = NULL;
  buffer->length = 0;
  buffer->allocated = 0;
}

void messenger_buffer_destroy(struct messenger_buffer_t* buffer)
{
  if (!buffer || !buffer->buffer)
    return;

  free(buffer->buffer);
  buffer->buffer = NULL;
  buffer->length = 0;
  buffer->allocated = NULL;
}

size_t messenger_buffer_alloc(struct messenger_buffer_t* buffer, size_t len, int preserve)
{
  if (!buffer)
    return 0;

  // 0 bytes buffer requested
  if (len == 0)
  {
    if (buffer->allocated == 0)
    {
      free(buffer->buffer);
      buffer->length = 0;
      buffer->allocated = 0;
    }
    return 0;
  }
  
  // we need to allocate more space
  if (len > buffer->allocated)
  {
    char* tmp = malloc(len);
    if (!tmp)
    {
      return 0;
    }

    if (preserve)
    {
      size_t copy = (len < buffer->length) ? len : buffer->length;
      for (size_t i = 0; i < copy; i++)
        tmp[i] = buffer->buffer[i];
    }

    if (buffer->buffer)
      free(buffer->buffer);

    buffer->allocated = len;
    buffer->length = len;
    buffer->buffer = tmp;

    return len;
  }

  // enough space is already allocated
  buffer->length = len;
  return len;
}

size_t messenger_buffer_length(struct messenger_buffer_t* buffer)
{
  if (!buffer)
    return 0;

  return buffer->length;
}

size_t messenger_buffer_capacity(struct messenger_buffer_t* buffer)
{
  if (!buffer)
    return 0;

  return buffer->allocated;
}

size_t messenger_buffer_copy_from_buffer(struct messenger_buffer_t* buffer, const char* source, size_t len)
{
  if (source == NULL)
    len = 0;

  if (!buffer || !messenger_buffer_alloc(buffer, len, FALSE))
    return 0;

  for (size_t i = 0; i < len; i++)
    buffer->buffer[i] = source[i];
  
  return len;
}

size_t messenger_buffer_copy_str(struct messenger_buffer_t* buffer, const char* str)
{
  if (!buffer)
    return 0;
  
  if (!str)
    return messenger_buffer_alloc(buffer, 0, FALSE);

  size_t len = strlen(str);
  return messenger_buffer_copy_from_buffer(buffer, str, len + 1);
}

size_t messenger_buffer_copy_str_s(struct messenger_buffer_t* buffer, const char* str, size_t mxlen)
{
  if (!buffer)
    return 0;
  
  if (!str)
    return messenger_buffer_alloc(buffer, 0, FALSE);
  
  size_t len = 0;
  const char* strend = str;
  while (*strend != 0x0 && len < mxlen)
    len++;
  
  return messenger_buffer_copy_from_buffer(buffer, str, len + 1);
}

#ifdef __cplusplus
}
#endif
