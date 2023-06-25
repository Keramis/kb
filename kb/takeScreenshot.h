#pragma once
#include "includes.h"
#include <gdiplus.h>

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

void save_ss_as_jpeg(std::wstring filename, HBITMAP hBitMap)
{
	Gdiplus::Bitmap bitmap(hBitMap, NULL);
	CLSID jpegClsid;
    GetEncoderClsid(L"image/jpeg", &jpegClsid);

    bitmap.Save(filename.c_str(), &jpegClsid, NULL);
}

__forceinline void takeScreenshot(std::wstring filename)
{
    Gdiplus::GdiplusStartupInput gdiplusStarupInput;
    ULONG_PTR gdiplustoken;
    Gdiplus::GdiplusStartup(&gdiplustoken, &gdiplusStarupInput, NULL);

	//screen dimensions
	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);

	//create device contet
	HDC hScreenDC = GetDC(NULL);

	//create compatible device
	HDC hMemDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitMap = CreateCompatibleBitmap(hScreenDC, screenW, screenH);

	//select bitmap into mem device obj
	HBITMAP hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);

	//copy screen contents
	BitBlt(hMemDC, 0, 0, screenW, screenH, hScreenDC, 0, 0, SRCCOPY);

    save_ss_as_jpeg(filename, hBitMap); 

    //clean up
    SelectObject(hMemDC, hOldBitMap);
    DeleteObject(hBitMap);
    DeleteDC(hMemDC);
    ReleaseDC(NULL, hScreenDC);
    Gdiplus::GdiplusShutdown(gdiplustoken);
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num = 0; // number of image encoders
    UINT size = 0; // size of the image encoder array in bytes

    // Get the size of the image encoder array
    Gdiplus::GetImageEncodersSize(&num, &size);

    if (size == 0)
    {
        return -1; // No image encoders found
    }

    // Allocate memory for the image encoder array
    Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));

    if (pImageCodecInfo == NULL)
    {
        return -1; // Failed to allocate memory
    }

    // Get the image encoder array
    Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

    // Search for the specified format in the image encoder array
    for (UINT i = 0; i < num; ++i)
    {
        if (wcscmp(pImageCodecInfo[i].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[i].Clsid; // Found the matching encoder
            free(pImageCodecInfo); // Free the allocated memory
            return i; // Return the index of the encoder
        }
    }

    free(pImageCodecInfo); // Free the allocated memory

    return -1; // No matching encoder found
}