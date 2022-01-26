add_library(
  messenger
  messenger.cpp
)

target_compile_features(messenger PRIVATE cxx_std_11)
target_link_libraries(messenger OpenSSL::SSL)
target_include_directories(messenger PUBLIC ../../include)

add_executable(testOpenssl test.cpp)
target_link_libraries(testOpenssl PRIVATE messenger)
target_include_directories(testOpenssl PUBLIC ../../include)
