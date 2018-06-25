#set(CMAKE_C_FLAGS)

add_executable(core_test test.cpp)
INCLUDE_DIRECTORIES(../src)
LINK_LIBRARIES("../src/libslicer_core.so")
target_link_libraries(core_test slicer_core)
