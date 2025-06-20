cmake_minimum_required(VERSION 3.16)
project(ECS_Tests)

add_subdirectory(../external/Catch2 Catch2-build)

add_executable(test_entity_manager ecs/test_EntityManager.cpp ../engine/ecs/EntityManager.cpp)
target_include_directories(test_entity_manager PRIVATE ../engine/ecs)
target_link_libraries(test_entity_manager PRIVATE Catch2::Catch2WithMain)
enable_testing()
add_test(NAME test_entity_manager COMMAND test_entity_manager)