#include "moduledll.h"
#include <QDir>
#include <windows.h>


extern "C" {

    void* StartDll()
    {

        return 0;
    }



    void EndDll(void * DllData)
    {

    }

    void* StartThread()
    {
        return 0;
    }

    void EndThread(void * DllData)
    {

    }


    void PlayDefaultSound(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        PlaySoundW(QDir("modules/UserNotification").absoluteFilePath("Notification.pcm").toStdWString().c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }


}
