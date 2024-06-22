#include "hook.h"

// 快速弹窗
void Mess() {
    MessageBoxA(0, "MESS", "tips", 0);
}

// 检查文件是否为支持的文件类型（.nsi/.nsh）
bool IsSupportedFile(HANDLE fileHandle) {
    char filePath[MAX_PATH];
    DWORD pathLength = GetFinalPathNameByHandleA(fileHandle, filePath, MAX_PATH, VOLUME_NAME_DOS);
    if (pathLength < 0 || pathLength > MAX_PATH)
        return false; // 获取文件路径失败或路径过长，返回false

    LPCSTR fileExtension = PathFindExtensionA(filePath);
    if (strcmp(fileExtension, ".nsi") == 0 || strcmp(fileExtension, ".nsh") == 0)
        return true; // 是支持的文件类型，返回true

    return false; // 不是支持的文件类型，返回false
}

// 获取指定DLL中函数地址的函数
PVOID GetFunctionAddress(const char* functionName, const char* dllPath)
{
    PVOID functionAddress = NULL;
    HMODULE hDll = LoadLibraryA(dllPath); // 加载指定DLL
    if (hDll == NULL)
        return NULL; // 加载失败则返回NULL
    functionAddress = GetProcAddress(hDll, functionName); // 获取函数地址
    FreeLibrary(hDll); // 释放DLL
    return functionAddress; // 返回函数地址
}

