# fpCefSharp
## Introduction
With fpCefSharp you can add a modern browser to your Visual FoxPro application. It's a wrapper around CefSharp which wraps CEF for .NET applications. To host the browser control in a form you need an instance of fpDotNet. Everything you need is in the release archive.

More details can be found in my [Virtual FoxFest 2020 white paper](https://github.com/cwollenhaupt/fpCefSharp/blob/master/Demos/Files/Wollenhaupt_Browser.pdf) and the [recording of my session](https://www.youtube.com/watch?v=hf5pQKOb0n4). 

## Quick Start
If you do not wish to contribute at this point, please do not clone the respository. It does not contain the files you need. Should you want to contribute, please read the corresponding section below.

### Just using fpCefSharp - first timer
Download the fpCefSharp ZIP file from the [latest release](https://github.com/cwollenhaupt/fpCefSharp/releases) and unpack it into your project folder.

If this is your first time you want the fpCefSharp.vXXX.zip file in this release. It contains everything in the core ZIP file plus several demo files and documentation. XXX is a version number. Each release only has one archive that looks like this file pattern.

The fpDotNet folder contains a COM control that you need to register. It contains a CMD file that you can execute as an administrator. You only need to do this once. As with all other COM controls this registers globally on the computer and might affect all applications using the same control. 

The prg files can be moved to any folder you want. The demo files can be deleted for your production application.

If you are using a commercial version of wwDotNetBridge, you can replace the following files with your commercial version. Please note that the file names in the commercial version differ from the free version:

- ClrHost.dll
- wwDotNetBridge.dll
- wwDotNetBridge.prg

ShowHtml.SCX is a very simple implementation of the control to mimik a browser interface. You can either use this form or integrate the control in any way you want. The UI is the COM object. Everything else is driven by the cefSharpBrowser class.

### Just using fpCefSharp - upgrading
If you are already using fpCefSharp and only need the latest version, please download the fpCefSharp.vXXX.core.zip. It does include the current release of CefSharp, wwDotNetBridge, fpDotNet, and fpCefSharp. There is no documentation and no demos in this archive. These are the files you have to distribute with your application.

As before, if you use a commercial version of wwDotNetBridge, retain your files and do not copy the files included with the archive into your application folder. Please ensure that your version is compatible with the one used in fpCefSharp.

### Contributing or just looking at the code
The repository does not contain any dependencies or redundant code. After you cloned the repository into your working folder you cannot actually execute anything. Open a terminal window (formerly known as command window or CMD.EXE), change to your working folder and execute the following command:

fox init

This will perform the following steps:

- Download the corresponding release of fpCefSharp
- Download the corresponding versions of fpDotNet and wwDotNetBridge
- Link wwDotNetBridge into the source folder
- Run TwoFox to generate binaries of all FoxPro source files

If you encounter problems, please check the following list of common problems:

fox needs access to VFP9.EXE. Make sure it is installed. If you installed it into a non-standard location, please specify the full path to VFP9.EXE including the name of the EXE in fox.user.cmd. This file is automatically created when VFP9 cannot be found in its standard location. The configuration line could look like this:

SET vfp9=d:\dev\fox9\vfp9.exe

The script creates symbolic links which requires NTFS formatted hard drives or file servers that support symbolic links. You cannot run the fox script on any kind of FAT file format drive.

Downloading the release requires curl.exe. Curl has been part of Windows 10 since 2017 and is part of all releases of Windows 11. If you use an older version of Windows you unfortunately have to upgrade Windows, first.

Git is required to pull submodules. You have Git installed, because that is how you cloned this repository in the first place. However, make sure that the command client is configured to authenticate against GitHub to clone the remaining repositories. This is often an issue when you use a visual UI like TortoiseGit, but never the command line. These tools sometimes have their own authentication agents and do not require the git executable to be in the path.

## Components and Dependencies
fpCefSharp relies on the following projects:

- [CefSharp](https://github.com/cefsharp/CefSharp)
- [wwDotNetBridge](https://github.com/RickStrahl/wwDotnetBridge)
- [fpDotNet](https://github.com/cwollenhaupt/fpDotNet)

### Breaking Changes
Visual C++ 2019 is used to build CefSharp in version v93 any beyond due to a change originating at Google. Clients must install the latest VC++ runtime to use any version later than v92.0.260. Microsoft provides the latest runtime for x86 systems [here](https://aka.ms/vs/17/release/vc_redist.x86.exe). 

fpCefSharp verifies which VC++ runtime is installed on a client. Without an appropriate runtime only CefSharp versions up to v92.0.260 are considered. You can disable this behavior by setting the lCheckRuntime property to .F. If you support clients with and without VC++ 2019 runtimes, you must deploy the current version of fpCefSharp as well as the cef-bin folder for version v92.0.260 or any previous one. Not running the latest version of CefSharp is a security risk and might make your application vulnerable to web browser exploits.

If you subclassed fpCefSharp and overrode the GetCefSharpPath to change how fpCefSharp locates CefSharp, then please be advised that the method now receives a toHost parameter. You are free to ignore the value, but your subclass must have a corresponding LParameters statement to receive the value.

## Making changes to fpCefSharp
fpCefSharp has two components. One is a .NET assembly written in C#, the other a program file written in FoxPro.

Changing the C# assembly or updating the version of CefSharp requires Visual Studio 2022 or something compatible like Rider. The project is configured to deploy its build artifacts right there were the FoxPro code needs it. This means, you can start testing FoxPro code right after building the project in Visual Studio. However, this also means that you need to quit VFP in order to build the project in Visual Studio.

The source code is located in Source/fpCefSharp.dll.

Many modifications do not require any changes in C#. The FoxPro code can be changed right after fox init completed. Source/CefSharpBrowser contains a CefSharp.pjx project file. Virtually all code is located in cefsharpbrowser.prg.