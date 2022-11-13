add_library(terminal_ui terminalUi.cpp)

target_link_libraries(${LIBRARY_NAME} terminal_ui models database_manager utils)
target_link_directories(terminal_ui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(terminal_ui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")