# Important
These are the companion files for my presentation of the CefSharp web browser control. Please refer to my [YouTube video](https://www.youtube.com/watch?v=hf5pQKOb0n4_) for details.

Before you can execute any sample code, you have to generate the project file and the form using TwoFox. Please run the following command in Visual FoxPro when the current folder is the FoxPro folder:

```foxpro
DO tools/genCode with "CEFSHARP.twofox"
```
Please note that this folder contains _only_ the demo files. It does not contain any dependency including:

- fpDotNet
- wwDotNetBridge
- CefSharp