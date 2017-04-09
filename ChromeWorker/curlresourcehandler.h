#ifndef CURLRESOURCEHANDLER_H
#define CURLRESOURCEHANDLER_H

#include "include/cef_app.h"
#include "browserdata.h"
#include "postmanager.h"
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <vector>
#include <curl/curl.h>
#include "refcountpublic.h"

class CurlResourceHandler : public CefResourceHandler
{
public:
    class CurlThreadDataClass
    {
        public:
            /* Defs */
            enum StatusClass{NotStarted,Running,HeadersParsed,Done};

            /* Outputs */
            /* If you want to access any of this, need to lock ResponseDataMutex */
            std::vector<char> ResponseData;
            int ResponseDataReadLength = 0;
            std::mutex ResponseDataMutex;


            /* If you want to access any of this, need to lock ResultHeadersMutex */
            std::multimap<std::string,std::string> ResultHeaders;
            int ResponceStatusId = 200;
            std::string ResponceStatusText;
            std::string MimeType = "text/html";
            std::string RedirectUrl;
            int ContentLength = -1;
            std::string ContentType;
            bool LastHeaderClear = false;
            bool AllHeaderParsed = false;
            std::mutex ResultHeadersMutex;

            std::atomic<CURLcode> Result = (CURLcode)-1;

            /* Inputs */
            /* Inputs are not protected, because set only one time before thread start */
            std::atomic_bool ForceUtf8 = true;
            std::atomic_bool ProxiesReconnect = false;
            std::string Url;
            std::string Method;
            std::string Referrer;
            std::map<std::string,std::string> RequestHeaders;
            //std::vector<char> PostData;
            bool IsPostData = false;
            PostParts _PostParts;
            PostManager *_PostManager;
            std::string Proxy;
            std::string ProxyAuth;
            std::string HttpAuthLogin;
            std::string HttpAuthPassword;
            std::vector<std::string> HeadersOrder;

            /* Sync */
            std::atomic_bool StopRequest = false;
            std::atomic_bool NeedToReadWholeResponceAndThanFixEncoding = false;
            std::atomic_bool FixEncodingDone = false;
        private:
            std::atomic<StatusClass> Status = NotStarted;

        public:
            StatusClass GetStatus(){return Status;}
            void SetStatus(StatusClass Status){this->Status = Status;}

    };
private:
    std::shared_ptr<std::thread> CurlThread;
    CefRefPtr<CefCallback> ProcessRequestCallback;
    bool CanUseProcessRequestCallback = false;
    CefRefPtr<CefCallback> ReadResponseCallback;
    bool CanUseReadResponseCallback = false;

    CurlThreadDataClass CurlThreadData;

    BrowserData * _BrowserData;
    PostManager * _PostManager;

    bool CanDelete = false;
    int IteratorWaitAfterDelete = 10;
    int64 StartTime;
    int TabNumber = -1;
public:



    CurlResourceHandler(BrowserData * _BrowserData, PostManager *_PostManager);

    int64 GetStartTime();
    //~CurlResourceHandler();
    void Join();
    bool GetCanDelete();
    void SetForceUtf8(bool ForceUtf8);
    void SetProxiesReconnect(bool ProxiesReconnect);
    void SetTabNumber(int TabNumber);

    void Timer();

    ///
    // Begin processing the request. To handle the request return true and call
    // CefCallback::Continue() once the response header information is available
    // (CefCallback::Continue() can also be called from inside this method if
    // header information is available immediately). To cancel the request return
    // false.
    ///
    /*--cef()--*/
    virtual bool ProcessRequest(CefRefPtr<CefRequest> request,
                                CefRefPtr<CefCallback> callback);

    ///
    // Retrieve response header information. If the response length is not known
    // set |response_length| to -1 and ReadResponse() will be called until it
    // returns false. If the response length is known set |response_length|
    // to a positive value and ReadResponse() will be called until it returns
    // false or the specified number of bytes have been read. Use the |response|
    // object to set the mime type, http status code and other optional header
    // values. To redirect the request to a new URL set |redirectUrl| to the new
    // URL.
    ///
    /*--cef()--*/
    virtual void GetResponseHeaders(CefRefPtr<CefResponse> response,
                                    int64& response_length,
                                    CefString& redirectUrl);

    ///
    // Read response data. If data is available immediately copy up to
    // |bytes_to_read| bytes into |data_out|, set |bytes_read| to the number of
    // bytes copied, and return true. To read the data at a later time set
    // |bytes_read| to 0, return true and call CefCallback::Continue() when the
    // data is available. To indicate response completion return false.
    ///
    /*--cef()--*/
    virtual bool ReadResponse(void* data_out,
                              int bytes_to_read,
                              int& bytes_read,
                              CefRefPtr<CefCallback> callback);



    ///
    // Request processing has been canceled.
    ///
    /*--cef()--*/
    virtual void Cancel();

private:
    IMPLEMENT_REFCOUNTING_PUBLIC(CurlResourceHandler);

};

#endif // CURLRESOURCEHANDLER_H
