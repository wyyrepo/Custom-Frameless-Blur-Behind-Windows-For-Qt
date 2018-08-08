#pragma once


#include <windows.h>


// Utility Enum for Windows Versions
enum  eWindowsVersion
{
    kNone = 0,
    kWindowsXP,
    kWindowsXPSP1,
    kWindowsXPSP2,
    kWindowsXPSP3,
    kWindowsVista,
    kWindowsVistaSP1,
    kWindowsVistaSP2,
    kWindows7,
    kWindows7SP1,
    kWindows8,
    kWindows8Point1,
    kWindows10
};


// Public utility Functions related to the Windows API
int                 GetZOrder( HWND iTarget );
eWindowsVersion     GetWindowsVersion();
bool                IsWindowsVersion( eWindowsVersion iWindowsVersion );
bool                EnableGlassForWindow8OrGreater( HWND iWindow );

// Internal Functions related to the Windows API
static HMODULE      _load_sys_library(WCHAR* name);

