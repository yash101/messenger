set(
  messenger_src
    base.cpp
    client.cpp
    server.cpp
    session.cpp
)

add_library(messenger_obj OBJECT ${messenger_src})
set_property(
  TARGET messenger_obj
  PROPERTY POSITION_INDEPENDENT_CODE 1
)
target_compile_features(messenger_obj PRIVATE c_std_11)
target_compile_definitions(messenger_obj PRIVATE cxx_std_11)

add_library(messenger SHARED $<TARGET_OBJECTS:messenger_obj>)
add_library(messenger_static STATIC $<TARGET_OBJECTS:messenger_obj>)

target_link_libraries(messenger OpenSSL::SSL)
target_link_libraries(messenger_static OpenSSL::SSL)

#set_target_properties(
#  messenger
#  PROPERTIES
#    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/../../../include/messenger"
#)

#set_target_properties(
#  messenger_static
#  PROPERTIES
#    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/../../../include/messenger"
#)

add_library(Messenger::Messenger ALIAS messenger)
add_library(Messenger::Messenger_static ALIAS messenger_static)
