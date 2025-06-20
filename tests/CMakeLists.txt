cmake_minimum_required(VERSION 3.16)
project(ECS_Tests)

add_subdirectory(../external/Catch2 Catch2-build)

# Test EntityManager (dacă are implementare în cpp)
add_executable(test_entity_manager ecs/test_EntityManager.cpp ../engine/ecs/EntityManager.cpp)
target_include_directories(test_entity_manager PRIVATE ../engine/ecs)
target_link_libraries(test_entity_manager PRIVATE Catch2::Catch2WithMain)
add_test(NAME test_entity_manager COMMAND test_entity_manager)

# Test ComponentManager (fără .cpp pentru template)
add_executable(test_component_manager ecs/test_ComponentManager.cpp)
target_include_directories(test_component_manager PRIVATE ../include)
target_link_libraries(test_component_manager PRIVATE Catch2::Catch2WithMain)
add_test(NAME test_component_manager COMMAND test_component_manager)