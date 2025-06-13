find_package(LLVM 18.1 REQUIRED CONFIG)

execute_process(
        COMMAND ${LLVM_TOOLS_BINARY_DIR}/llvm-config --system-libs --libnames core support passes all-targets
        OUTPUT_VARIABLE LLVM_LIBNAMES
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
separate_arguments(LLVM_LIBNAMES_LIST NATIVE_COMMAND ${LLVM_LIBNAMES})
separate_arguments(LLVM_DEFS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})

message(STATUS "LLVM version ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM config ${LLVM_DIR}")
message(STATUS "LLVM definitions ${LLVM_DEFS_LIST}")
message(STATUS "LLVM libraries ${LLVM_LIBNAMES_LIST}")
message(STATUS "LLVM lib dirs ${LLVM_LIBRARY_DIRS}")

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(block2bin ${SOURCES})
target_include_directories(block2bin PRIVATE include ${LLVM_INCLUDE_DIRS})
target_compile_definitions(block2bin PRIVATE ${LLVM_DEFS_LIST})
target_link_directories(block2bin PRIVATE ${LLVM_LIBRARY_DIRS})
target_link_libraries(block2bin PRIVATE ${LLVM_LIBNAMES_LIST})
