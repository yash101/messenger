set(
  messenger_src
    base.c
    map.c
    client.c
    server.c
    connection.c
)

add_library(messenger_obj OBJECT ${messenger_src})
set_property(
  TARGET messenger_obj
  PROPERTY POSITION_INDEPENDENT_CODE 1
)
target_compile_features(messenger_obj PRIVATE c_std_11)

add_library(messenger SHARED $<TARGET_OBJECTS:messenger_obj>)
add_library(messenger_static STATIC $<TARGET_OBJECTS:messenger_obj>)

target_link_libraries(messenger OpenSSL::SSL)
target_link_libraries(messenger_static OpenSSL::SSL)
