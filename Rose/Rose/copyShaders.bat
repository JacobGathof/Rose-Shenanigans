@echo off
if not "%1"=="" goto :continue
echo destination directory required
goto :end
:continue
@echo on
copy *.txt "%1"

copy *.png "%1"

:end
