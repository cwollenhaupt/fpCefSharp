# fpCefSharp
## Introduction
With fpCefSharp you can add a modern browser to your Visual FoxPro application. It's a wrapper around CefSharp which wraps CEF for .NET applications. To host the browser control in a form you need an instance of fpDotNet.

More details can be found in my [Virtual FoxFest 2020 white paper](https://github.com/cwollenhaupt/fpCefSharp/blob/master/Demos/Files/Wollenhaupt_Browser.pdf) and the [recording of my session](https://www.youtube.com/watch?v=hf5pQKOb0n4). 

## Quick Start

Download the fpCefSharp ZIP file from the [latest release](https://github.com/cwollenhaupt/fpCefSharp/releases) and unpack it into your project folder.

The fpDotNet folder contains a COM control that you need to register. It contains a CMD file that you can execute as an administrator. You only need to do this once. As with all other COM controls this registers globally on the computer and might affect all applications using the same control. 

The prg files can be moved to any folder you want. The demo files can be deleted for your production application.

ShowHtml.SCX is a very simple implementation of the control to mimik a browser interface. You can either use this form or integrate the control in any way you want. The UI is the COM object. Everything else is driven by the cefSharpBrowser class.

## Components and Dependencies
fpCefSharp relies on the following projects:

- [CefSharp](https://github.com/cefsharp/CefSharp)
- [wwDotNetBridge](https://github.com/RickStrahl/wwDotnetBridge)
- [fpDotNet](https://github.com/cwollenhaupt/fpDotNet)

### Breaking Changes
Visual C++ 2019 is used to build CefSharp in version v93 any beyond due to a change originating at Google. Clients must install the latest VC++ runtime to use any version later than v92.0.260. Microsoft provides the latest runtime for x86 systems [here](https://aka.ms/vs/17/release/vc_redist.x86.exe). 

fpCefSharp verifies which VC++ runtime is installed on a client. Without an appropriate runtime only CefSharp versions up to v92.0.260 are considered. You can disable this behavior by setting the lCheckRuntime property to .F. If you support clients with and without VC++ 2019 runtimes, you must deploy the current version of fpCefSharp as well as the cef-bin folder for version v92.0.260 or any previous one. Not running the latest version of CefSharp is a security risk and might make your application vulnerable to web browser exploits.

If you subclassed fpCefSharp and overrode the GetCefSharpPath to change how fpCefSharp locates CefSharp, then please be advised that the method now receives a toHost parameter. You are free to ignore the value, but your subclass must have a corresponding LParameters statement to receive the value.