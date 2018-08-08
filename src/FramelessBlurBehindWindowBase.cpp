#include "FramelessBlurBehindWindowBase.h"


#include "WinAPIUtils.h"


#include <QtWinExtras>


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------- Default values defines


#define  DEFAULT_BORDER_WIDTH 8


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Utilities defines


#define EXTRACT_X( lp )                        ( ( int )( short ) LOWORD( lp ) )
#define EXTRACT_Y( lp )                        ( ( int )( short ) HIWORD( lp ) )



//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cFramelessBlurBehindWindowBase::~cFramelessBlurBehindWindowBase()
{
}


cFramelessBlurBehindWindowBase::cFramelessBlurBehindWindowBase( QWidget* parent ) :
    tParent(parent),
    mBorderWidth( DEFAULT_BORDER_WIDTH )
{
    setObjectName( "cFramelessBlurBehindWindowBase" );

    // The functions are called in this order, and this is important.
    // otherwise some flags are overriden in an unwanted way and init isn't done properly.
    InitNativeGlass();
    InitNativeFrameless();
 
}


//--------------------------------------------------------------------------------------
//----------- Protected Non-Client OS geometry setup for behaviour override in childrens


int
cFramelessBlurBehindWindowBase::BorderWidth()
{
    return  mBorderWidth;
}


int
cFramelessBlurBehindWindowBase::DefaultBorderWidth()
{
    return  DEFAULT_BORDER_WIDTH;
}


void
cFramelessBlurBehindWindowBase::SetBorderWidth( int iValue )
{
    mBorderWidth = iValue;
}


void
cFramelessBlurBehindWindowBase::ResetBorderWidth()
{
    SetBorderWidth( DefaultBorderWidth() );
}


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Private WinAPI flags setup


void
cFramelessBlurBehindWindowBase::InitNativeGlass()
{
    // Do not set autofill background because it messes up the background erasing,
    // and transparent shapes will be painted over & not erased
    //setAutoFillBackground( true );

    // This flag is important for seeing behing the Qt painting of widgets and actually seeing the blur behind.
    setAttribute( Qt::WA_TranslucentBackground );

    // We enable blur in different ways according to windows version
    // That way all windows versions are covered since windows vista, simple enough.
    eWindowsVersion v = GetWindowsVersion();

    // The simple way with DWM access wrapped by Qt WinExtras for windows vista & 7
    if( v >= eWindowsVersion::kWindowsVista && v < eWindowsVersion::kWindows8 )
        QtWin::enableBlurBehindWindow( this );

    // The hard hacky way with to undocumented windows API, for windows 8 & 10
    if( v >= eWindowsVersion::kWindows8 )
        EnableGlassForWindow8OrGreater( (HWND)winId() );

}


void
cFramelessBlurBehindWindowBase::InitNativeFrameless()
{
    // Drop shadow, this is redundant but not conflicting with windows 8 ( or greater ) way of setting glass.
    QtWin::extendFrameIntoClientArea( this, 1, 1, 1, 1 );

    // Frameless Style, yet with some Custom Flags that enable aero snap behaviour.
    auto framelessStyle = ( WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX );
    ::SetWindowLongPtrW( (HWND)winId(), GWL_STYLE, framelessStyle );
}


//--------------------------------------------------------------------------------------
//------------------------------------------- Protected Non-Client OS behaviour handling


void
cFramelessBlurBehindWindowBase::WM_NCHITTEST_Event_Handler( int iX, int iY, long* oResult )
{
    // Custom Handling of NonClient Event, normally handled by the native Caption.
    // Here we handle native OS resize & move events.
    // This allows us to have custom frame style, yet handle correctly some native
    // events, like window snapping on borders.

    // Security, ensure *oResult = 0 as this will be the return result in case
    // nothing is handled in this function, that means we are in client area and
    // the Non Client Event shouldn't be processed.
    *oResult = 0;

    // Collect rect and size data
    bool resizeHorizontal   = minimumWidth() != maximumWidth();
    bool resizeVertical     = minimumHeight() != maximumHeight();

    // Shape the data to be compatible with windows API stuff.
    const LONG border_width = mBorderWidth;
    RECT winrect;
    GetWindowRect( reinterpret_cast< HWND >( winId() ), &winrect );
    QRect rect( winrect.left, winrect.top, winrect.right - winrect.left, winrect.bottom - winrect.top );

    // Allow resize ?
    if( resizeHorizontal )
    {
        if( NCHitLeftBorder(    rect, border_width, iX, iY) )   *oResult = HTLEFT;
        if( NCHitRightBorder(   rect, border_width, iX, iY) )   *oResult = HTRIGHT;
    }

    if( resizeVertical )
    {
        if( NCHitBottomBorder(   rect, border_width, iX, iY) )  *oResult = HTBOTTOM;
        if( NCHitTopBorder(      rect, border_width, iX, iY) )  *oResult = HTTOP;
    }

    if( resizeHorizontal && resizeVertical )
    {
        if( NCHitBotLeftCorner(  rect, border_width, iX, iY) )  *oResult = HTBOTTOMLEFT;
        if( NCHitBotRightCorner( rect, border_width, iX, iY) )  *oResult = HTBOTTOMRIGHT;
        if( NCHitTopLeftCorner(  rect, border_width, iX, iY) )  *oResult = HTTOPLEFT;
        if( NCHitTopRightCorner( rect, border_width, iX, iY) )  *oResult = HTTOPRIGHT;
    }

    // Allow drag move ?
    // This is reimplemented in children of this class.
    if(*oResult==0)
    {
        if( NCHitCaption( rect, border_width, iX, iY ) )        *oResult = HTCAPTION ;
    }
}


bool
cFramelessBlurBehindWindowBase::NCHitLeftBorder( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  iX >= iRect.left() && iX < iRect.left() + iBorderWidth;
}


bool
cFramelessBlurBehindWindowBase::NCHitRightBorder( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  iX < iRect.right() && iX >= iRect.right() - iBorderWidth;
}


bool
cFramelessBlurBehindWindowBase::NCHitTopBorder( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  iY >= iRect.top() && iY < iRect.top() + iBorderWidth;
}


bool
cFramelessBlurBehindWindowBase::NCHitBottomBorder( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  iY < iRect.bottom()&& iY >= iRect.bottom() - iBorderWidth;
}


bool
cFramelessBlurBehindWindowBase::NCHitTopLeftCorner( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  NCHitTopBorder( iRect, iBorderWidth, iX, iY ) &&
            NCHitLeftBorder( iRect, iBorderWidth, iX, iY );
}


bool
cFramelessBlurBehindWindowBase::NCHitTopRightCorner( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  NCHitTopBorder( iRect, iBorderWidth, iX, iY ) &&
            NCHitRightBorder( iRect, iBorderWidth, iX, iY );
}


bool
cFramelessBlurBehindWindowBase::NCHitBotRightCorner( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  NCHitBottomBorder( iRect, iBorderWidth, iX, iY ) &&
            NCHitRightBorder( iRect, iBorderWidth, iX, iY );
}


bool
cFramelessBlurBehindWindowBase::NCHitBotLeftCorner( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  NCHitBottomBorder( iRect, iBorderWidth, iX, iY ) &&
            NCHitLeftBorder( iRect, iBorderWidth, iX, iY );
}


bool
cFramelessBlurBehindWindowBase::NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Default implementation can be overriden in childs of this class.
    return  true;
}


//--------------------------------------------------------------------------------------
//----------------------------------------- Protected Qt / WinAPI native events override


bool
cFramelessBlurBehindWindowBase::nativeEvent( const  QByteArray&  eventType, void* message, long* result)
{
    // Cast to WINAPI standards
    MSG*    wmsg    = reinterpret_cast< MSG* >( message );
    LPARAM  lparam  = wmsg->lParam;
    WPARAM  wparam  = wmsg->wParam;
    HWND    hwnd    = wmsg->hwnd;
    UINT    msg     = wmsg->message;

    switch( msg )
    {

        case WM_NCCALCSIZE:
        {
            // Abort computing & drawing of the non client area.
            *result = 0;
            return  true; // Return true ( true means do not compute any further ), & Event is handled with result 0 is important.

        }

        case WM_NCHITTEST:
        {
            // Handle non-client area snap resize & drag behaviours & detection
            int x = EXTRACT_X( lparam );
            int y = EXTRACT_Y( lparam );

            // Custom handling delegate
            WM_NCHITTEST_Event_Handler( x, y, result );

            if( *result != 0 )
                return  true; // Return true, event is handled with result set in WM_NCHITTEST_Event_Handler
        }

        default:
        {
            // The case is not handled ? Treat it the normal way & return.
            return  tParent::nativeEvent( eventType, message, result );
        }
    }
}

