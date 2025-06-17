@echo off
setlocal enabledelayedexpansion

echo === Joc cu Mingea - Build Script ===

:: Creează folderul build dacă nu există
if not exist build (
    mkdir build
)

:: Colectează toate fișierele .cpp
set SOURCES=
for %%f in (*.cpp) do (
    set SOURCES=!SOURCES! %%f
)

echo === Compiling sources: !SOURCES! ===

:: Compilează și generează executabilul în build\
g++ !SOURCES! -o build\joc.exe -lraylib -lopengl32 -lgdi32 -lwinmm

if %errorlevel% neq 0 (
    echo === ❌ Build failed ===
    pause
    exit /b
)

echo === ✅ Build succeeded ===
echo === Launching joc.exe ===
cd build
joc.exe
