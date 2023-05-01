#include "pch.h"

extern "C"
{
    __declspec(dllexport) int __stdcall GetWindowsBuildNumber()
    {
        int buildNumber = -1;
        HMODULE hKernel32 = LoadLibrary(L"kernel32.dll");
        if (hKernel32)
        {
            HRSRC hResource = FindResource(hKernel32, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
            if (hResource)
            {
                HGLOBAL hResourceData = LoadResource(hKernel32, hResource);
                if (hResourceData)
                {
                    void* pData = LockResource(hResourceData);
                    if (pData)
                    {
                        UINT dwLen = 0;
                        VS_FIXEDFILEINFO* pFileInfo = NULL;
                        if (VerQueryValue(pData, L"\\", reinterpret_cast<LPVOID*>(&pFileInfo), &dwLen))
                        {
                            buildNumber = HIWORD(pFileInfo->dwProductVersionLS);
                        }
                    }
                }
            }
            FreeLibrary(hKernel32);
        }
        return buildNumber;
    }
}