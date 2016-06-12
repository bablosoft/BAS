#ifndef MODULEDLL_H
#define MODULEDLL_H

extern "C" {
typedef char* (*ResizeFunction)(int,void*);

__declspec(dllexport) void* StartDll();
__declspec(dllexport) void EndDll(void * DllData);
__declspec(dllexport) void* StartThread();
__declspec(dllexport) void EndThread(void * ThreadData);

__declspec(dllexport) void FileSystemReadFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError);
__declspec(dllexport) void FileSystemWriteFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError);
__declspec(dllexport) void FileSystemFileInfo(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError);
__declspec(dllexport) void FileSystemCreateDir(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError);
__declspec(dllexport) void FileSystemRemoveFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError);
__declspec(dllexport) void FileSystemMoveFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError);
__declspec(dllexport) void FileSystemCopyFile(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError);
__declspec(dllexport) void FileSystemSearch(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError);

}

#endif // MODULEDLL_H
