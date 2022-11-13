cmake_minimum_required(VERSION 3.24.3)

project(ProjetoLP1)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(terminal_ui)
add_subdirectory(models)
add_subdirectory(utils)
add_subdirectory(database_manager)

target_link_libraries(${PROJECT_NAME} terminal_ui)