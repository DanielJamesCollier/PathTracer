@echo off

echo:
echo:
echo ------------------------
echo ------Build Started-----
echo ------------------------
echo:
echo cl /O2 /Ot  ../../src/main.cpp /I ../../src/main.cpp /I deps/SDL2/include /link /LIBPATH:deps/SDL2/libs SDL2.lib SDL2main.lib /SUBSYSTEM:CONSOLE
cl /O2 /Ot  ../../src/main.cpp /I ../../src/main.cpp /I deps/SDL2/include /link /LIBPATH:deps/SDL2/libs SDL2.lib SDL2main.lib /SUBSYSTEM:CONSOLE
echo ------------------------
echo:
echo: