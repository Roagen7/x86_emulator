target_sources(basiccomponent PUBLIC
                ${SOURCE_DIR}/basicComponents/Cpu.cpp
                ${SOURCE_DIR}/basicComponents/InstructionDecoder.cpp)
target_include_directories(basiccomponent PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/basicComponents)
