cmake_minimum_required(VERSION 3.16)

project(
  Messenger
  VERSION 1.0
  DESCRIPTION "UDP-based messaging"
  LANGUAGES C CXX
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  endif()
endif()

find_package(OpenSSL REQUIRED)

include(FetchContent)

add_subdirectory(src)
