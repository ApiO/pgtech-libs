@echo off

if exist imgui\src			rd /s /q imgui\src
if exist imgui\include		rd /s /q imgui\include

mklink /j imgui\src			..\src
mklink /j imgui\include	..\include

pause
