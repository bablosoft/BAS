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
            Data->MimeType = MimeTypeSplit[0];
    }


    std::string LocationHeader = "Location";
    if(Data->ResultHeaders.count("location") > 0)
        LocationHeader = "location";

    if(Data->ResultHeaders.count(LocationHeader) > 0)
        Data->RedirectUrl = Data->ResultHeaders.find(LocationHeader)->second;

    Data->ResultHeaders.erase("content-security-policy");
    Data->ResultHeaders.erase("Content-Security-Policy");

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

    struct curl_slist *headers = NULL;

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
            std::string h = Header.first + std::string(": ") + Header.second;
            headers = curl_slist_append(headers, h.c_str());
        }
    }


    if(EmptyContentType)
        headers = curl_slist_append(headers, "Content-Type:");

    headers = curl_slist_append(headers, "Connection: keep-alive");
    headers = curl_slist_append(headers, "Expect:");
    curl_easy_setopt(curl_handle, CURLOPT_ACCEPT_ENCODING,"gzip, deflate");
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

    if(!Referer.empty())
    {
        NETWORK_LOG(std::string("> Referer=") + Referer);
        curl_easy_setopt(curl_handle, CURLOPT_REFERER, Referer.c_str());
    }

    bool postdatawasset = false;

    if(Data->Method == "HEAD")
        curl_easy_setopt(curl_handle, CURLOPT_NOBODY, 1L);
    else if(Data->Method == "POST")
    {
        curl_easy_setopt(curl_handle, CURLOPT_POST, 1L);
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, Data->PostData.data());
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)Data->PostData.size());
        if(Data->PostData.size() < 3000)
        {
            NETWORK_LOG(std::string("~ ") + std::string(Data->PostData.data(),Data->PostData.size()));
        }
        postdatawasset = true;
    }
    else
        curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, Data->Method.c_str());

    if(!postdatawasset && Data->PostData.size() > 0)
    {
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, Data->PostData.data());
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)Data->PostData.size());
        if(Data->PostData.size() < 3000)
        {
            NETWORK_LOG(std::string("~ ") + std::string(Data->PostData.data(),Data->PostData.size()));
        }
    }


    //Run
    Data->SetStatus(CurlResourceHandler::CurlThreadDataClass::Running);
    //const clock_t begin_time = clock();
    Data->Result = curl_easy_perform(curl_handle);
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
    curl_easy_cleanup(curl_handle);
    Data->SetStatus(CurlResourceHandler::CurlThreadDataClass::Done);
    curl_slist_free_all(headers);
}




CurlResourceHandler::CurlResourceHandler(BrowserData * _BrowserData)
{
    this->_BrowserData = _BrowserData;
    this->StartTime = duration_cast< milliseconds >( system_clock::now().time_since_epoch() ).count();

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
                RequestHeadersNew[Header.first] = Header.second;
                if(Header.first == "Referer")
                {
                    _BrowserData->_NextReferrer = Header.second;
                }
            }
            Map->erase("Referer");
            Map->erase("referer");
        }
    }

    CefRefPtr<CefPostData> PostData = request->GetPostData();
    if(/*request->GetMethod().ToString() == "POST" &&*/ PostData)
    {
        CefPostData::ElementVector Elements;
        PostData->GetElements(Elements);
        for(CefRefPtr<CefPostDataElement> Element:Elements)
        {
            bool IsFailedToLoad = false;
            std::vector<char> Data;

            if(Element->GetType() == PDE_TYPE_BYTES)
            {
                int Count = Element->GetBytesCount();
                Data.resize(Count);
                if(Count != Element->GetBytes(Count,Data.data()))
                    continue;


                std::string DataString(Data.data(),Count);
                std::string ContentType;


                try
                {
                    bool DataStringChanged = false;
                    while(true)
                    {
                        std::size_t StartPos = DataString.find("BrowserAutomationStudioBase64DataStart");
                        if(StartPos == std::string::npos)
                            break;

                        std::size_t EndPos = DataString.find("BrowserAutomationStudioBase64DataEnd");
                        if(EndPos == std::string::npos)
                            break;

                        if(StartPos >= EndPos)
                            break;

                        std::size_t SeparatorPos = DataString.find(";",StartPos);
                        if(SeparatorPos == std::string::npos)
                            break;

                        DataStringChanged = true;

                        ContentType = DataString.substr((StartPos + 38) + 1,SeparatorPos - (StartPos + 38) - 1);
                        DataString.erase(EndPos,36);
                        DataString.erase(StartPos,SeparatorPos - StartPos + 1);
                    }

                    if(DataStringChanged)
                    {
                        Data.assign(DataString.begin(),DataString.end());
                    }

                }catch(...)
                {
                }

                try
                {
                    bool DataStringChanged = false;
                    while(true)
                    {
                        std::size_t StartPos = DataString.find("66,114,111,119,115,101,114,65,117,116,111,109,97,116,105,111,110,83,116,117,100,105,111,66,97,115,101,54,52,68,97,116,97,83,116,97,114,116,");
                        if(StartPos == std::string::npos)
                            break;

                        std::size_t EndPos = DataString.find("66,114,111,119,115,101,114,65,117,116,111,109,97,116,105,111,110,83,116,117,100,105,111,66,97,115,101,54,52,68,97,116,97,69,110,100");
                        if(EndPos == std::string::npos)
                            break;

                        if(StartPos >= EndPos)
                            break;

                        DataStringChanged = true;

                        std::string Current;
                        std::string DataStringDecoded;
                        for(std::size_t i = StartPos + 139;i<EndPos;i++)
                        {
                            char c = DataString.at(i);
                            if(c == 44)
                            {
                                DataStringDecoded.push_back(std::stoi(Current));
                                Current.clear();
                            }else
                            {
                                Current.push_back(c);
                            }
                        }

                        std::size_t SeparatorPos = DataStringDecoded.find(";");
                        ContentType = DataStringDecoded.substr(0,SeparatorPos);
                        DataStringDecoded.erase(0,SeparatorPos + 1);

                        DataString.replace(StartPos,EndPos - StartPos + 131,DataStringDecoded);
                    }

                    if(DataStringChanged)
                    {
                        Data.assign(DataString.begin(),DataString.end());
                    }

                }catch(...)
                {
                }



                if(!ContentType.empty())
                {
                    static std::regex ContentTypeRegexp("Content-Disposition:([^\\r]*)");

                    std::smatch Match;
                    if(std::regex_search(DataString,Match,ContentTypeRegexp))
                    {
                         std::string m = Match[1];
                         DataString.replace(Match.position(),Match.length(),std::string("Content-Disposition:") + m + std::string("\r\nContent-Type: ") + ContentType);
                         Data.assign(DataString.begin(),DataString.end());
                    }
                }
            }


            if(Element->GetType() == PDE_TYPE_FILE && !Element->GetFile().ToString().empty())
            {
                try{
                    Data = ReadAllBytes(Element->GetFile().ToString());
                }catch(...)
                {
                   IsFailedToLoad = true;
                }
            }
            if(!IsFailedToLoad && Data.size() > 0)
                CurlThreadData.PostData.insert(CurlThreadData.PostData.end(), Data.begin(), Data.end());

        }
        /*WORKER_LOG("!!Post Data!!");
        std::string DataString(CurlThreadData.PostData.data(),CurlThreadData.PostData.size());

        WORKER_LOG(DataString);
        WORKER_LOG("!!Post Data End!!");*/

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

void CurlResourceHandler::Timer()
{
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
