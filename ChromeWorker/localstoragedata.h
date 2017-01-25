#ifndef LOCALSTORAGEDATA_H
#define LOCALSTORAGEDATA_H

#include <string>
#include <map>
#include <vector>


struct LocalStorageDataItem
{
    std::string TypeString;
    std::string Key;
    std::string Value;
    std::string Domain;
    int FrameHash = 0;
    std::string Time;
    void Clear()
    {
        Time.clear();
        FrameHash = 0;
        TypeString.clear();
        Key.clear();
        Value.clear();
        Domain.clear();
    }
};

class LocalStorageData
{
    struct Item
    {
        enum {Set,Remove,ClearDomain,ClearAll} Type;
        std::string Key;
        std::string Value;
        std::string Domain;
        int FrameHash;
        std::string Time;
    };
    std::map<std::string,std::string> Current;
    std::vector<Item> Items;
    void SortAndUpdate();
public:
    LocalStorageData();
    std::string Get();
    void Parse(const std::string& value);
    void Set(const LocalStorageDataItem& item);
    void Clear();
};

#endif // LOCALSTORAGEDATA_H
