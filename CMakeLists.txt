cmake_minimum_required(VERSION 3.16)
project(AshenVeins LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adaugă toate fișierele sursă și header din src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.c)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.hpp src/*.h)

add_executable(AshenVeins ${SOURCES} ${HEADERS})

# Caută raylib instalat în sistem (MSYS2)
find_package(raylib REQUIRED)

target_link_libraries(AshenVeins PRIVATE raylib)

# Include path pentru surse (dacă ai include-uri de forma #include "core/foo.hpp")
target_include_directories(AshenVeins PRIVATE src)

# Pentru Windows: copiază DLL-urile raylib la build
if(WIN32)
    add_custom_command(TARGET AshenVeins POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/msys64/mingw64/bin/libraylib.dll"
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