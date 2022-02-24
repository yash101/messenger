
# FetchContent_Declare(
#   catch
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG v2.13.8
# )

# FetchContent_MakeAvailable(catch)

# add_executable(testmessenger testmessenger.cpp)
# target_compile_features(testmessenger PRIVATE cxx_std_11)
# target_link_libraries(testmessenger PRIVATE Catch2::Catch2)
# add_test(NAME testmessenger COMMAND testmessenger)

# add_executable(messenger_test_core core.test.cpp)
# target_compile_features(messenger_test_core PRIVATE cxx_std_11)
# target_link_libraries(messenger_test_core PRIVATE Catch2::Catch2WithMain)
# add_test(NAME messenger_test_core COMMAND messenger_test_core)

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/googletest" "vender/googletest")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER vendor)
set_target_properties(gtest_main PROPERTIES FOLDER vendor)
set_target_properties(gmock PROPERTIES FOLDER vendor)
set_target_properties(gmock_main PROPERTIES FOLDER vendor)

macro(package_add_test TESTNAME)
  add_executable(${TESTNAME} ${ARGN})
  target_link_libraries(${TESTNAME} gtest gmock gtest_main)
  gtest_discover_tests(
    ${TESTNAME}
    WORKING_DIRECTORY ${PROJECT_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
  )
  set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(messenger_test_core core.test.cpp)
target_link_libraries(messenger_test_core messenger)

