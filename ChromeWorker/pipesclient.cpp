#include "pipesclient.h"
#include "log.h"
#include <Windows.h>
#include <locale>
#include <codecvt>
#include "snappy.h"
#include "base64.h"

PipesClient::PipesClient()
{
}

void PipesClient::Log(const std::string& text)
{
    WORKER_LOG(text);
}

void PipesClient::Sleep()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

void PipesClient::ThreadFuntion()
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string pipe_name_string = std::string("\\\\.\\pipe\\basworkerpipes") + Pid;
    std::wstring pipe_name = converter.from_bytes(pipe_name_string);
    Log("Starting client. Pipe name:");
    Log(pipe_name_string);
    HANDLE Pipe;

    //Connect to pipe
    while(true)
    {
        Log("Try to connect");
        Pipe = CreateFile(
             pipe_name.c_str(),   // pipe name
             GENERIC_READ |  // read and write access
             GENERIC_WRITE,
             0,              // no sharing
             NULL,           // default security attributes
             OPEN_EXISTING,  // opens existing pipe
             0,              // default attributes
             NULL);          // no template file

        if (Pipe != INVALID_HANDLE_VALUE)
        {
            Log("Connected!");
            break;
        }
        Log("Failed");
        Sleep();
    }

    //Set async mode
    DWORD Mode = PIPE_NOWAIT;
    SetNamedPipeHandleState(
          Pipe,    // pipe handle
          &Mode,  // new pipe mode
          NULL,     // don't set maximum bytes
          NULL);    // don't set maximum time

    //Read / Write
    while(true)
    {
        DWORD ReadBytes;
        std::string ReadDataString;
        while(true)
        {
            bool ReadSuccess = ReadFile(
                Pipe,    // pipe handle
                Buffer,    // buffer to receive reply
                BUFSIZE*sizeof(TCHAR),  // size of buffer
                &ReadBytes,  // number of bytes read
                NULL);    // not overlapped
            if(ReadSuccess)
                ReadDataString.append(std::string((char *)Buffer,ReadBytes));
            if (ReadBytes != BUFSIZE)
                break;
        }
        //Report about success read
        if(!ReadDataString.empty())
        {
            Log("Got data : ");
            Log(ReadDataString);
            {
                std::lock_guard<std::mutex> lock(MutexInput);
                InputString.append(ReadDataString);
            }
        }

        //Take data need to write
        std::string OutputStringCopy;
        {
            std::lock_guard<std::mutex> lock(MutexOutput);
            OutputStringCopy = OutputString;
            OutputString.clear();
        }

        //Write Data
        if(!OutputStringCopy.empty())
        {
            Log("Writing");
            Log(OutputStringCopy);
            DWORD WriteBytes;

            while(true)
            {
                bool WriteSuccess = WriteFile(
                  Pipe,                  // pipe handle
                  (void *)OutputStringCopy.c_str(),             // message
                  OutputStringCopy.length(),              // message length
                  &WriteBytes,             // bytes written
                  NULL);                  // not overlapped

                if(WriteSuccess)
                {
                    OutputStringCopy.erase(0,WriteBytes);
                }
                if(OutputStringCopy.empty())
                {
                    Log("Writing Done");
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

        }

        Sleep();
    }

    Log("Finished");
    CloseHandle(Pipe);
}

void PipesClient::Start(const std::string& Name,const std::string& Pid)
{
    this->Name = Name;
    this->Pid = Pid;
    this->OutputString = std::string("<Key>") + Name + std::string("</Key>");
    Thread = std::thread(&PipesClient::ThreadFuntion, this);
}

void PipesClient::Join()
{
    Thread.join();
}

void PipesClient::Write(const std::string& Data)
{
    std::string Compressed;
    snappy::Compress(Data.c_str(),Data.length(),&Compressed);
    Compressed = std::string("<Messages>") + base64_encode((const unsigned char*)Compressed.data(),Compressed.length()) + std::string("</Messages>");

    std::lock_guard<std::mutex> lock(MutexOutput);
    OutputString.append(Compressed);
}

std::string PipesClient::Read()
{
    std::lock_guard<std::mutex> lock(MutexInput);
    std::string Res = InputString;
    InputString.clear();
    return Res;
}

