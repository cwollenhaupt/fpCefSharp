using System;
using System.Collections.Generic;
using CefSharp;

namespace fpCefSharp
{
    public class fpSchemeHandlerFactory : ISchemeHandlerFactory
    {
        public fpSchemeHandlerFactory() { }

        static readonly Dictionary<Int32, fpCallback> RegisteredClients = new Dictionary<Int32, fpCallback>();

        public static void RegisterCallback(IBrowser browser, Object callback)
        {
            var handler = new fpCallback(callback);
            RegisteredClients.Add(browser.Identifier, handler);
        }

        public static void UnregisterCallback(IBrowser browser)
        {
            if (RegisteredClients.ContainsKey(browser.Identifier))
                RegisteredClients.Remove(browser.Identifier);
        }

        public IResourceHandler Create(IBrowser browser, IFrame frame, string schemeName, IRequest request)
        {
            if (RegisteredClients.ContainsKey(browser.Identifier))
            {
                var callback = RegisteredClients[browser.Identifier];
                return new fpHandler(callback);
            }

            return null;
        }
    }
}