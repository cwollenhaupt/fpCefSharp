@echo off
rem =====================================================================================
rem This build tool provides a number of options to support development. Call this script
rem from the terminal with the command as the first parameter, such as:
rem
rem   fox init
rem 
rem Currently the following commands are supported
rem
rem init: Call once after cloning the repository to prepare for development
rem
rem NOTE: Requires Windows 10 build 17063 or later
rem =====================================================================================
setlocal

rem These parameters require updates whenever there is a new release. This happens
rem automatically in the release process.

rem DO NOT MODIFY - version {
set versionCefSharp=v97.1.61
set versionFpCefSharp=%versionCefSharp%.2
rem } - DO NOT MODIFY

rem These values are supposed to simplify the code
set urlGithub=https://github.com/cwollenhaupt/fpCefSharp
set urlDownload=%urlGithub%/releases/download
set urlRelease=%urlDownload%/%versionFpCefSharp%/fpCefSharp.%versionFpCefSharp%.zip
set urlFpDotNet=https://github.com/cwollenhaupt/fpDotNet/releases/download/v1.0/fpDotNet.zip

rem These values can be configured
set vfp9=%programfiles(x86)%\Microsoft Visual FoxPro 9\vfp9.exe

if exist fox.user.cmd call fox.user.cmd

if /I "%~1"=="init" goto Init
if /I "%~1"=="release" goto Release
if /I "%~1"=="test" goto Test

echo Supported commands are init, release, test
goto :eof

rem =====================================================================================
rem INIT
rem
rem The repository does not include any redundant files. Especially there is a minimal
rem number of non-mergable binary files (only tools). 
rem
rem You run INIT once after cloning the repository to prepare your working folder for
rem development. 
rem =====================================================================================
:Init

rem =====================================================================================
rem Check prerequisites
rem =====================================================================================
if not exist "%vfp9%" (
   echo.
   echo VFP executable "%vfp9%" does not exist
   if exist fox.user.cmd (
      echo Please add the following line to fox.user.cmd:
      echo.
      echo   SET vfp9=full path to VFP9.exe
   ) else (
      echo Please configure the location of VFP9.EXE in fox.user.cmd
      echo SET vfp9=full path to VFP9.exe >>fox.user.cmd
   )
   goto end
) 

rem =====================================================================================
rem Download cefSharp runtime
rem =====================================================================================
rem
rem The runtime is part of the latest fpCefSharp release. Alternatively, we can build
rem this folder with the C# project.
rem 
rem --location       GitHub sends a 302 Permanently Moved response
rem --ssl-no-revoke  curl cannot check certificate revocation
md temp
curl --location ^
     --ssl-no-revoke ^
     --output temp/release.zip ^
     --url %urlRelease%
tar -xf temp/release.zip --directory temp
xcopy temp\cef-bin-%versionCefSharp% ^
	Source\CefSharpBrowser\cef-bin-%versionCefSharp%\ /yce
rmdir temp /q /s

rem =====================================================================================
rem Download all other dependencies
rem =====================================================================================
git submodule init
git submodule update

rem =====================================================================================
rem Initial pass to generate FoxPro binaries
rem =====================================================================================
"%vfp9%" Source/CefSharpBrowser/tools/run_gencode.prg

rem =====================================================================================
rem Deploy wwDotNetBridge into multiple locations
rem =====================================================================================
call :init-deploy-wwdotnetbridge Source\CefSharpBrowser ..\..
call :init-deploy-wwdotnetbridge Source\Tests\dpi-awareness ..\..\..

rem =====================================================================================
rem Prepare the test environment for the dpi-aware test suite
rem =====================================================================================
rmdir Source\Tests\dpi-awareness\cef-bin-%versionCefSharp%
del Source\Tests\dpi-awareness\Acodey.h
del Source\Tests\dpi-awareness\aco_lde.h
del Source\Tests\dpi-awareness\aco_len.h
del Source\Tests\dpi-awareness\iAcodey.h
del Source\Tests\dpi-awareness\CefSharpBrowser.prg

mklink /d Source\Tests\dpi-awareness\cef-bin-%versionCefSharp% ^
       ..\..\CefSharpBrowser\cef-bin-%versionCefSharp%
mklink Source\Tests\dpi-awareness\Acodey.h ..\..\CefSharpBrowser\Acodey.h
mklink Source\Tests\dpi-awareness\aco_lde.h ..\..\CefSharpBrowser\aco_lde.h
mklink Source\Tests\dpi-awareness\aco_len.h ..\..\CefSharpBrowser\aco_len.h
mklink Source\Tests\dpi-awareness\iAcodey.h ..\..\CefSharpBrowser\iAcodey.h
mklink Source\Tests\dpi-awareness\CefSharpBrowser.prg ^
       ..\..\CefSharpBrowser\CefSharpBrowser.prg

goto :eof

rem =====================================================================================
rem Deploy wwDotNetBridge. We use a symbolic link here to always use the same file as 
rem we downloaded in the submodule. This requires an NTFS formatted drive (as opposed
rem to a FAT-family type of drive). For network shares you must have the "create symbolic
rem links" permission on the server.
rem =====================================================================================
:init-deploy-wwdotnetbridge
del %~1\ClrHost.dll
del %~1\wwDotNetBridge.dll
del %~1\wwDotNetBridge.prg
mklink %~1\ClrHost.dll ^
       %~2\Modules\wwDotNetBridge\Distribution\ClrHost.dll
mklink %~1\wwDotNetBridge.dll ^
       %~2\Modules\wwDotNetBridge\Distribution\wwDotNetBridge.dll
mklink %~1\wwDotNetBridge.prg ^
       %~2\Modules\wwDotNetBridge\Distribution\wwDotNetBridge.prg

goto :eof



rem =====================================================================================
rem RELEASE
rem
rem Creates a full and a core release for the last built of fpCefSharp. These releases
rem are the ones that are uploaded as a release on GitHub.
rem
rem Release does not include a build process! You must build all required files before
rem creating a release.
rem =====================================================================================
:Release

rem =====================================================================================
rem Prepare Release folder. The Release folder is a transient folder that gets completely
rem wiped out for each build.
rem =====================================================================================
rmdir Release /q /s

rem =====================================================================================
rem Full release
rem =====================================================================================
set release=Release\fpCefSharp.%versionFpCefSharp%
md %release%
call :release-cefsharp %release%
call :release-fpdotnet %release%
call :release-wwdotnetbridge %release%
call :release-fpcefsharp %release%
call :release-demos %release%
call :release-docs %release%
call :release-zip %release%

rem =====================================================================================
rem Core release
rem =====================================================================================
set release=Release\fpCefSharp.%versionFpCefSharp%.core
md %release%
call :release-cefsharp %release%
call :release-fpdotnet %release%
call :release-wwdotnetbridge %release%
call :release-fpcefsharp %release%
call :release-zip %release%

echo Release completed in folder Release

goto :eof

rem =====================================================================================
rem RELEASE - CefSharp
rem
rem Releases CefSharp into the specified release folder
rem =====================================================================================
:release-cefsharp
echo Copying CefSharp
xcopy Source\CefSharpBrowser\cef-bin-%versionCefSharp%\ ^
      %~1\cef-bin-%versionCefSharp%\ /yce
for %%f in (%~1\cef-bin-%versionCefSharp%\*.pdb) do (
    rem %%~df returns the drive
    rem %%~pf returns the path
    rem %%~nf returns the file name without extension
    call :release-removepdb %%~df%%~pf%%~nf
)
goto :eof

:release-removepdb
echo Deleting %~1.pdb
del %~1.pdb
if exist %~1.xml del %~1.xml

goto :eof

rem =====================================================================================
rem RELEASE - fpDotNet
rem
rem Releases fpDotNet into the specified release folder
rem =====================================================================================
:release-fpdotnet
echo Downloading fpDotNet
md temp
curl --location ^
     --ssl-no-revoke ^
     --output temp/fpdotnet.zip ^
     --url %urlFpDotNet%
md %~1\fpDotNet
tar -xf temp/fpdotnet.zip --directory %~1\fpDotNet
rmdir temp /q /s
goto :eof

rem =====================================================================================
rem RELEASE - wwDotNetBridge
rem
rem Releases wwDotNetBridge into the specified release folder
rem =====================================================================================
:release-wwdotnetbridge
echo Copying wwDotNetBridge
copy Source\CefSharpBrowser\ClrHost.dll %~1
copy Source\CefSharpBrowser\wwDotNetBridge.dll %~1
copy Source\CefSharpBrowser\wwDotNetBridge.prg %~1\
goto :eof

rem =====================================================================================
rem RELEASE - fpCefSharp
rem
rem Releases fpCefSharp into the specified release folder
rem =====================================================================================
:release-fpcefsharp
echo Copying fpCefSharp files
copy Source\CefSharpBrowser\aco_lde.h %~1
copy Source\CefSharpBrowser\aco_len.h %~1
copy Source\CefSharpBrowser\acodey.h %~1\
copy Source\CefSharpBrowser\cefsharpbrowser.prg %~1\
copy Source\CefSharpBrowser\iacodey.h %~1\
goto :eof

rem =====================================================================================
rem RELEASE - Demos
rem
rem Releases Demos into the specified release folder
rem =====================================================================================
:release-demos
echo Coyping demo files
copy Source\CefSharpBrowser\demo_*.prg %~1
copy Source\CefSharpBrowser\showhtml*.scx %~1
copy Source\CefSharpBrowser\showhtml*.sct %~1
goto :eof

rem =====================================================================================
rem RELEASE - Demos
rem
rem Releases Demos into the specified release folder
rem =====================================================================================
:release-docs
echo Coyping documentation
xcopy Source\CefSharpBrowser\Files\  %~1\Files\ /yce
goto :eof

rem =====================================================================================
rem RELEASE - Zip
rem
rem Creates a ZIP file the specified release folder
rem =====================================================================================
:release-zip
echo Building archive %~1.zip
tar -C %~1 -acf %~1.zip *
rmdir %~1 /q /s
goto :eof

rem =====================================================================================
rem Test <test suite>
rem
rem Runs interactive and non-interactive tests
rem =====================================================================================
:Test

if /I "%~2"=="dpi-aware" goto test-dpi-aware

echo Syntax
echo.
echo   fox test test_suite
echo.
echo Supported values for test_suite are: dpi-aware
goto :eof

rem =====================================================================================
rem Test dpi-aware
rem
rem Builds and runs various combinations of setting the dpi awareness through API calls
rem and manifests. Runs each EXE that displays a simple browser window. Users need to
rem interactively verify that the result looks OK.
rem =====================================================================================
:test-dpi-aware
setlocal
for %%f in (Source\Tests\dpi-awareness\*_main.prg) DO (
    call :test-dpi-aware-build "%%f" "%%~df%%~pf%%~nf"
)
goto :eof

rem =====================================================================================
rem Test dpi-aware 
rem 
rem Build and run a single test case
rem =====================================================================================
:test-dpi-aware-build
setlocal
"%vfp9%" Source/Tests/dpi-awareness/build.prg "%~1"
set p2=%~2
set exe=%p2:~0,-5%.exe
if exist "%exe%" (
   %exe%
) else (
  echo Failed to build %exe%
)
goto :eof