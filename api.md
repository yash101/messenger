# Messenger API

## C API

- The C API is the main API. All other APIs are built atop this API.

- Server
- Client
- Session
- Message

- The server will listen for connections "sessions" and generate a Session object with that.
- The client will communicate with a session in the server.

- Server
  - `messenger_server_init()`
  - `messenger_server_bind()`
  - `messenger_server_accept_session()`
  - `messenger_server_accept_session_async(callback)`
  - `messenger_server_close()`
  - `messenger_server_destroy()`

- Session
  - `messenger_session_init()`
  - `messenger_session_close()`
  - `messenger_session_destroy()`
  - `messenger_session_get_client_info()`
  - `messenger_session_next()`
  - `messenger_session_send(message)`

- Message
  - `messenger_message_init()`
  - `messenger_message_destroy()`
  - `messenger_message_write(message, size)`
  - `messenger_message_property_set(PROPERTY, endis)`
  - `messenger_message_property_get(PROPERTY)`
  - `messenger_message_read()`
  - `messenger_message_size()`
  - `messenger_message_transmitted()`
  - `messenger_message_received()`
  - `messenger_message_close()`

- Client
  - `messenger_client_init()`
  - `messenger_client_destroy()`
  - `messenger_client_