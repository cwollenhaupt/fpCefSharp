using System.Threading.Tasks;
using CefSharp;

namespace fpCefSharp
{
    internal class fpHandler : ResourceHandler
    {
        readonly fpCallback Handler;

        public fpHandler(fpCallback handler)
        {
            Handler = handler;
        }

        /// <summary>
        ///  Process request and craft response.
        /// </summary>
        /// <param name="request">the request object from CefSharp</param>
        /// <param name="callback">the object we call when we are done with processing</param>
        /// <returns></returns>
        public override CefReturnValue ProcessRequestAsync(IRequest request, ICallback callback)
        {
            Task.Run(() =>
            {
                using (callback)
                {
                    Handler.OnProcessRequest(this, request);
                    callback.Continue();
                }
            });

        return CefReturnValue.ContinueAsync;
        }
    }
}