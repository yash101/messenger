add_subdirectory(main)

if (PACKAGE_TESTS)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(test)
endif()

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
