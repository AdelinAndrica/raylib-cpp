cmake_minimum_required(VERSION 3.16)
project(ECS_Tests)

add_subdirectory(../external/Catch2 Catch2-build)

# Test EntityManager (dacă are implementare în cpp)
add_executable(test_entity_manager ecs/test_EntityManager.cpp)
target_include_directories(test_entity_manager PRIVATE ../engine/ecs ../include)
target_link_libraries(test_entity_manager PRIVATE engine Catch2::Catch2WithMain)
add_test(NAME test_entity_manager COMMAND test_entity_manager)

# Test ComponentManager (fără .cpp pentru template)
add_executable(test_component_manager ecs/test_ComponentManager.cpp)
target_include_directories(test_component_manager PRIVATE ../include)
target_link_libraries(test_component_manager PRIVATE engine Catch2::Catch2WithMain)
add_test(NAME test_component_manager COMMAND test_component_manager)

# Test IScene (fara .cpp pentru interfață)
add_executable(test_i_scene scene/test_IScene.cpp)
target_include_directories(test_i_scene PRIVATE ../include)
target_link_libraries(test_i_scene PRIVATE engine Catch2::Catch2WithMain)
add_test(NAME test_i_scene COMMAND test_i_scene)

# Test SceneManager (dacă are implementare în cpp)
add_executable(test_scene_manager scene/test_SceneManager.cpp ../engine/scene/SceneManager.cpp)
target_include_directories(test_scene_manager PRIVATE ../engine/scene ../include)
target_link_libraries(test_scene_manager PRIVATE engine Catch2::Catch2WithMain)
add_test(NAME test_scene_manager COMMAND test_scene_manager)

# Test ECSWorld Serialization
add_executable(test_ecsworld_serialization ecs/test_ECSWorld_Serialization.cpp)
target_include_directories(test_ecsworld_serialization PRIVATE
    ../include
    ../engine/ecs
    ../game/components
)
target_link_libraries(test_ecsworld_serialization PRIVATE engine Catch2::Catch2WithMain)
add_test(NAME test_ecsworld_serialization COMMAND test_ecsworld_serialization)

# Test ResourceManager
add_executable(test_resourcemanager test_ResourceManager.cpp)
target_include_directories(test_resourcemanager PRIVATE ../include ../engine)
target_link_libraries(test_resourcemanager PRIVATE engine raylib Catch2::Catch2WithMain)
add_test(NAME test_resourcemanager COMMAND test_resourcemanager)

# Test ConfigManager
add_executable(test_configmanager test_ConfigManager.cpp)
target_include_directories(test_configmanager PRIVATE ../include ../engine)
target_link_libraries(test_configmanager PRIVATE engine Catch2::Catch2WithMain)
add_test(NAME test_configmanager COMMAND test_configmanager)

# Test AudioManager
add_executable(test_audiomanager test_AudioManager.cpp)
target_include_directories(test_audiomanager PRIVATE ../include ../engine)
target_link_libraries(test_audiomanager PRIVATE engine raylib Catch2::Catch2WithMain)
add_test(NAME test_audiomanager COMMAND test_audiomanager)

# Test EventBus
add_executable(test_eventbus ecs/test_EventBus.cpp)
target_include_directories(test_eventbus PRIVATE ../include ../engine/ecs)
target_link_libraries(test_eventbus PRIVATE engine Catch2::Catch2WithMain)
add_test(NAME test_eventbus COMMAND test_eventbus)

# Test Profiler
add_executable(test_profiler test_Profiler.cpp)
target_include_directories(test_profiler PRIVATE ../include)
target_link_libraries(test_profiler PRIVATE engine Catch2::Catch2WithMain)
add_test(NAME test_profiler COMMAND test_profiler)

# Test AssetWatcher
add_executable(test_assetwatcher test_AssetWatcher.cpp)
target_include_directories(test_assetwatcher PRIVATE ../include ../engine)
target_link_libraries(test_assetwatcher PRIVATE engine raylib Catch2::Catch2WithMain)
add_test(NAME test_assetwatcher COMMAND test_assetwatcher)

# Test ResourceManager_Reload
add_executable(test_resourcemanager_reload test_ResourceManager_Reload.cpp)
target_include_directories(test_resourcemanager_reload PRIVATE ../include ../engine)
target_link_libraries(test_resourcemanager_reload PRIVATE engine raylib Catch2::Catch2WithMain)
add_test(NAME test_resourcemanager_reload COMMAND test_resourcemanager_reload)

# Test AssetPipeline__Fallback
add_executable(test_assetpipeline_fallback test_AssetPipeline_Fallback.cpp)
target_include_directories(test_assetpipeline_fallback PRIVATE ../include ../engine)
target_link_libraries(test_assetpipeline_fallback PRIVATE engine raylib Catch2::Catch2WithMain)
add_test(NAME test_assetpipeline_fallback COMMAND test_assetpipeline_fallback)
