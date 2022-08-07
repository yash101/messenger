#ifndef _MESSENGER_WIRE_PROTOCOL
#define _MESSENGER_WIRE_PROTOCOL

#ifdef __cplusplus

  class MessengerBasicWireStream
  {
  public:
    MessengerBasicWireStream();
    virtual ~MessengerBasicWireStream();
  };

  class MessengerBasicWireProtocol
  {
  public:
    MessengerBasicWireProtocol();
    virtual ~MessengerBasicWireProtocol();

    virtual void dial();
    virtual void close();
    virtual void listen();

    virtual void newStream();
    virtual void getActiveStreams();
  };

#endif

#endif
