
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.8
)

FetchContent_MakeAvailable(catch)

add_executable(testmessenger testmessenger.cpp)
target_compile_features(testmessenger PRIVATE cxx_std_11)
target_link_libraries(testmessenger PRIVATE Catch2::Catch2)
target_include_directories(testmessenger PUBLIC ../../include)
add_test(NAME testmessenger COMMAND testmessenger)
