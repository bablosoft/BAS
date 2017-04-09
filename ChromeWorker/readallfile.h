#ifndef READALLFILE_H
#define READALLFILE_H

#include <vector>
#include <string>

std::vector<char> ReadAllBytes(const std::string& filename);
void ReadAllBytes(const std::string& filename,std::vector<char>& result);

std::string ReadAllString(const std::string& filename);
struct FileEntry
{
    std::string Path;
    std::string FileName;
    bool IsDirectory;
};
std::vector<FileEntry> GetFilesInDirectory(const std::string &Directory);


#endif // READALLFILE_H
