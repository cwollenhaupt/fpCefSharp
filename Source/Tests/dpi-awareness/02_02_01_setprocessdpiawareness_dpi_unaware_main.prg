? Program()
_Screen.Move (100,100)
on Shutdown Quit

#define PROCESS_DPI_UNAWARE 0
Declare long SetProcessDpiAwareness in Shcore.dll long value
SetProcessDpiAwareness (PROCESS_DPI_UNAWARE)

DO FORM ShowHtml WITH "https://github.com/cwollenhaupt/fpCefSharp"
