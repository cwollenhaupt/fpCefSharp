*========================================================================================
* Handle missing files
*========================================================================================
	
	LOCAL loConfig
	loConfig = CREATEOBJECT("MyHandler")	
	DO FORM ShowHtml WITH "https://myApp/index.html", m.loConfig
	

DEFINE CLASS MyHandler as Custom

	index_html = ""

	PROCEDURE Init
		TEXT TO This.index_html NoShow
			<html>
				<img src="favicon.ico">
			</html>	
		ENDTEXT 

ENDDEFINE