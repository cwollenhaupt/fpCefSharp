? Program()
_Screen.Move (100,100)
on Shutdown Quit

#define PROCESS_SYSTEM_DPI_AWARE 1
Declare long SetProcessDpiAwareness in Shcore.dll long value
SetProcessDpiAwareness (PROCESS_SYSTEM_DPI_AWARE)

DO FORM ShowHtml WITH "https://github.com/cwollenhaupt/fpCefSharp"
