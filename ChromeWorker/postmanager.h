#ifndef POSTMANAGER_H
#define POSTMANAGER_H

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "include/cef_app.h"


struct PostPartsClass
{
    std::vector<char> Data;
    std::vector<int> AttachmentIds;
};

using PostParts = std::shared_ptr<PostPartsClass>;

struct PostAttachmentItemClass
{
    std::string Data;
    std::string Type;
    std::string Filename;
    long long Added;
    int Id;
};

using PostAttachmentItem = std::shared_ptr<PostAttachmentItemClass>;


class PostManager
{
    std::map<int, PostAttachmentItem> Attachments;
public:
    PostManager();
    void AddAttachment(int Id, const std::string& Data, const std::string& Type, const std::string& Filename);
    PostParts PreparePostParts(CefPostData::ElementVector Elements);
    bool FinalizePostParts(PostParts Data, std::vector<char>& Result);
    void Cleanup();
};

#endif // POSTMANAGER_H
