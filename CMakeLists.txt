cmake_minimum_required(VERSION "2.8")

project("t2")

# set(CMAKE_VERBOSE_MAKEFILE ON)

# add_definitions(-DDEBUG)
# set(CMAKE_C_FLAGS -ggdb)
# set(CMAKE_CXX_FLAGS -ggdb)

# library world
include_directories(${PROJECT_SOURCE_DIR}/lib/world)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/world)

# library hello
include_directories(${PROJECT_SOURCE_DIR}/lib/hello)
set(hello_SRC "lib/hello/hello.cpp")
## .so
add_library(hello SHARED ${hello_SRC})
set_target_properties(
    hello PROPERTIES
        LIBRARY_OUTPUT_NAME hello
        # CLEAN_DIRECT_OUTPUT 1
        VERSION 0.1 SOVERSION 0
)
## .a
add_library(hello_static STATIC ${hello_SRC})
set_target_properties(
    hello_static PROPERTIES
        ARCIHVE_OUTPUT_NAME hello
        # CLEAN_DIRECT_OUTPUT 1
)

# executable
set(main_SRC "src/main.cpp")
add_executable(main ${main_SRC})
add_executable(main_with_static ${main_SRC})

# link
target_link_libraries(main hello world)
target_link_libraries(main_with_static hello_static world_static)

# install
## targets
install(
    TARGETS main main_with_static hello hello_static

    ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/release/lib
    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/release/lib
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/release/bin
)
## include
install(
    FILES lib/hello/hello.h lib/world/world.h
    DESTINATION ${PROJECT_SOURCE_DIR}/release/include
)