add_library(utils string_utils.cpp)

target_link_libraries(${LIBRARY_NAME} utils)
message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/includes")
target_link_directories(utils PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")