cmake_minimum_required(VERSION 3.16)
project(SpeedPainters C)

set(CMAKE_C_STANDARD 23)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(raylib)
endif ()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(SpeedPainters ${SRC_FILES})

target_include_directories(SpeedPainters PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(SpeedPainters PRIVATE raylib m)

set_target_properties(SpeedPainters PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


