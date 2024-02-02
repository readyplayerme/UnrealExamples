@ECHO OFF

echo Unreal Cleanup Script
echo Client directory: %~dp0
pushd "%~dp0"

@RD /S /Q "Intermediate"
@RD /S /Q "Binaries"
@RD /S /Q "DerivedDataCache"
:: Deletes saved source control settings @RD /S /Q "Saved"
del /S *.sln


:choice
set /P c=Clean plugins as well?[Y/N]? (default = no) 
if /I "%c%" EQU "Y" goto :plugins
if /I "%c%" EQU "N" goto :cleaned
if /I "%c%" EQU "" goto :cleaned

goto :choice

:plugins
for /d %%a in (
    "Plugins\*"
) do if exist "%%~fa\Intermediate\" rmdir /s /q "%%~fa\Intermediate" do if exist "%%~fa\Binaries\" rmdir /s /q "%%~fa\Binaries"

for /d %%a in (
    "Plugins\Developer\*"
) do if exist "%%~fa\Intermediate\" rmdir /s /q "%%~fa\Intermediate" do if exist "%%~fa\Binaries\" rmdir /s /q "%%~fa\Binaries"

:cleaned
echo Project cleaned

set /P c=Run Unreal Project?[Y/N]? (default = Yes)
if /I "%c%" EQU "Y" goto :run
if /I "%c%" EQU "N" goto :exit
if /I "%c%" EQU "N" goto :run

:run

for /r %%x in (*.uproject) do "%%x"

:exit
echo Exiting