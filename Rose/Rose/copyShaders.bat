:@echo off
if not "%1"=="" goto :continue
echo destination directory required
goto :end
:continue
:@echo on
echo D|xcopy "%~dp0Resources" "%1" /s /e /y

:end
