*========================================================================================
* Creating your own protocol...
*========================================================================================

	#include Acodey.h

	*--------------------------------------------------------------------------------------
	* Create a factory instance. cefBrowser calls the factory to create a new handler
	* instance. This is a special implementation that calls the OnProcessRequest method.
	*--------------------------------------------------------------------------------------
	Local loFactory
	loFactory = toBridge.CreateInstance ("fpDotNet.fpCefSharp.fpSchemeHandlerFactory")
	#IF __DEBUGLEVEL >= __DEBUG_REGULAR
		Assert Vartype (m.loFactory) == T_OBJECT
	#ENDIF

	*--------------------------------------------------------------------------------------
	* Create a new protocol (scheme)
	*--------------------------------------------------------------------------------------
	Local loScheme
	loScheme = toBridge.CreateInstance ("CefSharp.CefCustomScheme")
	loScheme.SchemeName = "app"
	toBridge.SetProperty (m.loScheme, "SchemeHandlerFactory", m.loFactory)
	toBridge.InvokeMethod (m.toSettings, "RegisterScheme", m.loScheme)
