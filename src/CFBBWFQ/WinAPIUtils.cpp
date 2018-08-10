#include "WinAPIUtils.h"


#include <cstdlib>
#include <assert.h>

// Windows SDK versions functions
#include <VersionHelpers.h>


namespace  _CFBBWFQ_ext
{


// Mirror Enums & Structs for accessing non-documented windows API
typedef enum {
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_INVALID_STATE = 4,
    _ACCENT_STATE_SIZE = 0xFFFFFFFF
} ACCENT_STATE;


typedef struct {
    ACCENT_STATE accentState;
    int accentFlags;
    int gradientColor;
    int invalidState;
} DWMACCENTPOLICY;


typedef struct _WINCOMPATTR_DATA {
    DWMACCENTPOLICY AccentPolicy;
} WINCOMPATTR_DATA;


typedef struct tagWINCOMPATTR
{
    DWORD attribute; // the attribute to query
    WINCOMPATTR_DATA *pData; // buffer to store the result
    ULONG dataSize; // size of the pData buffer
} WINCOMPATTR;


// Non-documented windows API function & flags for enabling glass windows starting from windows 8
static HRESULT (WINAPI * _pSetWindowCompositionAttribute)(HWND, WINCOMPATTR *) = 0;
static const DWORD _WCA_ACCENT_POLICY = 19;
static const auto _dropShadowFlag = 0x20 | 0x40 | 0x80 | 0x100;


eWindowsVersion
GetWindowsVersion()
{
    eWindowsVersion  ret = kBadValue;
    if( IsWindowsXPOrGreater() )        ret = eWindowsVersion::kWindowsXP;
    if( IsWindowsXPSP1OrGreater() )     ret = eWindowsVersion::kWindowsXPSP1;
    if( IsWindowsXPSP2OrGreater() )     ret = eWindowsVersion::kWindowsXPSP2;
    if( IsWindowsXPSP3OrGreater() )     ret = eWindowsVersion::kWindowsXPSP3;
    if( IsWindowsVistaOrGreater() )     ret = eWindowsVersion::kWindowsVista;
    if( IsWindowsVistaSP1OrGreater() )  ret = eWindowsVersion::kWindowsVistaSP1;
    if( IsWindowsVistaSP2OrGreater() )  ret = eWindowsVersion::kWindowsVistaSP2;
    if( IsWindows7OrGreater() )         ret = eWindowsVersion::kWindows7;
    if( IsWindows7SP1OrGreater() )      ret = eWindowsVersion::kWindows7SP1;
    if( IsWindows8OrGreater() )         ret = eWindowsVersion::kWindows8;
    if( IsWindows8Point1OrGreater() )   ret = eWindowsVersion::kWindows8Point1;
    if( IsWindows10OrGreater() )        ret = eWindowsVersion::kWindows10;
    return  ret;
}


bool
IsWindowsVersion( eWindowsVersion iWindowsVersion )
{
    return  iWindowsVersion == GetWindowsVersion();
}


bool
EnableGlassForWindow8OrGreater( HWND iWindow )
{
    assert( GetWindowsVersion() >= eWindowsVersion::kWindows8 );

    HMODULE user32 = _load_sys_library(L"user32.dll");
    if (user32)
        _pSetWindowCompositionAttribute = (HRESULT(WINAPI*)(HWND, WINCOMPATTR*))GetProcAddress( user32, "SetWindowCompositionAttribute" );
    else
        return  false;  // Fail, function is not available. This undocumented function may have been moved somewhere else.

    DWMACCENTPOLICY policy = { ACCENT_ENABLE_BLURBEHIND , _dropShadowFlag, 0, 0 };
    //DWMACCENTPOLICY policy = { ACCENT_ENABLE_BLURBEHIND , 0, 0, 0 }; // Without drop shadow

    WINCOMPATTR data = { _WCA_ACCENT_POLICY, (WINCOMPATTR_DATA*)&policy, sizeof(WINCOMPATTR_DATA) };
    _pSetWindowCompositionAttribute( iWindow, &data);

    return  true;  // Success

}


static HMODULE
_load_sys_library(WCHAR* name)
{
    WCHAR path[MAX_PATH];
    unsigned int len = GetSystemDirectory( path, MAX_PATH );
    char* str = new  char[MAX_PATH];
    int ret = std::wcstombs( str, path, len+1 );
    str[ret]='\0';

    if ( len && len + wcslen( name ) + 1 < MAX_PATH )
    {
        path[len] = '\\';
        wcscpy ( &path[len + 1], name );
        return  LoadLibrary( path );
    }
    else
    {
        return  0;
    }
}


} // namespace  _CFBBWFQ_ext

