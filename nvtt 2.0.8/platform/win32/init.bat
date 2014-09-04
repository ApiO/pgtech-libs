@echo off

if exist third_party\nvcore		rd /s /q third_party\nvcore
if exist nvcore\nvcore			rd /s /q nvcore\nvcore
mklink /j third_party\nvcore	..\..\nvcore
mklink /j nvcore\nvcore			..\..\nvcore

if exist third_party\nvimage	rd /s /q third_party\nvimage
if exist nvimage\nvimage		rd /s /q nvimage\nvimage
mklink /j third_party\nvimage		..\..\nvimage
mklink /j nvimage\nvimage		..\..\nvimage

if exist third_party\nvmath	rd /s /q third_party\nvmath
if exist nvmath\nvmath			rd /s /q nvmath\nvmath
mklink /j third_party\nvmath	..\..\nvmath
mklink /j nvmath\nvmath		..\..\nvmath

if exist third_party\poshlib		rd /s /q third_party\poshlib
if exist poshlib\poshlib			rd /s /q poshlib\poshlib
mklink /j third_party\poshlib	..\..\poshlib
mklink /j poshlib\poshlib			..\..\poshlib

if exist third_party\squish		rd /s /q third_party\squish
if exist squish\squish			rd /s /q squish\squish
mklink /j third_party\squish	..\..\squish
mklink /j squish\squish			..\..\squish

if exist third_party\nvtt		rd /s /q third_party\nvtt
if exist nvtt\nvtt				rd /s /q nvtt\nvtt
mklink /j third_party\nvtt	..\..\nvtt
mklink /j nvtt\nvtt				..\..\nvtt

if exist third_party\config		rd /s /q third_party\config
mklink /j third_party\config		..\..\config

pause