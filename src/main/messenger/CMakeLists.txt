add_library(
  messenger
  base.c
  map.c
  client.c
  server.c
  connection.c
)

target_compile_features(messenger PRIVATE c_std_11)
target_link_libraries(messenger OpenSSL::SSL)
