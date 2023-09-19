? Program()
_Screen.Move (100,100)
on Shutdown Quit

#DEFINE DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE 18
DECLARE long SetProcessDpiAwarenessContext IN Win32Api Long
SetProcessDpiAwarenessContext (DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE)

DO FORM ShowHtml WITH "https://github.com/cwollenhaupt/fpCefSharp"
