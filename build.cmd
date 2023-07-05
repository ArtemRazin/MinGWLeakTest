SET SAVED_PATH=%PATH%

SETLOCAL
SET PATH=%SAVED_PATH%;%MINGW64_ROOT%\bin
MKDIR x64
g++.exe -g -std=c++17 main.cpp -o x64\main.exe
copy /Y "%MINGW64_ROOT%\bin\libgcc_s_dw2-1.dll" x64\.
copy /Y "%MINGW64_ROOT%\bin\libgcc_s_seh-1.dll" x64\.
copy /Y "%MINGW64_ROOT%\bin\libstdc++-6.dll" x64\.
copy /Y "%MINGW64_ROOT%\bin\libwinpthread-1.dll" x64\.
ENDLOCAL
