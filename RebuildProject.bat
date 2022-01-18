@echo off

echo Administrative permissions required. Detecting permissions...
net session >nul 2>&1
if %errorLevel% == 0 (
	echo Success: Administrative permissions confirmed.
) else (
	echo Failure: Current permissions inadequate.
	pause
	exit
)

rem change the current directory to the bat location
pushd %~dp0

echo downloading submodule
git submodule init DRGLibDevkitFiles
git submodule update

echo making symbolic link
rmdir "%cd%\Content\DRGLib"
del "%cd%\Content\DRGLib"
mklink /d "%cd%\Content\DRGLib" "%cd%\DRGLibDevkitFiles\FSD\Content\DRGLib"

pause
