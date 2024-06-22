// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <Windows.h>
#include "Detours/include/detours.h"
#include "hook.h"
#include "Conv.h"
#pragma comment(lib, "Detours/lib.X86/detours.lib")
#pragma warning(disable : 4996)

char path[MAX_PATH];


void HookOn()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)OG_SetFilePointer, DT_SetFilePointer);
    DetourAttach(&(PVOID&)OG_ReadFile, DT_ReadFile);
    DetourAttach(&(PVOID&)OG_WriteFile, DT_WriteFile);
    DetourTransactionCommit();
}

void HookOff()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)OG_SetFilePointer, DT_SetFilePointer);
    DetourDetach(&(PVOID&)OG_ReadFile, DT_ReadFile);
    DetourDetach(&(PVOID&)OG_WriteFile, DT_WriteFile);
    DetourTransactionCommit();
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        GetSystemDirectoryA(path, MAX_PATH);
        strcat(path, "\\VERSION.dll");
        LoadLibraryA(path);
        HookOn();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        HMODULE hDll = GetModuleHandleA(path);
        if (hDll) FreeLibrary(hDll);
        HookOff(); 
        break;
    }
    return TRUE;
}

// 导出
#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=_DG_GetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=_DG_GetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=_DG_GetFileVersionInfoExA,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=_DG_GetFileVersionInfoExW,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=_DG_GetFileVersionInfoSizeA,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=_DG_GetFileVersionInfoSizeExA,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=_DG_GetFileVersionInfoSizeExW,@7")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=_DG_GetFileVersionInfoSizeW,@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=_DG_GetFileVersionInfoW,@9")
#pragma comment(linker, "/EXPORT:VerFindFileA=_DG_VerFindFileA,@10")
#pragma comment(linker, "/EXPORT:VerFindFileW=_DG_VerFindFileW,@11")
#pragma comment(linker, "/EXPORT:VerInstallFileA=_DG_VerInstallFileA,@12")
#pragma comment(linker, "/EXPORT:VerInstallFileW=_DG_VerInstallFileW,@13")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=_DG_VerLanguageNameA,@14")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=_DG_VerLanguageNameW,@15")
#pragma comment(linker, "/EXPORT:VerQueryValueA=_DG_VerQueryValueA,@16")
#pragma comment(linker, "/EXPORT:VerQueryValueW=_DG_VerQueryValueW,@17")
// 函数
extern "C" void __declspec(naked) DG_GetFileVersionInfoA()
{
    GetFunctionAddress("GetFileVersionInfoA", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_GetFileVersionInfoByHandle()
{
    GetFunctionAddress("GetFileVersionInfoByHandle", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_GetFileVersionInfoExA()
{
    GetFunctionAddress("GetFileVersionInfoExA", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_GetFileVersionInfoExW()
{
    GetFunctionAddress("GetFileVersionInfoExW", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_GetFileVersionInfoSizeA()
{
    GetFunctionAddress("GetFileVersionInfoSizeA", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_GetFileVersionInfoSizeExA()
{
    GetFunctionAddress("GetFileVersionInfoSizeExA", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_GetFileVersionInfoSizeExW()
{
    GetFunctionAddress("GetFileVersionInfoSizeExW", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_GetFileVersionInfoSizeW()
{
    GetFunctionAddress("GetFileVersionInfoSizeW", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_GetFileVersionInfoW()
{
    GetFunctionAddress("GetFileVersionInfoW", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_VerFindFileA()
{
    GetFunctionAddress("VerFindFileA", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_VerFindFileW()
{
    GetFunctionAddress("VerFindFileW", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_VerInstallFileA()
{
    GetFunctionAddress("VerInstallFileA", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_VerInstallFileW()
{
    GetFunctionAddress("VerInstallFileW", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_VerLanguageNameA()
{
    GetFunctionAddress("VerLanguageNameA", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_VerLanguageNameW()
{
    GetFunctionAddress("VerLanguageNameW", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_VerQueryValueA()
{
    GetFunctionAddress("VerQueryValueA", path);
    __asm jmp eax
}
extern "C" void __declspec(naked) DG_VerQueryValueW()
{
    GetFunctionAddress("VerQueryValueW", path);
    __asm jmp eax
}

// 读文件并返回长度
static std::unique_ptr<char[]> ReadFileAndGetContent(HANDLE fileHandle, int* outLength) {
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(fileHandle, &fileSize)) return nullptr; // 获取文件大小失败，返回nullptr
    std::unique_ptr<char[]> readBuffer(new char[fileSize.QuadPart + 2]); // 使用智能指针管理内存
    if (!readBuffer) return nullptr; // 内存分配失败，返回nullptr
    DWORD bytesRead;
    BOOL result = OG_ReadFile(fileHandle, readBuffer.get(), static_cast<DWORD>(fileSize.QuadPart), &bytesRead, NULL);
    if (!result || bytesRead != fileSize.QuadPart) return nullptr; // 读取失败，返回nullptr
    readBuffer[fileSize.QuadPart] = '\0'; // 确保字符串以空字符结尾
    readBuffer[fileSize.QuadPart + 1] = '\0';
    *outLength = fileSize.QuadPart; // 设置输出长度
    return readBuffer; // 返回文件内容
}

int WINAPI DT_SetFilePointer(
    HANDLE hFile,
    LONG   lDistanceToMove,
    PLONG  lpDistanceToMoveHigh,
    DWORD  dwMoveMethod
) {
    if (IsSupportedFile(hFile) && dwMoveMethod == FILE_END) {
        // 如果是支持的文件类型并且移动方式是从文件末尾开始
        int fileSize = 0;
        auto readBuffer = ReadFileAndGetContent(hFile, &fileSize); // 使用智能指针管理内存
        if (!readBuffer || fileSize == 0)
            return FALSE; // 读取失败或文件长度为0，返回FALSE

        int type = CheckCode(readBuffer.get(), fileSize), nPos = 0;
        if (type == CODE_UTF8_BOM)
            nPos = conUTF8(readBuffer.get() + 3);
        else if (type == CODE_UTF8_NOBOM)
            nPos = conUTF8(readBuffer.get());
        else if (type == CODE_UTF16_LE)
            nPos = WC2MB(CP_ACP, readBuffer.get() + 2);
        else if (type == CODE_UTF16_BE) {
            LE2BE(readBuffer.get(), fileSize);
            nPos = WC2MB(CP_ACP, readBuffer.get() + 2);
        }
        else
            return OG_SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod); // 不处理的类型，直接调用原始函数

        nPos--; // 调整长度
        OG_SetFilePointer(hFile, nPos, 0, 0); // 设置文件指针位置
        return nPos; // 返回长度
    }
    return OG_SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod); // 非支持文件类型，调用原始函数
}

// 读文件的hook函数
BOOL WINAPI DT_ReadFile(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped) {
    if (IsSupportedFile(hFile)) {
        int fileSize = 0;
        auto readBuffer = ReadFileAndGetContent(hFile, &fileSize); // 使用智能指针管理内存
        if (!readBuffer)
            return FALSE; // 读取失败返回FALSE

        int type = CheckCode(readBuffer.get(), fileSize), bytesRead = 0;
        if (type == CODE_UTF8_BOM)
            bytesRead = conUTF8(readBuffer.get() + 3, lpBuffer, nNumberOfBytesToRead);
        else if (type == CODE_UTF8_NOBOM)
            bytesRead = conUTF8(readBuffer.get(), lpBuffer, nNumberOfBytesToRead);
        else if (type == CODE_UTF16_LE)
            bytesRead = WC2MB(CP_ACP, readBuffer.get() + 2, -1, lpBuffer, nNumberOfBytesToRead);
        else if (type == CODE_UTF16_BE) {
            LE2BE(readBuffer.get(), fileSize);
            bytesRead = WC2MB(CP_ACP, readBuffer.get() + 2, -1, lpBuffer, nNumberOfBytesToRead);
        }
        else
            memcpy(lpBuffer, readBuffer.get(), nNumberOfBytesToRead); // 拷贝文件原始内容

        return TRUE; // 返回成功
    }

    return OG_ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped); // 非支持文件类型，调用原始函数
}

// 写文件的hook函数
BOOL WINAPI DT_WriteFile(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
) {
    if (IsSupportedFile(hFile))
    {
        std::unique_ptr<char[]> rlpBuffer(new char[nNumberOfBytesToWrite + 1]); // 使用智能指针管理内存
        memcpy(rlpBuffer.get(), lpBuffer, nNumberOfBytesToWrite); // 拷贝数据
        rlpBuffer[nNumberOfBytesToWrite] = '\0'; // 确保字符串以空字符结尾

        int nLen = MultiByteToWideChar(CP_ACP, 0, rlpBuffer.get(), -1, NULL, 0); // 转换编码
        if (nLen == 0)
            return FALSE; // 转换失败，返回FALSE

        std::unique_ptr<wchar_t[]> wideStr(new wchar_t[nLen + 1]); // 使用智能指针管理内存
        if (MultiByteToWideChar(CP_ACP, 0, rlpBuffer.get(), -1, wideStr.get(), nLen) == 0)
            return FALSE; // 转换失败，返回FALSE
        wideStr[nLen] = '\0'; // 确保字符串以空字符结尾

        nLen = WC2MB(CP_UTF8, wideStr.get()); // 转换编码
        if (nLen == 0)
            return FALSE; // 转换失败，返回FALSE

        std::unique_ptr<char[]> multiByteStr(new char[nLen + 1]); // 使用智能指针管理内存
        if (WC2MB(CP_UTF8, wideStr.get(), -1, multiByteStr.get(), nLen) == 0)
            return FALSE; // 转换失败，返回FALSE
        multiByteStr[nLen] = '\0'; // 确保字符串以空字符结尾

        return OG_WriteFile(hFile, multiByteStr.get(), nLen + 1, lpNumberOfBytesWritten, lpOverlapped); // 调用WINAPI写文件函数
    }
    return OG_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped); // 调用原始WINAPI写文件函数
}


