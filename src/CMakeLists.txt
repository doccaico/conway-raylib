cmake_minimum_required(VERSION 3.10)

# set the project name
project(conway)
# add_subdirectory(./src)
add_definitions("-Wall")
add_executable(${CMAKE_PROJECT_NAME} main.c)
# add_executable(test .c)
# target_link_libraries(Main Mod1 Mod2)
target_link_libraries(conway -lraylib)

add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME}
    DEPENDS ${CMAKE_PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
