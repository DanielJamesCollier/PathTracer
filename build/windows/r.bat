@echo off
setlocal EnableDelayedExpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (
  set "DEL=%%a"
)

rem Prepare a file "X" with only one dot
<nul > X set /p ".=."

echo:
echo:
call :color 1b "------------------------"
echo:
call :color 1b "-------RUN STARTED------"
echo:
call :color 1b "------------------------"
echo:
main.exe
start render.ppm
echo:
echo:
call :color 1b "------------------------"
echo:
echo:
exit /b

:color
set "param=^%~2" !
set "param=!param:"=\"!"
findstr /p /A:%1 "." "!param!\..\X" nul
<nul set /p ".=%DEL%%DEL%%DEL%%DEL%%DEL%%DEL%%DEL%"
exit /b