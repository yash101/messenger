#ifndef _MESSENGER_BASE_H
#define _MESSENGER_BASE_H

#include <stddef.h>
#include <netinet/in.h>

#ifdef __cplusplus
#include <exception>
#include <string>
#endif

/*
 *    Enums and definitions
 *    C/C++
 */
typedef enum MessengerSystemExceptionCode
{
  EXCEPTION_NONE = 0,
  EXCEPTION_NOT_PERMITTED = 1,
  EXCEPTION_NOENT = 2,
  EXCEPTION_NO_PROCESS = 3, // ESRCH
  EXCEPTION_INTERRUPTED = 4,
  EXCEPTION_IO = 5,
  EXCEPTION_NO_DEVICE = 6,
  EXCEPTION_ARGUMENTS_LIST_TOO_LONG = 7,
  EXCEPTION_NO_EXEC = 8,
  EXCEPTION_BAD_FD = 9,
  EXCEPTION_NO_CHILD = 10,
  EXCEPTION_TRY_AGAIN = 11,
  EXCEPTION_OOM = 12,
  EXCEPTION_PERMISSION_DENIED = 13,
  EXCEPTION_BAD_ADDRESS = 14,
  EXCEPTION_NOTBLK = 15,
  EXCEPTION_BUSY = 16,
  EXCEPTION_EXISTS = 17,
  EXCEPTION_DEVICE = 18,
  EXCEPTION_NOTDIR = 20,
  EXCEPTION_ISDIR = 21,
  EXCEPTION_INVALID_ARGUMENT = 22,
} MessengerSystemExceptionCode;

/*
 *  C++ only classes (OOP implementation)
 */
#ifdef __cplusplus

  namespace messenger
  {
    class SystemException : public std::exception
    {
      MessengerSystemExceptionCode err_code;
      std::string message;
    public:
      SystemException();
      SystemException(MessengerSystemExceptionCode code);
      SystemException(std::string message, MessengerSystemExceptionCode code);

      virtual const char* what() const throw();
      virtual const MessengerSystemExceptionCode code() const throw();
    };
  }

#endif

#ifdef __cplusplus
  extern "C" {
#endif

struct SystemException* messenger_SystemException_new(const char* message, const MessengerSystemExceptionCode code);
struct SystemException* messenger_SystemException_destroy(struct SystemException* ex);
const char* messenger_SystemException_what(struct SystemException* ex);
const MessengerSystemExceptionCode messenger_SystemException_code(struct SystemException* ex);

#ifdef __cplusplus
  }
#endif

#endif
