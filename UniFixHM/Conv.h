#pragma once
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma warning(disable : 4996)

#define CODE_UNKNOWN    1
#define CODE_ANSI       2
#define CODE_UTF8_NOBOM 3
#define CODE_UTF8_BOM   4
#define CODE_UTF16_LE   5
#define CODE_UTF16_BE   6

#define SWAP16(x) \
    ((((x) & 0x00ff) << 8) | \
     (((x) & 0xff00) >> 8) )

#define SWAP32(x) \
    ((((x) & 0x000000ff) << 24) | \
     (((x) & 0x0000ff00) <<  8) | \
     (((x) & 0x00ff0000) >>  8) | \
     (((x) & 0xff000000) >> 24) )

int CheckCode(char* data, int dataSize);

void LE2BE(char* destination, int sourceSize);

int conUTF8(LPVOID Buffer, LPVOID lpBuffer = NULL, int n = 0);

int UTF8216(LPVOID mp, wchar_t** wp, int size = -1);

static int WC2MB(int codePage, LPCVOID wideString, int size = -1, LPCVOID multiByteString = NULL, int length = 0) {
    // ¼ò»¯·â×° WideCharToMultiByte
    return WideCharToMultiByte(codePage, 0, (wchar_t*)wideString, size, (char*)multiByteString, length, NULL, NULL);
}
