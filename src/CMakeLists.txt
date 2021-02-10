cmake_minimum_required(VERSION 3.10)

project(conway)

add_definitions("-Wall")
add_executable(${CMAKE_PROJECT_NAME} main.c)
target_link_libraries(conway -lraylib)

add_custom_target(run
    COMMAND conway
    DEPENDS conway
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
