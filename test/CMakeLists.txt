include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
if (MSVC)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

add_executable(emulator_test 
  binary_runner.cpp
  instruction.cpp
  logical_address.cpp
  memory.cpp
  register.cpp
  status.cpp
)

target_link_libraries(
  emulator_test
  basiccomponent
  GTest::gtest_main
)

target_include_directories(emulator_test PUBLIC ${SOURCE_DIR} ${TEST_DIR})

include(GoogleTest)
gtest_discover_tests(emulator_test)
