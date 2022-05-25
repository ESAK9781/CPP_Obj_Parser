@echo off


@REM build files
g++ -c src/main.cpp -o bin/main.o > ./bin/log.txt
g++ -c src/objloader.cpp -o bin/objloader.o > ./bin/log.txt

@REM link .o files
g++ bin/main.o bin/objloader.o -o bin/loader.exe > ./bin/log.txt

@REM run executable
cd bin
loader
cd ..

echo on