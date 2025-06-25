cmake_minimum_required(VERSION 3.16)
project(AshenVeins LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adaugă sursele din engine și game
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS engine/*.cpp engine/**/*.cpp)
# Adaugă explicit fișierul de serializare:
list(APPEND ENGINE_SOURCES ${CMAKE_SOURCE_DIR}/include/ecs/ECSWorld_serialization.cpp)
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS include/*.hpp include/**/*.hpp)
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS game/**/*.cpp)

# Creează librăria statică engine
add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/json/include
    ${CMAKE_SOURCE_DIR}/game/components
)

# Creează executabilul principal doar cu sursele jocului
add_executable(AshenVeins ${GAME_SOURCES} game/main.cpp)
set_target_properties(AshenVeins PROPERTIES WIN32_EXECUTABLE FALSE)
target_link_libraries(AshenVeins PRIVATE engine raylib)
target_include_directories(AshenVeins PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/engine
    ${CMAKE_SOURCE_DIR}/game
)

# Pentru Windows: copiază DLL-urile raylib la build
if(WIN32)
    add_custom_command(TARGET AshenVeins POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/msys64/mingw64/bin/libraylib.dll"
            "C:/msys64/mingw64/bin/glfw3.dll"
            "C:/msys64/mingw64/bin/libgcc_s_seh-1.dll"
            "C:/msys64/mingw64/bin/libstdc++-6.dll"
            "C:/msys64/mingw64/bin/libwinpthread-1.dll"
            $<TARGET_FILE_DIR:AshenVeins>)
endif()

# Copiază folderul assets în build/assets după build
add_custom_command(TARGET AshenVeins POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:AshenVeins>/assets"
)

# Setează folderul de output pentru executabil în build/
set_target_properties(AshenVeins PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

if (MSVC)
    set_target_properties(AshenVeins PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
else()
    set_target_properties(AshenVeins PROPERTIES LINK_FLAGS "-mconsole")
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
    enable_testing() # Activează testele dacă există CMakeLists.txt în tests
    add_subdirectory(tests)
endif()