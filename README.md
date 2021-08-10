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
