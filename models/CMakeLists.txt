add_library(models Diretor.cpp Funcionario.cpp Gerente.cpp Presidente.cpp)

target_link_libraries(${LIBRARY_NAME} models)
target_link_directories(models PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(models PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes/")

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes/")