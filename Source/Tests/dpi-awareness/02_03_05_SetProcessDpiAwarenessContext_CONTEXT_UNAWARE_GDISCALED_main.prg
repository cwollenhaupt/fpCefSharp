? Program()
_Screen.Move (100,100)
on Shutdown Quit

#DEFINE DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED 1073766416
DECLARE long SetProcessDpiAwarenessContext IN Win32Api Long
SetProcessDpiAwarenessContext (DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED)

DO FORM ShowHtml WITH "https://github.com/cwollenhaupt/fpCefSharp"
