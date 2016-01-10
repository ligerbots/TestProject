@echo off
"C:\Program Files\Cppcheck\cppcheck.exe"^
 --enable=warning,style,performance,portability,unusedFunction^
 -I C:\Users\Asdf\Documents\LigerBots\workspace\TestProject\src^
 --inconclusive -rp=C:\Users\Asdf\Documents\LigerBots\workspace\TestProject -q -v^
 --inline-suppr^
 --template={file}:{line},{severity},{id},{message}^
 C:\Users\Asdf\Documents\LigerBots\workspace\TestProject\src