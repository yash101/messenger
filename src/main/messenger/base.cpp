#include "messenger/base.h"

MessengerSystemException::MessengerSystemException() :
  err_code(MessengerSystemExceptionCode::EXCEPTION_NONE),
  message("")
{ }

MessengerSystemException::MessengerSystemException(
  MessengerSystemExceptionCode code
) :
  err_code(code),
  message("")
{ }

MessengerSystemException::MessengerSystemException(
  std::string message,
  MessengerSystemExceptionCode code
) :
  err_code(code),
  message(message)
{ }

const char* MessengerSystemException::what() const throw()
{
  return message.c_str();
}

const MessengerSystemExceptionCode MessengerSystemException::code() const throw()
{
  return err_code;
}

extern "C"
struct MessengerSystemException* messenger_SystemException_new(
  const char* message,
  const MessengerSystemExceptionCode code
)
{
  return new MessengerSystemException(std::string(message), code);
}

extern "C"
struct MessengerSystemException* messenger_SystemException_destroy(
  struct MessengerSystemException* ex
)
{
  if (ex)
    delete ex;
  return nullptr;
}

extern "C"
const char* messenger_SystemException_what(
  struct MessengerSystemException* ex
)
{
  return ex->what();
}

extern "C"
const MessengerSystemExceptionCode messenger_SystemException_code(
  struct MessengerSystemException* ex
)
{
  if (!ex)
    return MessengerSystemExceptionCode::EXCEPTION_NONE;
  return ex->code();
}
