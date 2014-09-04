@echo off

if exist src		rd /s /q src

mklink /j src 	..\..\src

pause
