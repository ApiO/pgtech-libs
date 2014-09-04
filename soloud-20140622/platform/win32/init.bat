@echo off

if exist include	rd /s /q include
if exist src		rd /s /q src

mklink /j include	..\..\include
mklink /j src			..\..\src

pause