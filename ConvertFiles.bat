@echo off
color 0a
@echo:
echo Found these FBX files:
@echo:
echo -----

cd 3DConverter\build\3DConverter\bin\x64\Release\
3DConverter "%~dp0"
@echo:
echo -----
@echo:
echo All Done!

TIMEOUT /T 5


