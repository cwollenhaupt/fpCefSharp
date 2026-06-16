	
	LOCAL loConfig
	loConfig = CREATEOBJECT("MyHandler")	
	DO FORM ShowHtml_Examples WITH "https://www.google.com", m.loConfig
	

DEFINE CLASS MyHandler as Custom

	Procedure Example (toForm, tnSample)
		toForm.oCefSharpBrowser.ShowDeveloperTools ()

ENDDEFINE
