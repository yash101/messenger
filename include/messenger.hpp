#ifndef _MESSENGER_MESSENGER_HPP
#define _MESSENGER_MESSENGER_HPP

#include "messenger.h"

#ifdef __cplusplus

namespace messenger
{
  class Client
  {
    messenger_client_t client;

  public:
    Client();
    ~Client();

    void bind(uint16_t port);

    void send_message();
    void on_message();
  };

  class Server
  {
    messenger_server_t server;
    
  public:
    Server();
    ~Server();

    void on_connect();
  };
}

#endif
#endif
