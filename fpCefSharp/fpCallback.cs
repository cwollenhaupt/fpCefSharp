using System;
using CefSharp;

namespace fpCefSharp
{
    public class fpCallback
    {
        /// <summary>
        /// Instance of a cefSharpBrowser class from cefSharpBrowser.prg.
        /// Each instance is bound to once IBrowser instance.
        /// </summary>
        readonly dynamic VfpHandler;

        public fpCallback(Object callback)
        {
            if (callback == null) 
                throw new ArgumentNullException(nameof(callback));

            VfpHandler = callback;
        }

        public void OnProcessRequest(ResourceHandler resourceHandler, IRequest request)
        {
            VfpHandler.OnProcessRequest(resourceHandler, request);
        }
    }
}