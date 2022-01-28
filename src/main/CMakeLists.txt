add_library(
  messenger
  messenger_capi.c
)

target_compile_features(messenger PRIVATE c_std_11)
target_link_libraries(messenger OpenSSL::SSL)
target_include_directories(messenger PUBLIC ../../include)

add_library(
  messengerpp
  messenger_cppapi.cpp
)

target_compile_features(messengerpp PRIVATE cxx_std_11)
target_link_libraries(messengerpp messenger)
target_include_directories(messengerpp PUBLIC ../../include)
