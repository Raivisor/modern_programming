@echo off
chcp 1251 > log
del log

set CPP_FILES="generator.cpp show_array.cpp shellSorting.cpp main1.cpp"
set EXE=bin/shellSorting.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" "%CPP_FILES%" -o %EXE%

%EXE%
