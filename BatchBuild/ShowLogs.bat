@echo off
set SEPERATOR=--------------------------------------------------------------------------------
for %%f in (*.log) do echo BUILD: %%f & echo %%f & echo %SEPERATOR% & type %%f