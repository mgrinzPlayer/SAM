@echo off
set path=C:\mingw-w64\mingw32\bin
mingw32-make -B sam32
mingw32-make clean



set path=C:\mingw-w64\mingw64\bin
mingw32-make -B sam64
mingw32-make clean


pause
