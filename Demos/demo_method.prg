*========================================================================================
* Respond to actions
*========================================================================================
	
	LOCAL loConfig
	loConfig = CREATEOBJECT("MyHandler")	
	DO FORM ShowHtml WITH "https://myApp/index.html", m.loConfig
	

DEFINE CLASS MyHandler as Custom

	index_html = ""

	PROCEDURE Init
		TEXT TO This.index_html NoShow
			<html>
			<!-- https://myApp/next -->
			<form action="next">
			  <input type="submit" value="Next">
			</form>
			</html>	
		ENDTEXT 

	PROCEDURE Next (toResponse, tcQuery, tcForm)
		MESSAGEBOX ("You clicked next. Good job!")

ENDDEFINE