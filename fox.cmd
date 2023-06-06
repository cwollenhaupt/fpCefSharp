::@echo off
setlocal

rem =====================================================================================
rem Requires Windows 10 build 17063 or later
rem =====================================================================================

rem These parameters require updates whenever there is a new release
set versionCefSharp=v97.1.61
set versionFpCefSharp=%versionCefSharp%.1

rem These values are supposed to simplify the code
set urlGithub=https://github.com/cwollenhaupt/fpCefSharp
set urlDownload=%urlGithub%/releases/download
set urlRelease=%urlDownload%/%versionFpCefSharp%/fpCefSharp.%versionFpCefSharp%.zip


if /I "%~1"=="init" goto Init
goto :End

:Init

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
xcopy temp\cef-bin-%versionCefSharp% Source\CefSharpBrowser\cef-bin-%versionCefSharp%\ /ce


:End