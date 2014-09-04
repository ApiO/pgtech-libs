@echo off

if exist Box2D\src\Box2D	rd /s /q Box2D\src\Box2D
if exist TestBed\src			rd /s /q TestBed\src

mklink /j Box2D\src\Box2D	..\..\Box2D
mklink /j TestBed\src\		..\..\TestBed

pause