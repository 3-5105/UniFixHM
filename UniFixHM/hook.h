#pragma once
#include <memory>
#include <Windows.h>
#include <fileapi.h>
#include <Shlwapi.h>
#include <string>
#pragma comment(lib, "Shlwapi.lib") // ָShlwapi.lib
#pragma warning(disable : 4996)
using namespace std;

static DWORD (WINAPI* OG_SetFilePointer)(
    HANDLE hFile,
    LONG   lDistanceToMove,
    PLONG  lpDistanceToMoveHigh,
    DWORD  dwMoveMethod ) = SetFilePointer;

static BOOL(WINAPI* OG_ReadFile)(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped) = ReadFile;

static BOOL(WINAPI* OG_WriteFile)(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped) = WriteFile;


int WINAPI DT_SetFilePointer(
    HANDLE hFile,
    LONG   lDistanceToMove,
    PLONG  lpDistanceToMoveHigh,
    DWORD  dwMoveMethod
);

BOOL WINAPI DT_ReadFile(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
);

BOOL WINAPI DT_WriteFile(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
);


std::unique_ptr<char[]> ReadFileAndGetContent(HANDLE fileHandle, int* outLength);
void Mess();
bool IsSupportedFile(HANDLE fileHandle);
PVOID GetFunctionAddress(const char* functionName, const char* dllPath);