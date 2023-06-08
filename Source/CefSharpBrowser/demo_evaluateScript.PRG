*========================================================================================
* Evaluate JavaScript values using EvaluateScript
*========================================================================================
	
	LOCAL loConfig
	loConfig = CREATEOBJECT("MyHandler")	
	DO FORM ShowHtml_Examples WITH "https://myApp/index.html", m.loConfig
	

DEFINE CLASS MyHandler as Custom

	index_html = ""

	PROCEDURE Init
		TEXT TO This.index_html NoShow
			<html>
			<form id="myform">
			  Text 1: <input type="text" id="text1" name="text1" value="Hello"><br>
			  Text 2: <input type="text" id="text2" name="text2" value="World"><br>
			  <input type="submit" value="Submit">
			</form>
			</html>	
		ENDTEXT 

	Procedure Example (toForm, tnSample)
		Local lcResult
		lcResult = toForm.oCefSharpBrowser.EvaluateScript ( ;
			"document.getElementById('myform').innerHTML" ;
		)
		MessageBox (m.lcResult)	

ENDDEFINE
