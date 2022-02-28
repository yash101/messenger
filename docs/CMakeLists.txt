# set(DOXYGEN_EXTRACT_ALL YES)
# set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

# doxygen_add_docs(
#   ../include
#   ../src
#   WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
# )

find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  )

  add_custom_target(
    docs_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API Documentation"
    VERBATIM
  )
endif()
