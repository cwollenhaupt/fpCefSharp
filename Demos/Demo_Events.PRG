*========================================================================================
* Respond to events in the browser
*========================================================================================
	
	LOCAL loConfig, loEvents
	loConfig = CREATEOBJECT("MyHandler")
	loEvents = CreateObject("MyEvents")

	Local loForm
	DO FORM ShowHtml WITH "https://myApp/index.html", m.loConfig Name loForm
	loEvents.AddProperty ("oCefSharpBrowser", m.loForm.oCefSharpBrowser)
	loForm.oCefSharpBrowser.HandleEvents (m.loEvents)

DEFINE CLASS MyHandler as Custom

	index_html = ""

	PROCEDURE Init
		TEXT TO This.index_html NoShow
			<html>
				<script>
					function changeTitle () {
						window.top.document.title = new Date().toLocaleString();
					}
				</script>
			  <button onclick="changeTitle();">Change title</button>
			</html>	
		ENDTEXT 
		
	Procedure TitleChangedEvent (m.tcTitle)
	MessageBox("TitleChangedEvent: " + m.tcTitle)

ENDDEFINE


Define Class MyEvents as Custom

Procedure OnTitleChanged (toSender, toEventArgs)
	This.oCefSharpBrowser.HandleTitleChangedEvent (m.toSender, m.toEventArgs)

EndDefine 