add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})

add_library(basiccomponent STATIC)
add_subdirectory(${SOURCE_DIR}/basicComponents)
add_subdirectory(${SOURCE_DIR}/instructions)
target_link_libraries(${PROJECT_NAME} PRIVATE basiccomponent)
