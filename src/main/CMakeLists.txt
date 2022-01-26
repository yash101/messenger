add_library(
  messenger
  messenger.cpp
)

target_compile_features(messenger PRIVATE cxx_std_11)
target_link_libraries(messenger OpenSSL::SSL)
target_include_directories(messenger PUBLIC ../../include)
