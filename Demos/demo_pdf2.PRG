*========================================================================================
* Displaying a PDF file
*========================================================================================

	Local lcPdf
	lcPdf = FullPath ("Files/Wollenhaupt_Browser.Pdf")
	lcPdf = "file://" + Chrtran (m.lcPdf, "\", "/")
	
	Do form ShowHtml with m.lcPdf

