#ifndef _MESSENGER_MESSAGE_H
#define _MESSENGER_MESSAGE_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus

#include <vector>
#include <string>
#include <list>

// Possibly not using this functionality
  class MessengerMessage
  {
  private:
    std::list<std::vector<char>> incoming;
    std::list<std::vector<char>> outgoing;

    size_t buffered_in;
    size_t buffered_out;

  public:
    MessengerMessage();
    virtual ~MessengerMessage();

    std::vector<char> read();
    std::vector<char> read(size_t num);
    std::vector<char> readSingleBuffer();
    size_t read(char* buffer, size_t maxlen);

    std::vector<char> peek();
    std::vector<char> peek(size_t num);
    std::vector<char> peekSingleBuffer();
    size_t peek(char* buffer, size_t maxlen);

    std::vector<char> readUntil(std::vector<char> ending);
    size_t readUntil(char* buffer, size_t maxlen, const char* ending, size_t ending_length);

    size_t write(std::vector<char> str);
    size_t write(const char* data, size_t len);

    size_t getIncomingBufferedBytes();
    size_t getOutgoingBufferedBytes();
    size_t getBufferCount();
  };

#endif

// typedef struct messenger_message_t
// {
//   size_t bufferred;
//   size_t* buffer_lengths;
//   char** buffer;

//   struct messenger_session_t* session;
//   struct messenger_client_t* client;
// } messenger_message_t;

// void messenger_message_init(struct messenger_message_t* message);
// void messenger_message_destroy(struct messenger_message_t* message);

// void messenger_message_property_set(struct messenger_message_t* message, uint16_t property, uint16_t value);
// uint16_t messenger_message_property_get(struct messenger_message_t* message, uint16_t property);
// void messenger_message_attach_client(struct messenger_message_t* message, struct messenger_client_t* client);
// void messenger_message_attach_session(struct messenger_message_t* message, struct messenger_session_t* session);

// void messenger_message_write(struct messenger_message_t* message, void* data, size_t len);
// size_t messenger_message_read(struct messenger_message_t* message, char* buffer);
// size_t messenger_message_size(struct messenger_message_t* message);
// size_t messenger_message_transmitted(struct messenger_message_t* message);
// size_t messenger_message_received(struct messenger_message_t* message);

// size_t messenger_message_close(struct messenger_message_t* message);

#endif
