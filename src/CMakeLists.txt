add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})

add_library(basic_emu STATIC)
target_include_directories(basic_emu PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/basicComponents ${SOURCE_DIR}/instructions)
add_subdirectory(${SOURCE_DIR}/basicComponents)
add_subdirectory(${SOURCE_DIR}/instructions)
add_subdirectory(${SOURCE_DIR}/utility)
target_link_libraries(${PROJECT_NAME} PRIVATE basic_emu)
