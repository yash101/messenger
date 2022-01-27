add_library(
  messenger
  messenger_capi.c
  messenger_cppapi.cpp
)

target_compile_features(messenger PRIVATE cxx_std_11)
target_link_libraries(messenger OpenSSL::SSL)
target_include_directories(messenger PUBLIC ../../include)

add_library(
  messenger_capi
  messenger_capi.c
)

target_compile_features(messenger_capi PRIVATE c_std_11)
target_link_libraries(messenger_capi OpenSSL::SSL)
target_include_directories(messenger_capi PUBLIC ../../include)
