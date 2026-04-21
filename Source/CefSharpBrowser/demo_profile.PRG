*========================================================================================
* Each process that uses CEF must have their own profile folder. By default all 
* processes running CEF use the same folder. When fpCefSharp detects that the profile
* folder is already in use it automatically creates an empty profile folder. This
* means the user starts with a fresh browser instance that requires them to authenticate
* again due to the lack of cookies.
*
* Sometimes however, you want the new instance to start with some prior established
* cookies and session data. However, you cannot access a profile folder that is in use.
* One workaround is to make a backup of the folder at a time when it is not in use and
* copy this backup into any newly created profile. 
*
* Users then won't have their latest data remembered, but wouldn't start from scratch 
* either.
*========================================================================================

	*--------------------------------------------------------------------------------------
	* Check whether we can make a backup. This can only happen before we or another 
	* process uses the profile.
	*--------------------------------------------------------------------------------------
	Local loCefBrowser, lcPath
	loCefBrowser = NewObject("CefSharpBrowser", "CefSharpBrowser.prg")
	lcPath = loCefBrowser.GetSafeCachePath ()
	If Empty(m.lcPath)
		MessageBox("Profile already in use. NO BACKUP created.")
	Else
		MessageBox("Creating a BACKUP of the profile folder")
		* Write your code to actually create a backup here
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Launch the browser with the config object that handles the profile event.
	*--------------------------------------------------------------------------------------	
	LOCAL loConfig
	loConfig = CREATEOBJECT("MyConfig")
	DO FORM ShowHtml WITH "https://myApp/index.html", m.loConfig	

*========================================================================================
* This config class handles the event to initialize a profile directory. If you use your
* own subclass of CefSharpBrowser you can alternatively overide the OnCreateUniqueCache 
* method instead.
*========================================================================================
Define Class MyConfig as Custom

	Index_html = ;
		"Launch a second copy of FoxPro and run this program again to see the differences"	

*========================================================================================
* In this method you copy the backup into the new profile folder. The parameter is the
* location of the new profile folder. The profile contains subfolders, so make sure you
* copy everything recursively.
*========================================================================================
Procedure OnCreateUniqueCache (tcPath)
	MessageBox("Copy BACKUP to '"+m.tcPath+"'")
	* Write your code to actually copy the backup to the profile folder here

EndDefine