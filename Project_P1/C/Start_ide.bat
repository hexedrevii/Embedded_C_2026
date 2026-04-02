@echo off
setlocal

set "SCRIPT_DIR=%~dp0"

set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

start "" code "%SCRIPT_DIR%"

endlocal
exit