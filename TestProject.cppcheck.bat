@echo off
set PATH=%PATH%;C:\mingw\msys\1.0\bin

rem echo #include ^<WPILib.h^> > ..\src\TestProject.h
rem C:\mingw\msys\1.0\bin\find "../src/" -name "*.h" | sed -n "s|^\.\./src/|#include ""|p" | sed -n "s|$|""|p" >> ..\src\TestProject.h

"C:\Program Files\Cppcheck\cppcheck.exe"^
 --enable=warning,style,performance,portability,unusedFunction^
 -I C:\Users\Asdf\Documents\LigerBots\workspace\TestProject\src^
 --inconclusive -rp=C:\Users\Asdf\Documents\LigerBots\workspace\TestProject -q -v^
 --inline-suppr^
 --template={file}:{line},{severity},{id},{message}^
 C:\Users\Asdf\Documents\LigerBots\workspace\TestProject\src