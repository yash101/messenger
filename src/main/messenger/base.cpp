#include "messenger/base.h"

messenger::SystemException::SystemException() :
  err_code(MessengerSystemExceptionCode::EXCEPTION_NONE),
  message("")
{ }

messenger::SystemException::SystemException(
  MessengerSystemExceptionCode code
) :
  err_code(code),
  message("")
{ }

messenger::SystemException::SystemException(
  std::string message,
  MessengerSystemExceptionCode code
) :
  err_code(code),
  message(message)
{ }

const char* messenger::SystemException::what() const throw()
{
  return message.c_str();
}

const MessengerSystemExceptionCode messenger::SystemException::code() const throw()
{
  return err_code;
}

extern "C"
struct SystemException* messenger_SystemException_new(
  const char* message,
  const MessengerSystemExceptionCode code
)
{
  return reinterpret_cast<struct SystemException*>(new messenger::SystemException(std::string(message), code));
}

extern "C"
struct SystemException* messenger_SystemException_destroy(
  struct SystemException* ex
)
{
  if (ex)
    delete reinterpret_cast<messenger::SystemException*>(ex);
  return nullptr;
}

extern "C"
const char* messenger_SystemException_what(
  struct SystemException* ex
)
{
  auto exc = reinterpret_cast<messenger::SystemException*>(ex);
  if (!exc)
    return nullptr;
  return exc->what();
}

extern "C"
const MessengerSystemExceptionCode messenger_SystemException_code(
  struct SystemException* ex
)
{
  auto exc = reinterpret_cast<messenger::SystemException*>(ex);
  if (!exc)
    return MessengerSystemExceptionCode::EXCEPTION_NONE;
  return exc->code();
}
