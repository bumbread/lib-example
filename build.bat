@echo off
cl /FC /Z7 /nologo src\dll.c /LD /link /dll user32.lib /out:math.dll
cl /FC /Z7 /nologo src\main.c /link user32.lib