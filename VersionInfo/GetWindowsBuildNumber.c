#include <windows.h>

__declspec(dllexport) int __stdcall GetWindowsBuildNumber()
{
    DWORD verHandle = 0;
    DWORD verSize = GetFileVersionInfoSize(TEXT("kernel32.dll"), &verHandle);
    if (verSize > 0)
    {
        LPVOID verData = malloc(verSize);
        if (GetFileVersionInfo(TEXT("kernel32.dll"), verHandle, verSize, verData))
        {
            UINT len = 0;
            VS_FIXEDFILEINFO* verInfo = NULL;
            if (VerQueryValue(verData, TEXT("\\"), (LPVOID*)&verInfo, &len))
            {
                return (verInfo->dwProductVersionMS >> 16) & 0xFFFF;
            }
        }
        free(verData);
    }
    return -1;
}