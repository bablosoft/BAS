#include "postmanager.h"
#include "multithreading.h"
#include "readallfile.h"
#include "base64.h"
#include <chrono>

using namespace std::chrono;

PostManager::PostManager()
{

}

void PostManager::AddAttachment(int Id, const std::string& Data, const std::string& Type, const std::string& Filename)
{
    LOCK_POST_MANAGER
    PostAttachmentItem a = std::make_shared<PostAttachmentItemClass>();
    a->Id = Id;
    a->Data = base64_decode(Data);
    a->Type = Type;
    a->Filename = Filename;
    a->Added = duration_cast< milliseconds >( system_clock::now().time_since_epoch() ).count();
    Attachments[Id] = a;
    //WORKER_LOG(std::string("PostManager::AddAttachment<<") + std::to_string(Id) + std::string("<<") + std::to_string(Attachments.size()));

}

PostParts PostManager::PreparePostParts(CefPostData::ElementVector Elements)
{
    PostParts d = std::make_shared<PostPartsClass>();

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

            try
            {
                std::size_t Pos = 0;
                while(true)
                {
                    std::size_t StartPos = DataString.find("BrowserAutomationStudioAttachmentStart", Pos);
                    if(StartPos == std::string::npos)
                        break;

                    std::size_t EndPos = DataString.find("BrowserAutomationStudioAttachmentEnd",StartPos);
                    if(EndPos == std::string::npos)
                        break;

                    if(StartPos >= EndPos)
                        break;

                    std::string Id = DataString.substr((StartPos + 38),EndPos - (StartPos + 38));

                    int IdInt = std::stoi(Id);
                    d->AttachmentIds.push_back(IdInt);

                    Pos = EndPos;
                }

                
            }catch(...)
            {
            }


            try
            {
                std::size_t Pos = 0;
                while(true)
                {

                    std::size_t StartPos = DataString.find("66,114,111,119,115,101,114,65,117,116,111,109,97,116,105,111,110,83,116,117,100,105,111,65,116,116,97,99,104,109,101,110,116,83,116,97,114,116,", Pos);
                    if(StartPos == std::string::npos)
                        break;

                    std::size_t EndPos = DataString.find("66,114,111,119,115,101,114,65,117,116,111,109,97,116,105,111,110,83,116,117,100,105,111,65,116,116,97,99,104,109,101,110,116,69,110,100", StartPos);
                    if(EndPos == std::string::npos)
                        break;

                    if(StartPos >= EndPos)
                        break;

                    std::string Current;
                    std::string DataStringDecoded;
                    for(std::size_t i = StartPos + 143;i<EndPos;i++)
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

                    int IdInt = std::stoi(DataStringDecoded);
                    d->AttachmentIds.push_back(IdInt);

                    Pos = EndPos;

                }
            }catch(...)
            {
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
        {
            d->Data.insert(d->Data.end(), Data.begin(), Data.end());
        }
    }
    //WORKER_LOG(std::string("PostManager::PreparePostParts<<") + std::string(d->Data.data(),d->Data.size()));
    /*for(int id: d->AttachmentIds)
    {
        WORKER_LOG(std::string("PostManager::PreparePostParts<<") + std::to_string(id));
    }*/

    return d;
}

bool PostManager::FinalizePostParts(PostParts Data, std::vector<char>& Result)
{

    if(!Data.get())
    {
        Result.clear();
        //WORKER_LOG(std::string("PostManager::FinalizePostParts1<<") + std::string(Result.data(),Result.size()));
        return true;
    }
    LOCK_POST_MANAGER
    for(int AttachmentId: Data->AttachmentIds)
    {
        if(Attachments.find(AttachmentId) == Attachments.end())
        {
            return false;
        }
    }
    Result.clear();
    if(Data->AttachmentIds.empty())
    {
        Result = Data->Data;
        //WORKER_LOG(std::string("PostManager::FinalizePostParts2<<") + std::string(Result.data(),Result.size()));
        return true;
    }

    std::string DataString(Data->Data.data(),Data->Data.size());
    try
    {
        while(true)
        {
            std::size_t StartPos = DataString.find("66,114,111,119,115,101,114,65,117,116,111,109,97,116,105,111,110,83,116,117,100,105,111,65,116,116,97,99,104,109,101,110,116,83,116,97,114,116,");
            if(StartPos == std::string::npos)
                break;

            std::size_t EndPos = DataString.find("66,114,111,119,115,101,114,65,117,116,111,109,97,116,105,111,110,83,116,117,100,105,111,65,116,116,97,99,104,109,101,110,116,69,110,100");
            if(EndPos == std::string::npos)
                break;

            if(StartPos >= EndPos)
                break;

            std::string Current;
            std::string DataStringDecoded;
            for(std::size_t i = StartPos + 143;i<EndPos;i++)
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

            int AttachmentId = std::stoi(DataStringDecoded);
            std::string ContentType = Attachments[AttachmentId]->Type;
            std::string Filename = Attachments[AttachmentId]->Filename;

            DataString.replace(StartPos,EndPos - StartPos + 135,Attachments[AttachmentId]->Data);

            if(!ContentType.empty() || !Filename.empty())
            {
                std::size_t StartContentDisposition = DataString.rfind("Content-Disposition:",StartPos);
                if(StartContentDisposition != std::string::npos)
                {
                    std::size_t EndContentDisposition = DataString.find("\r",StartContentDisposition);
                    if(EndContentDisposition != std::string::npos)
                    {
                        std::string ContentTypeString;
                        std::string FilenameString;
                        if(!Filename.empty())
                        {
                            FilenameString = std::string("; filename=\"") + Filename + std::string("\"");
                        }

                        if(!ContentType.empty())
                        {
                            ContentTypeString = std::string("\r\nContent-Type: ") + ContentType;
                        }

                        std::string OriginalContentDisposition = DataString.substr(StartContentDisposition + 20, EndContentDisposition - StartContentDisposition - 20);
                        DataString.replace(StartContentDisposition,EndContentDisposition - StartContentDisposition,std::string("Content-Disposition:") + OriginalContentDisposition + FilenameString + ContentTypeString);
                    }
                }

            }
        }
    }catch(...)
    {
    }

    try
    {
        while(true)
        {
            std::size_t StartPos = DataString.find("BrowserAutomationStudioAttachmentStart");
            if(StartPos == std::string::npos)
                break;

            std::size_t EndPos = DataString.find("BrowserAutomationStudioAttachmentEnd");
            if(EndPos == std::string::npos)
                break;

            if(StartPos >= EndPos)
                break;


            int AttachmentId = std::stoi(DataString.substr((StartPos + 38),EndPos - (StartPos + 38)));
            std::string ContentType = Attachments[AttachmentId]->Type;
            std::string Filename = Attachments[AttachmentId]->Filename;

            DataString.replace(StartPos,EndPos - StartPos + 36,Attachments[AttachmentId]->Data);

            if(!ContentType.empty() || !Filename.empty())
            {
                std::size_t StartContentDisposition = DataString.rfind("Content-Disposition:",StartPos);
                if(StartContentDisposition != std::string::npos)
                {
                    std::size_t EndContentDisposition = DataString.find("\r",StartContentDisposition);
                    if(EndContentDisposition != std::string::npos)
                    {
                        std::string ContentTypeString;
                        std::string FilenameString;
                        if(!Filename.empty())
                        {
                            FilenameString = std::string("; filename=\"") + Filename + std::string("\"");
                        }

                        if(!ContentType.empty())
                        {
                            ContentTypeString = std::string("\r\nContent-Type: ") + ContentType;
                        }

                        std::string OriginalContentDisposition = DataString.substr(StartContentDisposition + 20, EndContentDisposition - StartContentDisposition - 20);
                        DataString.replace(StartContentDisposition,EndContentDisposition - StartContentDisposition,std::string("Content-Disposition:") + OriginalContentDisposition + FilenameString + ContentTypeString);
                    }
                }

            }
        }
    }catch(...)
    {
    }

    Result.assign(DataString.begin(),DataString.end());

    for(int AttachmentId: Data->AttachmentIds)
    {
        Attachments.erase(AttachmentId);
    }

    //WORKER_LOG(std::string("PostManager::FinalizePostParts3<<") + std::string(Result.data(),Result.size()));

    return true;
}

void PostManager::Cleanup()
{
    long long now = duration_cast< milliseconds >( system_clock::now().time_since_epoch() ).count();
    LOCK_POST_MANAGER
    std::map<int, PostAttachmentItem>::iterator it = Attachments.begin();
    while (it != Attachments.end())
    {
      if(now > it->second->Added + 60000)
      {
        std::map<int, PostAttachmentItem>::iterator toerase = it;
        ++it;
        Attachments.erase(toerase);
      }
      else
        ++it;
    }


}
