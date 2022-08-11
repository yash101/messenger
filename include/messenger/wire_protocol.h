#ifndef _MESSENGER_WIRE_PROTOCOL
#define _MESSENGER_WIRE_PROTOCOL

#include "base.h"

#ifdef __cplusplus

  #include <list>
  #include <vector>

  class MessengerBasicWireStream
  {
  protected:
    std::list<MessengerMessage> pending_in;
    std::list<MessengerMessage> pending_out;

  public:
    MessengerBasicWireStream();
    virtual ~MessengerBasicWireStream();

    virtual void send(MessengerMessage message);
    virtual MessengerMessage receive();

    virtual void close();
  };

  class MessengerBasicWireProtocol
  {
  protected:
      std::list<MessengerBasicWireStream> active_streams;

  public:
    MessengerBasicWireProtocol();
    virtual ~MessengerBasicWireProtocol();

    virtual void dial();
    virtual void listen(std::string address);

    virtual void close();

    virtual void send(MessengerMessage message);
    virtual MessengerMessage receive();

    virtual MessengerBasicWireStream& newStream();
    virtual std::list<MessengerBasicWireStream> getActiveStreams();
  };

#endif

#endif
