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
			<form action="Submit?source=from_form">
			  Text 1: <input type="text" id="text1" name="text1"><br>
			  Text 2: <input type="text" id="text2" name="text2"><br>
			  <input type="submit" value="Submit">
			</form>
			</html>	
		ENDTEXT 

	PROCEDURE Submit (toResponse, tcQuery, tcForm)
		MESSAGEBOX ("Query string is ignored: " + m.tcQuery)
		MESSAGEBOX ("Form data is empty: " + m.tcForm)
		toResponse.Response = "<h1>Your request has been submitted!<h1>"

ENDDEFINE