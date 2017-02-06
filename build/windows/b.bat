@echo off
echo ------------------------
echo ------Build Started-----
echo ------------------------
echo:
echo cl /EHsc /MD  ../../src/main.cpp /I deps/SDL2/include /link /LIBPATH:deps/SDL2/libs SDL2.lib SDL2main.lib /SUBSYSTEM:CONSOLE
cl /EHsc /MD  ../../src/main.cpp /I deps/SDL2/include /link /LIBPATH:deps/SDL2/libs SDL2.lib SDL2main.lib /SUBSYSTEM:CONSOLE
echo ------------------------
echo:
echo:
