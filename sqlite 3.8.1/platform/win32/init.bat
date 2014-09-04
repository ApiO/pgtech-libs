@echo off

if exist sqlite\src			rd /s /q sqlite\src
if exist sqlite\include		rd /s /q sqlite\include

mklink /j sqlite\src			..\..\sqlite\src
mklink /j sqlite\include	..\..\sqlite\include

pause