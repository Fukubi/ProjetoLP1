add_library(database_manager database_manager.cpp)

target_link_libraries(${LIBRARY_NAME} database_manager utils models)
target_link_directories(database_manager PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(database_manager PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")