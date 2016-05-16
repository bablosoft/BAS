#ifndef PIPESCLIENT_H
#define PIPESCLIENT_H

#include <thread>
#include <mutex>
#include <tchar.h>

class PipesClient
{
    std::thread Thread;
    std::mutex MutexOutput;
    std::mutex MutexInput;
    std::string Name;
    std::string Pid;
    void ThreadFuntion();
    std::string OutputString;
    std::string InputString;
    const int BUFSIZE = 512;
    TCHAR Buffer[512];
    void Sleep();
public:
    PipesClient();
    void Start(const std::string& Name,const std::string& Pid);
    void Join();
    void Write(const std::string& Data);
    std::string Read();
    void Log(const std::string& text);
};

#endif // PIPESCLIENT_H
