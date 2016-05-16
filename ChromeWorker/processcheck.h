#ifndef PROCESSCHECK_H
#define PROCESSCHECK_H
#include <windows.h>
#include "log.h"
bool isRunning(int pid)
{
    HANDLE ph = OpenProcess(SYNCHRONIZE,false,pid);
    if(ph == NULL)
    {
        return true;
    }
    DWORD w = WaitForSingleObject(ph,0);
    CloseHandle(ph);
    return w == WAIT_TIMEOUT;
}
#endif // PROCESSCHECK_H
