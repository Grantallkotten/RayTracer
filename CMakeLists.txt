cmake_minimum_required(VERSION 3.13.0...3.20)
project(TNCG15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable profiling with gprof
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

function(enable_warnings target)
    target_compile_options(${target} PUBLIC
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
        $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
    )
endfunction()

# Create a list of source files dynamically
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Create a list of header files dynamically
file(GLOB_RECURSE HEADER_FILES "include/*.h")

add_executable(Raytracing ${SOURCE_FILES} ${HEADER_FILES})

enable_warnings(Raytracing)
