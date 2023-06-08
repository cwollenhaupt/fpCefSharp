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
set versionFpCefSharp=%versionCefSharp%.1
rem } - DO NOT MODIFY

rem These values are supposed to simplify the code
set urlGithub=https://github.com/cwollenhaupt/fpCefSharp
set urlDownload=%urlGithub%/releases/download
set urlRelease=%urlDownload%/%versionFpCefSharp%/fpCefSharp.%versionFpCefSharp%.zip

rem These values can be configured
set vfp9=%programfiles(x86)%\Microsoft Visual FoxPro 9\vfp9.exe

if exist fox.user.cmd call fox.user.cmd


if /I "%~1"=="init" goto Init
goto :End

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
xcopy temp\cef-bin-%versionCefSharp% Source\CefSharpBrowser\cef-bin-%versionCefSharp%\ /yce
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
rem Deploy wwDotNetBridge. We use a symbolic link here to always use the same file as 
rem we downloaded in the submodule. This requires an NTFS formatted drive (as opposed
rem to a FAT-family type of drive). For network shares you must have the "create symbolic
rem links" permission on the server.
rem =====================================================================================
del Source\CefSharpBrowser\ClrHost.dll
del Source\CefSharpBrowser\wwDotNetBridge.dll
del Source\CefSharpBrowser\wwDotNetBridge.prg
mklink Source\CefSharpBrowser\ClrHost.dll ^
       ..\..\Modules\wwDotNetBridge\Distribution\ClrHost.dll
mklink Source\CefSharpBrowser\wwDotNetBridge.dll ^
       ..\..\Modules\wwDotNetBridge\Distribution\wwDotNetBridge.dll
mklink Source\CefSharpBrowser\wwDotNetBridge.prg ^
       ..\..\Modules\wwDotNetBridge\Distribution\wwDotNetBridge.prg

:End