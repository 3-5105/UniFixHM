#include "Conv.h"
#include <vector>

// 定义UTF-8字节模式常量
struct Utf8BytePattern {
    unsigned char mask;  // 掩码
    unsigned char value; // 比较值
};

const Utf8BytePattern Utf8NumMap[] = {
    {0xE0, 0xC0}, // 110xxxxx
    {0xF0, 0xE0}, // 1110xxxx
    {0xF8, 0xF0}, // 11110xxx
    {0xFC, 0xF8}, // 111110xx
    {0xFE, 0xFC}  // 1111110x
};

// 检查编码类型（根据BOM或UTF-8字节模式）
int CheckCode(char* pData, int dataSize) {
    if (pData == nullptr || dataSize < 1)
        return -1;

    // 检查UTF-8 BOM
    if (
        static_cast<unsigned char>(pData[0]) == 0xEF &&
        static_cast<unsigned char>(pData[1]) == 0xBB &&
        static_cast<unsigned char>(pData[2]) == 0xBF &&
        dataSize >= 3)
        return CODE_UTF8_BOM;

    // 检查UTF-16 小端序
    else if (dataSize >= 2 && static_cast<unsigned char>(pData[0]) == 0xFF &&
        static_cast<unsigned char>(pData[1]) == 0xFE)
        return CODE_UTF16_LE;

    // 检查UTF-16 大端序
    else if (dataSize >= 2 && static_cast<unsigned char>(pData[0]) == 0xFE &&
        static_cast<unsigned char>(pData[1]) == 0xFF)
        return CODE_UTF16_BE;

    // 检查UTF-8（无BOM）
    else {
        int check_sub = 0;

        for (int i = 0; i < dataSize; ++i) {
            if (check_sub == 0) {
                // 跳过ASCII字符
                if ((pData[i] & 0x80) == 0)
                    continue;

                // 确定UTF-8序列长度
                for (const auto& pattern : Utf8NumMap)
                    if ((pData[i] & pattern.mask) == pattern.value) {
                        check_sub = (&pattern - Utf8NumMap) + 1;
                        break;
                    }

                if (check_sub == 0)
                    return CODE_UNKNOWN;
            }
            else {
                // 验证UTF-8后续字节
                if ((pData[i] & 0xC0) != 0x80)
                    return CODE_UNKNOWN;

                --check_sub;
            }
        }
        return CODE_UTF8_NOBOM;
    }
}

// 将UTF-8转换为UTF-16
int UTF8216(LPVOID mp, wchar_t** wp, int size) {
    int l = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<LPCCH>(mp), size, nullptr, 0);
    if (l <= 0) return 0;

    *wp = new wchar_t[l];
    l = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<LPCCH>(mp), size, *wp, l);
    if (l <= 0) {
        delete[] * wp;
        *wp = nullptr;
        return 0;
    }

    return l;
}

// 将小端序转换为大端序
void LE2BE(char* d, int s) {
    if (s < 2) return;

    for (int i = 0; i < s - 1; i += 2) {
        char t = d[i];
        d[i] = d[i + 1];
        d[i + 1] = t;
    }
}

// 将UTF-8转换为当前ANSI代码页
int conUTF8(LPVOID Buffer, LPVOID lpBuffer, int n) {
    wchar_t* sResW = nullptr;
    int res = UTF8216(Buffer, &sResW);
    if (res <= 0) return 0;
    res = WC2MB(CP_ACP, sResW, -1, lpBuffer,n);
    delete[] sResW;
    return res;
}