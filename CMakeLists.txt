cmake_minimum_required(VERSION 3.16)

# Project Definition
project(
  Messenger
  VERSION 1.0
  DESCRIPTION "UDP-based messaging"
  LANGUAGES C CXX
)

# Output directories for outputs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build tests
option(BUILD_TESTS "Build tests" OFF)
# Build documentation
option(BUILD_DOC "Build documentation" OFF)

# Include directory for messenger
include_directories(include)

# Build documentation if enabled and Doxygen was found
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_DOC)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  endif()
endif()

# OpenSSL
find_package(OpenSSL REQUIRED)
# FetchContent
include(FetchContent)

add_subdirectory(src)
add_subdirectory(include)

install(
  TARGETS messenger messenger_static
  EXPORT MessengerTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
  PUBLIC_HEADER DESTINATION include
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  MessengerConfigVersion.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  EXPORT MessengerTargets
  FILE MessengerTargets.cmake
  NAMESPACE Messenger::
  DESTINATION lib/cmake/Messenger
)

configure_file(cmake/MessengerConfig.cmake.in MessengerConfig.cmake @ONLY)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MessengerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MessengerConfigVersion.cmake"
  DESTINATION lib/cmake/Messenger
)

export(
  TARGETS
    messenger
    messenger_static
  NAMESPACE Messenger::
  FILE MessengerTargets.cmake
)

set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)

set(CPACK_PACKAGE_VENDOR "Devyash Lodha")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "High performance, client-server I/O")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES
  /.git
  /vendor
  /.*build.*
  /\\\\.DS_Store
)
