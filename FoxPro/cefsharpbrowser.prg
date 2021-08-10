*========================================================================================
* CefSharp Browser Control
*
* This object binds to a DotNetContainer Host to load an instance of the cefSharp
* Browser control.
*========================================================================================
Define Class CefSharpBrowser as Custom

	#include Acodey.h

	*--------------------------------------------------------------------------------------
	* Hostname for call back Urls. 
	*--------------------------------------------------------------------------------------
	cHostName = "MyApp"
	
	*--------------------------------------------------------------------------------------
	* Languages
	*--------------------------------------------------------------------------------------
	cLanguages = "en-US,en"
	
	*--------------------------------------------------------------------------------------
	* We need the reference when we Reload a page
	*--------------------------------------------------------------------------------------
	oChromium = null
	
	*--------------------------------------------------------------------------------------
	* An optional config object that is passed to BindToHost.
	*--------------------------------------------------------------------------------------
	oConfig = null
	
	*--------------------------------------------------------------------------------------
	* Internal properties. Ensures that BindToHost is never called more than once per
	* instance. We avoid repeated calls by maintaining a .NET Bridge instance that is 
	* bound to the AppDomain of the InterOp layer.
	*--------------------------------------------------------------------------------------
	lBoundToHost = .F.	
	oDotNetBridge = null
	
*========================================================================================
* Returns the cefSharp folder with the highest supported and installed version of 
* cefSharp. We always return a path, even when it doesn't exist.
*========================================================================================
Function GetCefSharpPath

	*--------------------------------------------------------------------------------------
	* specify the program folder.
	*--------------------------------------------------------------------------------------
	Local lcRoot
	IF __VFPENV_DEVELOP
		lcRoot = Sys(5)+Curdir()
	ELSE
		lcRoot = JustPath(_VFP.ServerName)
	ENDIF
	lcRoot = Addbs (m.lcRoot)
	
	*--------------------------------------------------------------------------------------
	* These are all supported versions of the CefSharp browser. The cefSharp team only
	* releases the odd version numbers of the Chromium browser.
	*--------------------------------------------------------------------------------------
	Local laSupportedVersion[4]
	laSupportedVersion[1] = "cef-bin-v65"
	laSupportedVersion[2] = "cef-bin-v75.1.142"	
	laSupportedVersion[3] = "cef-bin-v79.1.360"
	laSupportedVersion[4] = "cef-bin-v84.4.10"
	laSupportedVersion[4] = "cef-bin-v91.1.230"
	
	*--------------------------------------------------------------------------------------
	* CefSharp is located in a sub folder. We are looking for the highest available 
	* version. If we can't find a version, we return the the path of the oldest supported
	* version.
	*--------------------------------------------------------------------------------------
	Local lcPath, lnVersion
	For lnVersion = Alen (laSupportedVersion, ALEN_LINES) to 1 step -1
		lcPath = m.lcRoot + laSupportedVersion[m.lnVersion]
		If Directory (m.lcPath, 1)
			Exit
		EndIf
	EndFor
	
	*--------------------------------------------------------------------------------------
	* Check return value
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.lcPath) == T_CHARACTER
		Assert not Empty (m.lcPath)
	#ENDIF
	
Return m.lcPath
	
*========================================================================================
* Returns .T. if the cefSharp browser is available. This is the case when the application
* folder contains a cef-bin-vNNN subfolder. NN is the version that is used.
*========================================================================================
Function IsAvailable

	*--------------------------------------------------------------------------------------
	* Check folder. If necessary we could check for all required files, too, but there are
	* lots of them.
	*--------------------------------------------------------------------------------------
	Local lcPath, llAvailable
	lcPath = This.GetCefSharpPath ()
	llAvailable = Directory (m.lcPath, 1)
	
	*--------------------------------------------------------------------------------------
	* Check return value
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.llAvailable) == T_LOGICAL
	#ENDIF

Return m.llAvailable

*========================================================================================
* Loads the browser with the specified page. If the browser should start empty, pass
* "about:blank" as the Url.
*
* Each instance can only be bound to one host, because we create handlers and link
* them to the browser.
* 
* The config object is optional. It may have different properties and methods. All
* properties and methods are optional. You can hence pass either a Scatter-Object,
* a parameter object based on Empty or any handler object.
*
* All calls to https://myApp/ and http://myApp/ are intercepted and handled according
* to the config object. The server name "myApp" can be configured with the cHostName
* property.
*
* All requests with a file extension are treated as file content. If the config object
* has a property with the same name as the requested file, then the property value
* is returned. The dot in the file name should be replaced by an underscore in the
* property name. For instance, a call to "http://myApp/index.htm checks for a property
* named "index_htm". If one exists, its value is returned. The file extension controls
* the content type that is returned.
*
* Any request without a file extension is treated as a method call. The link
* http:/myApp/print calls the Print() method in the config object, if one exists.
*
* When the property or method does not exist, we raise an error.
*========================================================================================
Procedure BindToHost (toHost, tcAddress, toConfig)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toHost) == T_OBJECT
		Assert Vartype (m.tcAddress) == T_CHARACTER
		Assert Vartype (m.toConfig) $ T_OBJECT + T_OPTIONAL + T_NULL
		Assert not This.lBoundToHost
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Each instance can only by bound once.
	*--------------------------------------------------------------------------------------
	This.lBoundToHost = .T.
	This.oConfig = m.toConfig
	
	*--------------------------------------------------------------------------------------
	* wwDotNetBridge. We must use the instance create in the DotNetContainer instance,
	* so that any object we create resides in the same AppDomain as the browser.
	*--------------------------------------------------------------------------------------
	Local loBridge as wwdotnetbridge of wwdotnetbridge.prg
	loBridge = This.DotNet (m.toHost)
	
	*--------------------------------------------------------------------------------------
	* Load assemblies. 
	*--------------------------------------------------------------------------------------
	Local lcPath, llOK
	lcPath = Addbs (This.GetCefSharpPath ())
	loBridge.LoadAssembly (m.lcPath + "CefSharp.dll")
	loBridge.LoadAssembly (m.lcPath + "CefSharp.Core.dll")
	loBridge.LoadAssembly (m.lcPath + "CefSharp.WinForms.dll")	
	loBridge.LoadAssembly (m.lcPath + "fpCefSharp.dll")
	
	*--------------------------------------------------------------------------------------
	* Initialize Cef. Cef must be initialized exactly once per process. 
	*--------------------------------------------------------------------------------------
	This.GlobalInit (m.loBridge)
	
	*--------------------------------------------------------------------------------------
	* When we have a config object, we can not navigate to the requested Url directly.
	* It might be a redirection for which we we need the handler to be set up first.
	*--------------------------------------------------------------------------------------
	Local lcAddress
	If Vartype (m.toConfig) == T_OBJECT
		lcAddress = "about:blank"
	Else
		lcAddress = m.tcAddress
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Load browser control.
	*--------------------------------------------------------------------------------------
	Local loChromium
	loChromium = loBridge.CreateInstance("CefSharp.WinForms.ChromiumWebBrowser" ;
		,m.lcAddress ;
		,NULL ;
	)	
	toHost.SetControl (m.loChromium)
	
	*--------------------------------------------------------------------------------------
	* The ChromiumWebBrowser control creates the actual instance of cef browser in a 
	* background thread. Because this happens asynchronously we cannot access the browser
	* directly right away. We need the browser to register the call back handler, though.
	* Wait a maximum of five seconds for the browser to finish loading.
	*--------------------------------------------------------------------------------------
	Local ltStart, loBrowser
	loBrowser = null
	Declare Sleep in Win32Api Long
	ltStart = Datetime ()
	Do while not loBridge.GetProperty (m.loChromium, "IsBrowserInitialized")
		If Datetime() > ltStart+5
			EventLog ("cefsharp.bind-to-host.browser-timeout")
			Exit
		EndIf
		Sleep (50)
	EndDo
	If loBridge.GetProperty (m.loChromium, "IsBrowserInitialized")
		loBrowser = loBridge.InvokeMethod (m.loChromium, "GetBrowser")
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Register this handler instance. Callbacks from cefSharp give us the browser window.
	* Because there is only one instance of the fpSchemeHandlerFactory, the factory
	* object must be able to identify the handler based on the browser window.
	*
	* The callback uses the config object to figure out what to do with a request. There
	* is no need to regsiter a call back when we don't have a config object.
	*--------------------------------------------------------------------------------------
	If Vartype (m.toConfig) == T_OBJECT
		loBridge.InvokeStaticMethod ( ;
			 "fpCefSharp.fpSchemeHandlerFactory" ;
			,"RegisterCallback" ;
			,m.loBrowser ;
			,This ;
		)
		loBridge.InvoikeMethod (m.loChromium, "Load", m.tcAddress)
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Store a reference to the browser control. We need it to Reload pages.
	*--------------------------------------------------------------------------------------
	this.oChromium = m.loChromium
		
*========================================================================================
* We only execute GlobalInit once per process. Multiple instances of cefSharp at 
* different times will not execute this method ever again. Changes to the configuration
* of cefSharp have to be implemented here. You cannot use one set of configuration 
* values in one form, and another set in a different form. This makes it impossible
* to use generic classes that require different configurations.
*
* If you debug code and there is a problem with this method then you have to restart
* VFP before you can test any changes.
*========================================================================================
Procedure GlobalInit (toBridge)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toBridge) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Every call but the first one returns here
	*--------------------------------------------------------------------------------------
	If toBridge.GetStaticproperty("CefSharp.Cef", "IsInitialized")
		Return
	EndIf

	*--------------------------------------------------------------------------------------
	* Different versions of cefSharp have slightly different interfaces.
	*--------------------------------------------------------------------------------------
	Local lcVersion
	lcVersion = This.GetVersion ()
	
	*--------------------------------------------------------------------------------------
	* Initialize Cef. 
	*--------------------------------------------------------------------------------------
	Local loCefSettings, loCefCommandLineArgs
	If m.lcVersion == "cef-bin-v65"
		loCefSettings = toBridge.CreateInstance("CefSharp.CefSettings")
		loCefSettings.ResourcesDirPath = m.lcPath
		loCefSettings.BrowserSubprocessPath = m.lcPath + "CefSharp.BrowserSubprocess.exe"
	Else
		loCefSettings = toBridge.CreateInstance("CefSharp.WinForms.CefSettings")
	EndIf
	This.RegisterSchemaHandlers (m.toBridge, m.loCefSettings)
	This.SetLanguage (m.toBridge, m.loCefSettings)
	loCefCommandLineArgs = toBridge.GetProperty(loCefSettings, "CefCommandLineArgs")
	toBridge.InvokeMethod (m.loCefCommandLineArgs, "Add", "enable-media-stream", "1")
	toBridge.InvokeMethod (m.loCefCommandLineArgs, "Add", ;
		"--use-fake-ui-for-media-stream", "1")
	toBridge.InvokeStaticMethod("CefSharp.Cef", "Initialize", m.loCefSettings)	
	
*========================================================================================
* wwDotNetBrifge. We have to use the instance that the DotNet Container provided to
* make sure everything happens in the same AppDomain.
*========================================================================================
Function DotNet (toHost)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toHost) $ T_OBJECT + T_OPTIONAL
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* The first call of DotNet must pass a host object. Subsequent calls can omit the
	* host, because we only need it to create the bridge object.
	*--------------------------------------------------------------------------------------	
	If IsNull (This.oDotNetBridge)
		This.oDotNetBridge = m.toHost.CreateBridge()
	EndIf 

	*--------------------------------------------------------------------------------------
	* Create dotNet Bridge and supply the correct AppDomain instance.
	*--------------------------------------------------------------------------------------
	Local loBridge as wwdotnetbridge of wwdotnetbridge.prg
	loBridge = NewObject("wwDotNetBridge", "wwDotNetBridge.fxp", "", "v4")
	loBridge.oDotNetBridge = This.oDotNetBridge
	
Return m.loBridge

*========================================================================================
* We register our own scheme handler. This makes it possible to load an HTML document 
* without first creating a temporary file and use the file:// prototocol. This is 
* important, because some features in JavaScript only available when the origin of a 
* document is a web server. Additionally, we can define our own actions that execute VFP
* code.
*========================================================================================
Procedure RegisterSchemaHandlers (toBridge, toSettings)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toBridge) == T_OBJECT
		Assert Vartype (m.toSettings) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Create a factory instance. cefBrowser calls the factory to obtain a handler for 
	* a requrst. The handler then calls the OnProcessRequest method. There we process
	* the request and translate into a simpler request.
	*--------------------------------------------------------------------------------------
	Local loFactory
	loFactory = toBridge.CreateInstance ("fpCefSharp.fpSchemeHandlerFactory")
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.loFactory) == T_OBJECT
	#ENDIF

	*--------------------------------------------------------------------------------------
	* We handle any request for http://myApp/ and https://myApp/
	*--------------------------------------------------------------------------------------
	This.RegisterSchemeHandler ("http", m.toBridge, m.toSettings, m.loFactory)
	This.RegisterSchemeHandler ("https", m.toBridge, m.toSettings, m.loFactory)

*========================================================================================
* Register our schema handler that triggers the callback handler for a particular
* browser window.
*========================================================================================
Procedure RegisterSchemeHandler (tcProtocol, toBridge, toSettings, toFactory)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype(m.tcProtocol) == T_CHARACTER
		Assert Vartype(m.toBridge) == T_OBJECT
		Assert Vartype(m.toSettings) == T_OBJECT
		Assert Vartype(m.toFactory) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Create and configure a schema. MyApp acts as a virtual server.
	*--------------------------------------------------------------------------------------
	Local loScheme
	loScheme = toBridge.CreateInstance ("CefSharp.CefCustomScheme")
	loScheme.SchemeName = m.tcProtocol
	loScheme.DomainName = This.cHostName
	toBridge.SetProperty (m.loScheme, "SchemeHandlerFactory", m.toFactory)
	
	*--------------------------------------------------------------------------------------
	* Register schema
	*--------------------------------------------------------------------------------------
	toBridge.InvokeMethod (m.toSettings, "RegisterScheme", m.loScheme)

*========================================================================================
* Language settings
*========================================================================================
Procedure SetLanguage (toBridge, toCefSettings)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toBridge) == T_OBJECT
		Assert Vartype (m.toCefSettings) == T_OBJECT
	#ENDIF

	*--------------------------------------------------------------------------------------
	* The language list is whatever we have specified. These can be multiple languages
	* separated by a comma.
	*--------------------------------------------------------------------------------------
	toBridge.SetProperty (m.toCefSettings, "AcceptLanguageList", This.cLanguages)
	
	*--------------------------------------------------------------------------------------
	* The local is the default language, which is the first item in the list of languages.
	*--------------------------------------------------------------------------------------
	Local lcLocale
	lcLocale = Alltrim (GetWordNum (This.cLanguages, 1, ","))
	toBridge.SetProperty (m.toCefSettings, "Locale", m.lcLocale)

*========================================================================================
* This method handles a request. We're simplifying communication with the cefSharp 
* browser so that the application level code doesn't require a lot of .NET knowledge.
*========================================================================================
Procedure OnProcessRequest (toResourceHandler, toRequest)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toResourceHandler) == T_OBJECT
		Assert Vartype (m.toRequest) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* We can only process a request when we have a config object.
	*--------------------------------------------------------------------------------------
	If not Vartype (This.oConfig) == T_OBJECT
		Return
	EndIf
	
	*--------------------------------------------------------------------------------------
	* We need the bridge to talk to the browser control.
	*--------------------------------------------------------------------------------------
	Local loBridge
	loBridge = This.DotNet ()

	*--------------------------------------------------------------------------------------
	* First we get the requested file name, so that we can determine whether we call a
	* method or read a property from the config object.
	*--------------------------------------------------------------------------------------
	Local lcLocalPath, lcFileName
	lcLocalPath = This.GetLocalPath (m.toRequest)
	lcFileName = JustFname (m.lcLocalPath)
	
	*--------------------------------------------------------------------------------------
	* Is this a known route? We only support a rudimentary resolving mechanism for routes.
	* Each path can be bound to exactly one controller. We use the first one that we find,
	* starting with the full path. We do not automatically resolve IDs in a path.
	*--------------------------------------------------------------------------------------
	Local llIsController
	llIsController = This.OnProcessRequestController ( ;
		 m.lcLocalPath ;
		,m.toResourceHandler ;
		,m.toRequest ;
	)

	*--------------------------------------------------------------------------------------
	* If we couldn't find a registered route, we use the simpler default behavior: Each
	* request either calls a method or returns a property.
	*--------------------------------------------------------------------------------------
	If not m.llIsController
		If Empty (JustExt (m.lcFileName))
			This.OnProcessRequestMethod (m.lcFileName, m.toResourceHandler, m.toRequest)
		Else 
			This.OnProcessRequestProperty (m.lcFileName, m.toResourceHandler, m.toRequest)
		EndIf
	EndIf

*========================================================================================
* Returns the local path part
*========================================================================================
Function GetLocalPath (toRequest)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toRequest) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* We need the bridge to talk to the browser control.
	*--------------------------------------------------------------------------------------
	Local loBridge
	loBridge = This.DotNet ()

	*--------------------------------------------------------------------------------------
	* First we get the requested file name, so that we can determine whether we call a
	* method or read a property from the config object.
	*--------------------------------------------------------------------------------------
	Local lcUrl, loUri, loKind, llAbsolute, lcLocalPath, lcFileName
	lcUrl = loBridge.GetProperty (m.toRequest, "Url")
	loUri = loBridge.CreateComValue ()
	loKind = loBridge.CreateComValue ()
	loKind.SetEnum ("System.UriKind")
	llAbsolute = loBridge.InvokeStaticMethod ("System.Uri", "TryCreate" ;
		,m.lcUrl ;
		,m.loKind ;
		,loUri ;
	)
	If m.llAbsolute
		loUri = loUri.Value 
	Else
		loUri = loBridge.CreateInstance ("System.Uri", ;
			 "https://"+This.cHostName+"/" ;
			,m.lcUrl ;
		)
	EndIf
	lcLocalPath = m.loUri.LocalPath

Return m.lcLocalPath

*========================================================================================
* Processes a call to a controller if we can find a suitable route. In this case we 
* return .T. If we cannot process this request, we return .F.
*
* (...) This code is work in progress and not ready for use. For now do not register
* (...) a route and the class behaves as previous versions.
*========================================================================================
Procedure OnProcessRequestController (tcLocalPath, toResourceHandler, toRequest)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.tcLocalPath) == T_CHARACTER
		Assert Vartype (m.toResourceHandler) == T_OBJECT
		Assert Vartype (m.toRequest) == T_OBJECT
		Assert Vartype (This.oConfig) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Does our configuration contain a collection of routes?
	*--------------------------------------------------------------------------------------
	If not Vartype (This.oConfig.Routes) == T_OBJECT
		Return .F.
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Wir inspect every level of the local path.
	*--------------------------------------------------------------------------------------
	Local laPath[1], lnLevels
	lnLevels = ALines (laPath, m.tcLocalPath, 4+1, "/")
	If m.lnLevels == 0
		Return .F.
	EndIf
	
	*--------------------------------------------------------------------------------------
	* We search backward from the specific route to the more generic route. Therefore we
	* add the next part as we check every level.
	*
	* (...) TODO: Do what the comment says
	*--------------------------------------------------------------------------------------
	Local lcPath, lnLevel
	lcPath = ""
	For lnLevel = 1 to m.lnLevels
		lcPath = "/" + Lower(laPath[m.lnLevel])
		laPath[m.lnLevel] = m.lcPath
	EndFor
	
	*--------------------------------------------------------------------------------------
	* Search for the path in the collection of routes. Routes have to be defined in
	* lower case. A path must begin with "/", such as /api/controller
	*--------------------------------------------------------------------------------------
	Local lnLevel, loRoutes as Collection, lnRoute
	loRoutes = This.oConfig.Routes
	lnRoute = 0
	For lnLevel = m.lnLevels to 1 step -1
		lnRoute = loRoutes.GetKey(laPath[m.lnLevel])
		If m.lnRoute != 0
			Exit
		EndIf
	EndFor
	
	*--------------------------------------------------------------------------------------
	* If we found a controller we call it's OnProessRequest method where the details are
	* handled.
	*--------------------------------------------------------------------------------------
	Local loController
	If m.lnRoute != 0
		loController = loRoutes.Item[m.lnRoute]
		This.CallOnProcessRequest ( ;
			 m.loController ;
			,"OnProcessRequest" ;
			,m.toResourceHandler ;
			,m.toRequest ;
		)
	EndIf 

*========================================================================================
* Processes a method call.
*========================================================================================
Procedure CallOnProcessRequest (toHandler, tcMethod, toResourceHandler, toRequest)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toHandler) == T_OBJECT
		Assert Vartype (m.tcMethod) == T_CHARACTER
		Assert Vartype (m.toResourceHandler) == T_OBJECT
		Assert Vartype (m.toRequest) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* We need the bridge for the browser control
	*--------------------------------------------------------------------------------------
	Local loBridge
	loBridge = This.DotNet ()

	*--------------------------------------------------------------------------------------
	* Retrieve POST data. If there are multiple elements we only return the last one.
	*--------------------------------------------------------------------------------------
	Local loPostData, lcBody, lnCount
	lcBody = ""
	loPostData = loBridge.GetProperty (m.toRequest, "PostData")
	If not IsNull (m.loPostData)
		lnCount = loBridge.GetProperty (m.toRequest, "PostData.Elements.Count")
		If m.lnCount >= 1
			loPostData = loBridge.GetProperty (m.toRequest, "PostData.Elements[0]")
			lcBody = m.lobridge.InvokeStaticMethod ("CefSharp.PostDataExtensions", "GetBody" ;
				,m.loPostData ;
				,null ;
			)
		EndIf
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Retrieve the query string
	*--------------------------------------------------------------------------------------
	Local lcUrl, loUri, lcQuery
	lcUrl = loBridge.GetProperty (m.toRequest, "Url")
	loUri = loBridge.CreateInstance ("System.Uri", m.lcUrl)
	lcQuery = loBridge.GetProperty (m.loUri, "Query")
	If IsNull (m.lcQuery)
		lcQuery = ""
	EndIf
	If Len (m.lcQuery) >= 1
		If Left (m.lcQuery, 1) == "?"
			lcQuery = Substr (m.lcQuery, 2)
		EndIf 
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Create a response object
	*--------------------------------------------------------------------------------------
	Local loData
	loData = CreateObject ("Empty")
	AddProperty (m.loData, "Response", "")
	AddProperty (m.loData, "StatusCode", 200)
	AddProperty (m.loData, "MimeType", "text/html")
	AddProperty (m.loData, "Config", This.oConfig)
	AddProperty (m.loData, "Request", m.toRequest)
	AddProperty (m.loData, "ResourceHandler", m.toResourceHandler)
	
	*--------------------------------------------------------------------------------------
	* The local path is the part of the Url left to the question mark.
	*--------------------------------------------------------------------------------------
	Local lcLocalPath
	lcLocalPath = This.GetLocalPath (m.toRequest)
	AddProperty (m.loData, "LocalPath", m.lcLocalPath)
	
	*--------------------------------------------------------------------------------------
	* Call the method. The method name matches the requested file name. We pass the 
	* parameter object followed by more data parameters.
	*--------------------------------------------------------------------------------------
	toHandler.&tcMethod (m.loData, m.lcQuery, m.lcBody)
	
	*--------------------------------------------------------------------------------------
	* Write the response into a stream. We assume that the response is a text document that
	* can be encoded in UTF-8. We must not convert this document in VFP, because the COM
	* interface automatically converts parameters. We pass a VFP string in the current
	* ANSI code page and VFP handles to the conversion to Unicode.
	*--------------------------------------------------------------------------------------
	Local loStream
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Left (m.loData.MimeType, 5) == "text/"
	#ENDIF
	If Empty (m.loData.Response)
		loStream = null
	Else
		loStream = loBridge.InvokeStaticMethod ("CefSharp.ResourceHandler" ;
			,"GetMemoryStream" ;
			,loData.Response ;
			,loBridge.GetEnumValue ("System.Text.Encoding.UTF8") ;
			,.T. ;
		)
		loBridge.SetProperty (m.loStream, "Position", 0)
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Send the response to the browser.
	*--------------------------------------------------------------------------------------
	Local lnLength, loLength
	If IsNull (m.loStream)
		lnLength = 0
	Else 
		lnLength = loBridge.GetProperty (m.loStream, "Length")
	EndIf
	loLength = loBridge.ConvertToDotNetValue (m.lnLength, "Int64")
	loBridge.SetProperty (toResourceHandler, "ResponseLength", m.loLength)
	loBridge.SetProperty (toResourceHandler, "MimeType", m.loData.MimeType)
	loBridge.SetProperty (toResourceHandler, "StatusCode", m.loData.StatusCode)
	loBridge.SetProperty (toResourceHandler, "Stream", m.loStream)

*========================================================================================
* Processes a method call.
*========================================================================================
Procedure OnProcessRequestMethod (tcFileName, toResourceHandler, toRequest)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.tcFileName) == T_CHARACTER
		Assert Vartype (m.toResourceHandler) == T_OBJECT
		Assert Vartype (m.toRequest) == T_OBJECT
		Assert Vartype (This.oConfig) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Call the config object's method
	*--------------------------------------------------------------------------------------
	This.CallOnProcessRequest ( ;
		 This.oConfig ;
		,m.tcFileName ;
		,m.toResourceHandler ;
		,m.toRequest ;
	)

*========================================================================================
* Process a property request
*========================================================================================
Procedure OnProcessRequestProperty (tcFileName, toResourceHandler, toRequest)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.tcFileName) == T_CHARACTER
		Assert Vartype (m.toResourceHandler) == T_OBJECT
		Assert Vartype (m.toRequest) == T_OBJECT
		Assert Vartype (This.oConfig) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* We need the bridge for the browser control
	*--------------------------------------------------------------------------------------
	Local loBridge
	loBridge = This.DotNet ()

	*--------------------------------------------------------------------------------------
	* Determine the property with the requested document. We use macro substituion instead
	* of GETPEM(), so that we can mock this data object for unit tests. foxMock does not
	* work with meta data checks on properties, because GETPEM() doesn't trigger the
	* THIS_Access method.
	*--------------------------------------------------------------------------------------
	Local lcProperty, lcContent
	lcProperty = Chrtran (m.tcFileName, ".", "_")
	lcContent = This.oConfig.&lcProperty
	
	*--------------------------------------------------------------------------------------
	* Depending on the file extension we choose a different MIME type. Presently we support
	* only HTML, because this function's main purpose is to provide the browser with the
	* initial HTML document. If we need further types, these must be added here.
	*--------------------------------------------------------------------------------------
	Local lcExtension, lcMime
	lcExtension = Lower (JustExt (m.tcFileName))
	Do case
	Case m.lcExtension == "html"
		lcMime = "text/html"
	Case m.lcExtension == "htm"
		lcMime = "text/html"
	Case m.lcExtension == "pdf"
		lcMime = "application/pdf"
	Otherwise 
		lcMime = "text/plain"
	EndCase
	
	*--------------------------------------------------------------------------------------
	* Write the response into a stream. 
	* 
	* For strings we assume that the response is a text document that can be encoded in 
	* UTF-8. We must not convert this document in VFP, because the COM interface 
	* automatically converts parameters. We pass a VFP string in the current
	* ANSI code page and VFP handles to the conversion to Unicode.
	*
	* If your string is already encoded in UTF-8, you have to convert it to a 
	* varbinary to avoid a double conversion.
	*
	* For binary data we pass that data unchanged. The property needs already to be
	* encoded accordingly.
	*--------------------------------------------------------------------------------------
	Local loStream
	Do case 
	Case Vartype (m.lcContent) == T_CHARACTER
		loStream = loBridge.InvokeStaticMethod ("CefSharp.ResourceHandler" ;
			,"GetMemoryStream" ;
			,m.lcContent ;
			,loBridge.GetEnumValue ("System.Text.Encoding.UTF8") ;
			,.T. ;
		)
	Case Vartype (m.lcContent) == T_VARBINARY
		loStream = loBridge.CreateInstance ("System.IO.MemoryStream", m.lcContent)
	EndCase
	loBridge.SetProperty (m.loStream, "Position", 0)
	
	*--------------------------------------------------------------------------------------
	* Send the response back to the browser
	*--------------------------------------------------------------------------------------
	Local lnLength, loLength
	lnLength = loBridge.GetProperty (m.loStream, "Length")
	loLength = loBridge.ConvertToDotNetValue (m.lnLength, "Int64")
	loBridge.SetProperty (toResourceHandler, "ResponseLength", m.loLength)
	loBridge.SetProperty (toResourceHandler, "MimeType", m.lcMime)
	loBridge.SetProperty (toResourceHandler, "StatusCode" ;
		,loBridge.GetEnumValue ("System.Net.HttpStatusCode.OK") ;
	)
	loBridge.SetProperty (toResourceHandler, "Stream", m.loStream)
	loBridge.SetProperty (toResourceHandler, "AutoDisposeStream", .T.)
		
*=========================================================================================
* Reload the current page.
* 
* toHost is fpDotNet.DotNetContainer
*=========================================================================================
PROCEDURE Reload (toHost)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toHost) == T_OBJECT
		Assert Vartype (this.oChromium) = T_OBJECT
	#ENDIF	

	*--------------------------------------------------------------------------------------
	* Get a .NET bridge for the form's AppDomain
	*--------------------------------------------------------------------------------------
	Local loBridge as wwdotnetbridge of wwdotnetbridge.prg
	loBridge = DotNet ()
	loBridge.oDotNetBridge = m.toHost.CreateBridge()

	*--------------------------------------------------------------------------------------
	* Retrieve browser control and call Reload. loBrowserControl is of type IBrowser.
	*--------------------------------------------------------------------------------------
	Local loBrowserControl
	loBrowserControl = loBridge.InvokeMethod (this.oChromium, "GetBrowser")
	loBridge.InvokeMethod(loBrowserControl, "Reload", .F.)

*========================================================================================
* Returns the cefSharp version that we are using.
*========================================================================================
Function GetVersion ()

	*--------------------------------------------------------------------------------------
	* Determine version
	*--------------------------------------------------------------------------------------
	Local lcPath, lcVersion
	lcPath = This.GetCefSharpPath ()
	lcVersion = Lower (JustFName (m.lcPath))
	
	*--------------------------------------------------------------------------------------
	* Check return value
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.lcVersion) == T_CHARACTER
		Assert not Empty (m.lcVersion)
	#ENDIF
	
Return m.lcVersion

*========================================================================================
* Release cef Browser resources
*========================================================================================
Procedure Release

	*--------------------------------------------------------------------------------------
	* If we don't unregister ower handler for a browser window, we would hold onto it
	* until the applications should down.
	*--------------------------------------------------------------------------------------
	loBridge.InvokeStaticMethod ( ;
		 "fpCefSharp.fpSchemeHandlerFactory" ;
		,"UnregisterCallback" ;
		,m.loChromium ;
		,This ;
	)
	
	*--------------------------------------------------------------------------------------
	* Clear references
	*--------------------------------------------------------------------------------------
	This.oChromium = null	
	This.oConfig = null
	This.oDotNetBridge = null
	
EndDefine
