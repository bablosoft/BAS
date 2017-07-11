#include "curlresourcehandler.h"
#include "log.h"
#include "trim.h"
#include "split.h"
#include "startwith.h"
#include "readallfile.h"
#include "match.h"
#include "processlocation.h"
#include "multithreading.h"
#include "fixpagecontent.h"
#include <chrono>
#include <algorithm>
#include <iterator>
#include <regex>
#include "base64.h"
#include "startwith.h"

using namespace std::chrono;


void ParseHeaders(CurlResourceHandler::CurlThreadDataClass * Data)
{
    std::lock_guard<std::mutex> lock(Data->ResultHeadersMutex);

    if(Data->AllHeaderParsed)
        return;

    /* All headers parsed. */
    std::string ContentTypeHeader = "Content-Type";
    if(Data->ResultHeaders.count("content-type") > 0)
        ContentTypeHeader = "content-type";

    if(Data->ResultHeaders.count(ContentTypeHeader) > 0)
    {
        Data->MimeType = Data->ResultHeaders.find(ContentTypeHeader)->second;
        Data->ContentType = Data->MimeType;
        if(Data->ForceUtf8)
            Data->NeedToReadWholeResponceAndThanFixEncoding = FixPageContent().NeedToFix(Data->ContentType,Data->Url);
        std::vector<std::string> MimeTypeSplit = split(Data->MimeType,';');
        if(MimeTypeSplit.size() > 1)
            Data->MimeType = trim(MimeTypeSplit[0]);
    }


    std::string LocationHeader = "Location";
    if(Data->ResultHeaders.count("location") > 0)
        LocationHeader = "location";

    if(Data->ResultHeaders.count(LocationHeader) > 0)
        Data->RedirectUrl = Data->ResultHeaders.find(LocationHeader)->second;

    Data->ResultHeaders.erase("content-security-policy");
    Data->ResultHeaders.erase("Content-Security-Policy");

    std::multimap<std::string,std::string> NewResultHeaders;
    for(auto it:Data->ResultHeaders)
    {
        std::string key = it.first;
        std::string val = it.second;
        if(key == "Set-Cookie" || key == "set-cookie" )
        {
            try{
                static std::regex SameSiteRegexp(";\\s*[Ss]ame[Ss]ite\\s*\\=\\s*(Lax|lax|Strict|strict)");
                val = std::regex_replace (val,SameSiteRegexp,"");
            }catch(...)
            {
                val = it.second;
            }
        }
        NewResultHeaders.insert(std::pair<std::string,std::string>(key,val));
    }
    Data->ResultHeaders = NewResultHeaders;

    std::string ContentLengthHeader = "Content-Length";
    if(Data->ResultHeaders.count("content-length") > 0)
        ContentLengthHeader = "content-length";
    if(Data->ResultHeaders.count(ContentLengthHeader) > 0)
    {
        std::string ContentLength = Data->ResultHeaders.find(ContentLengthHeader)->second;
        if(ContentLength.empty())
        {
            try
            {
                Data->ContentLength = std::stoi(ContentLength);
            }catch(...)
            {
                Data->ContentLength = -1;
            }
        }
    }

    Data->AllHeaderParsed = true;
    if(Data->GetStatus() == CurlResourceHandler::CurlThreadDataClass::Running)
        Data->SetStatus(CurlResourceHandler::CurlThreadDataClass::HeadersParsed);

}

size_t CurlWriteMemoryCallback(char *data, size_t size, size_t nmemb, void *userp)
{
    int result = 0;

    CurlResourceHandler::CurlThreadDataClass * Data = (CurlResourceHandler::CurlThreadDataClass*)userp;

    ParseHeaders(Data);

    if (data != 0)
    {
        {
            std::lock_guard<std::mutex> lock(Data->ResponseDataMutex);
            Data->ResponseData.insert(Data->ResponseData.end(), data, data + size * nmemb);
        }
        result = size * nmemb;
    }


    return result;
}

size_t CurlProgressCallback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
    CurlResourceHandler::CurlThreadDataClass * Data = (CurlResourceHandler::CurlThreadDataClass*)clientp;
    return Data->StopRequest;
}

size_t CurlWriteHeaderCallback(char *data, size_t size, size_t nmemb, void *userp)
{
    int result = 0;

    CurlResourceHandler::CurlThreadDataClass * Data = (CurlResourceHandler::CurlThreadDataClass*)userp;
    std::string header(data,size * nmemb);
    //WORKER_LOG("QQHEADER :" + header);
    {
        std::lock_guard<std::mutex> lock(Data->ResultHeadersMutex);
        if(Data->LastHeaderClear)
        {
            /* Need only final header */
            Data->ResultHeaders.clear();
            Data->ResponceStatusId = 200;
            Data->ResponceStatusText.clear();
            Data->MimeType = "text/html";
            Data->RedirectUrl.clear();
            Data->LastHeaderClear = false;
        }
    }


    std::size_t found = header.find(":");
    if (found != std::string::npos && found > 0 && header.length() - found - 1 > 0)
    {
        std::lock_guard<std::mutex> lock(Data->ResultHeadersMutex);
        Data->ResultHeaders.insert(std::pair<std::string,std::string>(header.substr(0,found),trim(header.substr(found + 1,header.length() - found - 1))));
    }else
    {
        std::string http("HTTP");
        if(trim(header).empty())
        {
            std::lock_guard<std::mutex> lock(Data->ResultHeadersMutex);
            Data->LastHeaderClear = true;
        }else if(header.compare(0, http.length(), http) == 0)
        {
            /* Initial header */
            std::lock_guard<std::mutex> lock(Data->ResultHeadersMutex);
            std::vector<std::string> HeaderSplit = split(header, ' ');
            if(HeaderSplit.size() >= 2)
            {
                std::string ResponceStatusId = HeaderSplit[1];
                if(!ResponceStatusId.empty())
                {
                    try
                    {
                        Data->ResponceStatusId = std::stoi(ResponceStatusId);
                    }catch(...)
                    {
                        Data->ResponceStatusId = 200;
                    }
                }
            }

            if(HeaderSplit.size() >= 3)
            {
                Data->ResponceStatusText = HeaderSplit[2];
            }
        }


    }
    result = size * nmemb;

    return result;
}


void CurlThreadFunction(CurlResourceHandler::CurlThreadDataClass * Data)
{



    //Run
    Data->SetStatus(CurlResourceHandler::CurlThreadDataClass::Running);
    clock_t begin_time = clock();

    bool PostDataPrepared = false;
    std::vector<char> PostData;


    while(true)
    {
        NETWORK_LOG(std::string("\n>>>> ") + Data->Method + std::string(" ") + Data->Url);

        /* Prepare */
        CURL *curl_handle = curl_easy_init();
        curl_easy_setopt(curl_handle, CURLOPT_URL, Data->Url.c_str());
        curl_easy_setopt(curl_handle,CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl_handle,CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, CurlWriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)Data);

        curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, CurlWriteHeaderCallback);
        curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, (void *)Data);

        curl_easy_setopt(curl_handle,CURLOPT_TIMEOUT, 1500L);

        curl_easy_setopt(curl_handle,CURLOPT_PROGRESSFUNCTION, CurlProgressCallback);
        curl_easy_setopt(curl_handle,CURLOPT_PROGRESSDATA,(void *)Data);
        curl_easy_setopt(curl_handle,CURLOPT_NOPROGRESS,0L);

        if(Data->Proxy.empty())
        {
            curl_easy_setopt(curl_handle,CURLOPT_PROXY,"");
        }else
        {
            curl_easy_setopt(curl_handle,CURLOPT_PROXY,Data->Proxy.c_str());
            if(!Data->ProxyAuth.empty())
                curl_easy_setopt(curl_handle,CURLOPT_PROXYUSERPWD,Data->ProxyAuth.c_str());
        }

        if(!Data->HttpAuthLogin.empty() && !Data->HttpAuthPassword.empty())
        {
            curl_easy_setopt(curl_handle,CURLOPT_USERNAME,Data->HttpAuthLogin.c_str());
            curl_easy_setopt(curl_handle,CURLOPT_PASSWORD,Data->HttpAuthPassword.c_str());
        }

        /*if(write_logs)
        {
            curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
            curl_easy_setopt(curl_handle, CURLOPT_DEBUGFUNCTION, CurlTraceCallback);
            curl_easy_setopt(curl_handle, CURLOPT_DEBUGDATA, (void *)Data);

        }*/

        std::vector<std::pair<std::string,std::string> > Headers;

        std::string Referer = Data->Referrer;
        bool EmptyContentType = true;
        for (const auto& Header : Data->RequestHeaders)
        {
            if(Header.first == "Referer")
            {
                Referer = Header.second;
                continue;
            }
            if(Header.first == "Content-Type")
            {
                EmptyContentType = false;
            }

            NETWORK_LOG(std::string("> ") + Header.first + std::string("=") + Header.second);

            if(Header.first != "X-DevTools-Emulate-Network-Conditions-Client-Id")
            {
                Headers.push_back(Header);
            }
        }

        {
            std::pair<std::string,std::string> p;p.first = "Connection";p.second = "keep-alive";Headers.push_back(p);
        }
        {
            std::pair<std::string,std::string> p;p.first = "Accept-Encoding";p.second = "gzip, deflate";Headers.push_back(p);
        }

        curl_easy_setopt(curl_handle, CURLOPT_ACCEPT_ENCODING,"gzip, deflate");

        if(!Referer.empty())
        {
            NETWORK_LOG(std::string("> Referer=") + Referer);
            std::pair<std::string,std::string> p;p.first = "Referer";p.second = Referer;Headers.push_back(p);
        }

        //Generate headers list

        struct curl_slist *headers = NULL;

        for(std::string HeaderOrdered: Data->HeadersOrder)
        {

            std::string Found;
            std::string FoundValue;
            for (std::vector<std::pair<std::string,std::string> >::iterator it=Headers.begin(); it!=Headers.end(); )
            {
                if(it->first == HeaderOrdered)
                {
                    Found = HeaderOrdered;
                    FoundValue = it->second;
                    it = Headers.erase(it);
                    break;
                }else
                    ++it;
             }

            if(!Found.empty())
            {

                std::string h = Found + std::string(": ") + FoundValue;
                headers = curl_slist_append(headers, h.c_str());

            }
        }

        for(std::pair<std::string,std::string> Header: Headers)
        {
            std::string h = Header.first + std::string(": ") + Header.second;
            headers = curl_slist_append(headers, h.c_str());
        }

        if(EmptyContentType)
            headers = curl_slist_append(headers, "Content-Type:");

        headers = curl_slist_append(headers, "Expect:");

        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

        //Prepare post data

        if(!PostDataPrepared)
        {
            if(Data->IsPostData)
            {
                bool done = false;
                for(int i = 0;i<30;i++)
                {
                    done = Data->_PostManager->FinalizePostParts(Data->_PostParts,PostData);
                    if(done)
                        break;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                if(!done)
                    PostData.clear();

                PostDataPrepared = true;
                Data->_PostParts.reset();
            }
        }

        bool postdatawasset = false;

        if(Data->Method == "HEAD")
            curl_easy_setopt(curl_handle, CURLOPT_NOBODY, 1L);
        else if(Data->Method == "POST")
        {
            curl_easy_setopt(curl_handle, CURLOPT_POST, 1L);
            curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, PostData.data());
            curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)PostData.size());
            if(PostData.size() < 3000)
            {
                NETWORK_LOG(std::string("~ ") + std::string(PostData.data(),PostData.size()));
            }
            postdatawasset = true;
        }
        else
            curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, Data->Method.c_str());

        if(!postdatawasset && PostData.size() > 0)
        {
            curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, PostData.data());
            curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)PostData.size());
            if(PostData.size() < 3000)
            {
                NETWORK_LOG(std::string("~ ") + std::string(PostData.data(),PostData.size()));
            }
        }

        /* Clear all */
        {
            std::lock_guard<std::mutex> lock(Data->ResultHeadersMutex);
            Data->ResultHeaders.clear();
            Data->ResponceStatusId = 200;
            Data->ResponceStatusText.clear();
            Data->MimeType = "text/html";
            Data->RedirectUrl.clear();
            Data->ContentLength = -1;
            Data->ContentType.clear();
            Data->LastHeaderClear = false;
            Data->AllHeaderParsed = false;
        }
        {
            std::lock_guard<std::mutex> lock(Data->ResponseDataMutex);
            Data->ResponseData.clear();
            Data->ResponseDataReadLength = 0;
        }

        Data->NeedToReadWholeResponceAndThanFixEncoding = false;
        Data->FixEncodingDone = false;

        WORKER_LOG(std::string("Start request ") + Data->Url);

        Data->Result = curl_easy_perform(curl_handle);

        WORKER_LOG(std::string("Got data ") + std::to_string(Data->Result) + std::string(" ") + Data->Url);
        long total_request_bytes;
        curl_easy_getinfo(curl_handle, CURLINFO_REQUEST_SIZE, &total_request_bytes);

        curl_easy_cleanup(curl_handle);
        curl_slist_free_all(headers);
        CurlResourceHandler::CurlThreadDataClass::StatusClass Status = Data->GetStatus();
        if(
                (
                    Data->Result != CURLE_COULDNT_RESOLVE_PROXY &&
                    Data->Result != CURLE_COULDNT_RESOLVE_HOST &&
                    Data->Result != CURLE_COULDNT_CONNECT &&
                    //Data->Result != CURLE_SEND_ERROR &&
                    //Data->Result != CURLE_RECV_ERROR &&

                    //Data->Result != CURLE_HTTP_POST_ERROR &&
                    Data->Result != CURLE_SSL_CONNECT_ERROR

                    //Data->Result == CURLE_OK
                    //total_request_bytes > 0
                    ) || float( clock() - begin_time ) /  CLOCKS_PER_SEC > 360
                    || Data->StopRequest || Status == CurlResourceHandler::CurlThreadDataClass::HeadersParsed || Status == CurlResourceHandler::CurlThreadDataClass::Done
                    || (!Data->ProxiesReconnect)
                )
        {
            WORKER_LOG(std::string("Break ") + std::to_string(Data->Result)+ std::string(" ") + Data->Url + std::string(" ") + std::to_string(float( clock() - begin_time ) /  CLOCKS_PER_SEC));

            break;
        }

        WORKER_LOG(std::string("Retry ") + std::to_string(Data->Result)+ std::string(" ") + Data->Url);

        /* Retry */
        for(int i = 0;i<5;i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if(Data->StopRequest)
            {
                break;
            }
        }

    }
    ParseHeaders(Data);
    //WORKER_LOG(std::string("Curl Result Status: ") + std::to_string(Data->Result));
    //WORKER_LOG(std::string("Request time : ") + std::to_string(float( clock () - begin_time ) /  CLOCKS_PER_SEC));

    //Stats
    /*double val;
    curl_easy_getinfo(curl_handle, CURLINFO_SIZE_DOWNLOAD, &val);
    WORKER_LOG(std::string("Data downloaded: ") + std::to_string(val) + std::string("  bytes."));

    curl_easy_getinfo(curl_handle,  CURLINFO_TOTAL_TIME, &val);
    WORKER_LOG(std::string("Total download time: ") + std::to_string(val) + std::string("  secs."));

    curl_easy_getinfo(curl_handle, CURLINFO_SPEED_DOWNLOAD, &val);
    WORKER_LOG(std::string("Average download speed: ") + std::to_string(val / 1024.0) + std::string("  kbyte/sec."));

    curl_easy_getinfo(curl_handle,  CURLINFO_NAMELOOKUP_TIME, &val);
    WORKER_LOG(std::string("CURLINFO_NAMELOOKUP_TIME: ") + std::to_string(val) + std::string("  sec."));

    curl_easy_getinfo(curl_handle, CURLINFO_CONNECT_TIME, &val);
    WORKER_LOG(std::string("CURLINFO_CONNECT_TIME: ") + std::to_string(val) + std::string("  sec."));

    curl_easy_getinfo(curl_handle, CURLINFO_PRETRANSFER_TIME, &val);
    WORKER_LOG(std::string("CURLINFO_PRETRANSFER_TIME: ") + std::to_string(val) + std::string("  sec."));

    curl_easy_getinfo(curl_handle, CURLINFO_APPCONNECT_TIME, &val);
    WORKER_LOG(std::string("CURLINFO_APPCONNECT_TIME: ") + std::to_string(val) + std::string("  sec."));

    curl_easy_getinfo(curl_handle, CURLINFO_REDIRECT_TIME, &val);
    WORKER_LOG(std::string("CURLINFO_REDIRECT_TIME: ") + std::to_string(val) + std::string("  sec."));

    curl_easy_getinfo(curl_handle, CURLINFO_STARTTRANSFER_TIME, &val);
    WORKER_LOG(std::string("CURLINFO_STARTTRANSFER_TIME: ") + std::to_string(val) + std::string("  sec."));
    */

    //Clean
    Data->SetStatus(CurlResourceHandler::CurlThreadDataClass::Done);

}




CurlResourceHandler::CurlResourceHandler(BrowserData * _BrowserData, PostManager *_PostManager)
{
    this->_BrowserData = _BrowserData;
    this->StartTime = duration_cast< milliseconds >( system_clock::now().time_since_epoch() ).count();
    this->_PostManager = _PostManager;
}

void CurlResourceHandler::SetTabNumber(int TabNumber)
{
    this->TabNumber = TabNumber;
}

int64 CurlResourceHandler::GetStartTime()
{
    return this->StartTime;
}



bool CurlResourceHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback)
{
    //WORKER_LOG("CurlResourceHandler::ProcessRequest");
    CurlThreadData.Url = request->GetURL().ToString();
    CurlThreadData.Method = request->GetMethod().ToString();
    CurlThreadData.Referrer = request->GetReferrerURL().ToString();
    {
        LOCK_BROWSER_DATA
        ProxyData p = _BrowserData->_Proxy.Match(request->GetURL().ToString(),TabNumber);
        CurlThreadData.Proxy = p.ToString();
        CurlThreadData.ProxyAuth = p.AuthToString();
        CurlThreadData.HeadersOrder = _BrowserData->_HeadersDefaults;
    }

    {
        LOCK_HTTP_AUTH
        CurlThreadData.HttpAuthLogin = _BrowserData->_HttpAuthLogin;
        CurlThreadData.HttpAuthPassword = _BrowserData->_HttpAuthPassword;
    }

    CefRequest::HeaderMap ReqestHeaderMap;
    request->GetHeaderMap(ReqestHeaderMap);

    std::map<std::string,std::string> RequestHeadersNew;

    {
        LOCK_BROWSER_DATA

        for (const auto& Header : ReqestHeaderMap)
        {
            RequestHeadersNew[Header.first] = Header.second;
        }

        for(std::shared_ptr<std::map<std::string,std::string> > Map: _BrowserData->_Headers.MatchAll(request->GetURL().ToString(),TabNumber))
        {
            for(const auto& Header: *Map)
            {
                if(Header.first == "Referer")
                {
                    if(Header.second == "_BAS_NO_REFERRER")
                    {
                        _BrowserData->_NextReferrer = "_BAS_NO_REFERRER";
                        RequestHeadersNew.erase("Referer");
                        CurlThreadData.Referrer.clear();
                    }else
                    {
                        RequestHeadersNew[Header.first] = Header.second;
                        _BrowserData->_NextReferrer = Header.second;
                        CurlThreadData.Referrer = Header.second;
                    }
                }else
                {
                    RequestHeadersNew[Header.first] = Header.second;
                }

            }
        }
    }

    CefRefPtr<CefPostData> PostData = request->GetPostData();
    if(/*request->GetMethod().ToString() == "POST" &&*/ PostData)
    {
        CefPostData::ElementVector Elements;
        PostData->GetElements(Elements);

        PostParts _PostParts = _PostManager->PreparePostParts(Elements);
        CurlThreadData._PostParts = _PostParts;
        CurlThreadData._PostManager = _PostManager;
        CurlThreadData.IsPostData = true;

        /*WORKER_LOG("!!Post Data!!");
        std::string DataString(CurlThreadData.PostData.data(),CurlThreadData.PostData.size());

        WORKER_LOG(DataString);
        WORKER_LOG("!!Post Data End!!");*/

    }else
    {
        CurlThreadData.IsPostData = false;
    }

    CurlThreadData.RequestHeaders = RequestHeadersNew;

    CanUseProcessRequestCallback = true;
    ProcessRequestCallback = callback;

    //CurlThread = std::make_shared<std::thread>(CurlThreadFunction,&CurlThreadData);
    CurlThread = std::make_shared<std::thread>(CurlThreadFunction,&CurlThreadData);

    return true;
}

void CurlResourceHandler::Join()
{
    if(CurlThread)
    {
        Cancel();
        CurlThread->join();
        CurlThread.reset();
    }
}

/*CurlResourceHandler::~CurlResourceHandler()
{
    WORKER_LOG("Deleted");
}*/


bool CurlResourceHandler::GetCanDelete()
{
    return CanDelete && IteratorWaitAfterDelete<=0;
}

void CurlResourceHandler::SetForceUtf8(bool ForceUtf8)
{
    CurlThreadData.ForceUtf8 = ForceUtf8;
}

void CurlResourceHandler::SetProxiesReconnect(bool ProxiesReconnect)
{
    CurlThreadData.ProxiesReconnect = ProxiesReconnect;
}


void CurlResourceHandler::Timer()
{
    _PostManager->Cleanup();

    CurlThreadDataClass::StatusClass Status = CurlThreadData.GetStatus();

    if(_BrowserData->IsReset)
        Cancel();

    if(Status == CurlThreadDataClass::Done)
    {
        Join();
    }

    if(CanDelete)
    {
        IteratorWaitAfterDelete--;
    }

    if(Status == CurlThreadDataClass::Done && this->ref_count_.ref_count_ <= 1 && !CurlThread.get())
    {
        CanDelete = true;
    }



    if(CanUseProcessRequestCallback && (Status == CurlThreadDataClass::HeadersParsed || Status == CurlThreadDataClass::Done))
    {
        if(ProcessRequestCallback)
        {
            CanUseProcessRequestCallback = false;
            ProcessRequestCallback->Continue();
        }
    }

    if(CanUseReadResponseCallback && ReadResponseCallback)
    {
        if(Status == CurlThreadDataClass::Done)
        {
            CanUseReadResponseCallback = false;
            ReadResponseCallback->Continue();

        }else
        {
            bool DoContinue = false;
            {
                std::lock_guard<std::mutex> lock(CurlThreadData.ResponseDataMutex);
                if(CurlThreadData.ResponseDataReadLength < CurlThreadData.ResponseData.size() && !CurlThreadData.NeedToReadWholeResponceAndThanFixEncoding)
                {
                    DoContinue = true;

                }
            }
            if(DoContinue)
            {
                CanUseReadResponseCallback = false;
                ReadResponseCallback->Continue();
            }

        }
    }
}

void CurlResourceHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
{
    NETWORK_LOG(std::string("\n<<<< ") + CurlThreadData.Method + std::string(" ") + CurlThreadData.Url);


    //WORKER_LOG(std::string("CurlResourceHandler::GetResponseHeaders<<"));
    std::lock_guard<std::mutex> lock(CurlThreadData.ResultHeadersMutex);

    /* Headers */
    CefResponse::HeaderMap HeaderMapData;
    for (const auto& Header : CurlThreadData.ResultHeaders)
    {
        //WORKER_LOG(Header.first + std::string(": ") + Header.second);
        HeaderMapData.insert(std::pair<CefString, CefString>(Header.first,Header.second));
        NETWORK_LOG(std::string("< ") + Header.first + std::string("=") + Header.second);

    }
    response->SetHeaderMap(HeaderMapData);

    /* Status Id */

    if(CurlThreadData.Result > 0)
    {
        //WORKER_LOG(std::string("Status Id: ") + std::to_string(404));
        response->SetStatus(404);
    }
    else
    {
        //WORKER_LOG(std::string("Status Id: ") + std::to_string(CurlThreadData.ResponceStatusId));
        response->SetStatus(CurlThreadData.ResponceStatusId);
    }



    /* Status Text */
    //WORKER_LOG(std::string("Status Text: ") + CurlThreadData.ResponceStatusText);
    if(!CurlThreadData.ResponceStatusText.empty())
        response->SetStatusText(CurlThreadData.ResponceStatusText);

    /* Mime Type */
    //WORKER_LOG(std::string("MimeType: ") + CurlThreadData.MimeType);
    response->SetMimeType(CurlThreadData.MimeType);

    /* Redirect Url */

    if(!CurlThreadData.RedirectUrl.empty() && response->GetStatus() >= 300 && response->GetStatus() < 400)
    {
        std::string RedirectUrl = CurlThreadData.RedirectUrl;
        std::string OriginalUrl = CurlThreadData.Url;
        std::string Result = ProcessLocation(RedirectUrl,OriginalUrl);



        redirectUrl = Result;
    }else
    {
        LOCK_BROWSER_DATA

        for(std::shared_ptr<std::map<std::string,std::string> > Map: _BrowserData->_Headers.MatchAll(CurlThreadData.Url,TabNumber))
        {
            if(Map->count("Referer") > 0 && Map->at("Referer") != "_BAS_NO_REFERRER")
                Map->erase("Referer");
        }

    }

    NETWORK_LOG(std::string("<~") + redirectUrl.ToString());
    if(CurlThreadData.ResponseData.size() < 3000)
    {
        NETWORK_LOG(std::string("~") + std::string(CurlThreadData.ResponseData.data(),CurlThreadData.ResponseData.size()));
    }
    /* Responce Length */
    /*if(CurlThreadData.ContentLength >= 0)
    {
        WORKER_LOG(std::string("Data Size: ") + std::to_string(CurlThreadData.ContentLength));
    }else
    {
        WORKER_LOG(std::string("Data Size: Not Known"));
    }*/

    response_length = CurlThreadData.ContentLength;
}

bool CurlResourceHandler::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback)
{

    //WORKER_LOG("CurlResourceHandler::ReadResponse");

    CurlThreadDataClass::StatusClass Status = CurlThreadData.GetStatus();
    bool DoEnd = false;

    {
        std::lock_guard<std::mutex> lock(CurlThreadData.ResponseDataMutex);
        if(Status == CurlThreadDataClass::Done && !CurlThread.get() && CurlThreadData.ResponseDataReadLength >= CurlThreadData.ResponseData.size())
        {
            DoEnd = true;
        }
    }

    //No need to lock because status is done
    if(DoEnd)
    {
        LOCK_BROWSER_DATA
        //WORKER_LOG("End request because it is done. Start.");

        //If need to save
        bool SaveData = false;
        for(std::pair<bool, std::string> p:_BrowserData->_CacheMask)
        {
            if(match(p.second,CurlThreadData.Url))
            {
                SaveData = p.first;
            }
        }
        if(SaveData)
        {
            bool found = false;
            for(auto p: _BrowserData->_CachedData)
            {
                if(p.first == CurlThreadData.Url)
                {
                    p.second->insert(p.second->end(),CurlThreadData.ResponseData.begin(),CurlThreadData.ResponseData.end());
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                std::pair<std::string, std::shared_ptr<std::vector<char> > > p;
                p.first = CurlThreadData.Url;
                p.second = std::make_shared<std::vector<char> >();
                p.second->insert(p.second->end(),CurlThreadData.ResponseData.begin(),CurlThreadData.ResponseData.end());
                _BrowserData->_CachedData.push_back(p);
            }
        }
        return false;
    }

    {
        std::lock_guard<std::mutex> lock(CurlThreadData.ResponseDataMutex);


        /* Curl is still working */
        if(
                //Do not write anything if need to decode and status is not done yet.
                (CurlThreadData.NeedToReadWholeResponceAndThanFixEncoding && Status != CurlThreadDataClass::Done)

                || CurlThreadData.ResponseDataReadLength >= CurlThreadData.ResponseData.size())
        {
            ReadResponseCallback = callback;
            CanUseReadResponseCallback = true;
            bytes_read = 0;
            //WORKER_LOG("No data read next.");
            return true;
        }

        //Fix encoding one time
        bool IsChanged = false;
        FixPageContent Fix;
        if(Fix.NeedToFix(CurlThreadData.ContentType,CurlThreadData.Url))
        {
            std::string TempContent(CurlThreadData.ResponseData.data(),CurlThreadData.ResponseData.size());

            if(CurlThreadData.NeedToReadWholeResponceAndThanFixEncoding && !CurlThreadData.FixEncodingDone)
            {
                CurlThreadData.FixEncodingDone = true;
                if(Fix.FixCharset(CurlThreadData.ContentType,TempContent,CurlThreadData.Url))
                {
                    IsChanged = true;
                }
            }

            if(Fix.FixManifest(CurlThreadData.ContentType,TempContent,CurlThreadData.Url))
            {
                IsChanged = true;
            }

            if(IsChanged)
            {
                CurlThreadData.ResponseData.clear();
                std::copy( TempContent.begin(), TempContent.end(), std::back_inserter(CurlThreadData.ResponseData));
            }
        }

        int BytesWritten = CurlThreadData.ResponseData.size() - CurlThreadData.ResponseDataReadLength;
        if(BytesWritten > bytes_to_read)
            BytesWritten = bytes_to_read;

        memcpy(data_out,CurlThreadData.ResponseData.data() + CurlThreadData.ResponseDataReadLength,BytesWritten);
        CurlThreadData.ResponseDataReadLength += BytesWritten;
        bytes_read = BytesWritten;
        //WORKER_LOG(std::string("Write output, length ") + std::to_string(BytesWritten) + std::string(", "));
    }

    //WORKER_LOG("Proceed request.");
    return true;
}

void CurlResourceHandler::Cancel()
{
    //WORKER_LOG("CurlResourceHandler::Cancel");
    CurlThreadData.StopRequest = true;
}
