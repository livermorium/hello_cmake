# set(CMAKE_C_FLAGS -ggdb)
# set(CMAKE_CXX_FLAGS -ggdb)

set(world_SRC world.cpp)

add_library(world SHARED ${world_SRC})
set_target_properties(world 
    PROPERTIES
        LIBRARY_OUTPUT_NAME world
        VERSION 0.1 SOVERSION 0
)

add_library(world_static STATIC ${world_SRC})
set_target_properties(world_static
    PROPERTIES
        ARCHIVE_OUTPUT_NAME world
)

install(TARGETS world world_static
    ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/release/lib
    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/release/lib
)

install(
    FILES world.h
    DESTINATION ${PROJECT_SOURCE_DIR}/release/include
)