file (GLOB_RECURSE SOURCES src/*.cpp)
add_library(engine ${SOURCES})
target_include_directories(engine PRIVATE include)
