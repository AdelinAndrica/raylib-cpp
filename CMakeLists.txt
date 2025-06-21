cmake_minimum_required(VERSION 3.16)
project(AshenVeins LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adaugă sursele din engine (adaptează după structura ta)
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS engine/**/*.cpp)
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS include/**/*.hpp)
# Adaugă sursele din game (adaptează după structura ta)
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS game/**/*.cpp)
file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS game/**/*.hpp)

add_executable(AshenVeins ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GAME_SOURCES} ${GAME_HEADERS} game/main.cpp)

# Caută raylib instalat în sistem (MSYS2)
find_package(raylib REQUIRED)

target_link_libraries(AshenVeins PRIVATE raylib)

# Include path pentru surse (dacă ai include-uri de forma #include "core/foo.hpp")
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


# add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# target_include_directories(engine PUBLIC ${CMAKE_SOURCE_DIR}/include)

# if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
#     add_subdirectory(tests)
# endif()