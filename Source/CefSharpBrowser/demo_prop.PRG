*========================================================================================
* Providing the content as a property
*========================================================================================
	
	LOCAL loConfig
	loConfig = CREATEOBJECT("Empty")
	ADDPROPERTY(m.loConfig, "index_html")
	loConfig.index_html = "<h1>Hello world!</h1>"
	
	DO FORM ShowHtml WITH "https://myApp/index.html", m.loConfig