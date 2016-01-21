@echo off
set PATH=%PATH%;C:\mingw\msys\1.0\bin

echo Rebuilding index header
more ..\src\Includes.h > ..\src\TestProject.h
C:\mingw\msys\1.0\bin\find "../src/" -name "*.h" | sed -n "/TestProject\.h/!p" | sed -n "s|^\.\./src/|#include ""|p" | sed -n "s|$|""|p" >> ..\src\TestProject.h
arm-frc-linux-gnueabi-g++ -std=c++1y "-IC:\\Users\\Asdf\\Documents\\LigerBots\\workspace\\TestProject\\src" "-IC:\\Users\\Asdf\\navx-mxp\\cpp\\include" "-IC:\\Users\\Asdf/wpilib/cpp/current/include/" -O0 -g3 -Wall -c -fmessage-length=0 -H -x c++-header -o "..\\src\\TestProject.h.gch" "..\\src\\TestProject.h" 

"C:\Program Files\Cppcheck\cppcheck.exe"^
 --enable=warning,style,performance,portability,unusedFunction^
 -I C:\Users\Asdf\Documents\LigerBots\workspace\TestProject\src^
 --inconclusive -rp=C:\Users\Asdf\Documents\LigerBots\workspace\TestProject -q -v^
 --inline-suppr^
 --template={file}:{line},{severity},{id},{message}^
 C:\Users\Asdf\Documents\LigerBots\workspace\TestProject\src