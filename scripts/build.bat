@echo off
setlocal enabledelayedexpansion

echo === [🔧 BUILDING JOC.EXE] ===

:: 1. Creează folder build dacă nu există
if not exist build (
    mkdir build
)

:: 2. Detectează toate fișierele .cpp
set SOURCES=
for %%f in (*.cpp) do (
    set SOURCES=!SOURCES! %%f
)

:: 3. Compilează
g++ !SOURCES! -o build\joc.exe -lraylib -lopengl32 -lgdi32 -lwinmm

if %errorlevel% neq 0 (
    echo ❌ Build failed
    pause
    exit /b
)

echo ✅ Build succeeded

:: 4. Copiază DLL-urile esențiale din MSYS2 (ajustează dacă ai raylib altundeva!)
set DLL_PATH=C:\msys64\mingw64\bin
copy /Y "%DLL_PATH%\libraylib.dll" build\
copy /Y "%DLL_PATH%\libwinpthread-1.dll" build\
copy /Y "%DLL_PATH%\libstdc++-6.dll" build\
copy /Y "%DLL_PATH%\libgcc_s_seh-1.dll" build\
copy /Y "%DLL_PATH%\glfw3.dll" build\


:: 5. Copiază fișiere de resurse (dacă există)
xcopy /Y /S textures\ build\textures\
xcopy /Y /S levels\ build\levels\

:: 6. Rulează jocul
cd build
joc.exe
