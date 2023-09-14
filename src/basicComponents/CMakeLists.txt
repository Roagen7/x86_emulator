add_library(basiccomponent STATIC)
target_sources(basiccomponent PRIVATE
                Cpu.cpp)
target_include_directories(basiccomponent PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/basicComponents)
