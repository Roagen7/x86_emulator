add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})

add_subdirectory(${SOURCE_DIR}/basicComponents)
target_link_libraries(${PROJECT_NAME} PRIVATE basiccomponent)
