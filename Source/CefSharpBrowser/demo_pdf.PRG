*========================================================================================
* Displaying a PDF file
*========================================================================================

	Local lcPdf, loConfig
	lcPdf = FileToStr ("Files/Wollenhaupt_Browser.Pdf")
	loConfig = CreateObject ("Empty")
	AddProperty (m.loConfig, "Report_pdf", CreateBinary (m.lcPdf))
	
	Do form ShowHtml with "https://MyApp/Report.pdf", m.loConfig

