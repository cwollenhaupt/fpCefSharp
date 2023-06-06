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
	* Make sure we only load CefSharp releases that are supported by the runtimes installed
	* on the local machine.
	*--------------------------------------------------------------------------------------
	lCheckRuntime = .T.
	
	*--------------------------------------------------------------------------------------
	* Internal properties. Ensures that BindToHost is never called more than once per
	* instance. We avoid repeated calls by maintaining a .NET Bridge instance that is 
	* bound to the AppDomain of the InterOp layer.
	*--------------------------------------------------------------------------------------
	lBoundToHost = .F.	
	oDotNetBridge = null
	
	*--------------------------------------------------------------------------------------
	* Internal property. After subscribing to events this is a collection of subscription
	* objects.
	*--------------------------------------------------------------------------------------
	oSubscriptions = null
	
*========================================================================================
* Returns the cefSharp folder with the highest supported and installed version of 
* cefSharp. We always return a path, even when it doesn't exist.
*
* The first time we call GetCefSharpPath we must pass a host, so that we can execute
* code in the AppDomain of the browser control. Calling BindToHost takes care of this.
*========================================================================================
Function GetCefSharpPath (toHost)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toHost) $ T_OBJECT + T_OPTIONAL
	#ENDIF

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
	* CefSharp v93 requires at least the VC++ 2019 runtime. We determine what runtimes 
	* are installed: vc2015, vc2019.
	*--------------------------------------------------------------------------------------
	Local lcRuntime
	lcRuntime = This.GetInstalledVcRuntime (m.toHost)
	
	*--------------------------------------------------------------------------------------
	* These are all supported versions of the CefSharp browser and the supported VC++
	* runtimes.
	*--------------------------------------------------------------------------------------
	Local laSupportedVersion[7]
	laSupportedVersion[1] = "cef-bin-v65 vc2015/vc2019"
	laSupportedVersion[2] = "cef-bin-v75.1.142 vc2015/vc2019"
	laSupportedVersion[3] = "cef-bin-v79.1.360 vc2015/vc2019"
	laSupportedVersion[4] = "cef-bin-v84.4.10 vc2015/vc2019"
	laSupportedVersion[5] = "cef-bin-v91.1.230 vc2015/vc2019"
	laSupportedVersion[6] = "cef-bin-v92.0.260 vc2015/vc2019"
	laSupportedVersion[7] = "cef-bin-v97.1.61 vc2019"
	
	*--------------------------------------------------------------------------------------
	* CefSharp is located in a sub folder. We are looking for the highest available 
	* version. If we can't find a version, we return the the path of the oldest supported
	* version. We limit our search to those versions of CefSharp supported by the 
	* VC runtime that is installed on the machine.
	*--------------------------------------------------------------------------------------
	Local lcPath, lnVersion, lcSupported
	For lnVersion = Alen (laSupportedVersion, ALEN_LINES) to 1 step -1
		lcPath = m.lcRoot + GetWordNum (laSupportedVersion[m.lnVersion], 1)
		lcSupported = GetWordNum (laSupportedVersion[m.lnVersion], 2)
		If    m.lcRuntime $ m.lcSupported ;
		   or not This.lCheckRuntime 
			If Directory (m.lcPath, 1)
				Exit
			EndIf
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
* Returns the installed VC++ runtime (vc2015, vc2019). To remain backward compatible
* with previous releases of cefSharpBrowser we return vc2015 whenever we can't find any
* later runtime without actually checking if the runtime is installed.
*========================================================================================
Procedure GetInstalledVcRuntime (toHost)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toHost) $ T_OBJECT + T_OPTIONAL
	#ENDIF

	*--------------------------------------------------------------------------------------
	* VC2015, VC2017, VC2019 and VC2022 share the same runtime library. That is, the
	* library is backward compatible with the latest installed one being the one that is
	* used. VcRedist.exe updates the registry to indicate which version is installed
	* on the machine.
	*
	* We pass NULL instead of a default value to GetValue, because GetValue returns NULL
	* if the key doesn't exist (ie. the runtime is not installed at all). GetValue only
	* returns the default value if the key exists, but the value doesn't.
	*--------------------------------------------------------------------------------------
	Local lcVersion, loBridge
	loBridge = This.DotNet (m.toHost)
	lcVersion = loBridge.InvokeStaticMethod ( ;
		 "Microsoft.Win32.Registry", "GetValue" ;
		,"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\DevDiv\VC\Servicing\14.0\RuntimeMinimum" ;
		,"Version" ;
		,null ;
	)
	lcVersion = Nvl (m.lcVersion, "00.00.00")
	
	*--------------------------------------------------------------------------------------
	* Parse major and minor version
	*--------------------------------------------------------------------------------------
	Local lcMajor, lcMinor
	lcMajor = GetWordNum (m.lcVersion, 1, ".")
	lcMinor = GetWordNum (m.lcVersion, 2, ".")
	
	*--------------------------------------------------------------------------------------
	* Currently we only distinguish between vc2015 and vc2019. For newer runtimes such as
	* VC 2022 we still return vc2019 until a future version of CefSharp actually requires
	* this as a minimum version.
	*--------------------------------------------------------------------------------------
	Local lcVersion
	Do case
	Case Val (m.lcMajor) > 14
		lcVersion = "vc2019"
	Case Val (m.lcMajor) = 14 and Val (m.lcMinor) >= 20
		lcVersion = "vc2019"  && 14.20 is VC 2019 with multiple release up to 14.29.
	Otherwise 
		lcVersion = "vc2015"
	EndCase

Return m.lcVersion

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
	lcPath = Addbs (This.GetCefSharpPath (m.toHost))
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
		loBridge.InvokeMethod (m.loChromium, "Load", m.tcAddress)
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
	Local loCefSettings, loCefCommandLineArgs, lcPath
	If m.lcVersion == "cef-bin-v65"
		loCefSettings = toBridge.CreateInstance("CefSharp.CefSettings")
		lcPath = Addbs (This.GetCefSharpPath ())
		loCefSettings.ResourcesDirPath = m.lcPath
		loCefSettings.BrowserSubprocessPath = m.lcPath + "CefSharp.BrowserSubprocess.exe"
	Else
		loCefSettings = toBridge.CreateInstance("CefSharp.WinForms.CefSettings")
		This.CheckDpiAwareness (m.toBridge, m.loCefSettings)
	EndIf
	This.RegisterSchemaHandlers (m.toBridge, m.loCefSettings)
	This.SetLanguage (m.toBridge, m.loCefSettings)
	loCefCommandLineArgs = toBridge.GetProperty(loCefSettings, "CefCommandLineArgs")
	loCefCommandLineArgs = This.UnWrapType (m.toBridge, m.loCefCommandLineArgs)
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
* VFP9 is not DPI aware as aren't most VFP applications. Therefore Windows runs them
* sandboxed pretending that the resolution is lower than it actually is and scaling
* everything accordingly.
*
* CefSharp uses an out-of-process application for rendering and GPU activities. These
* have to match the settings of our own process. Because DPI awareness is configured
* through an application manifest that is embedded into the EXE, we created a copy of
* the CefSharp.BrowserSubProcess.EXE. Currently we distiguish two situations:
*
* VFP is not DPI aware (shown in Task Manager as "unaware"). We use our DPI unware
* implementation of the BrowserSubProcess.
*
* VFP is DPI aware. Regardless of whether that is System, per Monitor or per Monitor v2, 
* we always use the default option provided by CefSharp.
*
* If you change DPI awareness in your application programmatically, you have to do so
* before calling fpCefSharp.
*========================================================================================
Procedure CheckDpiAwareness (toBridge, toSettings)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toBridge) == T_OBJECT
		Assert Vartype (m.toSettings) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* If this process is DPI aware, we use the default
	*--------------------------------------------------------------------------------------
	DECLARE long IsProcessDPIAware IN Win32Api 
	If isProcessDPIAware () != 0
		Return
	EndIf
	
	*--------------------------------------------------------------------------------------
	* If we don't have a DPI unware sub process, we can't do anything either. This could
	* happen when older releases of CefSharp are mixed with later releases of fpCefSharp.
	*--------------------------------------------------------------------------------------
	Local lcPath, lcExe
	lcPath = This.GetCefSharpPath ()
	lcExe = Addbs (m.lcPath) + "CefSharp.BrowserSubprocess.dpiunaware.exe"
	If Empty (Sys (2000, m.lcExe))
		Return
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Otherwise we use the DPI unaware process.
	*--------------------------------------------------------------------------------------
	toBridge.SetProperty (m.toSettings, "BrowserSubprocessPath", m.lcExe)
	
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
	*
	* (...) Security issue: Make sure that tcMethod is a valid name and a valid name only.
	* (...)                 Adding extra characters might invoke arbitrary code.
	*--------------------------------------------------------------------------------------
	toHandler.&tcMethod (m.loData, m.lcQuery, m.lcBody)
	
	*--------------------------------------------------------------------------------------
	* Write the response into a stream. We assume that the response is a text document that
	* can be encoded in UTF-8. We must not convert this document in VFP, because the COM
	* interface automatically converts parameters. We pass a VFP string in the current
	* ANSI code page and VFP handles to the conversion to Unicode.
	*--------------------------------------------------------------------------------------
	Local loStream
	Do case 
	CASE EMPTY(m.loData.Response)
		loStream = null
	Case Vartype (m.loData.Response) == T_CHARACTER
		loStream = loBridge.InvokeStaticMethod ("CefSharp.ResourceHandler" ;
			,"GetMemoryStream" ;
			,m.loData.Response ;
			,loBridge.GetEnumValue ("System.Text.Encoding.UTF8") ;
			,.T. ;
		)
	Case Vartype (m.loData.Response) == T_VARBINARY
		loStream = loBridge.CreateInstance ("System.IO.MemoryStream", m.loData.Response)
	OTHERWISE
		loStream = null
	EndCase
	
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
	*
	* (...) Security issue: We should not allow access for any property that we accept
	* (...)                 for other purposes, such as Routes.
	*
	* (...) Security issue: Make sure that lcProperty is a valid name and a valid name 
	* (...)                 only. Adding extra characters might invoke arbitrary code.
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
*=========================================================================================
PROCEDURE Reload

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (this.oChromium) = T_OBJECT
	#ENDIF	

	*--------------------------------------------------------------------------------------
	* Get a .NET bridge for the form's AppDomain
	*--------------------------------------------------------------------------------------
	Local loBridge as wwdotnetbridge of wwdotnetbridge.prg
	loBridge = This.DotNet ()

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
	* If we have any event subscription, we unsubcribe from all of them.
	*--------------------------------------------------------------------------------------
	Local loSubscription
	If Vartype (This.oSubscriptions) == T_OBJECT
		For each loSubscription in This.oSubscriptions
			If Vartype (m.loSubscription) == T_OBJECT
				loSubscription.UnSubscribe ()
			EndIf
		EndFor
	EndIf

	*--------------------------------------------------------------------------------------
	* If we don't unregister our handler for a browser window, we would hold onto it
	* until the application shuts down.
	*--------------------------------------------------------------------------------------
	Local loBridge, loBrowser
	loBridge = This.DotNet ()
	If loBridge.GetProperty (This.oChromium, "IsBrowserInitialized")
		loBrowser = loBridge.InvokeMethod (This.oChromium, "GetBrowser")
		loBridge.InvokeStaticMethod ( ;
			 "fpCefSharp.fpSchemeHandlerFactory" ;
			,"UnregisterCallback" ;
			,m.loBrowser ;
		)
	EndIf	
	
	*--------------------------------------------------------------------------------------
	* Clear references
	*--------------------------------------------------------------------------------------
	This.oChromium = null	
	This.oConfig = null
	This.oDotNetBridge = null

*========================================================================================
* Executes JavaScript and returns the result
*========================================================================================
Function EvaluateScript (tcScript)

	*--------------------------------------------------------------------------------------
	* Assertions 
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.tcScript) == T_CHARACTER
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* We execute JavaScript on the main frame.
	*--------------------------------------------------------------------------------------
	Local loBridge, loBrowser, loFrame
	loBridge = This.DotNet ()
	If loBridge.GetProperty (This.oChromium, "IsBrowserInitialized")
		loBrowser = loBridge.InvokeMethod (This.oChromium, "GetBrowser")
		loFrame = loBridge.GetProperty (m.loBrowser, "MainFrame")
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Execute the script and wait for the result
	* 
	* Task<JavascriptResponse> EvaluateScriptAsync(
	*   string script, string scriptUrl = "about:blank", 
	*   int startLine = 1, TimeSpan? timeout = null, 
	*   bool useImmediatelyInvokedFuncExpression = false);
	*--------------------------------------------------------------------------------------
	Local loTask, loResponse, luResult
	loTask = loBridge.InvokeMethod (m.loFrame, "EvaluateScriptAsync" ;
		,m.tcScript ;
		,"about:blank" ;
		,1 ;
		,null ;
		,.F. ;
	)
	If Vartype (m.loTask) == T_OBJECT
		loResponse = loBridge.GetProperty (m.loTask, "Result")
		luResult = loBridge.GetProperty (m.loResponse, "Result")
	Else
		luResult = null
	EndIf
	
Return m.luResult

*========================================================================================
* Navigates the browser to a specified Url. To display a blank page call this method
* with "about:blank" as the Url.
*========================================================================================
Procedure Navigate (tcUrl)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.tcUrl) == T_CHARACTER
		Assert not Empty (m.tcUrl)
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Load is the equivialent of Navigate in the Microsoft WebBrowser control.
	*--------------------------------------------------------------------------------------
	Local loBridge
	loBridge = This.DotNet ()
	If loBridge.GetProperty (This.oChromium, "IsBrowserInitialized")
		loBridge.InvokeMethod (This.oChromium, "Load", m.tcUrl)
	EndIf	

*========================================================================================
* Provide an object that implements one or more events of the ChromiumWebBrowser class:
* 
* https://cefsharp.github.io/api/105.3.x/html/ 
*       Events_T_CefSharp_Wpf_ChromiumWebBrowser.htm
*
* If you use Rick Strahl's version of wwDotNetBridge, you have to implement all events 
* for this class. The version from the fpCefSharp release package is a specfial version
* that only requires you to implement those events you are interested in.
*
* Every event is named OnXxx where Xxx is the .NET event name according to the 
* documentation given earlier. All event handlers receive .NET objects that match the
* description. For certain events you can pass them to fpCefSharps HandleXxxEvent method
* which simplifies the usage of the event according to the specific description.
*
* You can call this method multiple times for different objects, if you implement 
* your event handler in different places or for different purposes. 
*========================================================================================
Procedure HandleEvents (toEvents)

	*--------------------------------------------------------------------------------------
	* Assertions 
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toEvents) == T_OBJECT		
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Subscribe to these events
	*--------------------------------------------------------------------------------------
	Local loBridge, loSubscription
	loBridge = This.DotNet ()
	loSubscription = This.Bridge_SubscribeToEvents (m.loBridge, This.oChromium, m.toEvents)

	*--------------------------------------------------------------------------------------
	* We maintain a collection of all subscriptions, so that we can unsubscribe from all
	* of them when we release resources.
	*--------------------------------------------------------------------------------------
	If Vartype (This.oSubscriptions) != T_OBJECT
		This.oSubscriptions = CreateObject ("Collection")
	EndIf
	This.oSubscriptions.Add (m.loSubscription)

*========================================================================================
* Handles the TitleChanged event. The event is raised whenever the browsers title 
* changes. This could happen when:
*
* The browser navigates to a new page. The title value in the HTML document or the url
* is the title value.
*
* The window.title property is set in JavaScript code.
*
* This method calls the TitleChangedEvent method in the config object passing the 
* new title as a parameter
*========================================================================================
Procedure HandleTitleChangedEvent (toSender, toEventArgs)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toSender) == T_OBJECT
		Assert Vartype (m.toEventArgs) == T_OBJECT
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Retrieve title
	*--------------------------------------------------------------------------------------
	Local loBridge, lcTitle
	loBridge = This.DotNet ()
	lcTitle = loBridge.GetProperty (m.toEventArgs, "Title")
	
	*--------------------------------------------------------------------------------------
	* Call the config object
	*--------------------------------------------------------------------------------------
	This.oConfig.TitleChangedEvent (m.lcTitle)
	
*========================================================================================
* wwDotNetBridge wraps certain return values in a ComArray.
*========================================================================================
Procedure UnWrapType (toBridge, toObject)

	*--------------------------------------------------------------------------------------
	* Assertions
	*--------------------------------------------------------------------------------------
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.toBridge) == T_OBJECT
		Assert Vartype (m.toObject) $ T_OBJECT + T_NULL
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Check for null values here so that we don't have to check them on every call.
	*--------------------------------------------------------------------------------------
	If IsNull (m.toObject)
		Return m.toObject
	EndIf
	
	*--------------------------------------------------------------------------------------
	* Check if .NET Bridge wrapped the native object with a ComArray.
	*--------------------------------------------------------------------------------------
	Local loType, lcName, loUnwrapped
	loType = m.toObject.GetType ()
	lcName = toBridge.GetProperty (m.loType, "FullName")
	If m.lcName == "Westwind.WebConnection.ComArray"
		loUnwrapped = m.toObject.Instance
	Else
		loUnwrapped = m.toObject
	EndIf

Return m.loUnwrapped

*========================================================================================
* The following methods are modified versions of the ones found in Rick Strahl's 
* wwDotNetBridge. They are here as a work around until pull request #26 has been merged.
*
* The following changes have been made to this code:
*
*  - Changed the name of the EventSubscription class to fpCefSharp_EventSubscription
*
*  - Pass in the reference to the wwDotNetBridge instance to replace "this".
*
*  - Changed the name and the visibility of the SubscribeToEvents method.
*
*========================================================================================

************************************************************************
*  SubscribeToEvents
****************************************
***  Function: Handles all events of a source object for subsequent retrieval by calling WaitForEvent.
***  loSource: The object for which to subscribe to events.
***  loHandler: An object with a method OnEvent(loEventName, loParams).
***  lcPrefix: The initial part of the event handler function for each event. Defaults to "On".
***    Return: A subscription object. The subscription ends when this object goes out of scope.
************************************************************************
Protected FUNCTION Bridge_SubscribeToEvents(toBridge, loSource, loHandler, lcPrefix)
IF EMPTY(lcPrefix)
	lcPrefix = "On"
ENDIF
LOCAL loSubscription
loSubscription = CREATEOBJECT("fpCefSharp_EventSubscription")
loSubscription.Setup(m.toBridge, loSource, loHandler, lcPrefix)
RETURN loSubscription
ENDFUNC
*   SubscribeToEvents

EndDefine


*========================================================================================
* This class is a work around for a wwDotNetBridge limitation. wwDotNetBridge only works
* if you implement all events which can have unintended side effects and introduce bugs.
*
* https://github.com/RickStrahl/wwDotnetBridge/pull/26
*
* We can remove this work around if the above pull request is ever accepted by Rick 
* Strahl. For now we implement our own implementation of the subscriber class that uses
* the Subscribtion object in fpCefSharp rather than wwDotNetBrisge.
*
* This class is based on Edward Brey's contribution to wwDotNetBridge
* (https://github.com/breyed). This code relies on other classes implemented in 
* wwDotNetBridge. Therefore wwDotNetBridge must be loaded, before this class can be
* instantiated.
* 
* The following changes were made to Edward's code:
*
*   - Changed the name of the class to avoid conflicts with wwDotNetBridge
*
*   - Changed the name of the .NET EventSubscriber class to the one implemented in
*     fpCefSharp.dll
*
*   - All changes made in pull request #26 for wwDotNetBridge to implement an extra
*     check which methods actually exist.
*
*========================================================================================
DEFINE CLASS fpCefSharp_EventSubscription as AsyncCallbackEvents of wwdotnetbridge.prg
*************************************************************
*:  Author: Edward Brey  - https://github.com/breyed
*:  Usage: Used internally by SubscribeToEvents
************************************************************
HIDDEN oBridge, oHandler, oSubscriber, oPrefix

oBridge = null
oHandler = null
oPrefix = null
oSubscriber = null

************************************************************************
*  Setup
****************************************
***  Function: Sets up an event subscription. 
***    Assume:
***      Pass: loBridge   - dnb instance
***            loSource   - Source Object fires events
***            loHandler  - Target Object that handles events
***            lcPrefix   - prefix for event methods
***                         implemented on target (defaults to "On")
************************************************************************
FUNCTION Setup(loBridge, loSource, loHandler, lcPrefix)
this.oBridge = loBridge
this.oHandler = loHandler
this.oPrefix = lcPrefix
Private handler
handler = m.loHandler
this.oSubscriber = loBridge.CreateInstance("fpCefSharp.fpEventSubscriber", loSource, m.lcPrefix, _Vfp)
this.HandleNextEvent()
ENDFUNC

************************************************************************
*  UnSubscribe
****************************************
***  Function: Unsubscribes events that are currently subscribed to
************************************************************************
FUNCTION UnSubscribe()
IF !ISNULL(THIS.oSubscriber)
	this.oSubscriber.Dispose()
ENDIF
ENDFUNC
 
  
FUNCTION HandleNextEvent()
this.oBridge.InvokeMethodAsync(this,this.oSubscriber,"WaitForEvent")
ENDFUNC

************************************************************************
*  OnComplete
****************************************
***  Function: Event Proxy that forwards the event to a function 
***            named On{Event} with event's parameters.
************************************************************************
FUNCTION OnCompleted(lvResult, lcMethod)
LOCAL loParams,lParamText,lCount

IF ISNULL(lvResult) && If the call to WaitForEvent was canceled:
	RETURN
ENDIF


loParams=CREATEOBJECT("EMPTY") && Workaround to index into array of parameters. 
lParamText = ""
IF NOT ISNULL(lvResult.Params)
	lCount = 0
	FOR EACH lParam IN lvResult.Params
		lCount = lCount + 1
		AddProperty(loParams,"P" + ALLTRIM(STR(lCount)),lParam)
		lParamText = lParamText + ",loParams.P" + ALLTRIM(STR(lCount))
	ENDFOR
ENDIF

IF VARTYPE(THIS.oHandler) = "O"
	=EVALUATE("this.oHandler." + this.oPrefix + lvResult.Name + "("+SUBSTR(lParamText,2)+")")
	this.HandleNextEvent()
ENDIF

ENDFUNC

ENDDEFINE