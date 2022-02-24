add_executable(
  trial_and_error
  main.c
)

target_compile_features(trial_and_error PRIVATE c_std_11)

find_package(Threads)
target_link_libraries(trial_and_error ${CMAKE_THREAD_LIBS_INIT})